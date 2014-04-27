//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInstance.h"
#include "ServiceRoot.h"

//======================================================================================================================

class LibPipe : public ILibPipe {
public:
	static std::vector<std::shared_ptr<LibPipe>> Instances;
	static std::vector<std::shared_ptr<PipeExtensionInstance>> Extensions;

private:
	std::shared_ptr<ServiceRoot> _serviceRoot;

public:
	LibPipe(const tstring& path, PipeArrayPtr serviceTypes);
	virtual ~LibPipe();

public:
	virtual void send(PipeArrayPtr messages);
	virtual PipeArrayPtr receive();
};

//======================================================================================================================
