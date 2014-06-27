//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterface.h"

//======================================================================================================================

class PurpleInterfaceContact;

//======================================================================================================================

class PurpleInterfaceAccount : public PipeServiceNodeBase {
private:
	PurpleAccount* _account;

public:
	PurpleInterfaceAccount(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& instance_name, const tstring& instance_description);
	~PurpleInterfaceAccount();

public:
	void init(const tstring& protocol_id);
	PurpleAccount* accountHandle() { return _account; }

public:
	virtual PipeArrayPtr receive();

public:
	PurpleInterfaceContact* contactService(PurpleBuddy* buddy);


public:
	void onConnecting();
	void onDisabled();
	void onEnabled();

	void onAuthRequest(tstring user, tstring message = _T(""));
	void onAuthDenied(tstring user);
	void onAuthGranted(tstring user);

	void onSignedOn();
	void onSignedOff();

	void onStatusChanged();// 
	void onActionsChanged();

	void onErrorChanged(tstring oldError, tstring newError);
	void onConnectionError(tstring error, tstring description = _T(""));

	void onBuddyAdded(PurpleBuddy* buddy);
	void onBuddyRemoved(PurpleBuddy* buddy);

	
	//// Actions ( deprecated )

	// connect
	// disconnect
	// ?register
	// ?unregister
	// request auth
	// ?set user info
	// ?set privacy type
	// set status
	// add buddy
	// remove buddy
	// ?group management
	// ?change password
};

//======================================================================================================================
