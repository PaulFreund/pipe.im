//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
using namespace std;

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes(PipeExtensionCbContext context, PipeExtensionCbStr cbServiceTypes) {
	auto&& types = PipeExtensionPurple::ExtensionInstance.serviceTypes();
	cbServiceTypes(context, PipeJSON(types).dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypeSettings(PipeExtensionCbContext context, PipeExtensionStr serviceType, PipeExtensionCbStr cbServiceTypeSettings) {
	auto&& typeSettings = PipeExtensionPurple::ExtensionInstance.serviceTypeSettings(serviceType);
	cbServiceTypeSettings(context, PipeJSON(typeSettings).dump().c_str());
}


//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate(PipeExtensionStr serviceType, PipeExtensionStr address, PipeExtensionStr path, PipeExtensionStr settings, HPipeExtensionService* service) {
	PipeJSON::object settingsData = PipeJSON::parse(settings).object_items(); // TODO
	(*service) = reinterpret_cast<HPipeExtensionService>(PipeExtensionPurple::ExtensionInstance.create(serviceType, address, path, settingsData));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy(HPipeExtensionService service) {
	PipeExtensionPurple::ExtensionInstance.destroy(reinterpret_cast<IPipeExtensionService*>(service));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend(HPipeExtensionService service, PipeExtensionStr message) {
	PipeJSON::object messageData = PipeJSON::parse(message).object_items(); // TODO
	reinterpret_cast<IPipeExtensionService*>(service)->send(messageData);
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceReceive(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbStr cbMessages) {
	auto&& messages = reinterpret_cast<IPipeExtensionService*>(service)->receive();
	cbMessages(context, PipeJSON(messages).dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeChildren(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbChildNodes) {
	auto&& children = reinterpret_cast<IPipeExtensionService*>(service)->nodeChildren(tstring(address));
	cbChildNodes(context, PipeJSON(children).dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeMessageTypes) {
	auto&& messageTypes = reinterpret_cast<IPipeExtensionService*>(service)->nodeMessageTypes(tstring(address));
	cbNodeMessageTypes(context, PipeJSON(messageTypes).dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeInfo(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeInfo) {
	auto&& info = reinterpret_cast<IPipeExtensionService*>(service)->nodeInfo(tstring(address));
	cbNodeInfo(context, PipeJSON(info).dump().c_str());
}

//======================================================================================================================
