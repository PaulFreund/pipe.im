//======================================================================================================================

#pragma once

//======================================================================================================================

class GatewayPipe : public InstanceClient {
private:
	InstanceConnection* _connection;
	std::map <tstring, InstanceSession*> _sessions;

	std::mutex _mutexQueue;
	std::vector<tstring> _incoming;
	std::vector<tstring> _outgoing;

public:
	static const tstring GatewayPipeFolderName;
	static const tstring GatewayPipeAccountName;

public:
	GatewayPipe();
	~GatewayPipe();

public:
	virtual void addIncoming(const tstring& message);
	virtual std::vector<tstring> getOutgoing();
	virtual void setConnection(InstanceConnection* connection);

	virtual void addOutgoing(const tstring& message);

public:
	virtual void addSession(tstring id, InstanceSession* session);
	virtual void removeSession(tstring id);
};

//======================================================================================================================
