//======================================================================================================================

#include "../PipeCore/PipeExtensionItf.h"
#include <iostream>

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders(PipeCbServiceProviders cbServiceProviders) {
    std::cout << "PipeExtensionGetServiceProviders for Websockets!" << std::endl;
	HPipeServiceProvider provs[10];
	EleCnt cnt = 10;
	cbServiceProviders(provs, cnt);
}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderGetType(HPipeServiceProvider provider, PipeCbZtStr cbType) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderGetSettingTypes(HPipeServiceProvider provider, PipeCbSettingTypes cbSettingTypes) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderCreateService(HPipeServiceProvider provider, ZtStr id, PipeServiceSetting* settings, EleCnt count, HPipeService* service) {
}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceProviderDestroyService(HPipeServiceProvider provider, HPipeService service) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetId(HPipeService service, PipeCbZtStr cbId) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetType(HPipeService service, PipeCbZtStr cbType) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceGetRoot(HPipeService service, PipeCbServiceNode cbServiceNode) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceSendMessages(HPipeService service, PipeMessage* messages, EleCnt count) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceReceiveMessages(HPipeService service, PipeCbMessages cbReceivedMessages) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetId(HPipeServiceNode node, PipeCbZtStr cbId) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetType(HPipeServiceNode node, PipeCbZtStr cbType) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetMessageTypes(HPipeServiceNode node, PipeCbMessageTypes cbMessageTypes) {

}

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeServiceNodeGetChildren(HPipeServiceNode node, PipeCbServiceNodes cbChildren) {

}

//----------------------------------------------------------------------------------------------------------------------


//======================================================================================================================
