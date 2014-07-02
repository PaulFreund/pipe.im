//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionAPI.h"

//======================================================================================================================

class IPipeExtensionService {
public:
	virtual void push(PipeArrayPtr messages) = 0;
	virtual PipeArrayPtr pull() = 0;

	//virtual PipeArrayPtr nodeChildren(const tstring& address) = 0;
	//virtual PipeArrayPtr nodeCommandTypes(const tstring& address) = 0;
	//virtual PipeArrayPtr nodeMessageTypes(const tstring& address) = 0;
	//virtual PipeObjectPtr nodeInfo(const tstring& address) = 0;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual void process() = 0;
	virtual PipeArrayPtr serviceTypes() = 0;
	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, PipeObjectPtr settings) = 0;
	virtual void destroy(IPipeExtensionService* service) = 0;
};

//======================================================================================================================
