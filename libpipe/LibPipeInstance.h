//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"

//======================================================================================================================

class LibPipeInstance : public ILibPipe {
private:
	HLibPipe _instance;

public:
	LibPipeInstance(const tstring& path, const tstring& serviceTypes) {
		HLibPipe instance;
		LibPipeCreate(path.c_str(), serviceTypes.c_str(), &instance);
		_instance = instance;
	}

	virtual ~LibPipeInstance() {
		LibPipeDestroy(_instance);
	}

public:
	virtual void send(const tstring& message) {
		LibPipeSend(_instance, message.c_str());
	}

	virtual tstring receive() {
		tstring messages;

		LibPipeReceive(_instance, &messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<tstring*>(context)) = messagesData;
		});

		return messages;
	}

public:
	static void loadExtensions(const tstring& path) {
		LibPipeLoadExtensions(path.c_str());
	}

	static tstring serviceTypes() {
		tstring serviceTypes;

		LibPipeGetServiceTypes(&serviceTypes, [](LibPipeCbContext context, LibPipeStr serviceTypesData) {
			(*static_cast<tstring*>(context)) = serviceTypesData;
		});

		return serviceTypes;
	}
};