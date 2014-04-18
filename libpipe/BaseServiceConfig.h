//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class BaseServiceConfig : public IPipeExtensionService {
private:
	tstring _id = _T("config");
	std::map<tstring, tstring> _settings;

public:
	BaseServiceConfig(std::map<tstring, tstring> settings);
	virtual ~BaseServiceConfig();

public:
	virtual void send(const std::vector<LibPipeMessage>& messages);
	virtual std::vector<LibPipeMessage> receive();

	virtual std::vector<tstring> children(tstring address);
	virtual PipeExtensionServiceNodeInfo info(tstring address);
};

//======================================================================================================================
