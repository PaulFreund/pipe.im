//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

using namespace std;
using namespace Poco;

//======================================================================================================================

void publishError(tstring error) {
	if(LibPipe::ErrorCallback != nullptr)
		LibPipe::ErrorCallback(error.c_str());
}

//----------------------------------------------------------------------------------------------------------------------

void* loadExtensionSymbol(SharedLibrary& library, const tstring& name) {
	if(!library.hasSymbol(name))
		throw;

	void* symbol = library.getSymbol(name);
	if(symbol == nullptr)
		throw;

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
	catch(...) { return; }

	LibPipe::Extensions.push_back(make_shared<PipeExtensionInstance>(extensionFunctions));
}

//======================================================================================================================

LIBPIPE_ITF void LibPipeSetErrorCallback(LibPipeCbErr cbError) {
	LibPipe::ErrorCallback = cbError;
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeLoadExtensions(LibPipeStr path) {
	try {
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
		PipeArray serviceTypes;

		for(auto&& extension : LibPipe::Extensions) {
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

LIBPIPE_ITF void LibPipeCreate(LibPipeStr path, LibPipeStr serviceTypes, HLibPipe* instance) {
	try {
		LibPipe::Instances.push_back(make_shared<LibPipe>(tstring(path), parseArray(serviceTypes)));
		(*instance) = reinterpret_cast<HLibPipe>(LibPipe::Instances.back().get());
	}
	catch(tstring error) { publishError(_T("LibPipeCreate: ") + error); }
	catch(...) { publishError(_T("LibPipeCreate: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeDestroy(HLibPipe instance) {
	// TODO: Improve
	try {
		LibPipe* pInstance = reinterpret_cast<LibPipe*>(instance);
		for(auto it = begin(LibPipe::Instances); it != end(LibPipe::Instances); it++) {
			if((*it).get() == pInstance) {
				LibPipe::Instances.erase(it);
				return;
			}
		}
	}
	catch(tstring error) { publishError(_T("LibPipeDestroy: ") + error); }
	catch(...) { publishError(_T("LibPipeDestroy: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend(HLibPipe instance, LibPipeStr messages) {
	try {
		reinterpret_cast<LibPipe*>(instance)->send(parseArray(messages));
	}
	catch(tstring error) { publishError(_T("LibPipeSend: ") + error); }
	catch(...) { publishError(_T("LibPipeSend: Unknown error")); }
}

LIBPIPE_ITF void LibPipeReceive(HLibPipe instance, LibPipeCbContext context, LibPipeCbStr cbMessages) {
	try {
		cbMessages(context, dumpArray(reinterpret_cast<LibPipe*>(instance)->receive()).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeReceive: ") + error); }
	catch(...) { publishError(_T("LibPipeReceive: Unknown error")); }
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeGetNodeChildren(HLibPipe instance, LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbChildNodes) {
	try {
		cbChildNodes(context, dumpArray(reinterpret_cast<LibPipe*>(instance)->nodeChildren(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeGetNodeChildren: ") + error); }
	catch(...) { publishError(_T("LibPipeGetNodeChildren: Unknown error")); }
}

LIBPIPE_ITF void LibPipeGetNodeCommandTypes(HLibPipe instance, LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbNodeCommandTypes) {
	try {
		cbNodeCommandTypes(context, dumpArray(reinterpret_cast<LibPipe*>(instance)->nodeCommandTypes(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeGetNodeCommandTypes: ") + error); }
	catch(...) { publishError(_T("LibPipeGetNodeCommandTypes: Unknown error")); }
}

LIBPIPE_ITF void LibPipeGetNodeMessageTypes(HLibPipe instance, LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbNodeMessageTypes) {
	try {
		cbNodeMessageTypes(context, dumpArray(reinterpret_cast<LibPipe*>(instance)->nodeMessageTypes(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeGetNodeMessageTypes: ") + error); }
	catch(...) { publishError(_T("LibPipeGetNodeMessageTypes: Unknown error")); }
}

LIBPIPE_ITF void LibPipeGetNodeInfo(HLibPipe instance, LibPipeStr address, LibPipeCbContext context, LibPipeCbStr cbNodeInfo) {
	try {
		cbNodeInfo(context, dumpObject(reinterpret_cast<LibPipe*>(instance)->nodeInfo(tstring(address))).c_str());
	}
	catch(tstring error) { publishError(_T("LibPipeGetNodeInfo: ") + error); }
	catch(...) { publishError(_T("LibPipeGetNodeInfo: Unknown error")); }
}

//======================================================================================================================
