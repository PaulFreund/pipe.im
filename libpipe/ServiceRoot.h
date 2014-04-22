//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceBase.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceBase {
private:
	std::map<tstring, std::shared_ptr<IPipeExtensionService>> _services;

public:
	ServiceRoot(tstring id, tstring path, PipeJSON::object settings);
	virtual ~ServiceRoot();

public:
	virtual void send(PipeJSON::object& message);
	virtual PipeJSON::array receive();

	virtual PipeJSON::array nodeChildren(tstring address);
	virtual PipeJSON::array nodeMessageTypes(tstring address);
	virtual PipeJSON::object nodeInfo(tstring address);
};

//======================================================================================================================
