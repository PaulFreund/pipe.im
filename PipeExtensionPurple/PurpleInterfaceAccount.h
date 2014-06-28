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
	PurpleInterfaceContact* contactService(PurpleBlistNode* contact);
	PurpleInterfaceContact* contactService(tstring name);

public:
	void onConnecting();
	void onDisabled();
	void onEnabled();

	void onAuthRequest(tstring user, tstring message = _T(""));
	void onAuthDenied(tstring user);
	void onAuthGranted(tstring user);

	void onSignedOn();
	void onSignedOff();

	void onStatusChanged();
	void onActionsChanged();

	void onErrorChanged(tstring oldError, tstring newError);
	void onConnectionError(tstring error, tstring description = _T(""));

	void onContactAdded(PurpleBlistNode* contact);
	void onContactRemoved(PurpleBlistNode* contact);

	void onMessageUnknownSender(tstring sender, tstring message);
	void onInvited(tstring who, tstring where, tstring message, GHashTable* joinData);

	// Important from PurplePluginProtocolInfo, could also be handled by server
	// chat_info
	// chat_info_defaults ? 
	// login ? 
	// close ? 
	// join_chat ( detect support )
	// get_chat_name
	// chat_invite ( detect support )
	// register_user ( detect support )
	// unregister_user ( detect support )
	// get_cb_real_name
	// set_chat_topic ( detect support )
	// roomlist_get_list ( detect support )
	// can_receive_file
	// send_file ( detect support )
	// send_raw ( detect support )
	// roomlist_room_serialize ?
	// add_buddy_with_invite ( detect support )

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
