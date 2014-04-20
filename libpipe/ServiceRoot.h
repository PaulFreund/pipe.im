//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceBase.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceBase {
private:
	std::map<tstring, std::shared_ptr<IPipeExtensionService>> _services;

public:
	ServiceRoot(tstring id, tstring path, tstring settings);
	virtual ~ServiceRoot();

public:
	virtual void send(const tstring& message);
	virtual tstring receive();

	virtual tstring nodeChildren(tstring address);
	virtual tstring nodeMessageTypes(tstring address);
	virtual tstring nodeInfo(tstring address);
};

//======================================================================================================================
