//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

class ServiceIRC : public PipeServiceNodeBase {
public:
	ServiceIRC(const tstring& address, const tstring& path, PipeObjectPtr settings) : PipeServiceNodeBase(_T("irc"), _T("Internet relay Chat"), address, path, settings) {
		// TODO: Add stuff
	}
	
	virtual ~ServiceIRC() {}
};

//======================================================================================================================
