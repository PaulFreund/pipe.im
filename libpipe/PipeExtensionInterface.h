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
	virtual void send(PipeArrayPtr messages) = 0;
	virtual PipeArrayPtr receive() = 0;

	virtual PipeArrayPtr nodeChildren(const tstring& address) = 0;
	virtual PipeArrayPtr nodeCommandTypes(const tstring& address) = 0;
	virtual PipeArrayPtr nodeMessageTypes(const tstring& address) = 0;
	virtual PipeObjectPtr nodeInfo(const tstring& address) = 0;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual ~IPipeExtension() {}

public:
	virtual PipeArrayPtr serviceTypes() = 0;
	virtual PipeObjectPtr serviceTypeSettings(const tstring& serviceType) = 0;
	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, PipeObjectPtr settings) = 0;
	virtual void destroy(IPipeExtensionService* service) = 0;
};

//======================================================================================================================
