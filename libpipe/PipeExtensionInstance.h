//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

const tstring NamePipeExtensionSetErrorCallback             = _T("PipeExtensionSetErrorCallback");
const tstring NamePipeExtensionSetPath                      = _T("PipeExtensionSetPath");
const tstring NamePipeExtensionGetServiceTypes              = _T("PipeExtensionGetServiceTypes");
const tstring NamePipeExtensionServiceCreate                = _T("PipeExtensionServiceCreate");
const tstring NamePipeExtensionServiceDestroy               = _T("PipeExtensionServiceDestroy");
const tstring NamePipeExtensionProcess                      = _T("PipeExtensionProcess");
const tstring NamePipeExtensionPush                         = _T("PipeExtensionPush");
const tstring NamePipeExtensionPull                         = _T("PipeExtensionPull");

typedef void(*FktPipeExtensionSetErrorCallback)             (PipeExtensionCbStr);
typedef void(*FktPipeExtensionSetPath)                      (PipeExtensionStr);
typedef void(*FktPipeExtensionGetServiceTypes)              (PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceCreate)                (PipeExtensionStr, PipeExtensionStr, PipeExtensionStr, HPipeExtensionService*);
typedef void(*FktPipeExtensionServiceDestroy)               (HPipeExtensionService);
typedef void(*FktPipeExtensionProcess)                      ();
typedef void(*FktPipeExtensionPush)                         (PipeExtensionStr);
typedef void(*FktPipeExtensionPull)                         (PipeExtensionCbContext, PipeExtensionCbStr);

//======================================================================================================================

struct PipeExtensionFunctions {
	FktPipeExtensionSetErrorCallback            fktPipeExtensionSetErrorCallback            = nullptr;
	FktPipeExtensionSetPath                     fktPipeExtensionSetPath                     = nullptr;
	FktPipeExtensionGetServiceTypes             fktPipeExtensionGetServiceTypes             = nullptr;
	FktPipeExtensionServiceCreate               fktPipeExtensionServiceCreate               = nullptr;
	FktPipeExtensionServiceDestroy              fktPipeExtensionServiceDestroy              = nullptr;
	FktPipeExtensionProcess                     fktPipeExtensionProcess                     = nullptr;
	FktPipeExtensionPush                        fktPipeExtensionPush                        = nullptr;
	FktPipeExtensionPull                        fktPipeExtensionPull                        = nullptr;
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

	virtual PipeArrayPtr serviceTypes() {
		PipeArrayPtr types;
		
		_functions.fktPipeExtensionGetServiceTypes(&types, [](PipeExtensionCbContext context, PipeExtensionStr typesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(typesData);
		});

		return types;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual HPipeExtensionService create(const tstring& serviceType, const tstring& address, const tstring& path, PipeObjectPtr settings) {
		HPipeExtensionService service = 0;

		_functions.fktPipeExtensionServiceCreate(serviceType.c_str(), address.c_str(), dumpObject(settings).c_str(), &service);

		return service;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual void destroy(HPipeExtensionService service) {
		_functions.fktPipeExtensionServiceDestroy(service);
	}

	//------------------------------------------------------------------------------------------------------------------
	
	virtual void process() {
		_functions.fktPipeExtensionProcess();
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual void push(PipeArrayPtr messages) {
		_functions.fktPipeExtensionPush(dumpArray(messages).c_str());
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr pull() {
		PipeArrayPtr messages;

		_functions.fktPipeExtensionPull(&messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(messagesData);
		});

		return messages;
	}

};

//======================================================================================================================
