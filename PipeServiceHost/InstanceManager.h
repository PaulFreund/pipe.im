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
private:
	const int _retryLimitSend;
	int _retryCountSend;

public:
	InstanceConnection(const Poco::Net::StreamSocket& s);

public:
	void run();
};

//======================================================================================================================

class InstanceSession;
class InstanceClient {
public:
	virtual void addIncoming(const tstring& message) = 0;
	virtual std::vector<tstring> getOutgoing() = 0;
	virtual void setConnection(InstanceConnection* connection) = 0;
	
	virtual void addOutgoing(const tstring& message) = 0;
	
public:
	virtual void addSession(tstring id, InstanceSession* session) = 0;
	virtual void removeSession(tstring id) = 0;
};

//======================================================================================================================

class PipeShell;
class InstanceSession {
private:
	tstring _id;
	std::shared_ptr<InstanceClient> _client;
	const std::function<void(tstring)> _cbClientOutput;

	bool _enableShell;
	std::shared_ptr<PipeShell> _shell;

public:
	InstanceSession(const tstring& id, std::shared_ptr<InstanceClient> client, std::function<void(tstring)> cbClientOutput, bool enableShell = false);
	~InstanceSession();

public:
	const tstring& id() { return _id; }
	void clientInputAdd(const tstring& data);
	void accountIncomingAdd(const tstring& message);
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

