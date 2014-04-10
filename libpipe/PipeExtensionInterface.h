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

class IPipeExtensionService;
class IPipeExtensionServiceProvider {
public:
	virtual ~IPipeExtensionServiceProvider() {}

public:
	virtual tstring type() = 0;
	virtual std::map<tstring, tstring> settings() = 0;

	virtual std::shared_ptr<IPipeExtensionService> create(tstring id, const std::map<tstring, tstring>& settings) = 0;
};

//======================================================================================================================

class IPipeExtensionServiceNode;
class IPipeExtensionService {
public:
	virtual ~IPipeExtensionService() {}

public:
	virtual tstring id() = 0;
	virtual tstring type() = 0;

	virtual std::shared_ptr<IPipeExtensionServiceNode> root() = 0;

	virtual void send(const std::vector<LibPipeMessage>& messages) = 0;
	virtual std::vector<LibPipeMessage> receive() = 0;
};

//======================================================================================================================

class IPipeExtensionServiceNode {
public:
	virtual ~IPipeExtensionServiceNode() {}

public:
	virtual tstring id() = 0;
	virtual tstring type() = 0;

	virtual std::vector<PipeExtensionMessageType> messageTypes() = 0;
	virtual std::map<tstring, std::shared_ptr<IPipeExtensionServiceNode>> children() = 0;
};

//======================================================================================================================

class IPipeExtension {
public:
	virtual ~IPipeExtension() {}

public:
	virtual std::vector<std::shared_ptr<IPipeExtensionServiceProvider>> serviceProviders() = 0;
};

//======================================================================================================================

