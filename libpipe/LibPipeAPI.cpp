//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
#include "PipeExtensionInstance.h"

using namespace std;
using namespace Poco;

//======================================================================================================================

static bool InitDone;
static tstring InstancePath;

static LibPipeCbContext ErrorCallbackContext;
static LibPipeCbErr ErrorCallback;

static shared_ptr<ServiceRoot> ServiceRootInstance;

//======================================================================================================================

void publishError(tstring error) {
	if(ErrorCallback != nullptr)
		ErrorCallback(ErrorCallbackContext, error.c_str());
}

//----------------------------------------------------------------------------------------------------------------------

void* loadExtensionSymbol(SharedLibrary& library, const tstring& name) {
	if(!library.hasSymbol(name))
		throw tstring(_T("LibPipeLoadExtensions: library ") + library.getPath() + _T(" is missing symbol ") + name);

	void* symbol = library.getSymbol(name);
	if(symbol == nullptr)
		throw tstring(_T("LibPipeLoadExtensions: library ") + library.getPath() + _T(" returned invalid symbol ") + name);

	return symbol;
}

//----------------------------------------------------------------------------------------------------------------------

void loadExtension(const tstring& path) {
	auto suffix = SharedLibrary::suffix();
	if(path.length() <= suffix.length())
		return;

	auto ext = path.substr(path.length() - suffix.length(), string::npos);
	if(!File(path).isFile() || ext != suffix)
		return;

	SharedLibrary library(path);
	if(!library.isLoaded())
		return;

	if(!library.hasSymbol(NamePipeExtensionGetServiceTypes))
		return;

	PipeExtensionFunctions extensionFunctions;
	try {
		extensionFunctions.fktPipeExtensionSetErrorCallback             = reinterpret_cast<FktPipeExtensionSetErrorCallback>            (loadExtensionSymbol(library, NamePipeExtensionSetErrorCallback             ));
		extensionFunctions.fktPipeExtensionSetPath                      = reinterpret_cast<FktPipeExtensionSetPath>                     (loadExtensionSymbol(library, NamePipeExtensionSetPath                      ));

		extensionFunctions.fktPipeExtensionGetServiceTypes              = reinterpret_cast<FktPipeExtensionGetServiceTypes>             (loadExtensionSymbol(library, NamePipeExtensionGetServiceTypes              ));
		extensionFunctions.fktPipeExtensionServiceCreate                = reinterpret_cast<FktPipeExtensionServiceCreate>               (loadExtensionSymbol(library, NamePipeExtensionServiceCreate                ));
		extensionFunctions.fktPipeExtensionServiceDestroy               = reinterpret_cast<FktPipeExtensionServiceDestroy>              (loadExtensionSymbol(library, NamePipeExtensionServiceDestroy               ));

		extensionFunctions.fktPipeExtensionServiceSend                  = reinterpret_cast<FktPipeExtensionServiceSend>                 (loadExtensionSymbol(library, NamePipeExtensionServiceSend                  ));
		extensionFunctions.fktPipeExtensionServiceReceive               = reinterpret_cast<FktPipeExtensionServiceReceive>              (loadExtensionSymbol(library, NamePipeExtensionServiceReceive               ));

		extensionFunctions.fktPipeExtensionServiceGetNodeChildren       = reinterpret_cast<FktPipeExtensionServiceGetNodeChildren>      (loadExtensionSymbol(library, NamePipeExtensionServiceGetNodeChildren       ));
		extensionFunctions.fktPipeExtensionServiceGetNodeCommandTypes   = reinterpret_cast<FktPipeExtensionServiceGetNodeCommandTypes>  (loadExtensionSymbol(library, NamePipeExtensionServiceGetNodeCommandTypes   ));
		extensionFunctions.fktPipeExtensionServiceGetNodeMessageTypes   = reinterpret_cast<FktPipeExtensionServiceGetNodeMessageTypes>  (loadExtensionSymbol(library, NamePipeExtensionServiceGetNodeMessageTypes   ));
		extensionFunctions.fktPipeExtensionServiceGetNodeInfo           = reinterpret_cast<FktPipeExtensionServiceGetNodeInfo>          (loadExtensionSymbol(library, NamePipeExtensionServiceGetNodeInfo           ));
	}
	catch(tstring error) { publishError(error); }
	catch(...) { return; }


	ServiceRoot::Extensions.push_back(make_shared<PipeExtensionInstance>(extensionFunctions, InstancePath));
}

