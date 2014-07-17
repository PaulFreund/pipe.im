//======================================================================================================================

#pragma once

//======================================================================================================================

class PipeShell;
class Account;
class InstanceConnection;
class InstanceSession;

//======================================================================================================================

class Account : public InstanceClient {
public:
	static const tstring AccountFileName;

private:
	const tstring _path;
	PipeObjectPtr _config;
	InstanceConnection* _connection;

	std::map <tstring, InstanceSession*> _sessions;

	std::mutex _mutexQueue;
	std::vector<tstring> _incoming;
	std::vector<tstring> _outgoing;

public:
	Account(const tstring& path);
	Account(const tstring& path, const tstring& account_, const tstring& password);
	~Account();

public:
	virtual void addIncoming(const tstring& message);
	virtual std::vector<tstring> getOutgoing();
	virtual void setConnection(InstanceConnection* connection);

	virtual void addOutgoing(const tstring& message);

public:
	virtual void addSession(tstring id, InstanceSession* session);
	virtual void removeSession(tstring id);

public:
	bool authenticate(const tstring& suppliedPassword);
	bool admin();

public:
	tstring getGatewayHandle(const tstring& gateway);
	void setGatewayHandle(const tstring& gateway, const tstring& handle);
	void removeGatewayHandle(const tstring& gateway);

private:
	void createAccount(const tstring& account, const tstring& password);
	bool readConfig();
	void writeConfig();

	const tstring& account();
	const tstring& password();
};

//======================================================================================================================
