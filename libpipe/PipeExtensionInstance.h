//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

const tstring NamePipeExtensionGetServiceProviders = _T("PipeExtensionGetServiceProviders");
const tstring NamePipeExtensionServiceProviderGetType = _T("PipeExtensionServiceProviderGetType");
const tstring NamePipeExtensionServiceProviderGetSettingTypes = _T("PipeExtensionServiceProviderGetSettingTypes");
const tstring NamePipeExtensionServiceProviderCreateService = _T("PipeExtensionServiceProviderCreateService");
const tstring NamePipeExtensionServiceProviderDestroyService = _T("PipeExtensionServiceProviderDestroyService");
const tstring NamePipeExtensionServiceGetId = _T("PipeExtensionServiceGetId");
const tstring NamePipeExtensionServiceGetType = _T("PipeExtensionServiceGetType");
const tstring NamePipeExtensionServiceGetRoot = _T("PipeExtensionServiceGetRoot");
const tstring NamePipeExtensionServiceSendMessages = _T("PipeExtensionServiceSendMessages");
const tstring NamePipeExtensionServiceReceiveMessages = _T("PipeExtensionServiceReceiveMessages");
const tstring NamePipeExtensionServiceNodeGetId = _T("PipeExtensionServiceNodeGetId");
const tstring NamePipeExtensionServiceNodeGetType = _T("PipeExtensionServiceNodeGetType");
const tstring NamePipeExtensionServiceNodeGetMessageTypes = _T("PipeExtensionServiceNodeGetMessageTypes");
const tstring NamePipeExtensionServiceNodeGetChildren = _T("PipeExtensionServiceNodeGetChildren");

typedef void(*FktPipeExtensionGetServiceProviders)(PipeExtensionCbServiceProviders);
typedef void(*FktPipeExtensionServiceProviderGetType)(HPipeExtensionServiceProvider, PipeExtensionCbZtStr);
typedef void(*FktPipeExtensionServiceProviderGetSettingTypes)(HPipeExtensionServiceProvider, PipeExtensionCbSettingTypes);
typedef void(*FktPipeExtensionServiceProviderCreateService)(HPipeExtensionServiceProvider, PipeExtensionStr, PipeExtensionServiceSettingData*, PipeExtensionEleCnt, HPipeExtensionService*);
typedef void(*FktPipeExtensionServiceProviderDestroyService)(HPipeExtensionServiceProvider, HPipeExtensionService);
typedef void(*FktPipeExtensionServiceGetId)(HPipeExtensionService, PipeExtensionCbZtStr);
typedef void(*FktPipeExtensionServiceGetType)(HPipeExtensionService, PipeExtensionCbZtStr);
typedef void(*FktPipeExtensionServiceGetRoot)(HPipeExtensionService, PipeExtensionCbServiceNode);
typedef void(*FktPipeExtensionServiceSendMessages)(HPipeExtensionService, PipeExtensionMessageData*, PipeExtensionEleCnt);
typedef void(*FktPipeExtensionServiceReceiveMessages)(HPipeExtensionService, PipeExtensionCbMessages);
typedef void(*FktPipeExtensionServiceNodeGetId)(HPipeExtensionServiceNode, PipeExtensionCbZtStr);
typedef void(*FktPipeExtensionServiceNodeGetType)(HPipeExtensionServiceNode, PipeExtensionCbZtStr);
typedef void(*FktPipeExtensionServiceNodeGetMessageTypes)(HPipeExtensionServiceNode, PipeExtensionCbMessageTypes);
typedef void(*FktPipeExtensionServiceNodeGetChildren)(HPipeExtensionServiceNode, PipeExtensionCbServiceNodes);

//======================================================================================================================