//======================================================================================================================

LIBPIPE_ITF void LibPipeSetErrorCallback(LibPipeCbContext context, LibPipeCbErr cbError) {
	ErrorCallbackContext = context;
	ErrorCallback = cbError;
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSetPath(LibPipeStr path) {
	try {
		InstancePath = tstring(path);
		if(InstancePath.empty()) { throw tstring(_T("Empty path supplied")); }
	}
	catch(tstring error) { publishError(_T("LibPipeSetPath: ") + error); }
	catch(...) { publishError(_T("LibPipeSetPath: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeLoadExtensions(LibPipeStr path) {
	try {
		if(InstancePath.empty()) { throw tstring(_T("Empty or invalid path supplied")); }
		File extensionPath(path);

		if(!extensionPath.exists() || !extensionPath.canRead())
			return;

		if(extensionPath.isDirectory()) {
			for(DirectoryIterator it(extensionPath), itEnd; it != itEnd; ++it) {
				loadExtension(it->path());
			}
		}
		else {
			loadExtension(extensionPath.path());
		}
	}
	catch(tstring error) { publishError(_T("LibPipeLoadExtensions: ") + error); }
	catch(...) { publishError(_T("LibPipeLoadExtensions: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeGetServiceTypes(LibPipeCbContext context, LibPipeCbStr cbServiceTypes) {
	try {
		if(InstancePath.empty()) { throw tstring(_T("Empty or invalid path supplied")); }
		PipeArray serviceTypes;

		for(auto&& extension : ServiceRoot::Extensions) {
			auto extensionServiceTypes = extension->serviceTypes();
			for(auto&& extensionServiceType : *extensionServiceTypes) {
				serviceTypes.push_back(extensionServiceType);
			}
		}

		cbServiceTypes(context, dumpArray(serviceTypes).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeGetServiceTypes: ") + error); }
	catch(...) { publishError(_T("LibPipeGetServiceTypes: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeInit(LibPipeStr serviceTypes) {
	try {
		if(InstancePath.empty()) { throw tstring(_T("Empty or invalid path supplied")); }

		PipeObjectPtr settings = newObject();
		(*settings)[_T("service_types")] = *parseArray(serviceTypes);
		ServiceRootInstance = make_shared<ServiceRoot>(InstancePath, settings);

		InitDone = true;
	}
	catch(tstring error) { publishError(_T("LibPipeCreate: ") + error); }
	catch(...) { publishError(_T("LibPipeCreate: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend(LibPipeStr messages) {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		ServiceRootInstance->send(parseArray(messages));
	}
	catch(tstring error) { publishError(_T("LibPipeSend: ") + error); }
	catch(...) { publishError(_T("LibPipeSend: Unknown error")); }
}

LIBPIPE_ITF void LibPipeReceive(LibPipeCbContext context, LibPipeCbStr cbMessages) {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		cbMessages(context, dumpArray(ServiceRootInstance->receive()).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeReceive: ") + error); }
	catch(...) { publishError(_T("LibPipeReceive: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeGetNodeChildren(LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbChildNodes) {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		cbChildNodes(context, dumpArray(ServiceRootInstance->nodeChildren(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeGetNodeChildren: ") + error); }
	catch(...) { publishError(_T("LibPipeGetNodeChildren: Unknown error")); }
}

LIBPIPE_ITF void LibPipeGetNodeCommandTypes(LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbNodeCommandTypes) {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		cbNodeCommandTypes(context, dumpArray(ServiceRootInstance->nodeCommandTypes(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeGetNodeCommandTypes: ") + error); }
	catch(...) { publishError(_T("LibPipeGetNodeCommandTypes: Unknown error")); }
}

LIBPIPE_ITF void LibPipeGetNodeMessageTypes(LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbNodeMessageTypes) {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		cbNodeMessageTypes(context, dumpArray(ServiceRootInstance->nodeMessageTypes(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeGetNodeMessageTypes: ") + error); }
	catch(...) { publishError(_T("LibPipeGetNodeMessageTypes: Unknown error")); }
}

LIBPIPE_ITF void LibPipeGetNodeInfo(LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbNodeInfo) {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		cbNodeInfo(context, dumpObject(ServiceRootInstance->nodeInfo(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeGetNodeInfo: ") + error); }
	catch(...) { publishError(_T("LibPipeGetNodeInfo: Unknown error")); }
}

//======================================================================================================================
