//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeScript.h"
#include "PipeServiceNodeBase.h"
#include "PipeExtensionInstance.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceNodeBase {
public:
	static std::vector<std::shared_ptr<PipeExtensionInstance>> Extensions;

private:
	PipeObjectPtr _config;

	std::vector<tstring> _providerTypes;

	PipeArrayPtr _scriptIncomingQueue;
	PipeArrayPtr _scriptOutgoingQueue;
	std::vector<std::shared_ptr<PipeScript>> _scriptsPreSend;
	std::vector<std::shared_ptr<PipeScript>> _scriptsPostReceive;

	std::shared_ptr<PipeServiceNodeBase> _serviceScripts;
	std::shared_ptr<PipeServiceNodeBase> _serviceServices;
	std::shared_ptr<PipeServiceNodeBase> _serviceServicesProviders;
	std::shared_ptr<PipeServiceNodeBase> _serviceServicesInstances;

public:
	ServiceRoot(const tstring& path, PipeObjectPtr settings);
	virtual ~ServiceRoot();

	void scriptPushIncoming(PipeObjectPtr message);
	void scriptPushOutgoing(PipeObjectPtr message);

public:
	void process();

private:
	void loadConfig();
	bool readConfig();
	void writeConfig();
	tstring configPath();

private:
	void initServices();
	tstring createService(const tstring& type, const tstring& name, PipeObject& settings);
	void deleteService(const tstring& name);

private:
	void initScripts();
	tstring createScript(const tstring& name, bool preSend, bool postReceive, int priority, const tstring& data);
	void deleteScript(const tstring& name);
	void executeScripts(PipeArrayPtr messages, bool preSend, bool postReceive);
};

//======================================================================================================================