struct PipeExtensionFunctions {
	FktPipeExtensionGetServiceProviders					fktGetServiceProviders = nullptr;
	FktPipeExtensionServiceProviderGetType				fktServiceProviderGetType = nullptr;
	FktPipeExtensionServiceProviderGetSettingTypes		fktServiceProviderGetSettingTypes = nullptr;
	FktPipeExtensionServiceProviderCreateService		fktServiceProviderCreateService = nullptr;
	FktPipeExtensionServiceProviderDestroyService		fktServiceProviderDestroyService = nullptr;
	FktPipeExtensionServiceGetId						fktServiceGetId = nullptr;
	FktPipeExtensionServiceGetType						fktServiceGetType = nullptr;
	FktPipeExtensionServiceGetRoot						fktServiceGetRoot = nullptr;
	FktPipeExtensionServiceSendMessages					fktServiceSendMessages = nullptr;
	FktPipeExtensionServiceReceiveMessages				fktServiceReceiveMessages = nullptr;
	FktPipeExtensionServiceNodeGetId					fktServiceNodeGetId = nullptr;
	FktPipeExtensionServiceNodeGetType					fktServiceNodeGetType = nullptr;
	FktPipeExtensionServiceNodeGetMessageTypes			fktServiceNodeGetMessageTypes = nullptr;
	FktPipeExtensionServiceNodeGetChildren				fktServiceNodeGetChildren = nullptr;
};

//======================================================================================================================

class PipeExtensionServiceInstance;
class PipeExtensionServiceProviderInstance : public IPipeExtensionServiceProvider {
private:
	HPipeExtensionServiceProvider _provider;
public:
	PipeExtensionServiceProviderInstance(HPipeExtensionServiceProvider provider) : _provider(provider) {}
	virtual ~PipeExtensionServiceProviderInstance() {}


	virtual tstring type() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetType(PipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
	}

	virtual std::map<tstring, tstring> settings() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetSettingTypes(PipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbSettingTypes cbSettingTypes);
	}

	virtual std::shared_ptr<IPipeExtensionService> create(tstring id, const std::map<tstring, tstring>& settings) {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceProviderCreateService(PipeExtensionServiceProvider provider, PipeExtensionStr id, PipeExtensionServiceSettingData* settings, PipeExtensionEleCnt count, HPipeExtensionService* service);

	}
};

//======================================================================================================================

class PipeExtensionServiceInstance : public IPipeExtensionService {
private:
	HPipeExtensionServiceProvider _provider;
	HPipeExtensionService _service;
public:
	PipeExtensionServiceInstance(HPipeExtensionServiceProvider provider, HPipeExtensionService service) : _provider(provider), _service(service) {

	}

	~PipeExtensionServiceInstance() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceProviderDestroyService(PipeExtensionServiceProvider provider, HPipeExtensionService service);
	}

public:
	virtual tstring id() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceGetId(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId);
	}

	virtual tstring type() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceGetType(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);

	}

	virtual std::shared_ptr<IPipeExtensionServiceNode> root() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceGetRoot(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbServiceNode cbServiceNode);
	}

	virtual void send(const std::vector<LibPipeMessage>& messages) {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceSendMessages(HPipeExtensionService service, PipeExtensionMessageData* messages, PipeExtensionEleCnt count);
	}

	virtual std::vector<LibPipeMessage> receive() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceReceiveMessages(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbReceivedMessages);
	}
};

//======================================================================================================================

class PipeExtensionServiceNodeInstance : IPipeExtensionServiceNode {
private:

public:
	PipeExtensionServiceNodeInstance() {

	}

	virtual ~PipeExtensionServiceNodeInstance() {

	}

public:
	virtual tstring id() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetId(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId);
	}

	virtual tstring type() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetType(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
	}

	virtual std::vector<PipeExtensionMessageType> messageTypes() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetMessageTypes(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbMessageTypes cbMessageTypes);
	}

	virtual std::map<tstring, std::shared_ptr<IPipeExtensionServiceNode>> children() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetChildren(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbServiceNodes cbChildren);
	}
};

//======================================================================================================================

class PipeExtensionInstance : public IPipeExtension {
private:
	PipeExtensionFunctions _functions;

public:
	PipeExtensionInstance(PipeExtensionFunctions functions) : _functions(functions) {}

	virtual ~PipeExtensionInstance() {}

public:
	virtual std::vector<std::shared_ptr<IPipeExtensionServiceProvider>> serviceProviders() {
		return {}; // TODO!
		// PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders(PipeExtensionCbContext context, PipeExtensionCbServiceProviders cbServiceProviders);
	}
};

//======================================================================================================================