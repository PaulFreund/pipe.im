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


//----------------------------------------------------------------------------------------------------------------------

//======================================================================================================================
