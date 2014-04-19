//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class PipeServiceBase : public IPipeExtensionService {
public:
	std::map<tstring, tstring> _settings;
	std::vector<LibPipeMessage> _outgoing;

public:
	PipeServiceBase(std::map<tstring, tstring> settings) : _settings(settings) {}
	virtual ~PipeServiceBase() {}

public:
	virtual void send(const LibPipeMessage& message) {

	}

	virtual std::vector<LibPipeMessage> receive() = 0;

	virtual std::vector<tstring> children(tstring address) = 0;
	virtual PipeExtensionServiceNodeInfo info(tstring address) = 0;
};

//======================================================================================================================
