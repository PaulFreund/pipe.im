//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
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
