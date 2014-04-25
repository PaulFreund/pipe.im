//======================================================================================================================

#include "PipeWebsocketShell.h"

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

using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

//======================================================================================================================

#include <libpipe/LibPipeInstance.h>

//======================================================================================================================

class PipeRequestHandlerPage : public HTTPRequestHandler {
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		PipeWebsocketShellApplication* pApp = reinterpret_cast<PipeWebsocketShellApplication*>(&Application::instance());

		auto uri = request.getURI();
		if(uri.compare(0, pApp->_uripath.length(), pApp->_uripath) == 0)
			uri = uri.substr(pApp->_uripath.length());

		if(uri.length() == 0 || uri == _T("/")) {
			uri = _T("/index.html");
		}

		response.setChunkedTransferEncoding(true);
		std::ostream& responseStream = response.send();

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
			responseStream << _T("<h1>Requested file could not be found</h1>") << endl;
			if(pApp->_debug) { cout << _T("File not found: " << requestPath.path()) << endl; }
		}
	}
};

//======================================================================================================================

class PipeRequestHandlerWebSocket : public HTTPRequestHandler {
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		PipeWebsocketShellApplication* pApp = reinterpret_cast<PipeWebsocketShellApplication*>(&Application::instance());

		try {
			WebSocket ws(request, response);
			if(pApp->_debug) { cout << _T("Websocket connection established") << endl; }

			ws.setBlocking(false);
			ws.setReceiveTimeout(Poco::Timespan(60*60, 0));

			const int bufferSize = 2048;
			ws.setReceiveBufferSize(bufferSize);

			auto&& serviceTypes = LibPipeInstance::serviceTypes();
			LibPipeInstance pipe(pApp->_datadir, serviceTypes);

			vector<tstring> incoming;
			vector<tstring> outgoing;

			tstring serviceTypesMessage = _T("Available services: ");
			//for(PipeJson& serviceType : serviceTypes) { serviceTypesMessage.append(_T(" ") + serviceType.toString()); }
			serviceTypesMessage.append(dumpArray(serviceTypes));
			outgoing.push_back(serviceTypesMessage);

			char buffer[bufferSize];
			int flags;
			int bytesRead;
			do {
				this_thread::sleep_for(chrono::microseconds(100));

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

						pipe.send(newArray({ *PipeJson::parse(message).object_items() }));
					}

					incoming.clear();
				}

				// Receive from pipe
				auto pipeMessages = pipe.receive();
				for(auto& pipeMessage : *pipeMessages) {
					outgoing.push_back(pipeMessage.dump());
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
size_t lenWsToken = wsToken.length();
class PipeRequestHandlerFactory : public HTTPRequestHandlerFactory {
public:
		HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) {

			tstring uri = request.getURI();
			size_t lenUri = uri.length();

			if(lenUri >= lenWsToken && uri.compare(lenUri - lenWsToken, lenWsToken, wsToken) == 0)
				return new PipeRequestHandlerWebSocket;
			else
				return new PipeRequestHandlerPage;
		}
};

//======================================================================================================================

PipeWebsocketShellApplication::PipeWebsocketShellApplication() :_help(false), _debug(false) { setUnixOptions(true); }
PipeWebsocketShellApplication::~PipeWebsocketShellApplication() {}


void PipeWebsocketShellApplication::defineOptions(OptionSet& options) {
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

int PipeWebsocketShellApplication::main(const vector<tstring>& args) {
	try {
		if(_help) {
			HelpFormatter helpFormatter(options());
			helpFormatter.setUnixStyle(true);
			helpFormatter.setCommand(commandName());
			helpFormatter.setUsage("OPTIONS");
			helpFormatter.setHeader("PipeWebsocketShell - Tester");
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

		LibPipeInstance::loadExtensions(_extdir);

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

	return EXIT_OK;
}

void PipeWebsocketShellApplication::displayHelp(const tstring& name, const tstring& value) {
	_help = true;
	stopOptionsProcessing();
}

//======================================================================================================================

int main(int argc, char* argv[]) {
	PipeWebsocketShellApplication self;
	self.run(argc, argv);
	return 0;
}
