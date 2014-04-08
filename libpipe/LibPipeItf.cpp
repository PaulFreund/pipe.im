//======================================================================================================================

#include "CommonHeader.h"
#include "PipeInstance.h"
#include "PipeExtension.h"
using namespace std;
using namespace Poco;
//======================================================================================================================



//======================================================================================================================

vector<PipeInstance> g_Instances;
vector<PipeExtension> g_Extensions;

//======================================================================================================================

void* loadExtensionSymbol(SharedLibrary& library, tstring name) {
	if(!library.hasSymbol(name))
		throw;

	void* symbol = library.getSymbol(name);
	if(symbol == nullptr)
		throw;

	return symbol;
}

void loadExtension(tstring path) {
	auto suffix = SharedLibrary::suffix();
	if(path.length() <= suffix.length())
		return;

	auto ext = path.substr(path.length() - suffix.length(), string::npos);
	if(!File(path).isFile() || ext != suffix)
		return;

	SharedLibrary library(path);
	if(!library.isLoaded())
		return;

	if(!library.hasSymbol(NamePipeExtensionGetServiceProviders))
		return;

	PipeExtensionFunctions extensionFunctions;
	try {
		extensionFunctions.fktGetServiceProviders				= static_cast<FktPipeExtensionGetServiceProviders				>(loadExtensionSymbol(library, NamePipeExtensionGetServiceProviders));
		extensionFunctions.fktServiceProviderGetType			= static_cast<FktPipeExtensionServiceProviderGetType			>(loadExtensionSymbol(library, NamePipeExtensionServiceProviderGetType));
		extensionFunctions.fktServiceProviderGetSettingTypes	= static_cast<FktPipeExtensionServiceProviderGetSettingTypes	>(loadExtensionSymbol(library, NamePipeExtensionServiceProviderGetSettingTypes));
		extensionFunctions.fktServiceProviderCreateService		= static_cast<FktPipeExtensionServiceProviderCreateService		>(loadExtensionSymbol(library, NamePipeExtensionServiceProviderCreateService));
		extensionFunctions.fktServiceProviderDestroyService		= static_cast<FktPipeExtensionServiceProviderDestroyService		>(loadExtensionSymbol(library, NamePipeExtensionServiceProviderDestroyService));
		extensionFunctions.fktServiceGetId						= static_cast<FktPipeExtensionServiceGetId						>(loadExtensionSymbol(library, NamePipeExtensionServiceGetId));
		extensionFunctions.fktServiceGetType					= static_cast<FktPipeExtensionServiceGetType					>(loadExtensionSymbol(library, NamePipeExtensionServiceGetType));
		extensionFunctions.fktServiceGetRoot					= static_cast<FktPipeExtensionServiceGetRoot					>(loadExtensionSymbol(library, NamePipeExtensionServiceGetRoot));
		extensionFunctions.fktServiceSendMessages				= static_cast<FktPipeExtensionServiceSendMessages				>(loadExtensionSymbol(library, NamePipeExtensionServiceSendMessages));
		extensionFunctions.fktServiceReceiveMessages			= static_cast<FktPipeExtensionServiceReceiveMessages			>(loadExtensionSymbol(library, NamePipeExtensionServiceReceiveMessages));
		extensionFunctions.fktServiceNodeGetId					= static_cast<FktPipeExtensionServiceNodeGetId					>(loadExtensionSymbol(library, NamePipeExtensionServiceNodeGetId));
		extensionFunctions.fktServiceNodeGetType				= static_cast<FktPipeExtensionServiceNodeGetType				>(loadExtensionSymbol(library, NamePipeExtensionServiceNodeGetType));
		extensionFunctions.fktServiceNodeGetMessageTypes		= static_cast<FktPipeExtensionServiceNodeGetMessageTypes		>(loadExtensionSymbol(library, NamePipeExtensionServiceNodeGetMessageTypes));
		extensionFunctions.fktServiceNodeGetChildren			= static_cast<FktPipeExtensionServiceNodeGetChildren			>(loadExtensionSymbol(library, NamePipeExtensionServiceNodeGetChildren));
	}
	catch(...) { return; }

	g_Extensions.push_back(PipeExtension(extensionFunctions));
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

LIBPIPE_ITF void LibPipeGetServiceProviders(LibPipeCbServiceProviders cbServiceProviders) {

}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeCreateInstance(LibPipeStr path, LibPipeStr* serviceProviders, LibPipeEleCnt serviceProviderCount, LibPipeInstance* instance) {

}

LIBPIPE_ITF void LibPipeDestroyInstance(LibPipeInstance instance) {

}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend(LibPipeInstance instance, LibPipeMessageData* messages, LibPipeEleCnt count) {

}

LIBPIPE_ITF void LibPipeReceive(LibPipeInstance instance, LibPipeCbMessages cbMessages) {

}

//======================================================================================================================