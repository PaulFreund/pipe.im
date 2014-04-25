//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

const tstring NamePipeExtensionGetServiceTypes = _T("PipeExtensionGetServiceTypes");
const tstring NamePipeExtensionGetServiceTypeSettings = _T("PipeExtensionGetServiceTypeSettings");
const tstring NamePipeExtensionServiceCreate = _T("PipeExtensionServiceCreate");
const tstring NamePipeExtensionServiceDestroy = _T("PipeExtensionServiceDestroy");
const tstring NamePipeExtensionServiceSend = _T("PipeExtensionServiceSend");
const tstring NamePipeExtensionServiceReceive = _T("PipeExtensionServiceReceive");
const tstring NamePipeExtensionServiceGetNodeChildren = _T("PipeExtensionServiceGetNodeChildren");
const tstring NamePipeExtensionServiceGetNodeMessageTypes = _T("PipeExtensionServiceGetNodeMessageTypes");
const tstring NamePipeExtensionServiceGetNodeInfo = _T("PipeExtensionServiceGetNodeInfo");

typedef void(*FktPipeExtensionGetServiceTypes)(PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionGetServiceTypeSettings)(PipeExtensionCbContext, PipeExtensionStr, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceCreate)(PipeExtensionStr, PipeExtensionStr, PipeExtensionStr, PipeExtensionStr, HPipeExtensionService*);
typedef void(*FktPipeExtensionServiceDestroy)(HPipeExtensionService);
typedef void(*FktPipeExtensionServiceSend)(HPipeExtensionService, PipeExtensionStr);
typedef void(*FktPipeExtensionServiceReceive)(HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeChildren)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeMessageTypes)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeInfo)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);

//======================================================================================================================

struct PipeExtensionFunctions {
	FktPipeExtensionGetServiceTypes							fktPipeExtensionGetServiceTypes				= nullptr;
	FktPipeExtensionGetServiceTypeSettings					fktPipeExtensionGetServiceTypeSettings		= nullptr;
	FktPipeExtensionServiceCreate							fktPipeExtensionServiceCreate				= nullptr;
	FktPipeExtensionServiceDestroy							fktPipeExtensionServiceDestroy				= nullptr;
	FktPipeExtensionServiceSend								fktPipeExtensionServiceSend					= nullptr;
	FktPipeExtensionServiceReceive							fktPipeExtensionServiceReceive				= nullptr;
	FktPipeExtensionServiceGetNodeChildren					fktPipeExtensionServiceGetNodeChildren		= nullptr;
	FktPipeExtensionServiceGetNodeMessageTypes				fktPipeExtensionServiceGetNodeMessageTypes	= nullptr;
	FktPipeExtensionServiceGetNodeInfo						fktPipeExtensionServiceGetNodeInfo			= nullptr;
};

//======================================================================================================================

class PipeExtensionServiceInstance : public IPipeExtensionService {
private:
	PipeExtensionFunctions _functions;
	HPipeExtensionService _service;

public:
	PipeExtensionServiceInstance(const PipeExtensionFunctions& functions, HPipeExtensionService service) : _functions(functions), _service(service) {}

	virtual ~PipeExtensionServiceInstance() {
		_functions.fktPipeExtensionServiceDestroy(_service);
	}

public:
	virtual void send(PipeMessageList messages) {
		_functions.fktPipeExtensionServiceSend(_service, PipeJSON(*messages).dump().c_str());
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeMessageList receive() {
		PipeMessageList messages;

		_functions.fktPipeExtensionServiceReceive(_service, &messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeMessageList*>(context)) = std::make_shared<PipeMessageListData>(PipeJSON::parse(messagesData).array_items());
		});

		return messages;
	}
	
	//------------------------------------------------------------------------------------------------------------------

	virtual PipeServiceNodeChildren nodeChildren(const tstring& address) {
		PipeServiceNodeChildren children;

		_functions.fktPipeExtensionServiceGetNodeChildren(_service, address.c_str(), &children, [](PipeExtensionCbContext context, PipeExtensionStr childrenData) {
			(*static_cast<PipeServiceNodeChildren*>(context)) = std::make_shared<PipeServiceNodeChildrenData>(PipeJSON::parse(childrenData).array_items());
		});

		return children;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeServiceNodeMessageTypes nodeMessageTypes(const tstring& address) {
		PipeServiceNodeMessageTypes messageTypes;

		_functions.fktPipeExtensionServiceGetNodeMessageTypes(_service, address.c_str(), &messageTypes, [](PipeExtensionCbContext context, PipeExtensionStr messageTypesData) {
			(*static_cast<PipeServiceNodeMessageTypes*>(context)) = std::make_shared<PipeServiceNodeMessageTypesData>(PipeJSON::parse(messageTypesData).array_items());
		});

		return messageTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeServiceNodeInfo nodeInfo(const tstring& address) {
		PipeServiceNodeInfo info;

		_functions.fktPipeExtensionServiceGetNodeInfo(_service, address.c_str(), &info, [](PipeExtensionCbContext context, PipeExtensionStr infoData) {
			(*static_cast<PipeServiceNodeInfo*>(context)) = std::make_shared<PipeServiceNodeInfoData>(PipeJSON::parse(infoData).object_items());
		});

		return info;
	}
};

//======================================================================================================================

class PipeExtensionInstance : public IPipeExtension {
private:
	PipeExtensionFunctions _functions;

public:
	PipeExtensionInstance(const PipeExtensionFunctions& functions) : _functions(functions) {}
	virtual ~PipeExtensionInstance() {}

public:
	virtual PipeServiceTypes serviceTypes() {
		PipeServiceTypes types;
		
		_functions.fktPipeExtensionGetServiceTypes(&types, [](PipeExtensionCbContext context, PipeExtensionStr typesData) {
			(*static_cast<PipeServiceTypes*>(context)) = std::make_shared<PipeServiceTypesData>(PipeJSON::parse(typesData).array_items());
		});

		return types;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeServiceTypeSettings serviceTypeSettings(const tstring& serviceType) {
		PipeServiceTypeSettings typeSettings;

		_functions.fktPipeExtensionGetServiceTypeSettings(&typeSettings, serviceType.c_str(), [](PipeExtensionCbContext context, PipeExtensionStr typeSettingsData) {
			(*static_cast<PipeServiceTypeSettings*>(context)) = std::make_shared<PipeServiceTypeSettingsData>(PipeJSON::parse(typeSettingsData).object_items());
		});

		return typeSettings;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, PipeServiceSettings settings) {
		HPipeExtensionService service = 0;

		_functions.fktPipeExtensionServiceCreate(serviceType.c_str(), address.c_str(), path.c_str(), PipeJSON(*settings).dump().c_str(), &service);

		return new PipeExtensionServiceInstance(_functions, service);
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual void destroy(IPipeExtensionService* service) {
		_functions.fktPipeExtensionServiceDestroy(reinterpret_cast<HPipeExtensionService>(service));
	}
};

//======================================================================================================================
