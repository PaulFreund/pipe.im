//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================
/*
	Required functions in libpurple headers:

	* account
		* purple_account_connect
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


	* blist
		* purple_buddy_get_group
		* purple_buddy_icon_get_data
		* purple_buddy_get_presence
		* purple_buddy_new
		* purple_blist_request_add_chat
		* purple_blist_add_group
		* purple_blist_add_buddy
		* purple_blist_add_chat
		* purple_blist_add_new_buddy
		* purple_group_new
		* purple_group_get_name
		* purple_group_get_accounts
		* purple_chat_get_account
		* purple_chat_get_components
		* purple_chat_get_name
		* purple_chat_new
		* purple_chat_get_group


	* buddyicon ( Sets account icon for example)
		* purple_buddy_icon_update
		* purple_buddy_icon_get_data


	* conversation
		TODO: Search for:
			purple_conv_


	* ft ( in the future )


	* imgstore ( Usefull helper for buddy icons )


	* log ( Might be needed to delete/disable? logs )


	* status ( Helper functions might be needed )



	TODO: General events
	// request input
	// request choice
	// request action
	// request fields
	// request file
	// close request
	// request folder
	// request action with icon

*/
class PipeExtensionPurple;
class PurpleInterface {
public:
	static const tstring InterfaceID;

private:
	PurpleEventLoopUiOps _eventloopUIOps;
	PurpleRequestUiOps _requestUIOps;
	PipeExtensionPurple* _instance;
public:
	PurpleInterface(PipeExtensionPurple* instance, const tstring& path);
	~PurpleInterface();

public:
	PipeArrayPtr getProtocols();

private:
	void initSignalCallbacks();

public:

};

//======================================================================================================================
