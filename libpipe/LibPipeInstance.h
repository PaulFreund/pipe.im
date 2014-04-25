//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"

//======================================================================================================================

class LibPipeInstance : public ILibPipe {
private:
	HLibPipe _instance;

public:
	LibPipeInstance(const tstring& path, const PipeJSON::array& serviceTypes) {
		HLibPipe instance;
		LibPipeCreate(path.c_str(), PipeJSON(serviceTypes).dump().c_str(), &instance);
		_instance = instance;
	}

	virtual ~LibPipeInstance() {
		LibPipeDestroy(_instance);
	}

public:
	virtual void send(const PipeJSON::array& messages) {
		LibPipeSend(_instance, PipeJSON(messages).dump().c_str());
	}

	virtual PipeJSON::array receive() {
		PipeJSON::array messages;

		LibPipeReceive(_instance, &messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeJSON::array*>(context)) = PipeJSON::parse(messagesData).array_items();
		});

		return messages;
	}

public:
	static void loadExtensions(const tstring& path) {
		LibPipeLoadExtensions(path.c_str());
	}

	static PipeJSON::array serviceTypes() {
		PipeJSON::array serviceTypes;

		LibPipeGetServiceTypes(&serviceTypes, [](LibPipeCbContext context, LibPipeStr serviceTypesData) {
			(*static_cast<PipeJSON::array*>(context)) = PipeJSON::parse(serviceTypesData).array_items();
		});

		return serviceTypes;
	}
};