//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
using namespace std;

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes(PipeExtensionCbContext context, PipeExtensionCbStr cbServiceTypes) {
	auto&& types = PipeExtensionPurple::ExtensionInstance.serviceTypes();
	cbServiceTypes(context, types.c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypeSettings(PipeExtensionCbContext context, PipeExtensionStr serviceType, PipeExtensionCbStr cbServiceTypeSettings) {
	auto&& typeSettings = PipeExtensionPurple::ExtensionInstance.serviceTypeSettings(serviceType);
	cbServiceTypeSettings(context, typeSettings.c_str());
}


//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate(PipeExtensionStr serviceType, PipeExtensionStr id, PipeExtensionStr path, PipeExtensionStr settings, HPipeExtensionService* service) {
	(*service) = reinterpret_cast<HPipeExtensionService>(PipeExtensionPurple::ExtensionInstance.create(serviceType, id, path, settings));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy(HPipeExtensionService service) {
	PipeExtensionPurple::ExtensionInstance.destroy(reinterpret_cast<IPipeExtensionService*>(service));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend(HPipeExtensionService service, PipeExtensionStr message) {
	reinterpret_cast<IPipeExtensionService*>(service)->send(message);
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceReceive(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbStr cbMessages) {
	auto&& messages = reinterpret_cast<IPipeExtensionService*>(service)->receive();
	cbMessages(context, messages.c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeChildren(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbChildNodes) {
	auto&& children = reinterpret_cast<IPipeExtensionService*>(service)->nodeChildren(tstring(address));
	cbChildNodes(context, children.c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeMessageTypes) {
	auto&& messageTypes = reinterpret_cast<IPipeExtensionService*>(service)->nodeMessageTypes(tstring(address));
	cbNodeMessageTypes(context, messageTypes.c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeInfo(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeInfo) {
	auto&& info = reinterpret_cast<IPipeExtensionService*>(service)->nodeInfo(tstring(address));
	cbNodeInfo(context, info.c_str());
}

//======================================================================================================================
