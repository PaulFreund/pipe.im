//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class BaseServiceScript : public IPipeExtensionService {
private:
	tstring _id = _T("script");
	std::map<tstring, tstring> _settings;

public:
	BaseServiceScript(std::map<tstring, tstring> settings);
	virtual ~BaseServiceScript();

public:
	virtual void send(const std::vector<LibPipeMessage>& messages);
	virtual std::vector<LibPipeMessage> receive();

	virtual std::vector<tstring> children(tstring address);
	virtual PipeExtensionServiceNodeInfo info(tstring address);
};

//======================================================================================================================
