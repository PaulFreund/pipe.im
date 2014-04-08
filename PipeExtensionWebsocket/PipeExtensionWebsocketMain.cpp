//======================================================================================================================

#include "../PipeCore/PipeExtensionItf.h"
#include <iostream>

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders(void(*cbServiceProviders)(HPipeServiceProvider*, Count)) {
    std::cout << "PipeExtensionGetServiceProviders for Websockets!" << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderGetType(HPipeServiceProvider provider, void(*cbType)(ZtStr)) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderGetSettingTypes(HPipeServiceProvider provider, void(*cbSettingTypes)(PipeServiceSettingType*, Count)) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderCreateService(HPipeServiceProvider provider, ZtStr id, PipeServiceSetting* settings, Count count, HPipeService* service) {
}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderDestroyService(HPipeServiceProvider provider, HPipeService service) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetId(HPipeService service, void(*cbId)(ZtStr)) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetType(HPipeService service, void(*cbType)(ZtStr)) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetRoot(HPipeService service, void(*cbRoot)(HPipeServiceNode)) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceSendMessages(HPipeService service, PipeMessage* messages, Count count) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceReceiveMessages(HPipeService service, void(*cbReceiveMessages)(PipeMessage*, Count)) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetId(HPipeServiceNode node, void(*cbId)(ZtStr)) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetType(HPipeServiceNode node, void(*cbType)(ZtStr)) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetMessageTypes(HPipeServiceNode node, void(*cbMessageTypes)(PipeMessageType*, Count)) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetChildren(HPipeServiceNode node, void(*cbChildren)(HPipeServiceNode*, Count)) {

}

//----------------------------------------------------------------------------------------------------------------------


//======================================================================================================================
