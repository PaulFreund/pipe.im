//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeHelper.h"
#include "LibPipeAPI.h"

//======================================================================================================================

namespace LibPipe {
	typedef void* ErrorCallbackContxt;
	typedef void(*ErrorCallback)(ErrorCallbackContxt, tstring);

	//------------------------------------------------------------------------------------------------------------------

	inline void setErrorCallback(ErrorCallbackContxt ctx, ErrorCallback cb) {
		struct ErrorCallbackData {
			ErrorCallbackContxt ctx;
			ErrorCallback cb;
		};

		ErrorCallbackData data;
		data.ctx = ctx;
		data.cb = cb;

		LibPipeSetErrorCallback(reinterpret_cast<void*>(&data), [](LibPipeCbContext context, LibPipeStr error) {
			ErrorCallbackData* pData = reinterpret_cast<ErrorCallbackData*>(context);
			(*pData->cb)(pData->ctx, tstring(error));
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
