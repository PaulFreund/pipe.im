//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceBase.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceBase {
private:
	std::map<tstring, std::shared_ptr<IPipeExtensionService>> _services;

public:
	ServiceRoot(tstring id, tstring path, PipeJSON settings);
	virtual ~ServiceRoot();

public:
	virtual void send(PipeJSON& message);
	virtual PipeJSON receive();

	virtual PipeJSON nodeChildren(tstring address);
	virtual PipeJSON nodeMessageTypes(tstring address);
	virtual PipeJSON nodeInfo(tstring address);
};

//======================================================================================================================
