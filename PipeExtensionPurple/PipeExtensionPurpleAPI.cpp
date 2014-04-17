//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
using namespace std;

//======================================================================================================================

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviders(PipeExtensionCbContext context, PipeExtensionCbStrList cbProviders) {
	auto&& providers = PipeExtensionPurple::ExtensionInstance.providers();
	vector<PipeExtensionStr> pointers;
	for(auto& provider : providers) {
		pointers.push_back(provider.c_str());
	}
	cbProviders(context, pointers.data(), pointers.size());
}

PIPE_EXTENSION_ITF void PipeExtensionGetServiceProviderSettingTypes(PipeExtensionStr type, PipeExtensionCbContext context, PipeExtensionCbProviderSettingTypes cbProviderSettingTypes) {
	auto&& providerSettings = PipeExtensionPurple::ExtensionInstance.providerSettings(tstring(type));

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
	(*service) = reinterpret_cast<HPipeExtensionService>(PipeExtensionPurple::ExtensionInstance.create(tstring(provider), tstring(id), settingsData));
}

PIPE_EXTENSION_ITF void PipeExtensionServiceDestroy(HPipeExtensionService service) {
	PipeExtensionPurple::ExtensionInstance.destroy(reinterpret_cast<IPipeExtensionService*>(service));
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceSend(HPipeExtensionService service, PipeExtensionMessageData* messages, PipeExtensionEleCnt count) {
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

	IPipeExtensionService* pService = reinterpret_cast<IPipeExtensionService*>(service);
	pService->send(sendMessages);
}

PIPE_EXTENSION_ITF void PipeExtensionServiceReceive(HPipeExtensionService service, PipeExtensionCbContext context, PipeExtensionCbMessages cbMessages) {
	IPipeExtensionService* pService = reinterpret_cast<IPipeExtensionService*>(service);
	auto&& messages = pService->receive();

	std::vector<PipeExtensionMessageData> messagePointers;
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

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceGetChildNodes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStrList cbChildNodes) {
	IPipeExtensionService* pService = reinterpret_cast<IPipeExtensionService*>(service);
	auto&& childNodes = pService->childNodes(tstring(address));

	vector<PipeExtensionStr> childNodePointers;
	for(auto i = 0; i < childNodes.size(); i++) {
		childNodePointers.push_back(childNodes[i].c_str());
	}

	cbChildNodes(context, childNodePointers.data(), childNodePointers.size());
}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeType(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStr cbNodeType) {
	IPipeExtensionService* pService = reinterpret_cast<IPipeExtensionService*>(service);
	auto&& nodeType = pService->nodeType(tstring(address));
	cbNodeType(context, nodeType.c_str());
}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeMessageTypes(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbMessageTypes cbNodeMessageTypes) {
	IPipeExtensionService* pService = reinterpret_cast<IPipeExtensionService*>(service);
	auto&& messageTypes = pService->nodeMessagesTypes(tstring(address));

	std::vector<PipeExtensionMessageTypeData> messageTypePointers;
	std::vector<std::vector<PipeExtensionMessageParameterTypeData>> parameterDataPointers;

	for(auto i = 0; i < messageTypes.size(); i++) {
		parameterDataPointers.push_back({});
		for(auto& parameter : messageTypes[i].parameterTypes) {
			parameterDataPointers[i].push_back({
				parameter.id.c_str(),
				parameter.description.c_str(),
				parameter.optional,
				parameter.binary
			});
		}

		messageTypePointers.push_back({
			messageTypes[i].id.c_str(),
			messageTypes[i].description.c_str(),
			messageTypes[i].receiving,
			messageTypes[i].parameterTypes.size(),
			parameterDataPointers[i].data()
		});
	}

	cbNodeMessageTypes(context, messageTypePointers.data(), messageTypePointers.size());
}

//======================================================================================================================
