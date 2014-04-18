//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"
#include "PipeExtensionAPI.h"

//======================================================================================================================

struct PipeExtensionServiceType {
	tstring id;
	tstring description;
	std::map<tstring, tstring> settings;
};

//======================================================================================================================

struct PipeExtensionMessageParameterType {
	tstring id;
	tstring description;
	bool optional;
	bool binary;
};

//----------------------------------------------------------------------------------------------------------------------

struct PipeExtensionMessageType {
	tstring id;
	tstring description;
	bool command;
	std::vector<PipeExtensionMessageParameterType> parameterTypes;
};

//----------------------------------------------------------------------------------------------------------------------

struct PipeExtensionServiceNodeType {
	tstring id;
	tstring description;
	std::vector<PipeExtensionMessageType> messageTypes;
};

//----------------------------------------------------------------------------------------------------------------------

struct PipeExtensionServiceNodeInfo {
	tstring id;
	PipeExtensionServiceNodeType type;
	std::map<tstring, tstring> meta;
};

//======================================================================================================================

class IPipeExtensionService {
public:
	virtual ~IPipeExtensionService() {}

public:
	virtual void send(const std::vector<LibPipeMessage>& messages) = 0;
	virtual std::vector<LibPipeMessage> receive() = 0;

	virtual std::vector<tstring> children(tstring address) = 0;
	virtual PipeExtensionServiceNodeInfo info(tstring address) = 0;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual ~IPipeExtension() {}

public:
	virtual std::vector<PipeExtensionServiceType> serviceTypes() = 0;
	virtual IPipeExtensionService* create(tstring serviceTypeId, tstring id, std::map<tstring, tstring> settings) = 0;
	virtual void destroy(IPipeExtensionService* service) = 0;
};

//======================================================================================================================
