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

typedef const char*     LibPipeStr;

typedef void*           LibPipeCbContext;
typedef void            (*LibPipeCbErr)(LibPipeCbContext, LibPipeStr);
typedef void            (*LibPipeCbStr)(LibPipeCbContext, LibPipeStr);

//======================================================================================================================

LIBPIPE_ITF void LibPipeSetErrorCallback    (LibPipeCbContext context, LibPipeCbErr cbError);
LIBPIPE_ITF void LibPipeSetPath             (LibPipeStr path);
LIBPIPE_ITF void LibPipeLoadExtensions      (LibPipeStr path);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeGetServiceTypes     (LibPipeCbContext context, LibPipeCbStr cbServiceTypes);
LIBPIPE_ITF void LibPipeInit                (LibPipeStr serviceTypes);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend                (LibPipeStr messages);
LIBPIPE_ITF void LibPipeReceive             (LibPipeCbContext context, LibPipeCbStr cbMessages);

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeGetNodeChildren     (LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbChildNodes);
LIBPIPE_ITF void LibPipeGetNodeCommandTypes (LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbNodeCommandTypes);
LIBPIPE_ITF void LibPipeGetNodeMessageTypes (LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbNodeMessageTypes);
LIBPIPE_ITF void LibPipeGetNodeInfo         (LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbNodeInfo);

//======================================================================================================================
