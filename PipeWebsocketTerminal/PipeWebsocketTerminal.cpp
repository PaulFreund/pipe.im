//======================================================================================================================

#include "PipeWebsocketTerminal.h"

#include <thread>
#include <chrono>
#include <algorithm>
#include <exception>
#include <numeric>
#include <fstream>
#include <iostream>
#include <map>
#include <array>
using namespace std;

//======================================================================================================================

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/HelpFormatter.h"
#include <Poco/DirectoryIterator.h>
#include <Poco/String.h>
#include <Poco/Timespan.h>
#include <Poco/StreamCopier.h>
#include <Poco/StringTokenizer.h>
#include <Poco/Format.h>
#include <Poco/ErrorHandler.h>

using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

//======================================================================================================================

bool checkAuth(PipeWebsocketTerminalApplication* pApp, HTTPServerRequest& request, HTTPServerResponse& response) {
	if(pApp->_authToken.empty()) { return true; } // Does not require authentication

	// Get authentication
	if(request.hasCredentials()) {
		try {
			tstring scheme = _T("");
			tstring authInfo = _T("");
			request.getCredentials(scheme, authInfo);
			if(authInfo == pApp->_authToken) { return true; }
		}
		catch(NotAuthenticatedException e) {}
	}

	// No valid authentication, request it
	response.setStatus(HTTPResponse::HTTP_UNAUTHORIZED);
	response.requireAuthentication(_T("Authentication required"));
	response.send();
	return false;
}

class PipeRequestHandlerPage : public HTTPRequestHandler {
public:
	void generateFileObject(const tstring& path, PipeObject& object, bool first = false) {
		File currentPath(path);
		if(!currentPath.exists() || !currentPath.canRead()) { return; }
		Path currentPathName(path);

		if(currentPath.isDirectory()) {
			object[_T("name")] = first ? _T("") : currentPathName.getFileName();
			object[_T("files")] = PipeArray();
			object[_T("folders")] = PipeArray();

			for(DirectoryIterator it(currentPath), itEnd; it != itEnd; ++it) {
				File elementPath(it->path());
				if(!elementPath.exists() || !elementPath.canRead()) { continue; }
				if(elementPath.isDirectory()) {
					object[_T("folders")].array_items().push_back(PipeObject());
					generateFileObject(it->path(), object[_T("folders")].array_items().back().object_items());
				}
				else {
					Path elementPathName(it->path());
					object[_T("files")].array_items().push_back(elementPathName.getFileName());
				}
			}
		}
	}

	void concatFiles(const tstring& path, const tstring& filter, tstring& result) {
		File currentPath(path);
		if(!currentPath.exists() || !currentPath.canRead()) { return; }

		if(currentPath.isDirectory()) {
			for(DirectoryIterator it(currentPath), itEnd; it != itEnd; ++it) {
				concatFiles(it->path(), filter, result);
			}
		}
		else {
			Path currentPathName(path);
			if(filter.empty() || currentPathName.getExtension() == filter) {
				try {
					ifstream fileReader(path);
					tstring fileData((istreambuf_iterator<TCHAR>(fileReader)), istreambuf_iterator<TCHAR>());

					result += _T("\n");
					result += _T("\n");
					result += _T("//======================================================================================================================\n");
					result += _T("// ") + currentPathName.getFileName() + _T(" (") + path + _T(")\n");
					result += _T("//======================================================================================================================\n");
					result += _T("\n");
					result += fileData + _T("\n");
					result += _T("\n");
					result += _T("\n");
				}
				catch(...) {}
			}
		}
	}

