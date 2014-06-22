//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================
/*
class PurpleInterfaceBuddy {
	// signed-on
	// signed-off
	// status-changed
	// privacy-changed
	// idle-changed
	// got-login-time
	// icon-changed
	// caps-changed
};

class PurpleInterfaceBuddyList {
	// blist node-added
	// blist node-removed
	// blist node-extended-menu
	// blist node-aliased
};

class PurpleInterfaceConversation {
	// sent-attention
	// got-attention
	// received-im-msg
	// blocked-im-msg
	// received-chat-msg
	// conversation-updated
	// buddy-typing
	// buddy-typed
	// buddy-typing-stopped
	// chat-buddy-joined
	// chat-buddy-flags
	// chat-buddy-left
	// deleting-chat-buddy
	// chat-invited
	// chat-invite-blocked
	// chat-joined
	// chat-join-failed
	// chat-left
	// chat-topic-changed
	// conversation-extended-menu
};

class PurpleInterfaceAccount {
	// conversation-created
	// deleting-conversation
	// displaying-userinfo
};

class PurpleInterfaceBase {
	// request input
	// request choice
	// request action
	// request fields
	// request file
	// close request
	// request folder
	// request action with icon
};
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
