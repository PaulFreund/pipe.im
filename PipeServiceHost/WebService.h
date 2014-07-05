//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "UserInstanceManager.h"

#include <libpipe/PipeShell.h>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>


//======================================================================================================================

class WebServiceHandlerPage : public Poco::Net::HTTPRequestHandler {
public:
	void generateFileObject(const tstring& path, PipeObject& object, bool first = false);
	void concatFiles(const tstring& path, const tstring& filter, tstring& result);
	bool handleCommands(const tstring& uri, std::ostream& outstream, tstring body);
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

//======================================================================================================================

class WebServiceHandlerSocket : public Poco::Net::HTTPRequestHandler {
private:
	std::vector<tstring> _incoming;
	std::vector<tstring> _outgoing;

	std::shared_ptr<PipeShell> _shell;
	bool _shellEnabled;

public:
	WebServiceHandlerSocket(bool shellEnabled = false);
	~WebServiceHandlerSocket();
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

//======================================================================================================================

class WebServiceHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
private:
	const tstring _wsToken;
	const tstring _wssToken;
	const size_t _lenWsToken;
	const size_t _lenWssToken;

public:
	WebServiceHandlerFactory();
	~WebServiceHandlerFactory();
	
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};

//======================================================================================================================

class WebService {
private:
	std::shared_ptr<Poco::Net::ServerSocket> _socket;
	std::shared_ptr<Poco::Net::HTTPServer> _server;

public:
	WebService();
	~WebService();

};

// todo: 
// Authentication and registration layer
// Create Administration
// Configuration of bots
// Configuration for user management

// Create user management

//======================================================================================================================

