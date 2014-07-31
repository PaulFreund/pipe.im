//======================================================================================================================

#include "CommonHeader.h"
#include "GatewayWeb.h"

#include <thread>
#include <memory>

#include <Poco/DirectoryIterator.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/WebSocket.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/HTTPServerRequestImpl.h>


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

bool GatewayWebHandlerPage::handleCommands(const tstring& uri, HTTPServerRequest& request, HTTPServerResponse& response) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	auto parts = texplode(uri, _T('/'));
	if(parts.size() < 2) { return false; }

	if(parts[0] != _T("rest")) { return false; }
	tstring command = parts[1];

	//------------------------------------------------------------------------------------------------------------------
	// Authenticated command
	if(command == _T("authenticated")) {
		tstring accountName = _T("");
		NameValueCollection cookies;
		request.getCookies(cookies);
		if(cookies.has(_T("session"))) {
			accountName = pApp->_gatewayWeb->loggedIn(cookies[_T("session")]);
		}
			
		response.setContentType(_T("text/html"));

		if(!accountName.empty())
			response.send() << _T("true");
		else
			response.send() << _T("false");

		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	// Login command
	else if(command == _T("login")) {
		tstring body = _T("");
		if(request.getMethod() == HTTPServerRequest::HTTP_POST) {
			request.stream() >> body;
		}

		tstring account = _T("");
		tstring password = _T("");
		vector<tstring> fields = texplode(body, _T('&'));
		for(auto& field : fields) {
			vector<tstring> fieldElements = texplode(field, _T('='));
			if(fieldElements.size() == 2 && fieldElements[0] == _T("account"))
				account = HTTPCookie::unescape(fieldElements[1]);

			if(fieldElements.size() == 2 && fieldElements[0] == _T("password"))
				password = HTTPCookie::unescape(fieldElements[1]);
		}

		if(account.empty() || password.empty()) { throw tstring(_T("No login data supplied")); }

		tstring token = pApp->_gatewayWeb->login(account, password);
		if(token.empty()) { throw tstring(_T("Invalid login data")); }

		HTTPCookie cookie(_T("session"), token);
		cookie.setMaxAge(86400);
		cookie.setPath(_T("/"));
		response.addCookie(cookie);
		response.setContentType(_T("text/html"));
		response.send() << _T("Login successfull");
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	// Logout command
	else if(command == _T("logout")) {
		NameValueCollection cookies;
		request.getCookies(cookies);
		if(cookies.has(_T("session"))) {
			pApp->_gatewayWeb->logout(cookies[_T("session")]);

			HTTPCookie cookie(_T("session"), _T("")); 
			cookie.setMaxAge(0); // Deletes the cookie
			cookie.setPath(_T("/"));
			response.addCookie(cookie);
			response.setContentType(_T("text/html"));
			response.send() << _T("Logout successfull");
			return true;
		}
		else {
			throw tstring(_T("Invalid logout data"));
		}
	}

	//------------------------------------------------------------------------------------------------------------------
	// Register command
	else if(command == _T("register")) {
		// TODO
	}

	// TODO:
	/*
		- List user gateway accounts
		- Add user gateway account
		- List gateways
		- Service management
		
		- Rest Pull
		- Rest Push
	*/

	//------------------------------------------------------------------------------------------------------------------
	// Users command
	//if(command == _T("users")) {
	//	if(parts.size() < 4) { throw tstring(_T("Invalid arguments")); }
	//	if(parts[2] == _T("create")) {
	//		vector<tstring> authParts = texplode(parts[3], _T(':'));
	//		if(authParts.size() < 2) { return true; }

	//		pApp->_accountManager->createAccount(authParts[0], authParts[1]);
	//		return true;
	//	}
	//	else if(parts[2] == _T("delete")) {
	//		pApp->_accountManager->deleteAccount(parts[3]);
	//		return true;
	//	}
	//}

	//------------------------------------------------------------------------------------------------------------------
	// Concat command
	else if(command == _T("concat")) {
		if(parts.size() < 3) { throw tstring(_T("Invalid arguments")); }
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
		response.setContentType(_T("application/json"));
		response.send() << result;
		return true;
	}

	//------------------------------------------------------------------------------------------------------------------
	// Files command
	else if(command == _T("files")) {
		PipeObject files;
		generateFileObject(pApp->_staticdir, files, true);
		response.setContentType(_T("application/json"));
		response.send() << PipeJson(files).dump();
		return true;
	}

	return false;
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayWebHandlerPage::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
	response.setChunkedTransferEncoding(true);

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

	// Handle commands
	try {
		if(handleCommands(uri, request, response)) {
			return;
		}
	}
	catch(tstring message) {
		response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
		response.send() << message;
		return;
	}

	// Serve static files
	uri = texplode(uri, _T('?'))[0];
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
			else if(extension == _T("json"))
				contentType = _T("application/json");
			else
				contentType = _T("");

			response.setContentType(contentType);
			std::ifstream fileStream(requestPath.path());
			Poco::StreamCopier::copyStream(fileStream, response.send());
			pApp->logger().information(tstring(_T("[GatewayWebHandlerPage::handleRequest] File response: ")) + requestPath.path());
		}
		catch(exception e) {
			response.setStatus(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
			std::ostream& responseStream = response.send();
			responseStream << _T("<h1>Internal server error</h1>") << endl;
			responseStream << e.what();
			pApp->logger().warning(tstring(_T("[GatewayWebHandlerPage::handleRequest] File serving error: ")) + e.what());

		}
	}
	else {
		response.setContentType("text/html");
		response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
		response.send() << _T("<h1>Requested file could not be found</h1><br />") << uri << endl;
		pApp->logger().warning(tstring(_T("[GatewayWebHandlerPage::handleRequest] File not found: ")) + requestPath.path());
	}
}

