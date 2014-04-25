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
	virtual void send(PipeJsonArray messages) = 0;
	virtual PipeJsonArray receive() = 0;

	virtual PipeJsonArray nodeChildren(const tstring& address) = 0;
	virtual PipeJsonArray nodeMessageTypes(const tstring& address) = 0;
	virtual PipeJsonObject nodeInfo(const tstring& address) = 0;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual ~IPipeExtension() {}

public:
	virtual PipeJsonArray serviceTypes() = 0;
	virtual PipeJsonObject serviceTypeSettings(const tstring& serviceType) = 0;
	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, PipeJsonObject settings) = 0;
	virtual void destroy(IPipeExtensionService* service) = 0;
};

//======================================================================================================================
