//======================================================================================================================

#include "PipeExtensionWebsocketMain.h"
#include <iostream>
using namespace Pipe;
//======================================================================================================================

PIPE_EXTENSION_WEBSOCKET_API PtrExtension InitPipeExtension() {
    std::cout << "Websocket plugin init" << std::endl;

    return nullptr;
}

//======================================================================================================================
