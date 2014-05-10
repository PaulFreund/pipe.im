//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeServiceNodeBase.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceNodeBase {
private:
	PipeObjectPtr _config;

	std::shared_ptr<PipeServiceNodeBase> _serviceScripts;
	std::shared_ptr<PipeServiceNodeBase> _serviceServices;
	std::shared_ptr<PipeServiceNodeBase> _serviceServicesProvider;
	std::shared_ptr<PipeServiceNodeBase> _serviceServicesInstances;

public:
	ServiceRoot(const tstring& address, const tstring& path, PipeObjectPtr settings);
	virtual ~ServiceRoot();

private:
	void initScripts();
	void initServices();

	void loadConfig();
	bool readConfig();
	void writeConfig();
	tstring configPath();
};

//======================================================================================================================
