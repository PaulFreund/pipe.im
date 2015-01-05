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

