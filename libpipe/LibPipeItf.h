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

typedef unsigned char*	LibPipeZtStr;
typedef uint64_t		LibPipeEleCnt;
typedef uint64_t		LibPipeInstance;

//======================================================================================================================

struct LibPipeMessageData {
	unsigned int dataSize;
	unsigned char* data;
};

//======================================================================================================================

typedef void(*LibPipeCbServiceProviders)(LibPipeZtStr*, LibPipeEleCnt);
typedef void(*LibPipeCbMessages)(LibPipeMessageData*, LibPipeEleCnt);

//======================================================================================================================

LIBPIPE_ITF void LibPipeLoadExtension			(LibPipeZtStr path);
LIBPIPE_ITF void LibPipeGetServiceProviders		(LibPipeCbServiceProviders);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeCreateInstance			(LibPipeZtStr path, LibPipeZtStr* serviceProviders, LibPipeEleCnt serviceProviderCount, LibPipeInstance* instance);
LIBPIPE_ITF void LibPipeDestroyInstance			(LibPipeInstance instance);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend					(LibPipeInstance instance, LibPipeMessageData* messages, LibPipeEleCnt count);
LIBPIPE_ITF void LibPipeReceive					(LibPipeInstance instance, LibPipeCbMessages);

//======================================================================================================================
