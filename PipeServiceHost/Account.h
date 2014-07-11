//======================================================================================================================

#pragma once

//======================================================================================================================

class PipeShell;
class Account;
class InstanceConnection;

//======================================================================================================================

class AccountSession { // Separated from GatewayWeb session, needs to know the account, needs to be known by the account, will be created by GatewayWeb and GatewayPipe and registered here in account, can be shell or not shell!
private:
	tstring _id;
	std::shared_ptr<Account> _account;
	const std::function<void(tstring)> _cbClientOutput;

	bool _enableShell;
	std::shared_ptr<PipeShell> _shell;

public:
	AccountSession(const tstring& id, std::shared_ptr<Account> account, std::function<void(tstring)> cbClientOutput, bool enableShell = false);
	~AccountSession();

public:
	void clientInputAdd(const tstring& data);
	void accountIncomingAdd(const tstring& message);
};

//======================================================================================================================

class Account : public InstanceClient {
public:
	static const tstring AccountFileName;

private:
	const tstring _path;
	PipeObjectPtr _config;
	InstanceConnection* _connection;

	std::map <tstring, AccountSession*> _sessions;

	std::mutex _mutexQueue;
	std::vector<tstring> _incoming;
	std::vector<tstring> _outgoing;

public:
	Account(const tstring& path);
	Account(const tstring& path, const tstring& account_, const tstring& password);
	~Account();

public:
	void addOutgoing(const tstring& message);

	void addIncoming(const tstring& message);
	std::vector<tstring> getOutgoing();
	void setConnection(InstanceConnection* connection);

public:
	bool authenticate(const tstring& suppliedPassword);

	void addSession(tstring id, AccountSession* session);
	void removeSession(tstring id);

private:
	void createAccount(const tstring& account, const tstring& password);
	bool readConfig();
	void writeConfig();

	const tstring& account();
	const tstring& password();
};

//======================================================================================================================

/*
	* Gatewaydefinitionen statisch in config
		* Host bekommt starre host.json oder so
			* Ip adressen, gateways(bots) etc.
	* Rest API fuer Anmelden, Registrieren, PW Vergessen, Leistungsumfang, User management, Account Management (PW change, contact fuer bots etc)
		* Rest funktionen /rest/login, /rest/register mit POST daten, set-cookie im response header. Session objekt mit beziehung zu User-Object im client storen und bei jedem request mitgeben und aktiv bei websocket als erstes schicken. Evtl. koennte ich session=type oder so schicken fuer plain oder shell oder so :)
		* Bei Web erst auf seite (rest) und session token wird dann ueber websocket als erstes gesendet  zum auth und zur user assoziazion
		* Bei Bots gilt eintragen des controllers und gegenseitiges autorisieren als langzeitanmeldung
*/