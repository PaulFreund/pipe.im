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
	virtual void send(PipeJSON& message) = 0;
	virtual PipeJSON receive() = 0;

	virtual PipeJSON nodeChildren(tstring address) = 0;
	virtual PipeJSON nodeMessageTypes(tstring address) = 0;
	virtual PipeJSON nodeInfo(tstring address) = 0;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual ~IPipeExtension() {}

public:
	virtual PipeJSON serviceTypes() = 0;
	virtual PipeJSON serviceTypeSettings(tstring serviceType) = 0;
	virtual IPipeExtensionService* create(tstring serviceType, tstring id, tstring path, PipeJSON settings) = 0;
	virtual void destroy(IPipeExtensionService* service) = 0;
};

//======================================================================================================================
