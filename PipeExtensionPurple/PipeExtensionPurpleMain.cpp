//======================================================================================================================

#include <libpipe/PipeExtensionItf.h>
#include <iostream>

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders(PipeExtensionCbContext context, PipeExtensionCbServiceProviders cbServiceProviders) {
    std::cout << "PipeExtensionGetServiceProviders for Websockets!" << std::endl;
	PipeExtensionServiceProvider provs[10];
	PipeExtensionEleCnt cnt = 10;
	cbServiceProviders(context, provs, cnt);
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetType(PipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetSettingTypes(PipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbSettingTypes cbSettingTypes) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderCreateService(PipeExtensionServiceProvider provider, PipeExtensionStr id, PipeExtensionServiceSetting* settings, PipeExtensionEleCnt count, PipeExtensionService* service) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderDestroyService(PipeExtensionServiceProvider provider, PipeExtensionService service) {

}


//----------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetId(PipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetType(PipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetRoot(PipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbServiceNode cbServiceNode) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceSendMessages(PipeExtensionService service, PipeExtensionMessage* messages, PipeExtensionEleCnt count) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceReceiveMessages(PipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbReceivedMessages) {

}


//----------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetId(PipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetType(PipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetMessageTypes(PipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbMessageTypes cbMessageTypes) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetChildren(PipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbServiceNodes cbChildren) {

}


//======================================================================================================================
