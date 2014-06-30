//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeAPI.h"
#include "LibPipeDataTypes.h"

//======================================================================================================================

class ILibPipe {
public:
	virtual void process() = 0;
	virtual void push(PipeArrayPtr messages) = 0;
	virtual PipeArrayPtr pull() = 0;

	virtual PipeArrayPtr nodeChildren(const tstring& address) = 0;
	virtual PipeArrayPtr nodeCommandTypes(const tstring& address) = 0;
	virtual PipeArrayPtr nodeMessageTypes(const tstring& address) = 0;
	virtual PipeObjectPtr nodeInfo(const tstring& address) = 0;
};

//======================================================================================================================
