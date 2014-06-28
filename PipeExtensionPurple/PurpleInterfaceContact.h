//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterface.h"

//======================================================================================================================

class PurpleInterfaceContact : public PipeServiceNodeBase {
private:
	PurpleBuddy* _buddy;

public:
	PurpleInterfaceContact(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& instance_name, const tstring& instance_description, PurpleBuddy* buddy);
	~PurpleInterfaceContact();

public:
	PurpleBuddy* buddyHandle() { return _buddy; }
	tstring buddyName() { return tstring(_buddy->name); }

public:
	void onConversationChanged(PurpleConversation* conversation);

	void onMessage(tstring message);

	void onChatStatusChanged(bool joined);
	void onChatBuddyOnline(tstring name, PurpleConvChatBuddyFlags flags);
	void onChatBuddyOffline(tstring name, tstring reason);

	void onStatusChanged(PurpleStatus* status);
	void onStatusTypeChanged(tstring statusType);
	void onStatusMessageChanged(tstring message);
	void onStatusPriorityChanged(int priority);
	void onStatusNickChanged(tstring nick);
	void onIconChanged();
	void onIdleChanged(bool idle);

};

//======================================================================================================================
