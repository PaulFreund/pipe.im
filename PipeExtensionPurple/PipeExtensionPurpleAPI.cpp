//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
using namespace std;

//======================================================================================================================

PipeExtensionPurple g_Extension;

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders(PipeExtensionCbContext context, PipeExtensionCbStrList cbProviders) {
	auto& providers = g_Extension.providers();
	vector<PipeExtensionStr> pointers;
	for(auto& provider : providers) {
		pointers.push_back(provider.c_str());
	}
	cbProviders(context, pointers.data(), pointers.size());
}

PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviderSettingTypes(PipeExtensionStr type, PipeExtensionCbContext context, PipeExtensionCbProviderSettingTypes cbProviderSettingTypes) {
	auto& providerSettings = g_Extension.providerSettings(tstring(type));

	std::vector<PipeExtensionProviderSettingTypeData> providerSettingPointers;

	for(auto it = begin(providerSettings); it != end(providerSettings); it++) {
		providerSettingPointers.push_back({ it->first.c_str(), it->second.c_str() });
	}

	cbProviderSettingTypes(context, providerSettingPointers.data(), providerSettingPointers.size());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate(PipeExtensionStr provider, PipeExtensionStr id, PipeExtensionServiceSettingData* settings, PipeExtensionEleCnt count, HPipeExtensionService* service) {
	std::map<string, string> settingsData;
	for(auto i = 0; i < count; i++) {
		settingsData[settings[i].id] = settings[i].value;
	}
	(*service) = reinterpret_cast<HPipeExtensionService>(g_Extension.create(tstring(provider), tstring(id), settingsData));
}

PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy(HPipeExtensionService service) {
	g_Extension.destroy(reinterpret_cast<IPipeExtensionService*>(service));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend(HPipeExtensionService service, PipeExtensionMessageData* messages, PipeExtensionEleCnt count) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceReceive(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbMessages) {

}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetChildNodes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStrList cbChildNodes) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeType(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeType) {

}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbMessageTypes cbNodeMessageTypes) {

}

//======================================================================================================================
