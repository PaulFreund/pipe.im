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
const tstring NamePipeExtensionServiceNodeGetAddress = _T("PipeExtensionServiceNodeGetAddress");
const tstring NamePipeExtensionServiceNodeGetType = _T("PipeExtensionServiceNodeGetType");
const tstring NamePipeExtensionServiceNodeGetMessageTypes = _T("PipeExtensionServiceNodeGetMessageTypes");
const tstring NamePipeExtensionServiceNodeGetChildren = _T("PipeExtensionServiceNodeGetChildren");

typedef void(*FktPipeExtensionGetServiceProviders)(PipeExtensionCbContext, PipeExtensionCbServiceProviders);
typedef void(*FktPipeExtensionServiceProviderGetType)(HPipeExtensionServiceProvider, PipeExtensionCbContext, PipeExtensionCbZtStr);
typedef void(*FktPipeExtensionServiceProviderGetSettingTypes)(HPipeExtensionServiceProvider, PipeExtensionCbContext, PipeExtensionCbSettingTypes);
typedef void(*FktPipeExtensionServiceProviderCreateService)(HPipeExtensionServiceProvider, PipeExtensionStr, PipeExtensionServiceSettingData*, PipeExtensionEleCnt, HPipeExtensionService*);
typedef void(*FktPipeExtensionServiceProviderDestroyService)(HPipeExtensionServiceProvider, HPipeExtensionService);
typedef void(*FktPipeExtensionServiceGetId)(HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbZtStr);
typedef void(*FktPipeExtensionServiceGetType)(HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbZtStr);
typedef void(*FktPipeExtensionServiceGetRoot)(HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbServiceNode);
typedef void(*FktPipeExtensionServiceSendMessages)(HPipeExtensionService, PipeExtensionMessageData*, PipeExtensionEleCnt);
typedef void(*FktPipeExtensionServiceReceiveMessages)(HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbMessages);
typedef void(*FktPipeExtensionServiceNodeGetAddress)(HPipeExtensionService, HPipeExtensionServiceNode, PipeExtensionCbContext, PipeExtensionCbZtStr);
typedef void(*FktPipeExtensionServiceNodeGetType)(HPipeExtensionService, HPipeExtensionServiceNode, PipeExtensionCbContext, PipeExtensionCbZtStr);
typedef void(*FktPipeExtensionServiceNodeGetMessageTypes)(HPipeExtensionService, HPipeExtensionServiceNode, PipeExtensionCbContext, PipeExtensionCbMessageTypes);
typedef void(*FktPipeExtensionServiceNodeGetChildren)(HPipeExtensionService, HPipeExtensionServiceNode, PipeExtensionCbContext, PipeExtensionCbServiceNodes);

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
	FktPipeExtensionServiceNodeGetAddress				fktServiceNodeGetAddress = nullptr;
	FktPipeExtensionServiceNodeGetType					fktServiceNodeGetType = nullptr;
	FktPipeExtensionServiceNodeGetMessageTypes			fktServiceNodeGetMessageTypes = nullptr;
	FktPipeExtensionServiceNodeGetChildren				fktServiceNodeGetChildren = nullptr;
};


//======================================================================================================================

class PipeExtensionServiceNodeInstance : public IPipeExtensionServiceNode {
private:
	PipeExtensionFunctions _functions;
	HPipeExtensionService _service;
	HPipeExtensionServiceNode _node;
public:
	PipeExtensionServiceNodeInstance(PipeExtensionFunctions functions, HPipeExtensionService service, HPipeExtensionServiceNode node) : _functions(functions), _service(service), _node(node) {

	}

	virtual ~PipeExtensionServiceNodeInstance() {

	}

public:
	virtual tstring address() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetId(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId);
		return tstring(); // TODO
	}

	virtual tstring type() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetType(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
		return tstring(); // TODO
	}

	virtual std::vector<PipeExtensionMessageType> messageTypes() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetMessageTypes(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbMessageTypes cbMessageTypes);
		return {}; // TODO
	}

	virtual std::map<tstring, std::shared_ptr<IPipeExtensionServiceNode>> children() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetChildren(HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbServiceNodes cbChildren);
		return {}; // TODO
	}
};

