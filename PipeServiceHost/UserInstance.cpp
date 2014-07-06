//======================================================================================================================

#include "CommonHeader.h"
#include "UserInstance.h"

#include <Poco/File.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;

//======================================================================================================================

UserInstance::UserInstance(const tstring& path) 
	: _path(path)
	, _config(newObject())
{
	readConfig();
	loadUser();
}

//----------------------------------------------------------------------------------------------------------------------

UserInstance::UserInstance(const tstring& path, const tstring& address, const tstring& password)
	: _path(path)
	, _config(newObject()) 
{
	createUser(address, password);
	loadUser();
}

//----------------------------------------------------------------------------------------------------------------------

UserInstance::~UserInstance() {
	// TODO: Terminate connection etc?.
}

//----------------------------------------------------------------------------------------------------------------------

void UserInstance::loadUser() {

}

//----------------------------------------------------------------------------------------------------------------------

void UserInstance::createUser(const tstring& address, const tstring& password) {
	(*_config)[_T("address")] = address;
	(*_config)[_T("password")] = password;
	writeConfig();
}

//----------------------------------------------------------------------------------------------------------------------

bool UserInstance::readConfig() {
	File configFile(_path);

	if(!configFile.exists() || !configFile.canRead())
		return false;

	try {
		ifstream configReader(_path);
		tstring configData((istreambuf_iterator<TCHAR>(configReader)), istreambuf_iterator<TCHAR>());

		tstring error;
		PipeJson configJson = PipeJson::parse(configData, error);
		if(!error.empty()) {
			PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
			pApp->onError(_T("Can not read user config file: ") + error);
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
	File configFile(_path);

	if(!configFile.exists()) {
		try {
			configFile.createFile();
		}
		catch(...) {
			pApp->onError(_T("Can not create user config file"));
			return;
		}
	}

	if(!configFile.exists() || !configFile.canWrite()) {
		pApp->onError(_T("Can not save user config, file is not writable"));
		return;
	}

	try {
		ofstream configWriter(_path);
		configWriter << dumpObject(_config);
	}
	catch(...) {
		pApp->onError(_T("There was an error writing the pipe config file"));
		return;
	}
}

//======================================================================================================================
