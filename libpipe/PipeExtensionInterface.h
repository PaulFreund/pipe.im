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
	virtual void send(const PipeJSON::array& messages) = 0;
	virtual PipeJSON::array receive() = 0;

	virtual PipeJSON::array nodeChildren(const tstring& address) = 0;
	virtual PipeJSON::array nodeMessageTypes(const tstring& address) = 0;
	virtual PipeJSON::object nodeInfo(const tstring& address) = 0;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual ~IPipeExtension() {}

public:
	virtual PipeJSON::array serviceTypes() = 0;
	virtual PipeJSON::object serviceTypeSettings(const tstring& serviceType) = 0;
	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, const PipeJSON::object& settings) = 0;
	virtual void destroy(IPipeExtensionService* service) = 0;
};

//======================================================================================================================
