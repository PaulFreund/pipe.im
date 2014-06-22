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
	PurpleInterfaceContact(PurpleBuddy* buddy, const tstring& type, const tstring& description, const tstring& address, const tstring& path, PipeObjectPtr settings);
	~PurpleInterfaceContact();

public:
	PurpleBuddy* buddyHandle() { return _buddy; }

public:

};

//======================================================================================================================
