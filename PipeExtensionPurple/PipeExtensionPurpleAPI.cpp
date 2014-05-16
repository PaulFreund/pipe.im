//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
using namespace std;

//======================================================================================================================

void publishError(tstring error) {
	if(PipeExtensionPurple::ErrorCallback != nullptr)
		PipeExtensionPurple::ErrorCallback(error.c_str());
}

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionSetErrorCallback(PipeExtensionCbErr cbError) {
	PipeExtensionPurple::ErrorCallback = cbError;
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes(PipeExtensionCbContext context, PipeExtensionCbStr cbServiceTypes) {
	try {
		cbServiceTypes(context, dumpArray(PipeExtensionPurple::ExtensionInstance.serviceTypes()).c_str());
	}
	catch(tstring error) { publishError(_T("PipeExtensionGetServiceTypes: ") + error); }
	catch(...) { publishError(_T("PipeExtensionGetServiceTypes: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate(PipeExtensionStr serviceType, PipeExtensionStr address, PipeExtensionStr path, PipeExtensionStr settings, HPipeExtensionService* service) {
	try {
		(*service) = reinterpret_cast<HPipeExtensionService>(PipeExtensionPurple::ExtensionInstance.create(serviceType, address, path, parseObject(settings)));
	}
	catch(tstring error) { publishError(_T("PipeExtensionServiceCreate: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServiceCreate: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy(HPipeExtensionService service) {
	try {
		PipeExtensionPurple::ExtensionInstance.destroy(reinterpret_cast<IPipeExtensionService*>(service));
	}
	catch(tstring error) { publishError(_T("PipeExtensionServiceDestroy: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServiceDestroy: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend(HPipeExtensionService service, PipeExtensionStr messages) {
	try {
		reinterpret_cast<IPipeExtensionService*>(service)->send(parseArray(messages));
	}
	catch(tstring error) { publishError(_T("PipeExtensionServiceSend: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServiceSend: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceReceive(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbStr cbMessages) {
	try {
		cbMessages(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->receive()).c_str());
	}
	catch(tstring error) { publishError(_T("PipeExtensionServiceReceive: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServiceReceive: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeChildren(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbChildNodes) {
	try {
		cbChildNodes(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->nodeChildren(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("PipeExtensionServiceGetNodeChildren: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServiceGetNodeChildren: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeCommandTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeCommandTypes) {
	try {
		cbNodeCommandTypes(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->nodeCommandTypes(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("PipeExtensionServiceGetNodeCommandTypes: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServiceGetNodeCommandTypes: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeMessageTypes) {
	try {
		cbNodeMessageTypes(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->nodeMessageTypes(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("PipeExtensionServiceGetNodeMessageTypes: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServiceGetNodeMessageTypes: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeInfo(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeInfo) {
	try {
		cbNodeInfo(context, dumpObject(reinterpret_cast<IPipeExtensionService*>(service)->nodeInfo(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("PipeExtensionServiceGetNodeInfo: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServiceGetNodeInfo: Unknown error")); }
}

//======================================================================================================================
