//======================================================================================================================

#pragma once

//======================================================================================================================

class UserInstanceClient {

};

//======================================================================================================================

class UserInstanceClientShell {

};

//======================================================================================================================

class UserInstanceConnection;
class UserInstance {
public:
	static const tstring UserFileName;

private:
	const tstring _path;
	PipeObjectPtr _config;
	UserInstanceConnection* _connection;

	std::vector<tstring> _incoming;
	std::vector<tstring> _outgoing;

public:
	UserInstance(const tstring& path);
	UserInstance(const tstring& path, const tstring& account, const tstring& password);
	~UserInstance();

public:
	void addIncoming(const tstring& message);
	std::vector<tstring> getOutgoing();

	bool authenticate(const tstring& suppliedPassword);
	void setConnection(UserInstanceConnection* connection);

private:
	void loadUser();
	void createUser(const tstring& account, const tstring& password);
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