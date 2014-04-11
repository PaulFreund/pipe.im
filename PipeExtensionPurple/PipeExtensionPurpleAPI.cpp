//======================================================================================================================

#include <libpipe/PipeExtensionAPI.h>
#include <iostream>

//======================================================================================================================
/*
//----------------------------------------------------------------------------------------------------------------------
PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders(PipeExtensionCbContext context, PipeExtensionCbServiceProviders cbServiceProviders) {
	HPipeExtensionServiceProvider provs[10];
	PipeExtensionEleCnt cnt = 10;
	cbServiceProviders(context, provs, cnt);
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetType(HPipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderGetSettingTypes(HPipeExtensionServiceProvider provider, PipeExtensionCbContext context, PipeExtensionCbSettingTypes cbSettingTypes) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderCreateService(HPipeExtensionServiceProvider provider, PipeExtensionStr id, PipeExtensionServiceSettingData* settings, PipeExtensionEleCnt count, HPipeExtensionService* service) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceProviderDestroyService(HPipeExtensionServiceProvider provider, HPipeExtensionService service) {

}


//----------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetId(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetType(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetRoot(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbServiceNode cbServiceNode) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceSendMessages(HPipeExtensionService service, PipeExtensionMessageData* messages, PipeExtensionEleCnt count) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceReceiveMessages(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbReceivedMessages) {

}


//----------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetAddress(HPipeExtensionService service, HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbId) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetType(HPipeExtensionService service, HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbZtStr cbType) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetMessageTypes(HPipeExtensionService service, HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbMessageTypes cbMessageTypes) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceNodeGetChildren(HPipeExtensionService service, HPipeExtensionServiceNode node, PipeExtensionCbContext context, PipeExtensionCbServiceNodes cbChildren) {

}


//======================================================================================================================
*/