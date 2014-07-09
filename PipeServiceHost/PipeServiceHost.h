//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

#include "UserInstanceManager.h"
#include "GatewayWeb.h"

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/OptionSet.h>

//======================================================================================================================

class PipeServiceHost : public Poco::Util::ServerApplication {
public:
	bool _help;
	bool _debug;

	tstring _appPath;
	tstring _extdir;
	tstring _datadir;
	tstring _staticdir;

	tstring _webserverAddress;
	int _webserverPort = 9980;
	tstring _webserverPath;

	tstring _instanceAddress;
	int _instancePort = 9980;
	tstring _instanceCommand;

	std::shared_ptr<UserInstanceManager> _instanceManager;
	std::shared_ptr<GatewayWeb> _service;

public:
	PipeServiceHost();
	~PipeServiceHost();

public:
	int main(const std::vector<tstring>& args);

	void defineOptions(Poco::Util::OptionSet& options);
	void readOptions();

	void displayHelp(const tstring& name, const tstring& value);
};

//======================================================================================================================