//======================================================================================================================

GatewayWebHandlerSocket::GatewayWebHandlerSocket() {}

//----------------------------------------------------------------------------------------------------------------------

GatewayWebHandlerSocket::~GatewayWebHandlerSocket() {}

//----------------------------------------------------------------------------------------------------------------------

void GatewayWebHandlerSocket::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	shared_ptr<InstanceSession> session = shared_ptr<InstanceSession>(nullptr);
	bool associated = false;
	bool closeSession = false;

	try {
		HTTPServerRequestImpl& reqImpl = static_cast<HTTPServerRequestImpl&>(request);
		reqImpl.socket().setBlocking(false);

		WebSocket ws(request, response);

		pApp->logger().information(tstring(_T("[GatewayWebHandlerSocket::handleRequest] Websocket connection established")));

		const int bufferSize = 10240;
		ws.setReceiveBufferSize(bufferSize);
		ws.setBlocking(false);

		char buffer[bufferSize];
		int flags;
		int bytesRead;
		do {
			this_thread::sleep_for(chrono::milliseconds(10));

			// Receive from client
			bytesRead = ws.receiveFrame(buffer, sizeof(buffer), flags);
			if(bytesRead > 0)
				_incoming.push_back(tstring(buffer, bytesRead));

			// Send to pipe
			for(auto& message : _incoming) {
				pApp->logger().information(tstring(_T("[GatewayWebHandlerSocket::handleRequest] Websocket message received")) + message);

				try {
					if(!associated) {
						tstring TokenConnectionGui = _T("connection_gui=");
						tstring TokenConnectionShell = _T("connection_shell=");
						tstring TokenConnectionShellAdmin = _T("connection_shell_admin=");

						bool admin = false;
						bool enableShell = false;
						tstring authToken = _T("");
						if(startsWith(message, TokenConnectionGui)) {
							authToken = message.substr(TokenConnectionGui.length());
						}
						else if(startsWith(message, TokenConnectionShell)) {
							enableShell = true;
							authToken = message.substr(TokenConnectionShell.length());
						}
						else if(startsWith(message, TokenConnectionShellAdmin)) {
							admin = true;
							enableShell = true;
							authToken = message.substr(TokenConnectionShellAdmin.length());
						}

						tstring accountName = pApp->_gatewayWeb->loggedIn(authToken);
						if(accountName.empty()) {
							_outgoing.push_back(_T("invalid_token"));
						}
						else {
							shared_ptr<Account> account = pApp->_accountManager->account(accountName);
							if(account.get() == nullptr) {
								_outgoing.push_back(_T("exit_error")); // TODO: think of something better
								continue;
							}

							if(admin) {
								if(!account->admin()) {
									_outgoing.push_back(_T("no_admin_error")); // TODO: think of something better
									continue;
								}

								session = make_shared<InstanceSession>(authToken, pApp->_gatewayPipe, [&](tstring message) {
									_outgoingMutex.lock();
									_outgoing.push_back(message);
									_outgoingMutex.unlock();
								}, enableShell);

								pApp->_gatewayPipe->addSession(authToken, session.get());
								associated = true;
								continue;
							}

							session = make_shared<InstanceSession>(authToken, account, [&](tstring message) {
								_outgoingMutex.lock();
								_outgoing.push_back(message);
								_outgoingMutex.unlock();
							}, enableShell);

							account->addSession(authToken, session.get());
							associated = true;
						}
					}
					else if(session.get() != nullptr) {
						session->clientInputAdd(message);
					}
				}
				catch(...) {}

			}

			_incoming.clear();


			if(_outgoing.size() > 0) {
				// Send to client
				_outgoingMutex.lock();
				vector<tstring> currentOutgoing = _outgoing; // TOOD: Slow
				_outgoing.clear();
				_outgoingMutex.unlock();

				for(auto& message : currentOutgoing) {
					ws.sendFrame(message.data(), message.length());
					pApp->logger().information(tstring(_T("[GatewayWebHandlerSocket::handleRequest] Websocket message sent")) + message);
				}
			}
		}
		while((bytesRead != 0 && (flags & WebSocket::FRAME_OP_BITMASK) != WebSocket::FRAME_OP_CLOSE) && !closeSession);

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

GatewayWebHandlerFactory::GatewayWebHandlerFactory() {}

//----------------------------------------------------------------------------------------------------------------------

GatewayWebHandlerFactory::~GatewayWebHandlerFactory() {}

//----------------------------------------------------------------------------------------------------------------------

HTTPRequestHandler* GatewayWebHandlerFactory::createRequestHandler(const HTTPServerRequest& request) {
	tstring uri = request.getURI();
	size_t lenUri = uri.length();

	if(request.has(_T("Upgrade")) && request[_T("Upgrade")] == _T("websocket"))
		return new GatewayWebHandlerSocket();
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

//----------------------------------------------------------------------------------------------------------------------

tstring GatewayWeb::login(const tstring& account, const tstring& password) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	auto acc = pApp->_accountManager->account(account);
	if(acc.get() == nullptr) { return _T(""); }

	if(!acc->authenticate(password)) {
		return _T("");
	}

	tstring token = _uuidGenerator.createOne().toString();
	_webSessions[token] = account;
	return token;
}

//----------------------------------------------------------------------------------------------------------------------

void GatewayWeb::logout(const tstring& token) {
	if(_webSessions.count(token) == 1)
		_webSessions.erase(token);
}

//----------------------------------------------------------------------------------------------------------------------

tstring GatewayWeb::loggedIn(const tstring& token) {
	if(_webSessions.count(token) == 1)
		return _webSessions[token];

	return _T("");
}

//======================================================================================================================
