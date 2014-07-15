//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "InstanceManager.h"

#include <libpipe/PipeShell.h>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/UUID.h>

//======================================================================================================================

class GatewayWebHandlerPage : public Poco::Net::HTTPRequestHandler {
public:
	void generateFileObject(const tstring& path, PipeObject& object, bool first = false);
	void concatFiles(const tstring& path, const tstring& filter, tstring& result);
	bool handleCommands(const tstring& uri, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

//======================================================================================================================

class GatewayWebHandlerSocket : public Poco::Net::HTTPRequestHandler {
private:
	std::mutex _outgoingMutex;
	std::vector<tstring> _incoming;
	std::vector<tstring> _outgoing;

public:
	GatewayWebHandlerSocket();
	~GatewayWebHandlerSocket();
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

//======================================================================================================================

class GatewayWebHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
	GatewayWebHandlerFactory();
	~GatewayWebHandlerFactory();
	
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};

//======================================================================================================================

class GatewayWeb {
private:
	std::shared_ptr<Poco::Net::ServerSocket> _socket;
	std::shared_ptr<Poco::Net::HTTPServer> _server;
	std::map<tstring, tstring> _webSessions;
	Poco::UUIDGenerator _uuidGenerator;


public:
	GatewayWeb();
	~GatewayWeb();

public:
	tstring login(const tstring& account, const tstring& password);
	void logout(const tstring& token);
	tstring loggedIn(const tstring& token);
};

//======================================================================================================================

