//======================================================================================================================

#pragma once

//======================================================================================================================

class UserInstance {
	const tstring _path;
	PipeObjectPtr _config;

public:
	UserInstance(const tstring& path);
	UserInstance(const tstring& path, const tstring& address, const tstring& password);
	~UserInstance();

private:
	void loadUser();
	void createUser(const tstring& address, const tstring& password);
	bool readConfig();
	void writeConfig();
};

//======================================================================================================================