	bool handleCommands(const tstring& uri, std::ostream& outstream, tstring body) {
		PipeWebsocketTerminalApplication* pApp = reinterpret_cast<PipeWebsocketTerminalApplication*>(&Application::instance());
		auto parts = texplode(uri, _T('/'));
		if(parts.size() < 2) { return false; }

		if(parts[0] != _T("rest")) { return false; }

		try {
			// Commands with parameter
			if(parts.size() >= 3) {
				if(parts[1] == _T("nodeChildren")) {
					outstream << PipeJson(*LibPipe::nodeChildren(parts[2])).dump();
					return true;
				}
				else if(parts[1] == _T("nodeCommandTypes")) {
					outstream << PipeJson(*LibPipe::nodeCommandTypes(parts[2])).dump();
					return true;
				}
				else if(parts[1] == _T("nodeMessageTypes")) {
					outstream << PipeJson(*LibPipe::nodeMessageTypes(parts[2])).dump();
					return true;
				}
				else if(parts[1] == _T("nodeInfo")) {
					outstream << PipeJson(*LibPipe::nodeInfo(parts[2])).dump();
					return true;
				}
				else if(parts[1] == _T("concat")) {
					auto partsCopy = parts;
					partsCopy.erase(begin(partsCopy)); // Remove "rest"
					partsCopy.erase(begin(partsCopy)); // Remove "concat"
					
					tstring path = pApp->_staticdir;
					tstring filter = _T("");
					auto parameter = texplode(timplode(partsCopy, _T('/')), _T('.'));
					if(parameter.size() >= 1) { 
						filter = parameter[parameter.size() - 1]; 
					}
					if(parameter.size() >= 2) {
						path += Path::separator();
						tstring uriPath = pApp->_uripath;
						tstring subPath = _T("/") + parameter[0];

						if(uriPath[uriPath.size() - 1] != _T('/'))
							uriPath += _T("/");

						if(subPath.compare(0, uriPath.length(), uriPath) == 0)
							subPath = subPath.substr(uriPath.length() - 1);

						path += subPath;
					}

					tstring result = _T("");
					concatFiles(path, filter, result);
					outstream << result;
					return true;
				}
			}
			// Commands without
			else if(parts[1] == _T("push")) {
				tstring err;
				PipeJson message = PipeJson::parse(body, err);
				PipeArrayPtr outgoing;
				if(message.is_array())
					outgoing = std::make_shared<PipeArray>(message.array_items());
				else if(message.is_object())
					outgoing = std::make_shared<PipeArray>(PipeArray { message });
				else
					return false;

				pApp->_pipeMutex.lock();
				pApp->_pipeOutgoing->insert(end(*pApp->_pipeOutgoing), begin(*outgoing), end(*outgoing));
				pApp->_pipeMutex.unlock();

				return true;
			}
			else if(parts[1] == _T("pull")) {
				pApp->_pipeMutex.lock();
				outstream << PipeJson(*pApp->_pipeIncoming).dump();
				pApp->_pipeIncoming->clear();
				pApp->_pipeMutex.unlock();
				return true;
			}
			else if(parts[1] == _T("files")) {
				PipeObject files;
				generateFileObject(pApp->_staticdir, files, true);
				outstream << PipeJson(files).dump();
				return true;
			}
		}
		catch(...) {}

		return false;
	}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		PipeWebsocketTerminalApplication* pApp = reinterpret_cast<PipeWebsocketTerminalApplication*>(&Application::instance());
		if(!checkAuth(pApp, request, response))
			return;

		auto uri = request.getURI();
		auto uriPath = pApp->_uripath;
		if(uriPath[uriPath.size() - 1] != _T('/'))
			uriPath += _T("/");

		if(uri.compare(0, uriPath.length(), uriPath) == 0)
			uri = uri.substr(uriPath.length()-1);

		if(uri.length() == 0 || uri == _T("/")) {
			uri = _T("/index.html");
		}

		response.setChunkedTransferEncoding(true);
		std::ostream& responseStream = response.send();

		// Get body if any
		tstring body = _T("");
		if(request.getMethod() == HTTPServerRequest::HTTP_POST) {
			request.stream() >> body;
		}

		// Handle commands
		if(handleCommands(uri, responseStream, body)) {
			if(body.empty()) { response.setContentType(_T("application/json")); }
			response.setStatus(HTTPResponse::HTTP_OK);
			return;
		}

