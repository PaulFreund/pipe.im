//======================================================================================================================

#include "CommonHeader.h"
#include "AccountManager.h"

#include <thread>

#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/DirectoryIterator.h>

using namespace std;
using namespace Poco;
using namespace Poco::Util;

//======================================================================================================================

const tstring AccountManager::AccountsFolderName = _T("accounts");

//======================================================================================================================

AccountManager::AccountManager() {
	if(prepareAccountsDataPath())
		loadAccounts();
}

//----------------------------------------------------------------------------------------------------------------------

AccountManager::~AccountManager() {
	_accounts.clear();
}

//----------------------------------------------------------------------------------------------------------------------

shared_ptr<Account> AccountManager::account(const tstring& account) {
	if(_accounts.count(account) == 1)
		return _accounts[account];
	
	return shared_ptr<Account>(nullptr);
}

//----------------------------------------------------------------------------------------------------------------------

void AccountManager::loadAccounts() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	// Iterate over account directories
	for(DirectoryIterator it(_accountsDataPath), itEnd; it != itEnd; ++it) {
		File accountDirectory(it->path());
		if(!accountDirectory.exists() || !accountDirectory.canRead() || !accountDirectory.isDirectory()) { continue; }

		// Check if account file exist
		File accountFile(Path(Path(accountDirectory.path()), Account::AccountFileName));
		if(!accountFile.exists() || !accountFile.canRead() || !accountFile.isFile()) { continue; }

		Path accountDirectoryPath(accountDirectory.path());
		tstring accountName = accountDirectoryPath.getFileName();
		_accounts[accountName] = make_shared<Account>(accountDirectory.path());
	}
}

//----------------------------------------------------------------------------------------------------------------------

void AccountManager::createAccount(const tstring& account, const tstring& password) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	File accountDirectory(_accountsDataPath + Path::separator() + account);
	if(_accounts.count(account) != 0 || accountDirectory.exists()) {
		pApp->logger().warning(tstring(_T("[AccountManager::createAccount] Account already exists: ")) + account);
		return;
	}

	accountDirectory.createDirectory();
	if(!accountDirectory.exists() || !accountDirectory.canRead() || !accountDirectory.isDirectory()) { return; }

	_accounts[account] = make_shared<Account>(accountDirectory.path(), account, password);
}

//----------------------------------------------------------------------------------------------------------------------

void AccountManager::deleteAccount(const tstring& account) {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	if(_accounts.count(account) == 0) {
		pApp->logger().warning(tstring(_T("[AccountManager::deleteAccount] Account could not be deleted")) + account);
		return;
	}

	_accounts.erase(account);
	File accountDirectory(_accountsDataPath + Path::separator() + account);
	accountDirectory.remove(true);
}

//----------------------------------------------------------------------------------------------------------------------

bool AccountManager::prepareAccountsDataPath() {
	PipeServiceHost* pApp = reinterpret_cast<PipeServiceHost*>(&Application::instance());

	// Prepare data directory
	File dataPath(pApp->_datadir);
	if(!dataPath.exists()) { dataPath.createDirectory(); }

	if(!dataPath.exists() || !dataPath.canRead() || !dataPath.isDirectory()) {
		pApp->logger().warning(tstring(_T("[AccountManager::prepareAccountsDataPath] Could not open or create data folder: ")) + dataPath.path());
		return false;
	}

	// Prepare account data path
	tstring accountDataDir = pApp->_datadir;
	if(accountDataDir[accountDataDir.size() - 1] != Path::separator()) { accountDataDir += Path::separator(); }
	accountDataDir += AccountManager::AccountsFolderName;

	File accountDataPath(accountDataDir);
	if(!accountDataPath.exists()) { accountDataPath.createDirectory(); }

	if(!accountDataPath.exists() || !accountDataPath.canRead() || !accountDataPath.isDirectory()) {
		pApp->logger().warning(tstring(_T("[AccountManager::prepareAccountsDataPath] Could not open or create data folder: ")) + accountDataPath.path());
		return false;
	}

	_accountsDataPath = accountDataPath.path();
	return true;
}

//======================================================================================================================
