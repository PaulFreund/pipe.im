//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"
#include "PipeExtensionAPI.h"

//======================================================================================================================

struct PipeExtensionMessageParameterType {
	tstring id;
	tstring description;
	bool optional;
	bool binary;
};

//======================================================================================================================

struct PipeExtensionMessageType {
	tstring id;
	tstring description;
	bool receiving;
	std::vector<PipeExtensionMessageParameterType> parameterTypes;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual ~IPipeExtension() {}

public:
	virtual std::vector<tstring> providers() = 0;
	virtual std::map<tstring, tstring> providerSettings(tstring provider) = 0;
};

//======================================================================================================================

class IPipeExtensionService {
public:
	virtual ~IPipeExtensionService() {}

public:
	virtual tstring id() = 0;
	virtual void send(const std::vector<LibPipeMessage>& messages) = 0;
	virtual std::vector<LibPipeMessage> receive() = 0;

	virtual std::vector<tstring> childNodes(tstring address) = 0;
	virtual tstring nodeType(tstring address) = 0;
	virtual std::vector<PipeExtensionMessageType> nodeMessagesTypes(tstring address) = 0;
};

//======================================================================================================================
