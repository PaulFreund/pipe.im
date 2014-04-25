//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"

//======================================================================================================================

class LibPipeInstance : public ILibPipe {
private:
	HLibPipe _instance;

public:
	LibPipeInstance(const tstring& path, PipeServiceTypes serviceTypes) {
		HLibPipe instance;
		LibPipeCreate(path.c_str(), PipeJSON(*serviceTypes).dump().c_str(), &instance);
		_instance = instance;
	}

	virtual ~LibPipeInstance() {
		LibPipeDestroy(_instance);
	}

public:
	virtual void send(PipeMessageList messages) {
		LibPipeSend(_instance, PipeJSON(*messages).dump().c_str());
	}

	virtual PipeMessageList receive() {
		PipeMessageList messages;

		LibPipeReceive(_instance, &messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeMessageList*>(context)) = std::make_shared<PipeMessageListData>(PipeJSON::parse(messagesData).array_items());
		});

		return messages;
	}

public:
	static void loadExtensions(const tstring& path) {
		LibPipeLoadExtensions(path.c_str());
	}

	static PipeServiceTypes serviceTypes() {
		PipeServiceTypes serviceTypes;

		LibPipeGetServiceTypes(&serviceTypes, [](LibPipeCbContext context, LibPipeStr serviceTypesData) {
			(*static_cast<PipeServiceTypes*>(context)) = std::make_shared<PipeServiceTypesData>(PipeJSON::parse(serviceTypesData).array_items());
		});

		return serviceTypes;
	}
};