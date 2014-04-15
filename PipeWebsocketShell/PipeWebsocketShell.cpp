//======================================================================================================================

#include <thread>
#include <chrono>
#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <array>
#include <string>
using namespace std;

//======================================================================================================================

#define _TCHAR_DEFINED
#ifdef UNICODE
	#define _T(x) L ##x
	#define TCHAR wchar_t
#else
	#define _T(x) x
	#define TCHAR char
#endif
typedef basic_string<TCHAR> tstring;
typedef unsigned char ubyte;

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
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
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

bool g_Quit = false;
tstring g_AppPath;
LibPipeInstance* g_pPipeInstance = nullptr;

//======================================================================================================================

class PipeWebsocketShellApplication : public Application {
public:
	PipeWebsocketShellApplication(int argc, char* argv[]) : Application(argc, argv) {}
	~PipeWebsocketShellApplication() {}
};

//======================================================================================================================

class PipeRequestHandlerPage : public HTTPRequestHandler {
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		auto uri = request.getURI();
		if(uri == _T("/")) {
			uri = _T("/index.html");
		}

		response.setChunkedTransferEncoding(true);
		std::ostream& responseStream = response.send();

		File requestPath(g_AppPath + _T("static/") + uri);
		cout << _T("File requested: " << requestPath.path()) << endl;
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
				cout << _T("File response: " << requestPath.path()) << endl;
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
			cout << _T("File not found: " << requestPath.path()) << endl;
		}
	}
};

//======================================================================================================================

class PipeRequestHandlerWebSocket : public HTTPRequestHandler {
public:
	void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
		try {
			WebSocket ws(request, response);
			cout << _T("Websocket connection established") << endl;

			ws.setBlocking(false);
			ws.setReceiveTimeout(Poco::Timespan(60*60, 0));

			const int bufferSize = 2048;
			ws.setReceiveBufferSize(bufferSize);

			auto providers = LibPipeInstance::serviceProviders();
			LibPipeInstance pipe(g_AppPath, providers);

			vector<tstring> incoming;
			vector<tstring> outgoing;

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
						cout << _T("Websocket message received: ") << message << endl;
						
						if(message.compare(_T("quit")) == 0) {
							g_Quit = true;
							return;
						}

						StringTokenizer tokens(message, _T(" "), StringTokenizer::TOK_IGNORE_EMPTY);
						if(tokens.count() >= 2) {
							LibPipeMessage pipeMessage;
							pipeMessage.address = tokens[0];
							pipeMessage.type = tokens[1];

							for(auto i = 2; i < tokens.count(); i++) {
								pipeMessage.parameters.push_back(tokens[i]);
							}

							pipe.send({ pipeMessage });
						}
						else {
							outgoing.push_back(_T("Input syntax: <address> <type> [<parameter> ...] OR quit"));
						}
					}

					incoming.clear();
				}

				// Receive from pipe
				auto pipeMessages = pipe.receive();
				for(auto& pipeMessage : pipeMessages) {
					tstring message = pipeMessage.address + _T(" ") + pipeMessage.type;

					for(auto& parameter : pipeMessage.parameters) {
						message.append(_T(" ") + parameter);
					}

					outgoing.push_back(message);
				}

				// Send to client
				if(outgoing.size() > 0) {
					for(auto& message : outgoing) {
						ws.sendFrame(message.data(), message.length());
						cout << _T("Websocket message sent: ") << message << endl;
					}
					outgoing.clear();
				}
			}
			while(bytesRead > 0 || (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);

			cout << _T("Websocket connection closed") << endl;
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

		cout << _T("Websocket connection lost") << endl;
	}
};

//======================================================================================================================

class PipeRequestHandlerFactory : public HTTPRequestHandlerFactory {
public:
		HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) {
			if(request.getURI() == "/ws")
				return new PipeRequestHandlerWebSocket;
			else
				return new PipeRequestHandlerPage;
		}
};

//======================================================================================================================

int main(int argc, char* argv[]) {
	try {
		// Get application path
		PipeWebsocketShellApplication self(argc, argv);
		Path commandPath(self.commandPath());
		g_AppPath = commandPath.parent().toString();

		LibPipeInstance::loadExtensions(g_AppPath);

		// Set up Websocket server
		ServerSocket socket(SocketAddress(_T(""), 9980));
		HTTPServerParams* pParams = new HTTPServerParams();
		pParams->setMaxThreads(100);

		HTTPServer server(new PipeRequestHandlerFactory(), socket, pParams);

		server.start();

		while(!g_Quit) {
			this_thread::sleep_for(chrono::microseconds(1000));
		}

		server.stop();
	}
	catch(exception e) {
		cout << _T("Exception: ") << e.what() << endl;
	}
	
	return 0;
}
