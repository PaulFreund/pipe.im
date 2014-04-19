//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceBase.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceBase {
private:
	std::map<tstring, std::shared_ptr<IPipeExtensionService>> _services;

public:
	ServiceRoot(tstring id, tstring path, std::map<tstring, tstring> settings);
	virtual ~ServiceRoot();

public:
	virtual void send(const LibPipeMessage& message);
	virtual std::vector<LibPipeMessage> receive();

	virtual std::vector<tstring> children(tstring address);
	virtual PipeExtensionServiceNodeInfo info(tstring address);

};

//======================================================================================================================
