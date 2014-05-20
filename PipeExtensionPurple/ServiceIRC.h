//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleService.h"

//======================================================================================================================

class ServiceIRC : public PurpleService {
public:
	ServiceIRC(const tstring& address, const tstring& path, PipeObjectPtr settings) : PurpleService(_T("irc"), _T("Internet relay Chat"), address, path, settings) {
		
	}
	
	virtual ~ServiceIRC() {}
};

//======================================================================================================================
