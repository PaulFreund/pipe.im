//======================================================================================================================

#pragma once

//======================================================================================================================

class GatewayPipe : public InstanceClient {
private:
	InstanceConnection* _connection;
	std::map <tstring, InstanceSession*> _sessions;

	std::mutex _mutexQueue;
	std::vector<tstring> _outgoing;

	std::map<tstring, tstring> _gateways;
	std::map < tstring, std::map < tstring, std::shared_ptr < InstanceSession > > > _accountSessions;

public:
	static const tstring GatewayPipeFolderName;
	static const tstring GatewayPipeAccountName;
	static const tstring GatewayAddressIdentifier;
	
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

public:
	const std::map<tstring, tstring>& gateways();

private:
	void addGateway(const tstring& name, const tstring& description);
	void removeGateway(const tstring& name);
};

//======================================================================================================================
