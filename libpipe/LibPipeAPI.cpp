//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceRoot.h"
#include "PipeExtensionInstance.h"

using namespace std;

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

//void* loadExtensionSymbol(SharedLibrary& library, const tstring& name) {
//	if(!library.hasSymbol(name))
//		throw tstring(_T("LibPipeLoadExtensions: library ") + library.getPath() + _T(" is missing symbol ") + name);
//
//	void* symbol = library.getSymbol(name);
//	if(symbol == nullptr)
//		throw tstring(_T("LibPipeLoadExtensions: library ") + library.getPath() + _T(" returned invalid symbol ") + name);
//
//	return symbol;
//}

//----------------------------------------------------------------------------------------------------------------------

void loadExtension(const tstring& path) {
	/*
	auto suffix = SharedLibrary::suffix();
	if(path.length() <= suffix.length())
		return;

	auto ext = path.substr(path.length() - suffix.length(), string::npos);
	if(!fileIsFile(path) || ext != suffix)
		return;

	SharedLibrary library(path);
	if(!library.isLoaded())
		return;

	if(!library.hasSymbol(NamePipeExtensionGetServiceTypes))
		return;

	PipeExtensionFunctions extensionFunctions;
	try {
		extensionFunctions.fktPipeExtensionSetErrorCallback = reinterpret_cast<FktPipeExtensionSetErrorCallback>    (loadExtensionSymbol(library, NamePipeExtensionSetErrorCallback ));
		extensionFunctions.fktPipeExtensionSetPath          = reinterpret_cast<FktPipeExtensionSetPath>             (loadExtensionSymbol(library, NamePipeExtensionSetPath          ));

		extensionFunctions.fktPipeExtensionGetServiceTypes  = reinterpret_cast<FktPipeExtensionGetServiceTypes>     (loadExtensionSymbol(library, NamePipeExtensionGetServiceTypes  ));
		extensionFunctions.fktPipeExtensionServiceCreate    = reinterpret_cast<FktPipeExtensionServiceCreate>       (loadExtensionSymbol(library, NamePipeExtensionServiceCreate    ));
		extensionFunctions.fktPipeExtensionServiceDestroy   = reinterpret_cast<FktPipeExtensionServiceDestroy>      (loadExtensionSymbol(library, NamePipeExtensionServiceDestroy   ));

		extensionFunctions.fktPipeExtensionProcess          = reinterpret_cast<FktPipeExtensionProcess>             (loadExtensionSymbol(library, NamePipeExtensionProcess          ));

		extensionFunctions.fktPipeExtensionServicePush      = reinterpret_cast<FktPipeExtensionServicePush>         (loadExtensionSymbol(library, NamePipeExtensionServicePush      ));
		extensionFunctions.fktPipeExtensionServicePull      = reinterpret_cast<FktPipeExtensionServicePull>         (loadExtensionSymbol(library, NamePipeExtensionServicePull      ));
	}
	catch(tstring error) { publishError(error); }
	catch(...) { return; }


	ServiceRoot::Extensions.push_back(make_shared<PipeExtensionInstance>(extensionFunctions, InstancePath));
	*/
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
		tstring extensionPath(path);

		if(!fileExists(extensionPath) || !fileCanRead(extensionPath))
			return;

		if(fileIsDirectory(extensionPath)) {
			for(auto&& file: fileDirectoryContents(extensionPath)) {
				loadExtension(file);
			}
		}
		else {
			loadExtension(extensionPath);
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

LIBPIPE_ITF void LibPipeProcess() {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		ServiceRootInstance->process();
	}
	catch(tstring error) { publishError(_T("LibPipeProcess: ") + error); }
	catch(...) { publishError(_T("LibPipeProcess: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipePush(LibPipeStr messages) {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		ServiceRootInstance->addIncoming(parseArray(messages));
	}
	catch(tstring error) { publishError(_T("LibPipePush: ") + error); }
	catch(...) { publishError(_T("LibPipePush: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipePull(LibPipeCbContext context, LibPipeCbStr cbMessages) {
	try {
		if(!InitDone) { throw tstring(_T("LibPipe not initialized")); }
		cbMessages(context, dumpArray(ServiceRootInstance->getOutgoing()).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipePull: ") + error); }
	catch(...) { publishError(_T("LibPipePull: Unknown error")); }
}

//======================================================================================================================
