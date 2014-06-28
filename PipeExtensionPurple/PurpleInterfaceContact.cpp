//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterfaceContact.h"

//======================================================================================================================

PurpleInterfaceContact::PurpleInterfaceContact(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& instance_name, const tstring& instance_description, PurpleBuddy* buddy)
	: PipeServiceNodeBase(address, path, settings, _T("purple_contact"), _T("A purple chat contact"), instance_name, instance_description, _T("purple_contact")) {
	_buddy = buddy;
	if(_buddy == nullptr) { return; }
	PurplePresence* presence = purple_buddy_get_presence(_buddy);
	if(presence == nullptr) { return; }

	onStatusChanged(purple_presence_get_active_status(presence));

	auto cmdSay = PipeSchema::Create(PipeSchemaTypeString).title(_T("Message")).description(_T("Message text"));
	addCommand(_T("say"), _T("Send message"), cmdSay, [&](PipeObject& message) {
		auto ref = message[_T("ref")].string_value();
		if(!message.count(_T("data")) || !message[_T("data")].is_string()) {
			pushOutgoing(ref, _T("error"), _T("Missing command data"));
			return;
		}

		tstring messageText = message[_T("data")].string_value();

	});
}

//----------------------------------------------------------------------------------------------------------------------

PurpleInterfaceContact::~PurpleInterfaceContact() {}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onConversationChanged(PurpleConversation* conversation) {
	// TODO
	pushOutgoing(_T(""), _T("conversation_changed"), _T(""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onMessage(tstring message) {
	// TODO
	pushOutgoing(_T(""), _T("message"), message);
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
