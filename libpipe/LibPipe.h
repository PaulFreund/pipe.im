//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
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
