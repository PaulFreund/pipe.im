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
	if(_sessions.empty()) {
		_mutexQueue.lock();
		_incoming.push_back(message);
		_mutexQueue.unlock();
	}
	else {
		for(auto& session : _sessions) {
			session.second->accountIncomingAdd(message);
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

vector<tstring> Account::getOutgoing() {
	_mutexQueue.lock();
	vector<tstring> result = _outgoing; // TODO: Inefficient
	_outgoing.clear();
	_mutexQueue.unlock();
	return result;
}

//----------------------------------------------------------------------------------------------------------------------

void Account::setConnection(InstanceConnection* connection) {
	_connection = connection;
}

//----------------------------------------------------------------------------------------------------------------------

void Account::addOutgoing(const tstring& message) {
	_mutexQueue.lock();
	_outgoing.push_back(message);
	_mutexQueue.unlock();
}

//----------------------------------------------------------------------------------------------------------------------

void Account::addSession(tstring id, InstanceSession* session) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_sessions.count(id) != 0) {
		pApp->logger().warning(tstring(_T("[Account::addSession] InstanceSession already exists: ")) + id);
		return;
	}

	_sessions[id] = session;

	if(_sessions.size() == 1 && !_incoming.empty()) {
		_mutexQueue.lock();
		for(auto& message : _incoming) {
			session->accountIncomingAdd(message);
		}
		_incoming.clear();
		_mutexQueue.unlock();
	}
}

//----------------------------------------------------------------------------------------------------------------------

void Account::removeSession(tstring id) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_sessions.count(id) == 0) {
		pApp->logger().warning(tstring(_T("[Account::removeSession] InstanceSession could not be removed: ")) + id);
		return;
	}

	_sessions.erase(id);
}

//----------------------------------------------------------------------------------------------------------------------

bool Account::authenticate(const tstring& suppliedPassword) {
	return (password() == suppliedPassword);
}

//----------------------------------------------------------------------------------------------------------------------

bool Account::admin() {
	if(_config->count(_T("admin")) == 1)
		return (*_config)[_T("admin")].bool_value();

	return false;
}

//----------------------------------------------------------------------------------------------------------------------

void Account::createAccount(const tstring& account, const tstring& password) {
	(*_config)[_T("account")] = account;
	(*_config)[_T("password")] = password;
	(*_config)[_T("admin")] = false;
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
