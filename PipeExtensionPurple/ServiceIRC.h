//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

class ServiceIRC : public PipeServiceBase {
public:
	ServiceIRC(tstring id, tstring path, PipeJSON settings) : PipeServiceBase(id, path, settings) {}
	virtual ~ServiceIRC() {}

public:
	virtual void send(PipeJSON& message) {
	// TODO
	}

	virtual PipeJSON receive() {
		return PipeJSON(); // TODO
	}

	virtual PipeJSON nodeChildren(tstring address) {
		return PipeJSON(); // TODO
	}

	virtual PipeJSON nodeMessageTypes(tstring address) {
		return PipeJSON(); // TODO
	}

	virtual PipeJSON nodeInfo(tstring address) {
		return PipeJSON(); // TODO
	}
};

//======================================================================================================================