//======================================================================================================================

class PipeExtensionServiceInstance : public IPipeExtensionService {
private:
	PipeExtensionFunctions _functions;
	HPipeExtensionServiceProvider _provider;
	HPipeExtensionService _service;
public:
	PipeExtensionServiceInstance(PipeExtensionFunctions functions, HPipeExtensionServiceProvider provider, HPipeExtensionService service) : _functions(functions), _provider(provider), _service(service) {

	}

	~PipeExtensionServiceInstance() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceProviderDestroyService(PipeExtensionServiceProvider provider, HPipeExtensionService service);
	}

public:
	virtual tstring id() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceGetId(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId);
		return tstring(); // TODO
	}

	virtual tstring type() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceGetType(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
		return tstring(); // TODO
	}

	virtual std::shared_ptr<IPipeExtensionServiceNode> root() {
		HPipeExtensionServiceNode node = 0;
		// PIPE_EXTENSION_ITF void PipeExtensionServiceGetRoot(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbServiceNode cbServiceNode);
		return std::make_shared<PipeExtensionServiceNodeInstance>(PipeExtensionServiceNodeInstance(_functions, _service, node)); // TODO
	}

	virtual void send(const std::vector<LibPipeMessage>& messages) {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceSendMessages(HPipeExtensionService service, PipeExtensionMessageData* messages, PipeExtensionEleCnt count);
	}

	virtual std::vector<LibPipeMessage> receive() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceReceiveMessages(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbReceivedMessages);
		return {}; // TODO
	}
};

//======================================================================================================================

class PipeExtensionServiceProviderInstance : public IPipeExtensionServiceProvider {
private:
	PipeExtensionFunctions _functions;
	HPipeExtensionServiceProvider _provider;
public:
	PipeExtensionServiceProviderInstance(PipeExtensionFunctions functions, HPipeExtensionServiceProvider provider) : _functions(functions), _provider(provider) {}
	virtual ~PipeExtensionServiceProviderInstance() {}


	virtual tstring type() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetType(PipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType);
		return tstring(); // TODO
	}

	virtual std::map<tstring, tstring> settings() {
		// PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetSettingTypes(PipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbSettingTypes cbSettingTypes);
		return {}; // TODO
	}

	virtual std::shared_ptr<IPipeExtensionService> create(tstring id, const std::map<tstring, tstring>& settings) {
		HPipeExtensionService service = 0;
		// PIPE_EXTENSION_ITF void PipeExtensionServiceProviderCreateService(PipeExtensionServiceProvider provider, PipeExtensionStr id, PipeExtensionServiceSettingData* settings, PipeExtensionEleCnt count, HPipeExtensionService* service);
		return std::make_shared<PipeExtensionServiceInstance>(PipeExtensionServiceInstance(_functions, _provider, service));
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
		struct CbContext {
			PipeExtensionFunctions functions;
			std::vector<std::shared_ptr<IPipeExtensionServiceProvider>> serviceProviders;
		};

		CbContext cbContext;
		cbContext.functions = _functions;

		_functions.fktGetServiceProviders(&cbContext, [](LibPipeCbContext context, HPipeExtensionServiceProvider* providers, LibPipeEleCnt providerCount) {
			CbContext* pContext = static_cast<CbContext*>(context);
			for(auto i = 0; i < providerCount; i++) {
				pContext->serviceProviders.push_back(std::make_shared<PipeExtensionServiceProviderInstance>(PipeExtensionServiceProviderInstance(pContext->functions, providers[i])));
			}
		});

		return cbContext.serviceProviders;
	}
};

//======================================================================================================================
