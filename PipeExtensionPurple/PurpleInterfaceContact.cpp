//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterfaceContact.h"

//======================================================================================================================

PurpleInterfaceContact::PurpleInterfaceContact(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& instance_name, const tstring& instance_description, PurpleBuddy* buddy)
	: PipeServiceNodeBase(address, path, settings, _T("purple_contact"), _T("A purple chat contact"), instance_name, instance_description, _T("purple_contact")) {
	_buddy = buddy;
}

//----------------------------------------------------------------------------------------------------------------------

PurpleInterfaceContact::~PurpleInterfaceContact() {}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceContact::onStatusChanged(tstring status) {
	// TODO
	pushOutgoing(_T(""), _T("status_changed"), status);
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

//======================================================================================================================
