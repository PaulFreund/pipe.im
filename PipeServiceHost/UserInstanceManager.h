//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "UserInstance.h"

#include <Poco/Net/StreamSocket.h>
//#include <Poco/Net/ServerSocket.h>

//======================================================================================================================

class UserInstanceManager {
private:
	std::shared_ptr<Poco::Net::ServerSocket> _socket;
	//std::shared_ptr<Poco::Net::TCPServer> _server;

public:
	UserInstanceManager();
	~UserInstanceManager();

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

