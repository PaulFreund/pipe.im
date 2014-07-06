//======================================================================================================================

#pragma once

//======================================================================================================================

class UserInstanceConnection;
class UserInstance {
public:
	static const tstring UserFileName;

private:
	const tstring _path;
	PipeObjectPtr _config;
	UserInstanceConnection* _connection;

public:
	UserInstance(const tstring& path);
	UserInstance(const tstring& path, const tstring& account, const tstring& password);
	~UserInstance();

public:
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
