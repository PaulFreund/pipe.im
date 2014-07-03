//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeHelper.h"
#include "LibPipeAPI.h"

//======================================================================================================================

namespace LibPipe {
	typedef void(*ErrorCallback)(tstring);

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

	inline void process() {
		LibPipeProcess();
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
};

//======================================================================================================================
