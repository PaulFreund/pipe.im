//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
using namespace std;

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes(PipeExtensionCbContext context, PipeExtensionCbStr cbServiceTypes) {
	cbServiceTypes(context, dumpArray(PipeExtensionPurple::ExtensionInstance.serviceTypes()).c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate(PipeExtensionStr serviceType, PipeExtensionStr address, PipeExtensionStr path, PipeExtensionStr settings, HPipeExtensionService* service) {
	(*service) = reinterpret_cast<HPipeExtensionService>(PipeExtensionPurple::ExtensionInstance.create(serviceType, address, path, parseObject(settings)));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy(HPipeExtensionService service) {
	PipeExtensionPurple::ExtensionInstance.destroy(reinterpret_cast<IPipeExtensionService*>(service));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend(HPipeExtensionService service, PipeExtensionStr messages) {
	reinterpret_cast<IPipeExtensionService*>(service)->send(parseArray(messages));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceReceive(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbStr cbMessages) {
	cbMessages(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->receive()).c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeChildren(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbChildNodes) {
	cbChildNodes(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->nodeChildren(tstring(address))).c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeCommandTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeCommandTypes) {
	cbNodeCommandTypes(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->nodeCommandTypes(tstring(address))).c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeMessageTypes) {
	cbNodeMessageTypes(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->nodeMessageTypes(tstring(address))).c_str());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeInfo(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeInfo) {
	cbNodeInfo(context, dumpObject(reinterpret_cast<IPipeExtensionService*>(service)->nodeInfo(tstring(address))).c_str());
}

//======================================================================================================================
