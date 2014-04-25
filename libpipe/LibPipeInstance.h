//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"

//======================================================================================================================

class LibPipeInstance : public ILibPipe {
private:
	HLibPipe _instance;

public:
	LibPipeInstance(const tstring& path, PipeJsonArray serviceTypes) {
		HLibPipe instance;
		LibPipeCreate(path.c_str(), PipeJson(*serviceTypes).dump().c_str(), &instance);
		_instance = instance;
	}

	virtual ~LibPipeInstance() {
		LibPipeDestroy(_instance);
	}

public:
	virtual void send(PipeJsonArray messages) {
		LibPipeSend(_instance, PipeJson(*messages).dump().c_str());
	}

	virtual PipeJsonArray receive() {
		PipeJsonArray messages;

		LibPipeReceive(_instance, &messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeJsonArray*>(context)) = std::make_shared<PipeJsonArrayData>(PipeJson::parse(messagesData).array_items());
		});

		return messages;
	}

public:
	static void loadExtensions(const tstring& path) {
		LibPipeLoadExtensions(path.c_str());
	}

	static PipeJsonArray serviceTypes() {
		PipeJsonArray serviceTypes;

		LibPipeGetServiceTypes(&serviceTypes, [](LibPipeCbContext context, LibPipeStr serviceTypesData) {
			(*static_cast<PipeJsonArray*>(context)) = std::make_shared<PipeJsonArrayData>(PipeJson::parse(serviceTypesData).array_items());
		});

		return serviceTypes;
	}
};