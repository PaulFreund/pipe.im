//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
using namespace std;

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes(PipeExtensionCbContext context, PipeExtensionCbStr cbServiceTypes) {
	auto&& types = PipeExtensionPurple::ExtensionInstance.serviceTypes();
	cbServiceTypes(context, types.dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypeSettings(PipeExtensionCbContext context, PipeExtensionStr serviceType, PipeExtensionCbStr cbServiceTypeSettings) {
	auto&& typeSettings = PipeExtensionPurple::ExtensionInstance.serviceTypeSettings(serviceType);
	cbServiceTypeSettings(context, typeSettings.dump().c_str());
}


//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate(PipeExtensionStr serviceType, PipeExtensionStr id, PipeExtensionStr path, PipeExtensionStr settings, HPipeExtensionService* service) {
	PipeJSON settingsData;
	settingsData.parse(settings, tstring());
	(*service) = reinterpret_cast<HPipeExtensionService>(PipeExtensionPurple::ExtensionInstance.create(serviceType, id, path, settingsData));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy(HPipeExtensionService service) {
	PipeExtensionPurple::ExtensionInstance.destroy(reinterpret_cast<IPipeExtensionService*>(service));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend(HPipeExtensionService service, PipeExtensionStr message) {
	PipeJSON messageData;
	messageData.parse(message, tstring());
	reinterpret_cast<IPipeExtensionService*>(service)->send(messageData);
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceReceive(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbStr cbMessages) {
	auto&& messages = reinterpret_cast<IPipeExtensionService*>(service)->receive();
	cbMessages(context, messages.dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeChildren(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbChildNodes) {
	auto&& children = reinterpret_cast<IPipeExtensionService*>(service)->nodeChildren(tstring(address));
	cbChildNodes(context, children.dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeMessageTypes) {
	auto&& messageTypes = reinterpret_cast<IPipeExtensionService*>(service)->nodeMessageTypes(tstring(address));
	cbNodeMessageTypes(context, messageTypes.dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeInfo(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeInfo) {
	auto&& info = reinterpret_cast<IPipeExtensionService*>(service)->nodeInfo(tstring(address));
	cbNodeInfo(context, info.dump().c_str());
}

//======================================================================================================================
