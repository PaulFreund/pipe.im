//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

class ServiceIRC : public IPipeExtensionService {
private:
	tstring _id;
	std::map<tstring, tstring> _settings;

public:
	ServiceIRC(tstring id, std::map<tstring, tstring> settings) : _id(id), _settings(settings) {}
	virtual ~ServiceIRC() {}

public:
	virtual tstring id() {
		return _id;
	}

	virtual void send(const std::vector<LibPipeMessage>& messages) {
	
	}

	virtual std::vector<LibPipeMessage> receive() {
		return {};
	}

	virtual std::vector<tstring> childNodes(tstring address) {
		return {};
	}

	virtual tstring nodeType(tstring address) {
		return tstring();
	}

	virtual std::vector<PipeExtensionMessageType> nodeMessagesTypes(tstring address) {
		return {};
	}

public:
	static std::map<tstring, tstring> settingTypes() {
		return {};
	}
};

//======================================================================================================================
