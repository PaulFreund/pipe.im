//======================================================================================================================

#include "../PipeCore/PipeExtensionItf.h"
#include <iostream>

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders(PipeServiceProvider providers[], COUNT count) {
    std::cout << "PipeExtensionGetServiceProviders for Websockets!" << std::endl;
    providers = nullptr;
    count = 2;
}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderGetType(const PipeServiceProvider provider, ZTSTRPTR type) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderGetSettingTypes(const PipeServiceProvider provider, PipeServiceSettingType* types[], COUNT count) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderCreateService(const PipeServiceProvider provider, ZTSTRPTR id, PipeServiceSetting* settings[], const COUNT count, PipeService service) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderDestroyService(const PipeServiceProvider provider, const PipeService service) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetId(const PipeService service, ZTSTRPTR id) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetType(const PipeService service, ZTSTRPTR type) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetRoot(const PipeService service, PipeServiceNode node) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceSendMessages(const PipeService service, const PipeMessage* messages[], const COUNT count) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceReceiveMessages(const PipeService service, PipeMessage* messages[], COUNT count) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetId(const PipeServiceNode node, ZTSTRPTR id) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetType(const PipeServiceNode node, ZTSTRPTR type) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetMessageTypes(const PipeServiceNode node, PipeMessageType* types[], COUNT count) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetChildren(const PipeServiceNode node, PipeServiceNode children[], COUNT count) {

}

//----------------------------------------------------------------------------------------------------------------------


//======================================================================================================================
