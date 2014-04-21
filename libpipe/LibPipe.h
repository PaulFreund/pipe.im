//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInstance.h"
#include "ServiceRoot.h"

//======================================================================================================================

class LibPipe : public ILibPipe {
public:
	static std::vector<LibPipe> Instances;
	static std::vector<PipeExtensionInstance> Extensions;

private:
	std::shared_ptr<ServiceRoot> _serviceRoot;

public:
	LibPipe(tstring path, PipeJSON serviceTypes);
	virtual ~LibPipe();

public:
	virtual void send(PipeJSON& message);
	virtual PipeJSON receive();
};

//======================================================================================================================
