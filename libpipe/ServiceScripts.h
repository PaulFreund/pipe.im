//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceNodeBase.h"

//======================================================================================================================

class ServiceScripts : public PipeServiceNodeBase {
public:
	ServiceScripts(const tstring& address, const tstring& path, PipeObjectPtr settings);
	virtual ~ServiceScripts();

public:
	void processPreSend(PipeArrayPtr messages);
	void processPostReceive(PipeArrayPtr messages);
};

//======================================================================================================================
