//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
#include "PurpleInterface.h"
using namespace std;
using namespace Poco;

//======================================================================================================================

void publishError(tstring error) {
	if(PipeExtensionPurple::ErrorCallback != nullptr)
		PipeExtensionPurple::ErrorCallback(error.c_str());
}

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionProcess() {
	try {
		PipeExtensionPurple::ExtensionInstance.process();
	}
	catch(tstring error) { publishError(_T("PipeExtensionProcess: ") + error); }
	catch(...) { publishError(_T("PipeExtensionProcess: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionSetErrorCallback(PipeExtensionCbErr cbError) {
	PipeExtensionPurple::ErrorCallback = cbError;
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionSetPath(PipeExtensionStr path) {
	try {
		if(tstring(path).empty()) { throw tstring(_T("Empty path supplied")); }

		Path extensionDataPath;
		extensionDataPath.parseDirectory(tstring(path));
		extensionDataPath.append(_T("purple"));

		PipeExtensionPurple::ExtensionInstancePath = extensionDataPath.toString();

		PipeExtensionPurple::Purple = make_shared<PurpleInterface>(&PipeExtensionPurple::ExtensionInstance, PipeExtensionPurple::ExtensionInstancePath);
	}
	catch(tstring error) { publishError(_T("PipeExtensionSetPath: ") + error); }
	catch(...) { publishError(_T("PipeExtensionSetPath: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes(PipeExtensionCbContext context, PipeExtensionCbStr cbServiceTypes) {
	try {
		if(PipeExtensionPurple::ExtensionInstancePath.empty()) { throw tstring(_T("Empty or invalid path supplied")); }
		cbServiceTypes(context, dumpArray(PipeExtensionPurple::ExtensionInstance.serviceTypes()).c_str());
	}
	catch(tstring error) { publishError(_T("PipeExtensionGetServiceTypes: ") + error); }
	catch(...) { publishError(_T("PipeExtensionGetServiceTypes: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate(PipeExtensionStr serviceType, PipeExtensionStr address, PipeExtensionStr settings, HPipeExtensionService* service) {
	try {
		if(PipeExtensionPurple::ExtensionInstancePath.empty()) { throw tstring(_T("Empty or invalid path supplied")); }
		(*service) = reinterpret_cast<HPipeExtensionService>(PipeExtensionPurple::ExtensionInstance.create(serviceType, address, PipeExtensionPurple::ExtensionInstancePath, parseObject(settings)));
	}
	catch(tstring error) { service = nullptr; publishError(_T("PipeExtensionServiceCreate: ") + error); }
	catch(...) { service = nullptr; publishError(_T("PipeExtensionServiceCreate: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy(HPipeExtensionService service) {
	try {
		if(PipeExtensionPurple::ExtensionInstancePath.empty()) { throw tstring(_T("Empty or invalid path supplied")); }
		PipeExtensionPurple::ExtensionInstance.destroy(reinterpret_cast<IPipeExtensionService*>(service));
	}
	catch(tstring error) { publishError(_T("PipeExtensionServiceDestroy: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServiceDestroy: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServicePush(HPipeExtensionService service, PipeExtensionStr messages) {
	try {
		reinterpret_cast<IPipeExtensionService*>(service)->push(parseArray(messages));
	}
	catch(tstring error) { publishError(_T("PipeExtensionServicePush: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServicePush: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServicePull(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbStr cbMessages) {
	try {
		cbMessages(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->pull()).c_str());
	}
	catch(tstring error) { publishError(_T("PipeExtensionServicePull: ") + error); }
	catch(...) { publishError(_T("PipeExtensionServicePull: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

//PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeChildren(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbChildNodes) {
//	try {
//		cbChildNodes(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->nodeChildren(tstring(address))).c_str());
//	}
//	catch(tstring error) { publishError(_T("PipeExtensionServiceGetNodeChildren: ") + error); }
//	catch(...) { publishError(_T("PipeExtensionServiceGetNodeChildren: Unknown error")); }
//}
//
////----------------------------------------------------------------------------------------------------------------------
//
//PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeCommandTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeCommandTypes) {
//	try {
//		cbNodeCommandTypes(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->nodeCommandTypes(tstring(address))).c_str());
//	}
//	catch(tstring error) { publishError(_T("PipeExtensionServiceGetNodeCommandTypes: ") + error); }
//	catch(...) { publishError(_T("PipeExtensionServiceGetNodeCommandTypes: Unknown error")); }
//}
//
////----------------------------------------------------------------------------------------------------------------------
//
//PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeMessageTypes) {
//	try {
//		cbNodeMessageTypes(context, dumpArray(reinterpret_cast<IPipeExtensionService*>(service)->nodeMessageTypes(tstring(address))).c_str());
//	}
//	catch(tstring error) { publishError(_T("PipeExtensionServiceGetNodeMessageTypes: ") + error); }
//	catch(...) { publishError(_T("PipeExtensionServiceGetNodeMessageTypes: Unknown error")); }
//}
//
////----------------------------------------------------------------------------------------------------------------------
//
//PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeInfo(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeInfo) {
//	try {
//		cbNodeInfo(context, dumpObject(reinterpret_cast<IPipeExtensionService*>(service)->nodeInfo(tstring(address))).c_str());
//	}
//	catch(tstring error) { publishError(_T("PipeExtensionServiceGetNodeInfo: ") + error); }
//	catch(...) { publishError(_T("PipeExtensionServiceGetNodeInfo: Unknown error")); }
//}

//======================================================================================================================
