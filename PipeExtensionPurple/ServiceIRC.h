//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

class ServiceIRC : public PipeServiceBase {
private:
	tstring _id;
	tstring _settings;

public:
	ServiceIRC(tstring id, tstring path, tstring settings) : PipeServiceBase(id, path, settings) {}
	virtual ~ServiceIRC() {}

public:
	virtual void send(const tstring& message) {
	// TODO
	}

	virtual tstring receive() {
		return _T(""); // TODO
	}

	virtual tstring nodeChildren(tstring address) {
		return _T(""); // TODO
	}

	virtual tstring nodeMessageTypes(tstring address) {
		return _T(""); // TODO
	}

	virtual tstring nodeInfo(tstring address) {
		return _T(""); // TODO
	}
};

//======================================================================================================================
