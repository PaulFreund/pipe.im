//======================================================================================================================

#include "CommonHeader.h"
#include "LibPipe.h"
#include "PipeExtensionInstance.h"
using namespace std;
using namespace Poco;
//======================================================================================================================



//======================================================================================================================

vector<LibPipe> g_Instances;
vector<PipeExtensionInstance> g_Extensions;

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
		extensionFunctions.fktServiceNodeGetAddress				= static_cast<FktPipeExtensionServiceNodeGetAddress				>(loadExtensionSymbol(library, NamePipeExtensionServiceNodeGetAddress));
		extensionFunctions.fktServiceNodeGetType				= static_cast<FktPipeExtensionServiceNodeGetType				>(loadExtensionSymbol(library, NamePipeExtensionServiceNodeGetType));
		extensionFunctions.fktServiceNodeGetMessageTypes		= static_cast<FktPipeExtensionServiceNodeGetMessageTypes		>(loadExtensionSymbol(library, NamePipeExtensionServiceNodeGetMessageTypes));
		extensionFunctions.fktServiceNodeGetChildren			= static_cast<FktPipeExtensionServiceNodeGetChildren			>(loadExtensionSymbol(library, NamePipeExtensionServiceNodeGetChildren));
	}
	catch(...) { return; }

	g_Extensions.push_back(PipeExtensionInstance(extensionFunctions));
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

LIBPIPE_ITF void LibPipeGetServiceProviders(LibPipeCbContext context, LibPipeCbServiceProviders cbServiceProviders) {
	vector<tstring> providers;
	for(auto& extension : g_Extensions) {
		auto extensionProviders = extension.serviceProviders();
		for(auto& extensionProvider : extensionProviders) {
			providers.push_back(extensionProvider->type());
		}
	}

	vector<LibPipeStr> pointers;
	for(auto& provider : providers) {
		pointers.push_back(provider.c_str());
	}

	cbServiceProviders(context, pointers.data(), pointers.size());
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeCreateInstance(LibPipeStr path, LibPipeStr* serviceProviders, LibPipeEleCnt serviceProviderCount, HLibPipeInstance* instance) {
	vector<tstring> providers;
	for(auto i = 0; i < serviceProviderCount; i++) {
		providers.push_back(tstring(serviceProviders[i]));
	}

	g_Instances.push_back(LibPipe(tstring(path), providers));
	(*instance) = reinterpret_cast<HLibPipeInstance>(&g_Instances.back());
}

LIBPIPE_ITF void LibPipeDestroyInstance(HLibPipeInstance instance) {
	LibPipe* pInstance = reinterpret_cast<LibPipe*>(instance);
	for(auto it = g_Instances.begin(); it != g_Instances.end(); it++) {
		if(it._Ptr == pInstance) {
			g_Instances.erase(it);
			return;
		}
	}
}

//----------------------------------------------------------------------------------------------------------------------

LIBPIPE_ITF void LibPipeSend(HLibPipeInstance instance, LibPipeMessageData* messages, LibPipeEleCnt count) {
	LibPipe* pInstance = reinterpret_cast<LibPipe*>(instance);
	vector<LibPipeMessage> sendMessages;
	for(auto idxMessage = 0; idxMessage < count; idxMessage++) {
		std::vector<tstring> parameters;
		for(auto idxParameter = 0; idxParameter < messages[idxMessage].parameterCount; idxParameter++) {
			parameters.push_back(tstring(
				messages[idxMessage].parameterData[idxParameter],
				messages[idxMessage].parameterData[idxParameter] + messages[idxMessage].parameterLength[idxParameter]
			));
		}

		sendMessages.push_back({
			tstring(messages[idxMessage].address),
			tstring(messages[idxMessage].type),
			parameters
		});
	}

	pInstance->send(sendMessages);
}

LIBPIPE_ITF void LibPipeReceive(HLibPipeInstance instance, LibPipeCbContext context, LibPipeCbMessages cbMessages) {
	LibPipe* pInstance = reinterpret_cast<LibPipe*>(instance);
	auto& messages = pInstance->receive();

	std::vector<LibPipeMessageData> messagePointers;
	std::vector<std::vector<LibPipeEleCnt>> parameterLengthPointers;
	std::vector<std::vector<LibPipeStr>> parameterDataPointers;

	for(auto i = 0; i < messages.size(); i++) {
		parameterLengthPointers.push_back({});
		parameterDataPointers.push_back({});
		for(auto& parameter : messages[i].parameters) {
			parameterLengthPointers[i].push_back(parameter.length());
			parameterDataPointers[i].push_back(parameter.c_str());
		}

		messagePointers.push_back({
			messages[i].address.c_str(),
			messages[i].type.c_str(),
			messages[i].parameters.size(),
			parameterLengthPointers[i].data(),
			parameterDataPointers[i].data()
		});
	}

	cbMessages(context, messagePointers.data(), messagePointers.size());
}

//======================================================================================================================