		File requestPath(pApp->_staticdir + uri);
		if(pApp->_debug) { cout << _T("File requested: " << requestPath.path()) << endl; }
		if(requestPath.exists() && requestPath.canRead()) {
			auto extension = Path(requestPath.path()).getExtension();
			try {
				tstring contentType;
				if(extension == _T("html") || extension == _T("htm"))
					contentType = _T("text/html");
				else if(extension == _T("js"))
					contentType = _T("text/javascript");
				else if(extension == _T("css"))
					contentType = _T("text/css");
				else
					throw _T("File type unknown");

				response.setContentType(contentType);
				std::ifstream fileStream(requestPath.path());
				Poco::StreamCopier::copyStream(fileStream, responseStream);
				if(pApp->_debug) { cout << _T("File response: " << requestPath.path()) << endl; }
			}
			catch(exception e) {
				responseStream << _T("<h1>Internal server error</h1>") << endl;
				responseStream << e.what();
				response.setStatus(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
				cout << _T("File serving error: " << e.what()) << endl;
			}

			response.setStatus(HTTPResponse::HTTP_OK);
		}
		else {
			response.setContentType("text/html");
			response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
			responseStream << _T("<h1>Requested file could not be found</h1><br />") << uri << endl;
			if(pApp->_debug) { cout << _T("File not found: " << requestPath.path()) << endl; }
		}
	}
};

//======================================================================================================================

class PipeRequestHandlerWebSocket : public HTTPRequestHandler {
private:
	bool _acquiredLock;
	bool _shellEnabled;
	PipeShell _shell;

public:
	PipeRequestHandlerWebSocket(bool shellEnabled = false) 
		: _acquiredLock(false)
		, _shellEnabled(shellEnabled) 
		, _shell(_T("terminal"), true)
	{
	}

	~PipeRequestHandlerWebSocket() {
		if(_acquiredLock) {
			PipeWebsocketTerminalApplication* pApp = reinterpret_cast<PipeWebsocketTerminalApplication*>(&Application::instance());
			try { pApp->_pipeMutex.unlock(); }
			catch(...) {}
		}
	}
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		PipeWebsocketTerminalApplication* pApp = reinterpret_cast<PipeWebsocketTerminalApplication*>(&Application::instance());

		if(!checkAuth(pApp, request, response))
			return;

		try {
			WebSocket ws(request, response);

			if(pApp->_debug) { cout << _T("Websocket connection established") << endl; }

			ws.setBlocking(false);
			ws.setReceiveTimeout(Poco::Timespan(60 * 60, 0));

			const int bufferSize = 2048;
			ws.setReceiveBufferSize(bufferSize);

			vector<tstring> incoming;
			vector<tstring> outgoing;

			char buffer[bufferSize];
			int flags;
			int bytesRead;
			do {
				this_thread::sleep_for(chrono::milliseconds(10));

				// Receive from client
				try {
					bytesRead = ws.receiveFrame(buffer, sizeof(buffer), flags);
					incoming.push_back(tstring(buffer, bytesRead));
				}
				catch(TimeoutException& /*e*/) {} // Not very good but works for the moment

				// Send to pipe
				if(incoming.size() > 0) {
					for(auto& message : incoming) {


						if(pApp->_debug) { cout << _T("Websocket message received: ") << message << endl; }

						if(message == _T("debug")) { pApp->_debug = !pApp->_debug; }

						pApp->_pipeMutex.lock();
						_acquiredLock = true;
						try {
							if(_shellEnabled) {
								if(_shell.addOutgoing(message)) {
									pApp->_pipeOutgoing->push_back(_shell.getOutgoing());
								}
							}
							else if(!message.empty()) {
								pApp->_pipeOutgoing->push_back(message);
							}
						}
						catch(...) {}
						_acquiredLock = false;
						pApp->_pipeMutex.unlock();

					}

					incoming.clear();
				}

				// Receive from pipe
				pApp->_pipeMutex.lock();
				_acquiredLock = true;

				auto received = std::move(pApp->_pipeIncoming);
				pApp->_pipeIncoming = newArray();

				_acquiredLock = false;
				pApp->_pipeMutex.unlock();

				if(_shellEnabled) {
					auto&& result = _shell.addIncoming(received);
					if(!result.empty())
						outgoing.push_back(result);
				}
				else {
					for(auto& ele : *received) {
						outgoing.push_back(ele.dump());
					}
				}

				// Send to client
				if(outgoing.size() > 0) {
					for(auto& message : outgoing) {
						ws.sendFrame(message.data(), message.length());
						if(pApp->_debug) { cout << _T("Websocket message sent: ") << message << endl; }
					}
					outgoing.clear();
				}
			}
			while(bytesRead > 0 || (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);

			if(pApp->_debug) { cout << _T("Websocket connection closed") << endl; }
		}
		catch(WebSocketException& e) {
			if(_acquiredLock) {
				try { pApp->_pipeMutex.unlock(); }
				catch(...) {}
			}

			switch(e.code()) {
				case WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
					response.set("Sec-WebSocket-Version", WebSocket::WEBSOCKET_VERSION);
				case WebSocket::WS_ERR_NO_HANDSHAKE:
				case WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
				case WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
					response.setStatusAndReason(HTTPResponse::HTTP_BAD_REQUEST);
					response.setContentLength(0);
					response.send();
					break;
			}
			cout << _T("Websocket error: " << e.displayText()) << endl;
		}

		if(pApp->_debug) { cout << _T("Websocket connection lost") << endl; }
	}
};

