//======================================================================================================================

#include <libpipe/PipeExtensionItf.h>
#include <iostream>

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders(PipeExtensionCbServiceProviders cbServiceProviders) {
    std::cout << "PipeExtensionGetServiceProviders for Websockets!" << std::endl;
	PipeExtensionServiceProvider provs[10];
	PipeExtensionEleCnt cnt = 10;
	cbServiceProviders(provs, cnt);
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetType(PipeExtensionServiceProvider provider, PipeExtensionCbZtStr cbType) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetSettingTypes(PipeExtensionServiceProvider provider, PipeExtensionCbSettingTypes cbSettingTypes) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderCreateService(PipeExtensionServiceProvider provider, PipeExtensionStr id, PipeExtensionServiceSetting* settings, PipeExtensionEleCnt count, PipeExtensionService* service) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderDestroyService(PipeExtensionServiceProvider provider, PipeExtensionService service) {

}


//----------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetId(PipeExtensionService service, PipeExtensionCbZtStr cbId) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetType(PipeExtensionService service, PipeExtensionCbZtStr cbType) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetRoot(PipeExtensionService service, PipeExtensionCbServiceNode cbServiceNode) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceSendMessages(PipeExtensionService service, PipeExtensionMessage* messages, PipeExtensionEleCnt count) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceReceiveMessages(PipeExtensionService service, PipeExtensionCbMessages cbReceivedMessages) {

}


//----------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetId(PipeExtensionServiceNode node, PipeExtensionCbZtStr cbId) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetType(PipeExtensionServiceNode node, PipeExtensionCbZtStr cbType) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetMessageTypes(PipeExtensionServiceNode node, PipeExtensionCbMessageTypes cbMessageTypes) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetChildren(PipeExtensionServiceNode node, PipeExtensionCbServiceNodes cbChildren) {

}


//======================================================================================================================
