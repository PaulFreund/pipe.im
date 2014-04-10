//======================================================================================================================

#pragma once

//======================================================================================================================

#ifdef WIN32
	#ifdef LIBPIPE_EXPORTS
		#define LIBPIPE_ITF extern "C" __declspec(dllexport) 
	#else
		#define LIBPIPE_ITF extern "C" __declspec(dllimport) 
	#endif
#else
	#define LIBPIPE_ITF extern
#endif

//======================================================================================================================

#include <stdint.h>

//======================================================================================================================
typedef const char*		LibPipeStr;
typedef uint64_t		LibPipeEleCnt;
typedef uint64_t		HLibPipeInstance;

//======================================================================================================================

struct LibPipeMessageData {
	LibPipeStr address;									// Point separated path to sending or receiving PipeExtensionServiceNode
	LibPipeStr type;									// Id of a PipeMessageType
	LibPipeEleCnt parameterCount;						// Count of parameters
	LibPipeEleCnt* parameterLength;						// List of data buffer sizes
	LibPipeStr* parameterData;							// List of data buffers
};

//======================================================================================================================

typedef void* LibPipeCbContext;
typedef void(*LibPipeCbServiceProviders)(LibPipeCbContext, LibPipeStr*, LibPipeEleCnt);
typedef void(*LibPipeCbMessages)(LibPipeCbContext, LibPipeMessageData*, LibPipeEleCnt);

//======================================================================================================================

LIBPIPE_ITF void LibPipeLoadExtensions			(LibPipeStr path);
LIBPIPE_ITF void LibPipeGetServiceProviders		(LibPipeCbContext context, LibPipeCbServiceProviders cbServiceProviders);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeCreateInstance			(LibPipeStr path, LibPipeStr* serviceProviders, LibPipeEleCnt serviceProviderCount, HLibPipeInstance* instance);
LIBPIPE_ITF void LibPipeDestroyInstance			(HLibPipeInstance instance);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend					(HLibPipeInstance instance, LibPipeMessageData* messages, LibPipeEleCnt count);
LIBPIPE_ITF void LibPipeReceive					(HLibPipeInstance instance, LibPipeCbContext context, LibPipeCbMessages cbMessages);

//======================================================================================================================
