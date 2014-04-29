//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeAPI.h"
#include "LibPipeDataTypes.h"
#include "LibPipeHelper.h"

//======================================================================================================================

class ILibPipe {
public:
	virtual ~ILibPipe() {};

public:
	virtual void send(PipeArrayPtr messages) = 0;
	virtual PipeArrayPtr receive() = 0;

	virtual PipeArrayPtr nodeChildren(const tstring& address) = 0;
	virtual PipeArrayPtr nodeCommandTypes(const tstring& address) = 0;
	virtual PipeArrayPtr nodeMessageTypes(const tstring& address) = 0;
	virtual PipeObjectPtr nodeInfo(const tstring& address) = 0;
};

//======================================================================================================================
