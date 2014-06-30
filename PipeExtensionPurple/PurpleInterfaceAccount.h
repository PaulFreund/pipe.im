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
	void* _currentRequestHandle;

public:
	PurpleInterfaceAccount(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& instance_name, const tstring& instance_description);
	~PurpleInterfaceAccount();

public:
	void init(const tstring& protocol_id);
	PurpleAccount* accountHandle() { return _account; }
	bool hasRequestHandle(void* requestHandle);

	//void* nextRequestHandle() {
	//	_currentRequestHandle++;

	//	if(_currentRequestHandle == INTPTR_MAX)
	//		_currentRequestHandle = 0;

	//	return _currentRequestHandle;
	//}
public:
	virtual PipeArrayPtr pull();

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

	void onFileRecvUpdate(PurpleXfer *xfer);
	void onFileSendUpdate(PurpleXfer *xfer);

	void onCloseRequest(void* requestHandle);
	void* onRequestInput(PurpleConversation* conversation, PurpleInterfaceRequestInputCb ok_cb, PurpleInterfaceRequestCancelCb cancel_cb, void* user_data, tstring who, tstring title, tstring ok_text, tstring cancel_text, tstring primary, tstring secondary, tstring default_value, tstring hint, bool multiline, bool masked);
	void* onRequestChoice(PurpleConversation* conversation, PurpleInterfaceRequestChoiceCb ok_cb, PurpleInterfaceRequestCancelCb cancel_cb, void* user_data, tstring who, tstring title, tstring ok_text, tstring cancel_text, tstring primary, tstring secondary, int default_value, std::map<int, tstring> choices);
	void* onRequestAction(PurpleConversation* conversation, void* user_data, tstring who, tstring title, tstring primary, tstring secondary, int default_action, std::map<int, std::pair<tstring, PurpleInterfaceRequestActionCb>> actions);
	void* onRequestFile(PurpleConversation* conversation, PurpleInterfaceRequestFileCb ok_cb, PurpleInterfaceRequestCancelCb cancel_cb, void* user_data, tstring who, tstring title, tstring filanem, bool savedialog);
	void* onRequestFolder(PurpleConversation* conversation, PurpleInterfaceRequestFolderCb ok_cb, PurpleInterfaceRequestCancelCb cancel_cb, void* user_data, tstring who, tstring title, tstring dirname);
	
	/*
		*purple_account_connect
		* purple_account_disconnect
		* purple_account_request_close_with_account
		* purple_account_set_enabled
		* purple_account_get_presence

		* purple_account_get_active_status
		* purple_account_remove_buddy
		* purple_account_get_status_types
		* purple_account_get_status_type
		* purple_account_add_buddy

		* purple_account_set_password
		* purple_account_get_current_error
		* purple_account_clear_current_error
		* purple_account_set_buddy_icon_path
		* purple_account_get_buddy_icon_path
	*/

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
