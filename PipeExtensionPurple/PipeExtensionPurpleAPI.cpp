//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
using namespace std;

//======================================================================================================================

//======================================================================================================================

PIPE_EXTENSION_ITF void PipeExtensionGetServiceTypes(PipeExtensionCbContext context, PipeExtensionCbServiceType cbServiceTypes) {
	auto&& serviceTypes = PipeExtensionPurple::ExtensionInstance.serviceTypes();

	std::vector<PipeExtensionServiceTypeData> serviceTypesPointers;
	std::vector<std::vector<PipeExtensionStr>> serviceTypeSettingIdsPointers;
	std::vector<std::vector<PipeExtensionStr>> serviceTypeSettingDescriptionsPointers;

	for(int i = 0; i < serviceTypes.size(); i++) {
		serviceTypeSettingIdsPointers.push_back({});
		serviceTypeSettingDescriptionsPointers.push_back({});
		for(auto it = begin(serviceTypes[i].settings); it != end(serviceTypes[i].settings); it++) {
			serviceTypeSettingIdsPointers[i].push_back(it->first.c_str());
			serviceTypeSettingDescriptionsPointers[i].push_back(it->first.c_str());
		}

		serviceTypesPointers.push_back({
			serviceTypes[i].id.c_str(),
			serviceTypes[i].description.c_str(),
			serviceTypes[i].settings.size(),
			serviceTypeSettingIdsPointers[i].data(),
			serviceTypeSettingDescriptionsPointers[i].data(),
		});
	}

	cbServiceTypes(context, serviceTypesPointers.data(), serviceTypesPointers.size());
}

//----------------------------------------------------------------------------------------------------------------------

PIPE_EXTENSION_ITF void PipeExtensionServiceCreate(PipeExtensionStr serviceTypeId, PipeExtensionStr id, PipeExtensionServiceSettingData* settings, PipeExtensionEleCnt count, HPipeExtensionService* service) {
	std::map<string, string> settingsData;
	for(auto i = 0; i < count; i++) {
		settingsData[settings[i].id] = settings[i].value;
	}
	(*service) = reinterpret_cast<HPipeExtensionService>(PipeExtensionPurple::ExtensionInstance.create(tstring(serviceTypeId), tstring(id), settingsData));
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
	std::vector<std::vector<PipeExtensionEleCnt>> parameterLengthPointers;
	std::vector<std::vector<PipeExtensionStr>> parameterDataPointers;

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

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeChildren(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbStrList cbChildNodes) {
	IPipeExtensionService* pService = reinterpret_cast<IPipeExtensionService*>(service);
	auto&& childNodes = pService->children(tstring(address));

	vector<PipeExtensionStr> childNodePointers;
	for(auto i = 0; i < childNodes.size(); i++) {
		childNodePointers.push_back(childNodes[i].c_str());
	}

	cbChildNodes(context, childNodePointers.data(), childNodePointers.size());
}

PIPE_EXTENSION_ITF void PipeExtensionServiceGetNodeInfo(HPipeExtensionService service, PipeExtensionStr address, PipeExtensionCbContext context, PipeExtensionCbServiceNodeInfo cbNodeMessageTypes) {
	IPipeExtensionService* pService = reinterpret_cast<IPipeExtensionService*>(service);
	auto&& info = pService->info(tstring(address));

	PipeExtensionServiceNodeInfoData infoData;

	infoData.id = info.id.c_str();

	{
		std::vector<PipeExtensionStr> metaInfoKeysPointers;
		std::vector<PipeExtensionStr> metaInfoValuesPointers;

		for(auto it = begin(info.meta); it != end(info.meta); it++) {
			metaInfoKeysPointers.push_back(it->first.c_str());
			metaInfoValuesPointers.push_back(it->first.c_str());
		}

		infoData.metaInfoCount = info.meta.size();
		infoData.metaInfoKeys = metaInfoKeysPointers.data();
		infoData.metaInfoValues = metaInfoValuesPointers.data();
	}

	{
		infoData.type.id = info.type.id.c_str();
		infoData.type.description = info.type.description.c_str();

		std::vector<PipeExtensionMessageTypeData> messageTypePointers;
		std::vector<std::vector<PipeExtensionMessageParameterTypeData>> parameterDataPointers;

		for(auto i = 0; i < info.type.messageTypes.size(); i++) {
			parameterDataPointers.push_back({});
			for(auto& parameter : info.type.messageTypes[i].parameterTypes) {
				parameterDataPointers[i].push_back({
					parameter.id.c_str(),
					parameter.description.c_str(),
					parameter.optional,
					parameter.binary
				});
			}

			messageTypePointers.push_back({
				info.type.messageTypes[i].id.c_str(),
				info.type.messageTypes[i].description.c_str(),
				info.type.messageTypes[i].command,
				info.type.messageTypes[i].parameterTypes.size(),
				parameterDataPointers[i].data()
			});
		}

		infoData.type.messageTypeCount = info.type.messageTypes.size();
		infoData.type.messageTypes = messageTypePointers.data();
	}

	cbNodeMessageTypes(context, &infoData);
}

//======================================================================================================================
