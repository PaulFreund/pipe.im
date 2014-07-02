//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeHelper.h"
#include "LibPipeAPI.h"

//======================================================================================================================

namespace LibPipe {
	typedef void(*ErrorCallback)(tstring);

	//------------------------------------------------------------------------------------------------------------------

	inline void process() {
		LibPipeProcess();
	}

	//------------------------------------------------------------------------------------------------------------------

	inline void setErrorCallback(ErrorCallback cb) {
		
		LibPipeSetErrorCallback(reinterpret_cast<void*>(cb), [](LibPipeCbContext context, LibPipeStr error) {
			(*reinterpret_cast<ErrorCallback>(context))(tstring(error));
		});
	}

	//------------------------------------------------------------------------------------------------------------------

	inline void setPath(const tstring& path) {
		LibPipeSetPath(path.c_str());
	}

	//------------------------------------------------------------------------------------------------------------------

	inline void loadExtensions(const tstring& path) {
		LibPipeLoadExtensions(path.c_str());
	}

	//------------------------------------------------------------------------------------------------------------------

	inline PipeArrayPtr serviceTypes() {
		PipeArrayPtr serviceTypes;

		LibPipeGetServiceTypes(&serviceTypes, [](LibPipeCbContext context, LibPipeStr serviceTypesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(serviceTypesData);
		});

		return serviceTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	inline void init(PipeArrayPtr serviceTypes) {
		LibPipeInit(dumpArray(serviceTypes).c_str());
	}

	//------------------------------------------------------------------------------------------------------------------

	inline void push(PipeArrayPtr messages) {
		LibPipePush(dumpArray(messages).c_str());
	}

	//------------------------------------------------------------------------------------------------------------------

	inline PipeArrayPtr pull() {
		PipeArrayPtr messages;

		LibPipePull(&messages, [](LibPipeCbContext context, LibPipeStr messagesData) {
			(*static_cast<PipeArrayPtr*>(context)) = parseArray(messagesData);
		});

		return messages;
	}

	//------------------------------------------------------------------------------------------------------------------

	//inline PipeArrayPtr nodeChildren(const tstring& address) {
	//	PipeArrayPtr children;

	//	LibPipeGetNodeChildren(address.c_str(), &children, [](LibPipeCbContext context, LibPipeStr childrenData) {
	//		(*static_cast<PipeArrayPtr*>(context)) = parseArray(childrenData);
	//	});

	//	return children;
	//}

	////------------------------------------------------------------------------------------------------------------------

	//inline PipeArrayPtr nodeCommandTypes(const tstring& address) {
	//	PipeArrayPtr commandTypes;

	//	LibPipeGetNodeCommandTypes(address.c_str(), &commandTypes, [](LibPipeCbContext context, LibPipeStr commandTypesData) {
	//		(*static_cast<PipeArrayPtr*>(context)) = parseArray(commandTypesData);
	//	});

	//	return commandTypes;
	//}

	////------------------------------------------------------------------------------------------------------------------

	//inline PipeArrayPtr nodeMessageTypes(const tstring& address) {
	//	PipeArrayPtr messageTypes;

	//	LibPipeGetNodeMessageTypes(address.c_str(), &messageTypes, [](LibPipeCbContext context, LibPipeStr messageTypesData) {
	//		(*static_cast<PipeArrayPtr*>(context)) = parseArray(messageTypesData);
	//	});

	//	return messageTypes;
	//}

	////------------------------------------------------------------------------------------------------------------------

	//inline PipeObjectPtr nodeInfo(const tstring& address) {
	//	PipeObjectPtr info;

	//	LibPipeGetNodeInfo(address.c_str(), &info, [](LibPipeCbContext context, LibPipeStr infoData) {
	//		(*static_cast<PipeObjectPtr*>(context)) = parseObject(infoData);
	//	});

	//	return info;
	//}

	//------------------------------------------------------------------------------------------------------------------
};

//======================================================================================================================
