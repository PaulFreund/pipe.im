//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

const tstring NamePipeExtensionProcess                      = _T("PipeExtensionProcess");
const tstring NamePipeExtensionSetErrorCallback             = _T("PipeExtensionSetErrorCallback");
const tstring NamePipeExtensionSetPath                      = _T("PipeExtensionSetPath");
const tstring NamePipeExtensionGetServiceTypes              = _T("PipeExtensionGetServiceTypes");
const tstring NamePipeExtensionServiceCreate                = _T("PipeExtensionServiceCreate");
const tstring NamePipeExtensionServiceDestroy               = _T("PipeExtensionServiceDestroy");
const tstring NamePipeExtensionServicePush                  = _T("PipeExtensionServicePush");
const tstring NamePipeExtensionServicePull                  = _T("PipeExtensionServicePull");
//const tstring NamePipeExtensionServiceGetNodeChildren       = _T("PipeExtensionServiceGetNodeChildren");
//const tstring NamePipeExtensionServiceGetNodeCommandTypes   = _T("PipeExtensionServiceGetNodeCommandTypes");
//const tstring NamePipeExtensionServiceGetNodeMessageTypes   = _T("PipeExtensionServiceGetNodeMessageTypes");
//const tstring NamePipeExtensionServiceGetNodeInfo           = _T("PipeExtensionServiceGetNodeInfo");

typedef void(*FktPipeExtensionProcess)                      ();
typedef void(*FktPipeExtensionSetErrorCallback)             (PipeExtensionCbStr);
typedef void(*FktPipeExtensionSetPath)                      (PipeExtensionStr);
typedef void(*FktPipeExtensionGetServiceTypes)              (PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceCreate)                (PipeExtensionStr, PipeExtensionStr, PipeExtensionStr, HPipeExtensionService*);
typedef void(*FktPipeExtensionServiceDestroy)               (HPipeExtensionService);
typedef void(*FktPipeExtensionServicePush)                  (HPipeExtensionService, PipeExtensionStr);
typedef void(*FktPipeExtensionServicePull)                  (HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbStr);
//typedef void(*FktPipeExtensionServiceGetNodeChildren)       (HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
//typedef void(*FktPipeExtensionServiceGetNodeCommandTypes)   (HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
//typedef void(*FktPipeExtensionServiceGetNodeMessageTypes)   (HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
//typedef void(*FktPipeExtensionServiceGetNodeInfo)           (HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);

//======================================================================================================================

struct PipeExtensionFunctions {
	FktPipeExtensionProcess                     fktPipeExtensionProcess                     = nullptr;
	FktPipeExtensionSetErrorCallback            fktPipeExtensionSetErrorCallback            = nullptr;
	FktPipeExtensionSetPath                     fktPipeExtensionSetPath                     = nullptr;
	FktPipeExtensionGetServiceTypes             fktPipeExtensionGetServiceTypes             = nullptr;
	FktPipeExtensionServiceCreate               fktPipeExtensionServiceCreate               = nullptr;
	FktPipeExtensionServiceDestroy              fktPipeExtensionServiceDestroy              = nullptr;
	FktPipeExtensionServicePush                 fktPipeExtensionServicePush                 = nullptr;
	FktPipeExtensionServicePull                 fktPipeExtensionServicePull                 = nullptr;
	//FktPipeExtensionServiceGetNodeChildren      fktPipeExtensionServiceGetNodeChildren      = nullptr;
	//FktPipeExtensionServiceGetNodeCommandTypes  fktPipeExtensionServiceGetNodeCommandTypes  = nullptr;
	//FktPipeExtensionServiceGetNodeMessageTypes  fktPipeExtensionServiceGetNodeMessageTypes  = nullptr;
	//FktPipeExtensionServiceGetNodeInfo          fktPipeExtensionServiceGetNodeInfo          = nullptr;
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
	//------------------------------------------------------------------------------------------------------------------

	virtual void push(PipeArrayPtr messages) {
		_functions.fktPipeExtensionServicePush(_service, dumpArray(messages).c_str());
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr pull() {
		PipeArrayPtr messages;

		_functions.fktPipeExtensionServicePull(_service, &messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(messagesData);
		});

		return messages;
	}
	
	//------------------------------------------------------------------------------------------------------------------

	//virtual PipeArrayPtr nodeChildren(const tstring& address) {
	//	PipeArrayPtr children;

	//	_functions.fktPipeExtensionServiceGetNodeChildren(_service, address.c_str(), &children, [](PipeExtensionCbContext context, PipeExtensionStr childrenData) {
	//		(*static_cast<PipeArrayPtr*>(context)) = parseArray(childrenData);
	//	});

	//	return children;
	//}

	////------------------------------------------------------------------------------------------------------------------

	//virtual PipeArrayPtr nodeCommandTypes(const tstring& address) {
	//	PipeArrayPtr commandTypes;

	//	_functions.fktPipeExtensionServiceGetNodeCommandTypes(_service, address.c_str(), &commandTypes, [](PipeExtensionCbContext context, PipeExtensionStr commandTypesData) {
	//		(*static_cast<PipeArrayPtr*>(context)) = parseArray(commandTypesData);
	//	});

	//	return commandTypes;
	//}

	////------------------------------------------------------------------------------------------------------------------

	//virtual PipeArrayPtr nodeMessageTypes(const tstring& address) {
	//	PipeArrayPtr messageTypes;

	//	_functions.fktPipeExtensionServiceGetNodeMessageTypes(_service, address.c_str(), &messageTypes, [](PipeExtensionCbContext context, PipeExtensionStr messageTypesData) {
	//		(*static_cast<PipeArrayPtr*>(context)) = parseArray(messageTypesData);
	//	});

	//	return messageTypes;
	//}

	////------------------------------------------------------------------------------------------------------------------

	//virtual PipeObjectPtr nodeInfo(const tstring& address) {
	//	PipeObjectPtr info;

	//	_functions.fktPipeExtensionServiceGetNodeInfo(_service, address.c_str(), &info, [](PipeExtensionCbContext context, PipeExtensionStr infoData) {
	//		(*static_cast<PipeObjectPtr*>(context)) = parseObject(infoData);
	//	});

	//	return info;
	//}
};

//======================================================================================================================

class PipeExtensionInstance : public IPipeExtension {
private:
	PipeExtensionFunctions _functions;

public:
	PipeExtensionInstance(const PipeExtensionFunctions& functions, const tstring& path) : _functions(functions) {
		_functions.fktPipeExtensionSetPath(path.c_str());
	}
	virtual ~PipeExtensionInstance() {}

public:
	//------------------------------------------------------------------------------------------------------------------

	virtual void process() {
		_functions.fktPipeExtensionProcess();
	}

	//------------------------------------------------------------------------------------------------------------------

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

		_functions.fktPipeExtensionServiceCreate(serviceType.c_str(), address.c_str(), dumpObject(settings).c_str(), &service);

		if(service != 0)
			return new PipeExtensionServiceInstance(_functions, service);

		return nullptr;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual void destroy(IPipeExtensionService* service) {
		_functions.fktPipeExtensionServiceDestroy(reinterpret_cast<HPipeExtensionService>(service));
	}
};

//======================================================================================================================
