//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
using namespace std;

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes(PipeExtensionCbContext context, PipeExtensionCbStr cbServiceTypes) {
	auto&& types = PipeExtensionPurple::ExtensionInstance.serviceTypes();
	cbServiceTypes(context, PipeJson(*types).dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypeSettings(PipeExtensionCbContext context, PipeExtensionStr serviceType, PipeExtensionCbStr cbServiceTypeSettings) {
	auto&& typeSettings = PipeExtensionPurple::ExtensionInstance.serviceTypeSettings(serviceType);
	cbServiceTypeSettings(context, PipeJson(*typeSettings).dump().c_str());
}


//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate(PipeExtensionStr serviceType, PipeExtensionStr address, PipeExtensionStr path, PipeExtensionStr settings, HPipeExtensionService* service) {
	PipeJsonObject settingsData = std::make_shared<PipeJsonObjectData>(PipeJson::parse(settings).object_items());
	(*service) = reinterpret_cast<HPipeExtensionService>(PipeExtensionPurple::ExtensionInstance.create(serviceType, address, path, settingsData));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy(HPipeExtensionService service) {
	PipeExtensionPurple::ExtensionInstance.destroy(reinterpret_cast<IPipeExtensionService*>(service));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend(HPipeExtensionService service, PipeExtensionStr messages) {
	PipeJsonArray messagesData = std::make_shared<PipeJsonArrayData>(PipeJson::parse(messages).array_items());
	reinterpret_cast<IPipeExtensionService*>(service)->send(messagesData);
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceReceive(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbStr cbMessages) {
	auto&& messages = reinterpret_cast<IPipeExtensionService*>(service)->receive();
	cbMessages(context, PipeJson(*messages).dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeChildren(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbChildNodes) {
	auto&& children = reinterpret_cast<IPipeExtensionService*>(service)->nodeChildren(tstring(address));
	cbChildNodes(context, PipeJson(*children).dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeMessageTypes) {
	auto&& messageTypes = reinterpret_cast<IPipeExtensionService*>(service)->nodeMessageTypes(tstring(address));
	cbNodeMessageTypes(context, PipeJson(*messageTypes).dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeInfo(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeInfo) {
	auto&& info = reinterpret_cast<IPipeExtensionService*>(service)->nodeInfo(tstring(address));
	cbNodeInfo(context, PipeJson(*info).dump().c_str());
}

//======================================================================================================================
