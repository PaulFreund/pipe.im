//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"
#include "PipeExtensionAPI.h"

//======================================================================================================================

class IPipeExtensionService {
public:
	virtual ~IPipeExtensionService() {}

public:
	virtual void send(PipeJSON::object& message) = 0;
	virtual PipeJSON::array receive() = 0;

	virtual PipeJSON::array nodeChildren(tstring address) = 0;
	virtual PipeJSON::array nodeMessageTypes(tstring address) = 0;
	virtual PipeJSON::object nodeInfo(tstring address) = 0;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual ~IPipeExtension() {}

public:
	virtual PipeJSON::array serviceTypes() = 0;
	virtual PipeJSON::object serviceTypeSettings(tstring serviceType) = 0;
	virtual IPipeExtensionService* create(tstring serviceType, tstring address, tstring path, PipeJSON::object settings) = 0;
	virtual void destroy(IPipeExtensionService* service) = 0;
};

//======================================================================================================================
