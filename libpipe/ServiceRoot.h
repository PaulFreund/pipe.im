//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeScript.h"
#include "PipeServiceNode.h"
#include "PipeExtensionInstance.h"

//======================================================================================================================

class ServiceRoot : public PipeServiceNode {
public:
	static std::vector<std::shared_ptr<PipeExtensionInstance>> Extensions;

private:
	std::mutex _mutexQueue;
	PipeArrayPtr _queueIncoming;
	PipeArrayPtr _queueOutgoing;

	PipeObjectPtr _config;

	std::vector<tstring> _providerTypes;

	PipeArrayPtr _scriptIncomingQueue; // TODO: Recap/Cleanup
	PipeArrayPtr _scriptOutgoingQueue; // TODO: Recap/Cleanup
	std::vector<std::shared_ptr<PipeScript>> _scriptsPreSend; // TODO: Recap/Cleanup
	std::vector<std::shared_ptr<PipeScript>> _scriptsPostReceive; // TODO: Recap/Cleanup

	std::shared_ptr<PipeServiceNode> _serviceScripts;
	std::shared_ptr<PipeServiceNode> _serviceServices;
	std::shared_ptr<PipeServiceNode> _serviceServicesProviders;
	std::shared_ptr<PipeServiceNode> _serviceServicesInstances;

public:
	ServiceRoot(const tstring& path, PipeObjectPtr settings);
	virtual ~ServiceRoot();

	void scriptPushIncoming(PipeObjectPtr message); // TODO: Recap/Cleanup
	void scriptPushOutgoing(PipeObjectPtr message); // TODO: Recap/Cleanup

public:
	void process();

	virtual void addIncoming(PipeArrayPtr messages);
	virtual PipeArrayPtr getOutgoing();

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
