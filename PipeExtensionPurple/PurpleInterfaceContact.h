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

public:
	void onStatusChanged(tstring id, tstring message);
	void onIconChanged();

};

//======================================================================================================================
