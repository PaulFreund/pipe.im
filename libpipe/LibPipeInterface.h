//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeAPI.h"
#include "LibPipeDataTypes.h"

//======================================================================================================================

class ILibPipe {
public:
	virtual ~ILibPipe() {};

public:
	virtual void send(PipeArrayPtr messages) = 0;
	virtual PipeArrayPtr receive() = 0;
};

//======================================================================================================================
