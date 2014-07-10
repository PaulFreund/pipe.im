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

//======================================================================================================================

class GatewayWebHandlerPage : public Poco::Net::HTTPRequestHandler {
public:
	void generateFileObject(const tstring& path, PipeObject& object, bool first = false);
	void concatFiles(const tstring& path, const tstring& filter, tstring& result);
	bool handleCommands(const tstring& uri, std::ostream& outstream, tstring body);
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

//======================================================================================================================

class GatewayWebHandlerSocket : public Poco::Net::HTTPRequestHandler {
private:
	std::vector<tstring> _incoming;
	std::vector<tstring> _outgoing;

	std::shared_ptr<PipeShell> _shell;
	bool _shellEnabled;

public:
	GatewayWebHandlerSocket(bool shellEnabled = false);
	~GatewayWebHandlerSocket();
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

//======================================================================================================================

class GatewayWebHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
private:
	const tstring _wsToken;
	const tstring _wssToken;
	const size_t _lenWsToken;
	const size_t _lenWssToken;

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

public:
	GatewayWeb();
	~GatewayWeb();

};

// todo: 
// Authentication and registration layer
// Create Administration
// Configuration of bots
// Configuration for account management

// Create account management

//======================================================================================================================

