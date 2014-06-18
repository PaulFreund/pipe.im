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
#include <mutex>
using namespace std;

//======================================================================================================================



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

#include <libpipe/PipeShell.h>

//======================================================================================================================

class PipeRequestHandlerPage : public HTTPRequestHandler {
public:
	bool handleCommands(const tstring& uri, std::ostream& outstream, tstring body) {
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
			}
			// Commands without
			else if(parts[1] == _T("send")) {
				tstring err;
				PipeJson message = PipeJson::parse(body, err);
				if(message.is_array())
					LibPipe::send(std::make_shared<PipeArray>(message.array_items()));
				else if(message.is_object()) 
					LibPipe::send(std::make_shared<PipeArray>(PipeArray { message }));

				return true;
			}
			else if(parts[1] == _T("receive")) {
				outstream << PipeJson(*LibPipe::receive()).dump();
				return true;
			}
		}
		catch(...) {}

		return false;
	}

	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		PipeWebsocketTerminalApplication* pApp = reinterpret_cast<PipeWebsocketTerminalApplication*>(&Application::instance());

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

mutex multiClientMutex;
class PipeRequestHandlerWebSocketShell : public HTTPRequestHandler {
public:
	~PipeRequestHandlerWebSocketShell() {
		try { multiClientMutex.unlock(); } catch(...) {}
	}
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		PipeWebsocketTerminalApplication* pApp = reinterpret_cast<PipeWebsocketTerminalApplication*>(&Application::instance());

		try {
			WebSocket ws(request, response);

			if(pApp->_debug) { cout << _T("Websocket connection established") << endl; }

			ws.setBlocking(false);
			ws.setReceiveTimeout(Poco::Timespan(60*60, 0));

			const int bufferSize = 2048;
			ws.setReceiveBufferSize(bufferSize);

			PipeShell shell(_T("terminal"), true);

			vector<tstring> incoming;
			vector<tstring> outgoing;

			char buffer[bufferSize];
			int flags;
			int bytesRead;
			do {
				this_thread::sleep_for(chrono::microseconds(100));

				multiClientMutex.lock();

				// Receive from client
				try {
					bytesRead = ws.receiveFrame(buffer, sizeof(buffer), flags);
					incoming.push_back(tstring(buffer, bytesRead));
				}
				catch(TimeoutException& /*e*/) {} // Not very good but works for the moment

				// Send to pipe
				if(incoming.size() > 0) {
					for(auto& message : incoming) {
						if(message.empty())
							continue;

						if(pApp->_debug) { cout << _T("Websocket message received: ") << message << endl; }

						if(message == _T("debug")) { pApp->_debug = !pApp->_debug; }

						shell.send(message);
					}

					incoming.clear();
				}

				// Receive from pipe
				auto&& received = shell.receive();
				if(!received.empty())
					outgoing.push_back(received);

				// Send to client
				if(outgoing.size() > 0) {
					for(auto& message : outgoing) {
						ws.sendFrame(message.data(), message.length());
						if(pApp->_debug) { cout << _T("Websocket message sent: ") << message << endl; }
					}
					outgoing.clear();
				}

				multiClientMutex.unlock();
			}
			while(bytesRead > 0 || (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);

			if(pApp->_debug) { cout << _T("Websocket connection closed") << endl; }
		}
		catch(WebSocketException& e) {
			try { multiClientMutex.unlock(); } catch(...) {}

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
class PipeRequestHandlerWebSocket : public HTTPRequestHandler {
public:
	~PipeRequestHandlerWebSocket() {
		try { multiClientMutex.unlock(); }
		catch(...) {}
	}
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		PipeWebsocketTerminalApplication* pApp = reinterpret_cast<PipeWebsocketTerminalApplication*>(&Application::instance());

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
				this_thread::sleep_for(chrono::microseconds(100));

				multiClientMutex.lock();

				// Receive from client
				try {
					bytesRead = ws.receiveFrame(buffer, sizeof(buffer), flags);
					incoming.push_back(tstring(buffer, bytesRead));
				}
				catch(TimeoutException& /*e*/) {} // Not very good but works for the moment

				// Send to pipe
				if(incoming.size() > 0) {
					for(auto& message : incoming) {
						if(message.empty())
							continue;

						if(pApp->_debug) { cout << _T("Websocket message received: ") << message << endl; }

						if(message == _T("debug")) { pApp->_debug = !pApp->_debug; }

						LibPipe::send(make_shared<PipeArray>(PipeArray{ message }));
					}

					incoming.clear();
				}

				// Receive from pipe
				auto received = LibPipe::receive();
				if(!received->empty()) {
					for(auto& ele: *received) {
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

				multiClientMutex.unlock();
			}
			while(bytesRead > 0 || (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);

			if(pApp->_debug) { cout << _T("Websocket connection closed") << endl; }
		}
		catch(WebSocketException& e) {
			try { multiClientMutex.unlock(); }
			catch(...) {}

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
				return new PipeRequestHandlerWebSocketShell;
			else if(lenUri >= lenWsToken && uri.compare(lenUri - lenWsToken, lenWsToken, wsToken) == 0)
				return new PipeRequestHandlerWebSocket;
			else
				return new PipeRequestHandlerPage;
		}
};

//======================================================================================================================

PipeWebsocketTerminalApplication::PipeWebsocketTerminalApplication() :_help(false), _debug(false) { setUnixOptions(true); }
PipeWebsocketTerminalApplication::~PipeWebsocketTerminalApplication() {}


void PipeWebsocketTerminalApplication::defineOptions(OptionSet& options) {
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
		waitForTerminationRequest();
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
