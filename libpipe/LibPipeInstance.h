//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"

//======================================================================================================================

class LibPipeInstance : public ILibPipe {
private:
	HLibPipe _instance;

public:
	LibPipeInstance(const tstring& path, PipeArrayPtr serviceTypes) {
		HLibPipe instance;
		LibPipeCreate(path.c_str(), dumpArray(serviceTypes).c_str(), &instance);
		_instance = instance;
	}

	virtual ~LibPipeInstance() {
		LibPipeDestroy(_instance);
	}

public:
	virtual void send(PipeArrayPtr messages) {
		LibPipeSend(_instance, dumpArray(messages).c_str());
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr receive() {
		PipeArrayPtr messages;

		LibPipeReceive(_instance, &messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(messagesData);
		});

		return messages;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeChildren(const tstring& address) {
		PipeArrayPtr children;

		LibPipeGetNodeChildren(_instance, address.c_str(), &children, [](LibPipeCbContext context, LibPipeStr childrenData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(childrenData);
		});

		return children;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeCommandTypes(const tstring& address) {
		PipeArrayPtr commandTypes;

		LibPipeGetNodeCommandTypes(_instance, address.c_str(), &commandTypes, [](LibPipeCbContext context, LibPipeStr commandTypesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(commandTypesData);
		});

		return commandTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeArrayPtr nodeMessageTypes(const tstring& address) {
		PipeArrayPtr messageTypes;

		LibPipeGetNodeMessageTypes(_instance, address.c_str(), &messageTypes, [](LibPipeCbContext context, LibPipeStr messageTypesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(messageTypesData);
		});

		return messageTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual PipeObjectPtr nodeInfo(const tstring& address) {
		PipeObjectPtr info;

		LibPipeGetNodeInfo(_instance, address.c_str(), &info, [](LibPipeCbContext context, LibPipeStr infoData) {
			(*static_cast<PipeObjectPtr*>(context)) = parseObject(infoData);
		});

		return info;
	}

public:
	static void loadExtensions(const tstring& path) {
		LibPipeLoadExtensions(path.c_str());
	}

	static PipeArrayPtr serviceTypes() {
		PipeArrayPtr serviceTypes;

		LibPipeGetServiceTypes(&serviceTypes, [](LibPipeCbContext context, LibPipeStr serviceTypesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(serviceTypesData);
		});

		return serviceTypes;
	}
};