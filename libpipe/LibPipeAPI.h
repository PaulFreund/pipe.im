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

typedef const char*		LibPipeStr;
typedef void*			HLibPipe;

typedef void* LibPipeCbContext;
typedef void(*LibPipeCbStr)(LibPipeCbContext, LibPipeStr);

//======================================================================================================================

LIBPIPE_ITF void LibPipeLoadExtensions          (LibPipeStr path);
LIBPIPE_ITF void LibPipeGetServiceTypes         (LibPipeCbContext context, LibPipeCbStr cbServiceTypes);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeCreate                  (LibPipeStr path, LibPipeStr serviceTypes, HLibPipe* instance);
LIBPIPE_ITF void LibPipeDestroy                 (HLibPipe instance);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend                    (HLibPipe instance, LibPipeStr messages);
LIBPIPE_ITF void LibPipeReceive                 (HLibPipe instance, LibPipeCbContext context, LibPipeCbStr cbMessages);

//======================================================================================================================
