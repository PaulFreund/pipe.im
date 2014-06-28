//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterface.h"

//======================================================================================================================

class PurpleInterfaceContact : public PipeServiceNodeBase {
private:
	PurpleBlistNode* _contact;
	PurpleBlistNodeType _contactType;
	PurpleConversation* _conversation;

public:
	PurpleInterfaceContact(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& instance_name, const tstring& instance_description, PurpleBlistNode* contact);
	~PurpleInterfaceContact();

public:
	bool isBuddy() { return _contactType == PURPLE_BLIST_BUDDY_NODE; }
	bool isChat() { return _contactType == PURPLE_BLIST_CHAT_NODE; }
	PurpleBlistNode* contactHandle() { return _contact; }
	PurpleBuddy* buddyHandle() { return reinterpret_cast<PurpleBuddy*>(_contact); }
	PurpleChat* chatHandle() { return reinterpret_cast<PurpleChat*>(_contact); }
	PurpleConversation* conversationHandle() { return _conversation; }
	tstring contactName() { 
		if(isBuddy()) { return safe_tstring(buddyHandle()->name); }
		else if(isChat()) { return safe_tstring(chatHandle()->alias); }
		return _T("");
	}

public:
	void onConversationChanged(PurpleConversation* conversation);
	void onTopicChanged(tstring user, tstring topic);
	void onTypingStateChanged(PurpleTypingState state);

	void onMessage(tstring sender, tstring message);

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
