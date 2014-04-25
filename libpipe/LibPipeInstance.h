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
		LibPipeCreate(path.c_str(), dumpArray(serviceTypes).c_str(), &instance);
		_instance = instance;
	}

	virtual ~LibPipeInstance() {
		LibPipeDestroy(_instance);
	}

public:
	virtual void send(PipeJsonArray messages) {
		LibPipeSend(_instance, dumpArray(messages).c_str());
	}

	virtual PipeJsonArray receive() {
		PipeJsonArray messages;

		LibPipeReceive(_instance, &messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeJsonArray*>(context)) = parseArray(messagesData);
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
			(*static_cast<PipeJsonArray*>(context)) = parseArray(serviceTypesData);
		});

		return serviceTypes;
	}
};