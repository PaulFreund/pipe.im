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
	virtual void send(const tstring& message) = 0;
	virtual tstring receive() = 0;

	virtual tstring nodeChildren(tstring address) = 0;
	virtual tstring nodeMessageTypes(tstring address) = 0;
	virtual tstring nodeInfo(tstring address) = 0;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual ~IPipeExtension() {}

public:
	virtual tstring serviceTypes() = 0;
	virtual tstring serviceTypeSettings(tstring serviceType) = 0;
	virtual IPipeExtensionService* create(tstring serviceType, tstring id, tstring path, tstring settings) = 0;
	virtual void destroy(IPipeExtensionService* service) = 0;
};

//======================================================================================================================
