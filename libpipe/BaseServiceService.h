//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class BaseServiceService : public IPipeExtensionService {
private:
	tstring _id = _T("service");
	std::map<tstring, tstring> _settings;

public:
	BaseServiceService(std::map<tstring, tstring> settings);
	virtual ~BaseServiceService();

public:
	virtual void send(const std::vector<LibPipeMessage>& messages);
	virtual std::vector<LibPipeMessage> receive();

	virtual std::vector<tstring> children(tstring address);
	virtual PipeExtensionServiceNodeInfo info(tstring address);
};

//======================================================================================================================
