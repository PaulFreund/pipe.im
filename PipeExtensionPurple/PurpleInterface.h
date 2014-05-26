//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include <purple.h>

//======================================================================================================================

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
	// buddy added
	// buddy removed
	// blist node-added
	// blist node-removed
	// blist node-extended-menu
	// blist node-aliased
};

class PurpleInterfaceConversation {
	// writing-im-msg
	// wrote-im-msg
	// sent-attention
	// got-attention
	// sending-im-msg
	// sent-im-msg
	// receiving-im-msg
	// received-im-msg
	// blocked-im-msg
	// writing-chat-msg
	// wrote-chat-msg
	// sending-chat-msg
	// sent-chat-msg
	// receiving-chat-msg
	// received-chat-msg
	// conversation-updated
	// buddy-typing
	// buddy-typed
	// buddy-typing-stopped
	// chat-buddy-joining
	// chat-buddy-joined
	// chat-buddy-flags
	// chat-buddy-leaving
	// chat-buddy-left
	// deleting-chat-buddy
	// chat-inviting-user
	// chat-invited-user
	// chat-invited
	// chat-invite-blocked
	// chat-joined
	// chat-join-failed
	// chat-left
	// chat-topic-changed
	// cleared-message-history
	// conversation-extended-menu
};

class PurpleInterfaceAccount {
	// signing-on
	// signed-on
	// signing-off
	// signed-off
	// connection-error
	// autojoin

	// connecting
	// disabled
	// enabled
	// created
	// destroying
	// status-changed
	// actions-changed
	// alias-changed
	// authorization-requested
	// authorization-requested-with-message
	// authorization-denied
	// authorization-granted
	// error-changed
	// signed-on
	// signed-off
	// connection-error

	// conversation-created
	// deleting-conversation
	// displaying-userinfo
};

class PurpleInterfaceBase {
	// account added
	// account removed
	// request input
	// request choice
	// request action
	// request fields
	// request file
	// close request
	// request folder
	// request action with icon
};


class PurpleInterface {
private:
	PurpleEventLoopUiOps _eventloopUIOps;
	PurpleRequestUiOps _requestUIOps;

public:
	PurpleInterface(const tstring& path);
	~PurpleInterface();

public:
	PipeArrayPtr getProtocols();

private:
	void initSignalCallbacks();

public:

};

//======================================================================================================================
