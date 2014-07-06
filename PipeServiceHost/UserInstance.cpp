//======================================================================================================================

#include "CommonHeader.h"
#include "UserInstance.h"
#include "UserInstanceManager.h"

#include <Poco/File.h>
#include <Poco/Process.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;

//======================================================================================================================

const tstring UserInstance::UserFileName = _T("user.json");

//======================================================================================================================

UserInstance::UserInstance(const tstring& path) 
	: _path(path)
	, _config(newObject())
	, _connection(nullptr)
{
	readConfig();
	loadUser();
}

//----------------------------------------------------------------------------------------------------------------------

UserInstance::UserInstance(const tstring& path, const tstring& account, const tstring& password)
	: _path(path)
	, _config(newObject()) 
	, _connection(nullptr) 
{
	createUser(account, password);
	loadUser();
}

//----------------------------------------------------------------------------------------------------------------------

UserInstance::~UserInstance() {
}

//----------------------------------------------------------------------------------------------------------------------

bool UserInstance::authenticate(const tstring& suppliedPassword) {
	return (password() == suppliedPassword);
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstance::setConnection(UserInstanceConnection* connection) {
	_connection = connection;
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstance::loadUser() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	Process::Args args;
	args.push_back(_T("--account=") + account());
	args.push_back(_T("--address=") + pApp->_instanceAddress);
	args.push_back(_T("--port=") + to_tstring(pApp->_instancePort));
	args.push_back(_T("--extdir=") + pApp->_extdir);
	args.push_back(_T("--userdir=") + _path);

	if(pApp->_debug)
		args.push_back(_T("--debug"));

	//args.push_back(_T("--includedServices=")); // TODO
	//args.push_back(_T("--excludedServices="));

	Process::launch(pApp->_instanceCommand, args);
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstance::createUser(const tstring& account, const tstring& password) {
	(*_config)[_T("account")] = account;
	(*_config)[_T("password")] = password;
	writeConfig();
}

//----------------------------------------------------------------------------------------------------------------------

bool UserInstance::readConfig() {
	File configFile(_path + Path::separator() + UserInstance::UserFileName);

	if(!configFile.exists() || !configFile.canRead())
		return false;

	try {
		ifstream configReader(configFile.path());
		tstring configData((istreambuf_iterator<TCHAR>(configReader)), istreambuf_iterator<TCHAR>());

		tstring error;
		PipeJson configJson = PipeJson::parse(configData, error);
		if(!error.empty()) {
			PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
			pApp->logger().warning(_T("[UserInstance::readConfig] Can not read user config file: ") + error);
			return false;
		}

		_config = make_shared<PipeObject>(configJson.object_items());
	}
	catch(...) { return false; }

	return true;
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstance::writeConfig() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	File configFile(_path + Path::separator() + UserInstance::UserFileName);

	if(!configFile.exists()) {
		try {
			configFile.createFile();
		}
		catch(...) {
			pApp->logger().warning(tstring(_T("[UserInstance::writeConfig] Can not create user config file")));
			return;
		}
	}

	if(!configFile.exists() || !configFile.canWrite()) {
		pApp->logger().warning(tstring(_T("[UserInstance::writeConfig] Can not save user config, file is not writable")));
		return;
	}

	try {
		ofstream configWriter(configFile.path());
		configWriter << dumpObject(_config);
	}
	catch(...) {
		pApp->logger().warning(tstring(_T("[UserInstance::writeConfig] There was an error writing the pipe config file")));
		return;
	}
}

//----------------------------------------------------------------------------------------------------------------------

const tstring& UserInstance::account() {
	return (*_config)[_T("account")].string_value();
}

//----------------------------------------------------------------------------------------------------------------------

const tstring& UserInstance::password() {
	return (*_config)[_T("password")].string_value();
}

//======================================================================================================================
