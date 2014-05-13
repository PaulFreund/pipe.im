//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceNodeBase.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceNodeBase {
private:
	struct PipeScript {
		tstring name;
		int priority;
		tstring data;
	};

	PipeObjectPtr _config;

	std::vector<tstring> _providerTypes;

	std::vector<PipeScript> _scriptsPreSend;
	std::vector<PipeScript> _scriptsPostReceive;

	std::shared_ptr<PipeServiceNodeBase> _serviceScripts;
	std::shared_ptr<PipeServiceNodeBase> _serviceServices;
	std::shared_ptr<PipeServiceNodeBase> _serviceServicesProviders;
	std::shared_ptr<PipeServiceNodeBase> _serviceServicesInstances;

public:
	ServiceRoot(const tstring& address, const tstring& path, PipeObjectPtr settings);
	virtual ~ServiceRoot();

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
