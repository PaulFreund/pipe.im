//======================================================================================================================

#pragma once

//======================================================================================================================

#ifdef WIN32
	#ifdef PIPE_EXTENSION_EXPORTS
		#define PIPE_EXTENSION_ITF extern "C" __declspec(dllexport) 
	#else
		#define PIPE_EXTENSION_ITF extern "C" __declspec(dllimport) 
	#endif
#else
	#define PIPE_EXTENSION_ITF extern "C"
#endif

//======================================================================================================================

typedef void*           HPipeExtensionService;
typedef const char*     PipeExtensionStr;

typedef void*           PipeExtensionCbContext;
typedef void            (*PipeExtensionCbErr)(PipeExtensionStr);
typedef void            (*PipeExtensionCbStr)(PipeExtensionCbContext, PipeExtensionStr);

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionSetErrorCallback           (PipeExtensionCbErr cbError);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes            (PipeExtensionCbContext context, PipeExtensionCbStr cbServiceTypes);

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate              (PipeExtensionStr serviceType, PipeExtensionStr address, PipeExtensionStr path, PipeExtensionStr settings, HPipeExtensionService* service);
PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy             (HPipeExtensionService service);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend                (HPipeExtensionService service, PipeExtensionStr messages);
PIPE_EXTENSION_ITF void PipeExtensionServiceReceive             (HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbStr cbMessages);

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeChildren     (HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbChildNodes);
PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeCommandTypes (HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeCommandTypes);
PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes (HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeMessageTypes);
PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeInfo         (HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeInfo);

//======================================================================================================================
