//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInstance.h"

//======================================================================================================================

class LibPipe : public ILibPipe {
public:
	static std::vector<LibPipe> Instances;
	static std::vector<PipeExtensionInstance> Extensions;

private:
	tstring _id = _T("pipe");
	tstring _path;
	std::vector<tstring> _providers; 

	std::map<tstring, std::shared_ptr<IPipeExtensionService>> _services;
	std::vector<LibPipeMessage> _outgoing;

public:
	LibPipe(tstring path, std::vector<tstring> providers);
	virtual ~LibPipe();

public:
	virtual void send(const std::vector<LibPipeMessage>& messages);
	virtual std::vector<LibPipeMessage> receive();

private:
	void handleCommand(const LibPipeMessage& message);
};

//======================================================================================================================
