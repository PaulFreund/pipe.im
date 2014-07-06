//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "UserInstance.h"

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/TCPServerConnection.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/ServerSocket.h>


//======================================================================================================================

class UserInstanceConnection : public Poco::Net::TCPServerConnection {
public:
	UserInstanceConnection(const Poco::Net::StreamSocket& s);

public:
	void run();
};

//======================================================================================================================

class UserInstanceManager {
private:
	tstring _usersDataPath;
	const tstring _usersFolderName;
	const tstring _userFileName;
	std::shared_ptr<Poco::Net::ServerSocket> _socket;
	std::shared_ptr<Poco::Net::TCPServer> _server;

private:
	std::map<tstring, std::shared_ptr<UserInstance>> _instances;

public:
	UserInstanceManager();
	~UserInstanceManager();

public:
	void loadUsers();
	void createUser(const tstring& address, const tstring& password);
	void deleteUser(const tstring& address);

private:
	bool prepareUsersDataPath();

	// TODO:
	/*
		* Configuration management (loading, saving etc)
		* Instantiating of PipeServiceInstances
		* Managing between WebService and Instances
		* Own service for Host with bots
		* Where should the shell live?		
	*/

};

//======================================================================================================================

