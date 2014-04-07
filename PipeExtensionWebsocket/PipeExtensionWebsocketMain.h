//======================================================================================================================

#include "../PipeCore/PipeExtensionItf.h"


//======================================================================================================================

#ifdef WIN32
    #ifdef PIPE_EXTENSION_WEBSOCKET_EXPORTS
        #define PIPE_EXTENSION_WEBSOCKET_API extern "C" __declspec(dllexport) 
    #else
        #define PIPE_EXTENSION_WEBSOCKET_API extern "C" __declspec(dllimport) 
    #endif
#else
    #pragma warning("library export not defined for this OS")
    #define PIPE_EXTENSION_WEBSOCKET_API extern
#endif

//======================================================================================================================

PIPE_EXTENSION_WEBSOCKET_API PtrExtension InitPipeExtension();

//======================================================================================================================
