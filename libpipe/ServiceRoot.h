//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class ServiceRoot : public IPipeExtensionService {
private:
	tstring _id = _T("pipe");
	std::map<tstring, tstring> _settings;

	std::map<tstring, std::shared_ptr<IPipeExtensionService>> _services;
	std::vector<LibPipeMessage> _outgoing;

public:
	ServiceRoot(std::map<tstring, tstring> settings);
	virtual ~ServiceRoot();

public:
	virtual void send(const std::vector<LibPipeMessage>& messages);
	virtual std::vector<LibPipeMessage> receive();

	virtual std::vector<tstring> children(tstring address);
	virtual PipeExtensionServiceNodeInfo info(tstring address);

private:
	void handleCommand(const LibPipeMessage& message);
};

//======================================================================================================================
