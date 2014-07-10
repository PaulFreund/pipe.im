//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "Account.h"

//======================================================================================================================

class AccountManager {
public:
	static const tstring AccountsFolderName;

private:
	tstring _accountsDataPath;

private:
	std::map<tstring, std::shared_ptr<Account>> _accounts;

public:
	AccountManager();
	~AccountManager();

public:
	std::shared_ptr<Account> account(const tstring& account);

	void loadAccounts();
	void createAccount(const tstring& account, const tstring& password);
	void deleteAccount(const tstring& account);

private:
	bool prepareAccountsDataPath();
};

//======================================================================================================================

