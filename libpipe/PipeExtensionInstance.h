//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

const tstring NamePipeExtensionGetServiceProviders = _T("PipeExtensionGetServiceProviders");
const tstring NamePipeExtensionGetServiceProviderSettingTypes = _T("PipeExtensionGetServiceProviderSettingTypes");
const tstring NamePipeExtensionServiceCreate = _T("PipeExtensionServiceCreate");
const tstring NamePipeExtensionServiceDestroy = _T("PipeExtensionServiceDestroy");
const tstring NamePipeExtensionServiceSend = _T("PipeExtensionServiceSend");
const tstring NamePipeExtensionServiceReceive = _T("PipeExtensionServiceReceive");
const tstring NamePipeExtensionServiceGetChildNodes = _T("PipeExtensionServiceGetChildNodes");
const tstring NamePipeExtensionServiceGetNodeType = _T("PipeExtensionServiceGetNodeType");
const tstring NamePipeExtensionServiceGetNodeMessageTypes = _T("PipeExtensionServiceGetNodeMessageTypes");


typedef void(*FktPipeExtensionGetServiceProviders)(PipeExtensionCbContext, PipeExtensionCbStrList);
typedef void(*FktPipeExtensionGetServiceProviderSettingTypes)(PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbProviderSettingTypes);
typedef void(*FktPipeExtensionServiceCreate)(PipeExtensionStr, PipeExtensionStr, PipeExtensionServiceSettingData*, PipeExtensionEleCnt, HPipeExtensionService*);
typedef void(*FktPipeExtensionServiceDestroy)(HPipeExtensionService);
typedef void(*FktPipeExtensionServiceSend)(HPipeExtensionService, PipeExtensionMessageData*, PipeExtensionEleCnt);
typedef void(*FktPipeExtensionServiceReceive)(HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbMessages);
typedef void(*FktPipeExtensionServiceGetChildNodes)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStrList);
typedef void(*FktPipeExtensionServiceGetNodeType)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeMessageTypes)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbMessageTypes);

//======================================================================================================================


struct PipeExtensionFunctions {
	FktPipeExtensionGetServiceProviders					fktPipeExtensionGetServiceProviders = nullptr;
	FktPipeExtensionGetServiceProviderSettingTypes		fktPipeExtensionGetServiceProviderSettingTypes = nullptr;
	FktPipeExtensionServiceCreate						fktPipeExtensionServiceCreate = nullptr;
	FktPipeExtensionServiceDestroy						fktPipeExtensionServiceDestroy = nullptr;
	FktPipeExtensionServiceSend							fktPipeExtensionServiceSend = nullptr;
	FktPipeExtensionServiceReceive						fktPipeExtensionServiceReceive = nullptr;
	FktPipeExtensionServiceGetChildNodes				fktPipeExtensionServiceGetChildNodes = nullptr;
	FktPipeExtensionServiceGetNodeType					fktPipeExtensionServiceGetNodeType = nullptr;
	FktPipeExtensionServiceGetNodeMessageTypes			fktPipeExtensionServiceGetNodeMessageTypes = nullptr;
};

//======================================================================================================================

class PipeExtensionServiceInstance : public IPipeExtensionService {
private:
	PipeExtensionFunctions _functions;
	HPipeExtensionService _service;
public:
	PipeExtensionServiceInstance(PipeExtensionFunctions functions, HPipeExtensionService service) : _functions(functions), _service(service) {

	}

	virtual ~PipeExtensionServiceInstance() {
		// PipeExtensionServiceDestroy (HPipeExtensionService service);
	}

public:
	virtual tstring id() {
		return tstring();
	}

	virtual void send(const std::vector<LibPipeMessage>& messages) {
		// PipeExtensionServiceSend (HPipeExtensionService service, PipeExtensionMessageData* messages, PipeExtensionEleCnt count);
	}

	virtual std::vector<LibPipeMessage> receive() {
		// PipeExtensionServiceReceive (HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbMessages);
		return {};
	}

	virtual std::vector<tstring> childNodes(tstring address) {
		// PipeExtensionServiceGetChildNodes (HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStrList cbChildNodes);
		return {};
	}

	virtual tstring nodeType(tstring address) {
		// PipeExtensionServiceGetNodeType (HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeType);
		return tstring();
	}

	virtual std::vector<PipeExtensionMessageType> nodeMessagesTypes(tstring address) {
		// PipeExtensionServiceGetNodeMessageTypes (HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbMessageTypes cbNodeMessageTypes);
		return {};
	}
};

//======================================================================================================================

class PipeExtensionInstance : public IPipeExtension {
private:
	PipeExtensionFunctions _functions;

public:
	PipeExtensionInstance(PipeExtensionFunctions functions) : _functions(functions) {
	}

	virtual ~PipeExtensionInstance() {
	}

public:
	virtual std::vector<tstring> providers() {
		// PipeExtensionGetServiceProviders (PipeExtensionCbContext context, PipeExtensionCbStrList cbProviders);
		return {};
	}
	virtual std::map<tstring, tstring> providerSettings(tstring provider) {
		// PipeExtensionGetServiceProviderSettingTypes (PipeExtensionStr type, PipeExtensionCbContext context, PipeExtensionCbProviderSettingTypes cbProviderSettingTypes);
		return {};
	}

	virtual std::shared_ptr<IPipeExtensionService> createService(tstring provider, tstring name, std::map<tstring, tstring> settings) {
		HPipeExtensionService service = 0;
		// PipeExtensionServiceCreate (PipeExtensionStr provider, PipeExtensionStr name, PipeExtensionServiceSettingData* settings, PipeExtensionEleCnt count, HPipeExtensionService* service);
		return std::make_shared<PipeExtensionServiceInstance>(PipeExtensionServiceInstance(_functions, service));
	}
};

//======================================================================================================================

/*
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
*/