//======================================================================================================================
tstring wsToken = _T("/ws");
tstring wssToken = _T("/wss");
size_t lenWsToken = wsToken.length();
size_t lenWssToken = wssToken.length();
class PipeRequestHandlerFactory : public HTTPRequestHandlerFactory {
public:
		HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) {
			
			tstring uri = request.getURI();
			size_t lenUri = uri.length();

			if(lenUri >= lenWssToken && uri.compare(lenUri - lenWssToken, lenWssToken, wssToken) == 0)
				return new PipeRequestHandlerWebSocket(true);
			else if(lenUri >= lenWsToken && uri.compare(lenUri - lenWsToken, lenWsToken, wsToken) == 0)
				return new PipeRequestHandlerWebSocket(false);
			else
				return new PipeRequestHandlerPage;
		}
};

//======================================================================================================================

PipeWebsocketTerminalApplication::PipeWebsocketTerminalApplication()
	: _help(false)
	, _debug(false)
	, _pipeIncoming(newArray())
	, _pipeOutgoing(newArray())
	{
		setUnixOptions(true); 
	}

PipeWebsocketTerminalApplication::~PipeWebsocketTerminalApplication() {}


void PipeWebsocketTerminalApplication::defineOptions(OptionSet& options) {
	options.addOption(
		Option(_T("help"), _T("h"), _T("Display help"))
		.required(false)
		.repeatable(false)
		.callback(OptionCallback<PipeWebsocketTerminalApplication>(this, &PipeWebsocketTerminalApplication::displayHelp))
		);
	options.addOption(
		Option(_T("extdir"), _T("e"), _T("Path to folder where extensions are located"))
		.required(false)
		.repeatable(false)
		.binding(_T("extdir"))
		.argument(_T("[extdir]"))
		);
	options.addOption(
		Option(_T("datadir"), _T("d"), _T("Path to folder where user data will be located"))
		.required(false)
		.repeatable(false)
		.binding(_T("datadir"))
		.argument(_T("[datadir]"))
		);
	options.addOption(
		Option(_T("staticdir"), _T("s"), _T("Path to folder where web files are located"))
		.required(false)
		.repeatable(false)
		.binding(_T("staticdir"))
		.argument(_T("[staticdir]"))
		);
	options.addOption(
		Option(_T("port"), _T("p"), _T("Port on which application will listen"))
		.required(false)
		.repeatable(false)
		.binding(_T("port"))
		.argument(_T("[port]"))
		);
	options.addOption(
		Option(_T("address"), _T("a"), _T("Address to bind"))
		.required(false)
		.repeatable(false)
		.binding(_T("address"))
		.argument(_T("[address]"))
		);
	options.addOption(
		Option(_T("uripath"), _T("u"), _T("Subpath where application will be served"))
		.required(false)
		.repeatable(false)
		.binding(_T("uripath"))
		.argument(_T("[uripath]"))
		);
	options.addOption(
		Option(_T("authtoken"), _T("t"), _T("Authentication information in CRYPT form"))
		.required(false)
		.repeatable(false)
		.binding(_T("authtoken"))
		.argument(_T("[authtoken]"))
		);
}

