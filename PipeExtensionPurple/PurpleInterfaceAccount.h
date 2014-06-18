//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterface.h"

//======================================================================================================================

class PurpleInterfaceAccount : public PipeServiceNodeBase {
public:
	PurpleInterfaceAccount(const tstring& protocol_id, const tstring& type, const tstring& description, const tstring& address, const tstring& path, PipeObjectPtr settings);
	~PurpleInterfaceAccount();

public:
	virtual PipeArrayPtr receive();
};

//======================================================================================================================
