//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

#include "InstanceManager.h"
#include "AccountManager.h"
#include "GatewayWeb.h"
#include "GatewayPipe.h"

#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/OptionSet.h>

#include <Poco/UUIDGenerator.h>
#include <Poco/UUID.h>

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

	Poco::UUIDGenerator _uuidGenerator;

	std::shared_ptr<InstanceManager> _instanceManager;
	std::shared_ptr<AccountManager> _accountManager;

	std::shared_ptr<GatewayWeb> _gatewayWeb;
	std::shared_ptr<GatewayPipe> _gatewayPipe;

public:
	PipeServiceHost();
	~PipeServiceHost();

public:
	int main(const std::vector<tstring>& args);

	void defineOptions(Poco::Util::OptionSet& options);
	void readOptions();

	void displayHelp(const tstring& name, const tstring& value);

	tstring generateUUID();
};

//======================================================================================================================
