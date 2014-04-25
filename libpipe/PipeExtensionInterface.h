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
	virtual void send(PipeMessageList messages) = 0;
	virtual PipeMessageList receive() = 0;

	virtual PipeServiceNodeChildren nodeChildren(const tstring& address) = 0;
	virtual PipeServiceNodeMessageTypes nodeMessageTypes(const tstring& address) = 0;
	virtual PipeServiceNodeInfo nodeInfo(const tstring& address) = 0;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual ~IPipeExtension() {}

public:
	virtual PipeServiceTypes serviceTypes() = 0;
	virtual PipeServiceTypeSettings serviceTypeSettings(const tstring& serviceType) = 0;
	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, PipeServiceSettings settings) = 0;
	virtual void destroy(IPipeExtensionService* service) = 0;
};

//======================================================================================================================
