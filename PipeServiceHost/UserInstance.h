//======================================================================================================================

#pragma once

//======================================================================================================================

class UserInstance {
public:
	static const tstring UserFileName;

private:
	const tstring _path;
	PipeObjectPtr _config;

public:
	UserInstance(const tstring& path);
	UserInstance(const tstring& path, const tstring& address, const tstring& password);
	~UserInstance();

public:
	bool authenticate(const tstring& password);

private:
	void loadUser();
	void createUser(const tstring& address, const tstring& password);
	bool readConfig();
	void writeConfig();
};

//======================================================================================================================
