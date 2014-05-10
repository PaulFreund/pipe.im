//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

const tstring NamePipeExtensionGetServiceTypes              = _T("PipeExtensionGetServiceTypes");
const tstring NamePipeExtensionServiceCreate                = _T("PipeExtensionServiceCreate");
const tstring NamePipeExtensionServiceDestroy               = _T("PipeExtensionServiceDestroy");
const tstring NamePipeExtensionServiceSend                  = _T("PipeExtensionServiceSend");
const tstring NamePipeExtensionServiceReceive               = _T("PipeExtensionServiceReceive");
const tstring NamePipeExtensionServiceGetNodeChildren       = _T("PipeExtensionServiceGetNodeChildren");
const tstring NamePipeExtensionServiceGetNodeCommandTypes   = _T("PipeExtensionServiceGetNodeCommandTypes");
const tstring NamePipeExtensionServiceGetNodeMessageTypes   = _T("PipeExtensionServiceGetNodeMessageTypes");
const tstring NamePipeExtensionServiceGetNodeInfo           = _T("PipeExtensionServiceGetNodeInfo");

typedef void(*FktPipeExtensionGetServiceTypes)              (PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceCreate)                (PipeExtensionStr, PipeExtensionStr, PipeExtensionStr, PipeExtensionStr, HPipeExtensionService*);
typedef void(*FktPipeExtensionServiceDestroy)               (HPipeExtensionService);
typedef void(*FktPipeExtensionServiceSend)                  (HPipeExtensionService, PipeExtensionStr);
typedef void(*FktPipeExtensionServiceReceive)               (HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeChildren)       (HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeCommandTypes)   (HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeMessageTypes)   (HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeInfo)           (HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);

//======================================================================================================================

struct PipeExtensionFunctions {
	FktPipeExtensionGetServiceTypes             fktPipeExtensionGetServiceTypes             = nullptr;
	FktPipeExtensionServiceCreate               fktPipeExtensionServiceCreate               = nullptr;
	FktPipeExtensionServiceDestroy              fktPipeExtensionServiceDestroy              = nullptr;
	FktPipeExtensionServiceSend                 fktPipeExtensionServiceSend                 = nullptr;
	FktPipeExtensionServiceReceive              fktPipeExtensionServiceReceive              = nullptr;
	FktPipeExtensionServiceGetNodeChildren      fktPipeExtensionServiceGetNodeChildren      = nullptr;
	FktPipeExtensionServiceGetNodeCommandTypes  fktPipeExtensionServiceGetNodeCommandTypes  = nullptr;
	FktPipeExtensionServiceGetNodeMessageTypes  fktPipeExtensionServiceGetNodeMessageTypes  = nullptr;
	FktPipeExtensionServiceGetNodeInfo          fktPipeExtensionServiceGetNodeInfo          = nullptr;
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
	virtual void send(PipeArrayPtr messages) {
		_functions.fktPipeExtensionServiceSend(_service, dumpArray(messages).c_str());
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr receive() {
		PipeArrayPtr messages;

		_functions.fktPipeExtensionServiceReceive(_service, &messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(messagesData);
		});

		return messages;
	}
	
	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeChildren(const tstring& address) {
		PipeArrayPtr children;

		_functions.fktPipeExtensionServiceGetNodeChildren(_service, address.c_str(), &children, [](PipeExtensionCbContext context, PipeExtensionStr childrenData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(childrenData);
		});

		return children;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeCommandTypes(const tstring& address) {
		PipeArrayPtr commandTypes;

		_functions.fktPipeExtensionServiceGetNodeCommandTypes(_service, address.c_str(), &commandTypes, [](PipeExtensionCbContext context, PipeExtensionStr commandTypesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(commandTypesData);
		});

		return commandTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeMessageTypes(const tstring& address) {
		PipeArrayPtr messageTypes;

		_functions.fktPipeExtensionServiceGetNodeMessageTypes(_service, address.c_str(), &messageTypes, [](PipeExtensionCbContext context, PipeExtensionStr messageTypesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(messageTypesData);
		});

		return messageTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeObjectPtr nodeInfo(const tstring& address) {
		PipeObjectPtr info;

		_functions.fktPipeExtensionServiceGetNodeInfo(_service, address.c_str(), &info, [](PipeExtensionCbContext context, PipeExtensionStr infoData) {
			(*static_cast<PipeObjectPtr*>(context)) = parseObject(infoData);
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
	virtual PipeArrayPtr serviceTypes() {
		PipeArrayPtr types;
		
		_functions.fktPipeExtensionGetServiceTypes(&types, [](PipeExtensionCbContext context, PipeExtensionStr typesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(typesData);
		});

		return types;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual IPipeExtensionService* create(const tstring& serviceType, const tstring& address, const tstring& path, PipeObjectPtr settings) {
		HPipeExtensionService service = 0;

		_functions.fktPipeExtensionServiceCreate(serviceType.c_str(), address.c_str(), path.c_str(), dumpObject(settings).c_str(), &service);

		return new PipeExtensionServiceInstance(_functions, service);
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual void destroy(IPipeExtensionService* service) {
		_functions.fktPipeExtensionServiceDestroy(reinterpret_cast<HPipeExtensionService>(service));
	}
};

//======================================================================================================================
