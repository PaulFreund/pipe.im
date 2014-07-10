//======================================================================================================================

#include "CommonHeader.h"
#include "Account.h"
#include "InstanceManager.h"

#include <Poco/File.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;

//======================================================================================================================

const tstring Account::AccountFileName = _T("account.json");

//======================================================================================================================

Account::Account(const tstring& path) 
	: _path(path)
	, _config(newObject())
	, _connection(nullptr)
{
	readConfig();
	InstanceManager::spawnInstance(account(), _path);
}

//----------------------------------------------------------------------------------------------------------------------

Account::Account(const tstring& path, const tstring& account_, const tstring& password)
	: _path(path)
	, _config(newObject()) 
	, _connection(nullptr) 
{
	createAccount(account_, password);
	InstanceManager::spawnInstance(account(), _path);
}

//----------------------------------------------------------------------------------------------------------------------

Account::~Account() {
}

//----------------------------------------------------------------------------------------------------------------------

void Account::addIncoming(const tstring& message) {
	_incoming.push_back(message);
}

//----------------------------------------------------------------------------------------------------------------------

vector<tstring> Account::getOutgoing() {
	vector<tstring> result = _outgoing; // TODO: Inefficient
	_outgoing.clear();
	return result;
}

//----------------------------------------------------------------------------------------------------------------------

void Account::setConnection(InstanceConnection* connection) {
	_connection = connection;
}

//----------------------------------------------------------------------------------------------------------------------

bool Account::authenticate(const tstring& suppliedPassword) {
	return (password() == suppliedPassword);
}

//----------------------------------------------------------------------------------------------------------------------

void Account::addSession(tstring id, std::shared_ptr<AccountSession> session) {
	// TODO 
}

//----------------------------------------------------------------------------------------------------------------------

void Account::removeSession(tstring id) {
	// TODO
}

//----------------------------------------------------------------------------------------------------------------------

void Account::createAccount(const tstring& account, const tstring& password) {
	(*_config)[_T("account")] = account;
	(*_config)[_T("password")] = password;
	writeConfig();
}

//----------------------------------------------------------------------------------------------------------------------

bool Account::readConfig() {
	File configFile(_path + Path::separator() + Account::AccountFileName);

	if(!configFile.exists() || !configFile.canRead())
		return false;

	try {
		ifstream configReader(configFile.path());
		tstring configData((istreambuf_iterator<TCHAR>(configReader)), istreambuf_iterator<TCHAR>());

		tstring error;
		PipeJson configJson = PipeJson::parse(configData, error);
		if(!error.empty()) {
			PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
			pApp->logger().warning(_T("[Account::readConfig] Can not read account config file: ") + error);
			return false;
		}

		_config = make_shared<PipeObject>(configJson.object_items());
	}
	catch(...) { return false; }

	return true;
}

//----------------------------------------------------------------------------------------------------------------------

void Account::writeConfig() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());
	File configFile(_path + Path::separator() + Account::AccountFileName);

	if(!configFile.exists()) {
		try {
			configFile.createFile();
		}
		catch(...) {
			pApp->logger().warning(tstring(_T("[Account::writeConfig] Can not create account config file")));
			return;
		}
	}

	if(!configFile.exists() || !configFile.canWrite()) {
		pApp->logger().warning(tstring(_T("[Account::writeConfig] Can not save account config, file is not writable")));
		return;
	}

	try {
		ofstream configWriter(configFile.path());
		configWriter << dumpObject(_config);
	}
	catch(...) {
		pApp->logger().warning(tstring(_T("[Account::writeConfig] There was an error writing the pipe config file")));
		return;
	}
}

//----------------------------------------------------------------------------------------------------------------------

const tstring& Account::account() {
	return (*_config)[_T("account")].string_value();
}

//----------------------------------------------------------------------------------------------------------------------

const tstring& Account::password() {
	return (*_config)[_T("password")].string_value();
}

//======================================================================================================================
