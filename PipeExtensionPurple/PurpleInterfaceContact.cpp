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

#include "CommonHeader.h"
#include "PurpleInterfaceContact.h"

//======================================================================================================================

PurpleInterfaceContact::PurpleInterfaceContact(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& instance_name, const tstring& instance_description, PurpleBlistNode* contact)
	: PipeServiceNode(address, path, settings, _T("purple_contact"), _T("A purple chat contact"), instance_name, instance_description, _T("purple_contact"))
	, _contact(contact)
	, _contactType(purple_blist_node_get_type(contact))
	, _conversation(nullptr)
	{

	if(_contact == nullptr) { 
		pushOutgoing(_T(""), _T("error"), _T("Missing contact handle"));
		return;
	}
	
	// Get current status 
	if(isBuddy()) {
		auto* presence = purple_buddy_get_presence(buddyHandle());
		if(presence != nullptr) {
			onStatusChanged(purple_presence_get_active_status(presence));
		}
	}

	// Create conversation if it does not exist
	if(_conversation == nullptr) {
		if(isBuddy()) {
			auto* buddy = buddyHandle();
			_conversation = purple_conversation_new(PURPLE_CONV_TYPE_IM, buddy->account, safe_tstring(buddy->name).c_str()); 
		}
	}

	auto cmdSay = PipeSchema::Create(PipeSchemaTypeString).title(_T("Message")).description(_T("Message text"));
	addCommand(_T("say"), _T("Send message"), cmdSay, [&](PipeObject& message) {
		auto ref = message[_T("ref")].string_value();
		if(!message.count(_T("data")) || !message[_T("data")].is_string()) {
			pushOutgoing(ref, _T("error"), _T("Missing command data"));
			return;
		}

		tstring messageText = message[_T("data")].string_value();
		if(isBuddy()) {
			purple_conv_im_send(purple_conversation_get_im_data(_conversation), messageText.c_str());
		}
		else if(isChat()) {
			purple_conv_chat_send(purple_conversation_get_chat_data(_conversation), messageText.c_str());
		}
	});
}

//----------------------------------------------------------------------------------------------------------------------

PurpleInterfaceContact::~PurpleInterfaceContact() {}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onConversationChanged(PurpleConversation* conversation) {
	_conversation = conversation;
	// TODO
	pushOutgoing(_T(""), _T("conversation_changed"), _T(""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onTopicChanged(tstring user, tstring topic) {
	// TODO
	pushOutgoing(_T(""), _T("topic_changed"), user + _T(" changed topic to ") + topic);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onTypingStateChanged(PurpleTypingState state) {
	// TODO
	pushOutgoing(_T(""), _T("typing_state_changed"), to_tstring(state));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onMessage(tstring sender, tstring message) {
	// TODO
	pushOutgoing(_T(""), _T("message"), sender + _T(": ") + message);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onChatStatusChanged(bool joined) {
	// TODO
	pushOutgoing(_T(""), _T("chat_status_changed"), to_tstring(joined));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onChatBuddyOnline(tstring name, PurpleConvChatBuddyFlags flags) {
	// TODO
	pushOutgoing(_T(""), _T("chat_buddy_online"), name);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onChatBuddyOffline(tstring name, tstring reason) {
	// TODO
	pushOutgoing(_T(""), _T("chat_buddy_offline"), name + _T(" (") + reason + _T(")"));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onStatusChanged(PurpleStatus* status) {
	if(status == nullptr) { return; }

	onStatusTypeChanged(purple_status_get_id(status));

	for(GList* attr = purple_status_type_get_attrs(purple_status_get_type(status)); attr; attr = attr->next) {
		PurpleStatusAttr* attrPtr = reinterpret_cast<PurpleStatusAttr*>(attr->data);
		if(attrPtr == nullptr) { continue; }

		tstring attrId = safe_tstring(purple_status_attr_get_id(attrPtr));
		if(attrId == _T("message")) {
			onStatusMessageChanged(safe_tstring(purple_status_get_attr_string(status, _T("message"))));
		}
		else if(attrId == _T("priority")) {
			onStatusPriorityChanged(purple_status_get_attr_int(status, _T("priority")));
		}
		else if(attrId == _T("nick")) {
			onStatusNickChanged(safe_tstring(purple_status_get_attr_string(status, _T("nick"))));
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onStatusTypeChanged(tstring statusType) {
	// TODO
	pushOutgoing(_T(""), _T("status_changed"), statusType);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onStatusMessageChanged(tstring message) {
	// TODO
	pushOutgoing(_T(""), _T("status_message_changed"), message);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onStatusPriorityChanged(int priority) {
	// TODO
	pushOutgoing(_T(""), _T("status_priority_changed"), to_tstring(priority));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onStatusNickChanged(tstring nick) {
	// TODO
	pushOutgoing(_T(""), _T("status_nick_changed"), nick);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onIconChanged() {
	// TODO
	pushOutgoing(_T(""), _T("icon_changed"), _T(""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onIdleChanged(bool idle) {
	// TODO
	pushOutgoing(_T(""), _T("idle_changed"), to_tstring(idle));
}

//----------------------------------------------------------------------------------------------------------------------

//======================================================================================================================
