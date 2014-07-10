//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>

//======================================================================================================================

class InstanceConnection : public Poco::Net::TCPServerConnection {
public:
	InstanceConnection(const Poco::Net::StreamSocket& s);

public:
	void run();
};

//======================================================================================================================

class InstanceClient {
public:
	virtual void addIncoming(const tstring& message) = 0;
	virtual std::vector<tstring> getOutgoing() = 0;
	virtual void setConnection(InstanceConnection* connection) = 0;
};

//======================================================================================================================

class InstanceManager {
private:
	std::shared_ptr<Poco::Net::ServerSocket> _socket;
	std::shared_ptr<Poco::Net::TCPServer> _server;
	std::map<tstring, InstanceConnection*> _instances;

public:
	InstanceManager();
	~InstanceManager();

public:
	InstanceConnection* instance(const tstring& name);
	void addInstance(const tstring& name, InstanceConnection* instance);
	void removeInstance(const tstring& name);

	static void spawnInstance(const tstring& name, const tstring& path);
};

//======================================================================================================================

