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

//======================================================================================================================
/*
	Required functions in libpurple headers:


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
		* purple_conv_chat_get_id
		* purple_conv_chat_cb_find
		* purple_conv_chat_ignore
		* purple_conv_chat_unignore
		* purple_conv_chat_is_user_ignored
		* purple_conv_chat_has_left
		* purple_conv_chat_get_users
		* purple_conv_chat_invite_user
		* purple_conv_chat_get_topic

		* purple_conv_chat_send
		* purple_conv_chat_send_with_flags

		* purple_conv_im_send
		* purple_conv_im_send_with_flags

		* purple_conv_im_write
		* purple_conv_im_stop_send_typed_timeout
		* purple_conv_im_start_send_typed_timeout 
		* purple_conv_im_get_type_again
		* purple_conv_im_set_type_again
		* purple_conv_im_get_typing_state
		* purple_conv_im_get_icon

	* server
		* serv_send_typing
		* serv_move_buddy
		* serv_get_info
		* serv_set_info
		* serv_join_chat
		* serv_reject_chat
		* serv_send_file

		* serv_add_permit ? 
		* serv_add_deny ? 
		* serv_rem_permit ? 
		* serv_rem_deny ? 
		* serv_set_permit_deny ? 
		* serv_chat_invite ? 
		* serv_chat_leave ? 
		* serv_chat_whisper ? 
		* serv_alias_buddy ? 
		* serv_got_alias ? 


	* ft ( in the future )


	* imgstore ( Usefull helper for buddy icons )


	* log ( Might be needed to delete/disable? logs )


	* status ( Helper functions might be needed )
*/

//======================================================================================================================

typedef void(*PurpleInterfaceRequestCancelCb)(void* user_data);
typedef void(*PurpleInterfaceRequestInputCb)(void* user_data, const TCHAR * input);
typedef void(*PurpleInterfaceRequestActionCb)(void* user_data, int action);
typedef void(*PurpleInterfaceRequestChoiceCb)(void* user_data, int choice);
typedef void(*PurpleInterfaceRequestFileCb)(void* user_data, const TCHAR* filename);
typedef void(*PurpleInterfaceRequestFolderCb)(void* user_data, const TCHAR* dirname);

//======================================================================================================================

class PipeExtensionPurple;

//======================================================================================================================

class PurpleInterface {
public:
	static const tstring InterfaceID;
	static PipeExtensionPurple* InstanceContext;

private:
	PurpleEventLoopUiOps _eventloopUIOps;
	PurpleRequestUiOps _requestUIOps;
public:
	PurpleInterface(PipeExtensionPurple* instance, const tstring& path);
	~PurpleInterface();

public:
	PipeArrayPtr getProtocols();

private:
	void initSignalCallbacks();
};

//======================================================================================================================
