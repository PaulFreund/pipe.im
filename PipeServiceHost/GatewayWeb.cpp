//======================================================================================================================

#include "CommonHeader.h"
#include "GatewayWeb.h"

#include <thread>

#include <Poco/DirectoryIterator.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/WebSocket.h>
#include <Poco/Net/NetException.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

//======================================================================================================================

void GatewayWebHandlerPage::generateFileObject(const tstring& path, PipeObject& object, bool first) {
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

//----------------------------------------------------------------------------------------------------------------------

void GatewayWebHandlerPage::concatFiles(const tstring& path, const tstring& filter, tstring& result) {
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

//----------------------------------------------------------------------------------------------------------------------

bool GatewayWebHandlerPage::handleCommands(const tstring& uri, std::ostream& outstream, tstring body) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	auto parts = texplode(uri, _T('/'));
	if(parts.size() < 2) { return false; }

	if(parts[0] != _T("rest")) { return false; }

	try {
		// User commands
		if(parts.size() >= 4) {
			if(parts[1] == _T("users")) {
				if(parts[2] == _T("create")) {
					vector<tstring> authParts = texplode(parts[3], _T(':'));
					if(authParts.size() < 2) { return true; }

					pApp->_instanceManager->createUser(authParts[0], authParts[1]);
					return true;
				}
				else if(parts[2] == _T("delete")) {
					pApp->_instanceManager->deleteUser(parts[3]);
					return true;
				}
			}
		}

		// Commands with parameter
		else if(parts.size() >= 3) {
			if(parts[1] == _T("concat")) {
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
					tstring uriPath = pApp->_webserverPath;
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
		//// Commands without
		//else if(parts[1] == _T("push")) {
		//	tstring err;
		//	PipeJson message = PipeJson::parse(body, err);
		//	PipeArrayPtr outgoing;
		//	if(message.is_array())
		//		outgoing = std::make_shared<PipeArray>(message.array_items());
		//	else if(message.is_object())
		//		outgoing = std::make_shared<PipeArray>(PipeArray { message });
		//	else
		//		return false;

		//	LibPipe::push(outgoing);

		//	return true;
		//}
		//else if(parts[1] == _T("pull")) {
		//	outstream << PipeJson(*LibPipe::pull()).dump();
		//	return true;
		//}
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

//----------------------------------------------------------------------------------------------------------------------

void GatewayWebHandlerPage::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	auto uri = request.getURI();
	auto uriPath = pApp->_webserverPath;
	if(uriPath[uriPath.size() - 1] != _T('/'))
		uriPath += _T("/");

	if(uri.compare(0, uriPath.length(), uriPath) == 0)
		uri = uri.substr(uriPath.length() - 1);

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
	pApp->logger().information(tstring(_T("[GatewayWebHandlerPage::handleRequest] File requested: ")) + requestPath.path());
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
			pApp->logger().information(tstring(_T("[GatewayWebHandlerPage::handleRequest] File response: ")) + requestPath.path());
		}
		catch(exception e) {
			responseStream << _T("<h1>Internal server error</h1>") << endl;
			responseStream << e.what();
			response.setStatus(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
			pApp->logger().warning(tstring(_T("[GatewayWebHandlerPage::handleRequest] File serving error: ")) + e.what());

		}

		response.setStatus(HTTPResponse::HTTP_OK);
	}
	else {
		response.setContentType("text/html");
		response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
		responseStream << _T("<h1>Requested file could not be found</h1><br />") << uri << endl;
		pApp->logger().warning(tstring(_T("[GatewayWebHandlerPage::handleRequest] File not found: ")) + requestPath.path());
	}
}

//======================================================================================================================

GatewayWebHandlerSocket::GatewayWebHandlerSocket(bool shellEnabled)
	: _shellEnabled(shellEnabled) 
{
	_shell = make_shared<PipeShell>(
		_T("terminal"),
		[&](tstring text) {
			_outgoing.push_back(text);
		},
		[](PipeJson msg) {
			// LibPipe::push(std::make_shared<PipeArray>(PipeArray { msg })); // TODO
		},
		true
	);
}

//----------------------------------------------------------------------------------------------------------------------

GatewayWebHandlerSocket::~GatewayWebHandlerSocket() {}

//----------------------------------------------------------------------------------------------------------------------

void GatewayWebHandlerSocket::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	try {
		WebSocket ws(request, response);

		pApp->logger().information(tstring(_T("[GatewayWebHandlerSocket::handleRequest] Websocket connection established")));

		ws.setBlocking(false);
		ws.setReceiveTimeout(Poco::Timespan(60 * 60, 0));

		const int bufferSize = 10240;
		ws.setReceiveBufferSize(bufferSize);

		char buffer[bufferSize];
		int flags;
		int bytesRead;
		do {
			this_thread::sleep_for(chrono::milliseconds(10));

			// Receive from client
			try {
				bytesRead = ws.receiveFrame(buffer, sizeof(buffer), flags);
				_incoming.push_back(tstring(buffer, bytesRead));
			}
			catch(TimeoutException& ) {} // Not very good but works for the moment

			// Send to pipe
			if(_incoming.size() > 0) {
				for(auto& message : _incoming) {
					if(message.empty()) { continue; }
					pApp->logger().information(tstring(_T("[GatewayWebHandlerSocket::handleRequest] Websocket message received")) + message);

					try {
						if(_shellEnabled)
							_shell->inputText(message);
						else if(!message.empty())
							LibPipe::push(std::make_shared<PipeArray>(PipeArray { message }));
					}
					catch(...) {}
				}

				_incoming.clear();
			}

			// Receive from pipe
			auto received = LibPipe::pull();
			if(_shellEnabled) {
				_shell->inputMessages(received);
			}
			else {
				for(auto& ele : *received) {
					_outgoing.push_back(ele.dump());
				}
			}

			// Send to client
			if(_outgoing.size() > 0) {
				for(auto& message : _outgoing) {
					ws.sendFrame(message.data(), message.length());
					pApp->logger().information(tstring(_T("[GatewayWebHandlerSocket::handleRequest] Websocket message sent")) + message);
				}
				_outgoing.clear();
			}
		}
		while(bytesRead > 0 || (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE);

		pApp->logger().information(tstring(_T("[GatewayWebHandlerSocket::handleRequest] Websocket connection closed")));

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
		pApp->logger().warning(tstring(_T("[GatewayWebHandlerSocket::handleRequest] Websocket error: ")) + e.displayText());

	}

	pApp->logger().information(tstring(_T("[GatewayWebHandlerSocket::handleRequest] Websocket connection lost")));
}

//======================================================================================================================

GatewayWebHandlerFactory::GatewayWebHandlerFactory()
	: _wsToken(_T("/ws"))
	, _wssToken(_T("/wss"))
	, _lenWsToken(_wsToken.length())
	, _lenWssToken(_wssToken.length()) 
{}

//----------------------------------------------------------------------------------------------------------------------

GatewayWebHandlerFactory::~GatewayWebHandlerFactory() {}

//----------------------------------------------------------------------------------------------------------------------

HTTPRequestHandler* GatewayWebHandlerFactory::createRequestHandler(const HTTPServerRequest& request) {
	tstring uri = request.getURI();
	size_t lenUri = uri.length();

	if(lenUri >= _lenWssToken && uri.compare(lenUri - _lenWssToken, _lenWssToken, _wssToken) == 0)
		return new GatewayWebHandlerSocket(true);
	else if(lenUri >= _lenWsToken && uri.compare(lenUri - _lenWsToken, _lenWsToken, _wsToken) == 0)
		return new GatewayWebHandlerSocket(false);
	else
		return new GatewayWebHandlerPage;
}

//======================================================================================================================

GatewayWeb::GatewayWeb() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	_socket = make_shared<ServerSocket>(SocketAddress(pApp->_webserverAddress, pApp->_webserverPort));

	HTTPServerParams* pParams = new HTTPServerParams();
	pParams->setMaxThreads(1000);

	_server = make_shared<HTTPServer>(new GatewayWebHandlerFactory(), *_socket, pParams);

	_server->start();
}

//----------------------------------------------------------------------------------------------------------------------

GatewayWeb::~GatewayWeb() {
	_server->stop();
}

//======================================================================================================================
