//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

class BaseServiceService : public IPipeExtensionService {
private:
	tstring _id = _T("service");

public:
	BaseServiceService();
	virtual ~BaseServiceService();

public:
	virtual tstring id();
	virtual void send(const std::vector<LibPipeMessage>& messages);
	virtual std::vector<LibPipeMessage> receive();

	virtual std::vector<tstring> childNodes(tstring address);
	virtual tstring nodeType(tstring address);
	virtual std::vector<PipeExtensionMessageType> nodeMessagesTypes(tstring address);
};

//======================================================================================================================
