//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"

using namespace std;
using namespace Poco;

//======================================================================================================================



//======================================================================================================================

void* loadExtensionSymbol(SharedLibrary& library, const tstring& name) {
	if(!library.hasSymbol(name))
		throw;

	void* symbol = library.getSymbol(name);
	if(symbol == nullptr)
		throw;

	return symbol;
}

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
		extensionFunctions.fktPipeExtensionGetServiceTypes = reinterpret_cast<FktPipeExtensionGetServiceTypes>(loadExtensionSymbol(library, NamePipeExtensionGetServiceTypes));
		extensionFunctions.fktPipeExtensionServiceCreate = reinterpret_cast<FktPipeExtensionServiceCreate>(loadExtensionSymbol(library,NamePipeExtensionServiceCreate));
		extensionFunctions.fktPipeExtensionServiceDestroy = reinterpret_cast<FktPipeExtensionServiceDestroy>(loadExtensionSymbol(library,NamePipeExtensionServiceDestroy));
		extensionFunctions.fktPipeExtensionServiceSend = reinterpret_cast<FktPipeExtensionServiceSend>(loadExtensionSymbol(library,NamePipeExtensionServiceSend));
		extensionFunctions.fktPipeExtensionServiceReceive = reinterpret_cast<FktPipeExtensionServiceReceive>(loadExtensionSymbol(library,NamePipeExtensionServiceReceive));
		extensionFunctions.fktPipeExtensionServiceGetNodeChildren = reinterpret_cast<FktPipeExtensionServiceGetNodeChildren>(loadExtensionSymbol(library, NamePipeExtensionServiceGetNodeChildren));
		extensionFunctions.fktPipeExtensionServiceGetNodeInfo = reinterpret_cast<FktPipeExtensionServiceGetNodeInfo>(loadExtensionSymbol(library, NamePipeExtensionServiceGetNodeInfo));
	}
	catch(...) { return; }

	LibPipe::Extensions.push_back(make_shared<PipeExtensionInstance>(extensionFunctions));
}

//======================================================================================================================
LIBPIPE_ITF void LibPipeLoadExtensions(LibPipeStr path) {
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

LIBPIPE_ITF void LibPipeGetServiceTypes(LibPipeCbContext context, LibPipeCbStr cbServiceTypes) {
	PipeJson::array serviceTypes;

	for(auto&& extension : LibPipe::Extensions) {
		auto extensionServiceTypes = extension->serviceTypes();
		for(auto&& extensionServiceType : *extensionServiceTypes) {
			serviceTypes.push_back(extensionServiceType);
		}
	}

	cbServiceTypes(context, PipeJson(serviceTypes).dump().c_str());
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeCreate(LibPipeStr path, LibPipeStr serviceTypes, HLibPipe* instance) {
	auto serviceTypesData = std::make_shared<PipeJsonArrayData>(PipeJson::parse(serviceTypes).array_items());
	LibPipe::Instances.push_back(make_shared<LibPipe>(tstring(path), serviceTypesData));
	(*instance) = reinterpret_cast<HLibPipe>(LibPipe::Instances.back().get());
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeDestroy(HLibPipe instance) {
	LibPipe* pInstance = reinterpret_cast<LibPipe*>(instance);
	for(auto it = begin(LibPipe::Instances); it != end(LibPipe::Instances); it++) {
		if((*it).get() == pInstance) {
			LibPipe::Instances.erase(it);
			return;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend(HLibPipe instance, LibPipeStr messages) {
	auto messagesData = std::make_shared<PipeJsonArrayData>(PipeJson::parse(messages).array_items());
	reinterpret_cast<LibPipe*>(instance)->send(messagesData);
}

LIBPIPE_ITF void LibPipeReceive(HLibPipe instance, LibPipeCbContext context, LibPipeCbStr cbMessages) {
	auto&& messages = reinterpret_cast<LibPipe*>(instance)->receive();
	cbMessages(context, PipeJson(*messages).dump().c_str());
}

//======================================================================================================================
