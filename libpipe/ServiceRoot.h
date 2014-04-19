//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceBase.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceBase {
private:
	tstring _id = _T("pipe");
	std::map<tstring, std::shared_ptr<IPipeExtensionService>> _services;

public:
	ServiceRoot(std::map<tstring, tstring> settings);
	virtual ~ServiceRoot();

public:
	virtual void send(const LibPipeMessage& message);
	virtual std::vector<LibPipeMessage> receive();

	virtual std::vector<tstring> children(tstring address);
	virtual PipeExtensionServiceNodeInfo info(tstring address);

private:
	void handleCommand(const LibPipeMessage& message);
};

//======================================================================================================================

/*
	Was jeder service gleich machen muss:
	- Die basic commands handlen, das bedeutet send zuerst hooken
		- info ( bekommt infos aus info funktion )
		- commands (bekommt infos aus info funktion)
		- messages (bekommt infos aus info funktion)
		- children (bekommt infos aus children funktion
	- id, settings und path bekommen das bedeutet immer diese als construtcor fordern
	- Bei receive messages in outgoing weitergeben

*/