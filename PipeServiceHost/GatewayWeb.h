//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
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
	bool handleCommands(const tstring& uri, Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
};

//======================================================================================================================

class GatewayWebHandlerSocket : public Poco::Net::HTTPRequestHandler {
private:
	std::mutex _outgoingMutex;
	std::vector<tstring> _incoming;
	std::vector<tstring> _outgoing;

	const int _retryLimitSend;
	int _retryCountSend;

public:
	GatewayWebHandlerSocket();
	~GatewayWebHandlerSocket();
	void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

	void pushOutgoing(const tstring& message) {
		_outgoingMutex.lock();
		_outgoing.push_back(message);
		_outgoingMutex.unlock();
	}

	void popOutgoing() {
		_outgoingMutex.lock();
		_outgoing.erase(_outgoing.begin());
		_outgoingMutex.unlock();
	}
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

public:
	GatewayWeb();
	~GatewayWeb();

public:
	tstring login(const tstring& account, const tstring& password);
	void logout(const tstring& token);
	tstring loggedIn(const tstring& token);
};

//======================================================================================================================

