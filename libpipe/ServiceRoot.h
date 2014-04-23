//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceNodeBase.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceNodeBase {
public:
	ServiceRoot(tstring id, tstring path, PipeJSON::object settings);
	virtual ~ServiceRoot();

public:
	virtual void send(PipeJSON::object& message);
	virtual PipeJSON::array receive();
};

//======================================================================================================================
