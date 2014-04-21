//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"

//======================================================================================================================

class LibPipeInstance : public ILibPipe {
private:
	HLibPipe _instance;

public:
	LibPipeInstance(const tstring& path, PipeJSON& serviceTypes) {
		HLibPipe instance;
		LibPipeCreate(path.c_str(), serviceTypes.dump().c_str(), &instance);
		_instance = instance;
	}

	virtual ~LibPipeInstance() {
		LibPipeDestroy(_instance);
	}

public:
	virtual void send(PipeJSON& message) {
		LibPipeSend(_instance, message.dump().c_str());
	}

	virtual PipeJSON receive() {
		PipeJSON messages;

		LibPipeReceive(_instance, &messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeJSON*>(context)).parse(messagesData);
		});

		return messages;
	}

public:
	static void loadExtensions(const tstring& path) {
		LibPipeLoadExtensions(path.c_str());
	}

	static PipeJSON serviceTypes() {
		PipeJSON serviceTypes;

		LibPipeGetServiceTypes(&serviceTypes, [](LibPipeCbContext context, LibPipeStr serviceTypesData) {
			(*static_cast<PipeJSON*>(context)).parse(serviceTypesData);
		});

		return serviceTypes;
	}
};