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
	const std::map<tstring, std::shared_ptr<Account>>& accounts();

	void loadAccounts();
	void createAccount(const tstring& account, const tstring& password);
	void deleteAccount(const tstring& account);

private:
	bool prepareAccountsDataPath();
};

//======================================================================================================================

