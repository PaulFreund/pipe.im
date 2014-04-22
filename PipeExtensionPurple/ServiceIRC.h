//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

class ServiceIRC : public PipeServiceBase {
public:
	ServiceIRC(tstring id, tstring path, PipeJSON::object settings) : PipeServiceBase(id, path, settings) {}
	virtual ~ServiceIRC() {}

public:
	virtual void send(PipeJSON::object& message) {
		_outgoing.push_back(message);
	}

	virtual PipeJSON::array receive() {
		// TODO
		return _outgoing;
	}

	virtual PipeJSON::array nodeChildren(tstring address) {
		return {}; // TODO
	}

	virtual PipeJSON::array nodeMessageTypes(tstring address) {
		return {}; // TODO
	}

	virtual PipeJSON::object nodeInfo(tstring address) {
		return {}; // TODO
	}
};

//======================================================================================================================
