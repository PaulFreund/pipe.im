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
	static LibPipeCbErr ErrorCallback;

private:
	std::shared_ptr<ServiceRoot> _serviceRoot;

public:
	LibPipe(const tstring& path, PipeArrayPtr serviceTypes);
	virtual ~LibPipe();

public:
	virtual void send(PipeArrayPtr messages);
	virtual PipeArrayPtr receive();

	virtual PipeArrayPtr nodeChildren(const tstring& address);
	virtual PipeArrayPtr nodeCommandTypes(const tstring& address);
	virtual PipeArrayPtr nodeMessageTypes(const tstring& address);
	virtual PipeObjectPtr nodeInfo(const tstring& address);
};

//======================================================================================================================
