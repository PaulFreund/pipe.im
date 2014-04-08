//======================================================================================================================

#pragma once

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
typedef uint64_t		LibPipeInstance;

//======================================================================================================================

struct LibPipeMessageData {
	unsigned int dataSize;
	unsigned char* data;
};

//======================================================================================================================

typedef void(*LibPipeCbServiceProviders)(LibPipeStr*, LibPipeEleCnt);
typedef void(*LibPipeCbMessages)(LibPipeMessageData*, LibPipeEleCnt);

//======================================================================================================================

LIBPIPE_ITF void LibPipeLoadExtensions			(LibPipeStr path);
LIBPIPE_ITF void LibPipeGetServiceProviders		(LibPipeCbServiceProviders cbServiceProviders);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeCreateInstance			(LibPipeStr path, LibPipeStr* serviceProviders, LibPipeEleCnt serviceProviderCount, LibPipeInstance* instance);
LIBPIPE_ITF void LibPipeDestroyInstance			(LibPipeInstance instance);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend					(LibPipeInstance instance, LibPipeMessageData* messages, LibPipeEleCnt count);
LIBPIPE_ITF void LibPipeReceive					(LibPipeInstance instance, LibPipeCbMessages cbMessages);

//======================================================================================================================