class PipeWebsocketTerminalErrorHandler : public ErrorHandler {
public:
	PipeWebsocketTerminalErrorHandler() : ErrorHandler() {}

	virtual void exception(const Exception& exc) { cout << _T("[POCO ERROR] ") << exc.message() << endl; }
	virtual void exception(const std::exception& exc) { cout << _T("[POCO ERROR] ") << exc.what() << endl; }
	virtual void exception() { cout << _T("[POCO ERROR] Unknown") << endl; }
};

int PipeWebsocketTerminalApplication::main(const vector<tstring>& args) {
	ErrorHandler* origHandler = ErrorHandler::get();
	ErrorHandler* newHandler = new PipeWebsocketTerminalErrorHandler();
	ErrorHandler::set(newHandler);

	try {
		if(_help) {
			HelpFormatter helpFormatter(options());
			helpFormatter.setUnixStyle(true);
			helpFormatter.setCommand(commandName());
			helpFormatter.setUsage("OPTIONS");
			helpFormatter.setHeader("PipeWebsocketTerminal - Tester");
			helpFormatter.format(cout);
			return Application::EXIT_OK;
		}

		_appPath = Path(commandPath()).parent().toString();
		_extdir = config().getString(_T("extdir"), _appPath);
		_datadir = config().getString(_T("datadir"), _appPath + _T("Data"));
		_staticdir = config().getString(_T("staticdir"), _appPath + _T("static"));
		_port = config().getInt(_T("port"), 9980);
		_address = config().getString(_T("address"), _T("127.0.0.1"));
		_uripath = config().getString(_T("uripath"), _T(""));
		_authToken = config().getString(_T("authtoken"), _T("d29vazpkb2JiaWU1OTUw"));
		if(_uripath[0] != _T('/'))
			_uripath = _T("/") + _uripath;

		LibPipe::setErrorCallback([](tstring error) {
			cout << _T("[LIBPIPE ERROR]") << error << endl;
		});

		LibPipe::setPath(_datadir);
		LibPipe::loadExtensions(_extdir);
		auto&& serviceTypes = LibPipe::serviceTypes();
		LibPipe::init(serviceTypes);

		// Set up Websocket server
		ServerSocket socket(SocketAddress(_address, _port));
		HTTPServerParams* pParams = new HTTPServerParams();
		pParams->setMaxThreads(100);
		
		HTTPServer server(new PipeRequestHandlerFactory(), socket, pParams);

		server.start();

		while(true) {
			this_thread::sleep_for(chrono::milliseconds(10));

			_pipeMutex.lock();
			{
				// Receive
				PipeArrayPtr incoming = LibPipe::pull();
				_pipeIncoming->insert(end(*_pipeIncoming), begin(*incoming), end(*incoming));

				// Send
				LibPipe::push(_pipeOutgoing);
				_pipeOutgoing->clear();
			}
			_pipeMutex.unlock();
		}

		server.stop();
	}
	catch(exception e) {
		cout << _T("Exception: ") << e.what() << endl;
	}

	ErrorHandler::set(origHandler);
	delete newHandler;

	return EXIT_OK;
}

void PipeWebsocketTerminalApplication::displayHelp(const tstring& name, const tstring& value) {
	_help = true;
	stopOptionsProcessing();
}

//======================================================================================================================

int main(int argc, char* argv[]) {
	PipeWebsocketTerminalApplication self;
	self.run(argc, argv);
	return 0;
}
