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
	#define LIBPIPE_ITF extern "C"
#endif

//======================================================================================================================

#include <stdint.h>

//======================================================================================================================
typedef const char*		LibPipeStr;
typedef uint64_t		LibPipeEleCnt;
typedef uint64_t		HLibPipe;

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
typedef void(*LibPipeCbServiceTypes)(LibPipeCbContext, LibPipeStr*, LibPipeEleCnt);
typedef void(*LibPipeCbMessages)(LibPipeCbContext, LibPipeMessageData*, LibPipeEleCnt);

//======================================================================================================================

LIBPIPE_ITF void LibPipeLoadExtensions			(LibPipeStr path);
LIBPIPE_ITF void LibPipeGetServiceTypes			(LibPipeCbContext context, LibPipeCbServiceTypes cbServiceTypes);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeCreate					(LibPipeStr path, LibPipeStr* serviceTypes, LibPipeEleCnt serviceTypeCount, HLibPipe* instance);
LIBPIPE_ITF void LibPipeDestroy					(HLibPipe instance);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend					(HLibPipe instance, LibPipeMessageData* messages, LibPipeEleCnt count);
LIBPIPE_ITF void LibPipeReceive					(HLibPipe instance, LibPipeCbContext context, LibPipeCbMessages cbMessages);

//======================================================================================================================
