//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

const tstring NamePipeExtensionGetServiceProviders = _T("PipeExtensionGetServiceProviders");
const tstring NamePipeExtensionGetServiceProviderSettingTypes = _T("PipeExtensionGetServiceProviderSettingTypes");
const tstring NamePipeExtensionServiceCreate = _T("PipeExtensionServiceCreate");
const tstring NamePipeExtensionServiceDestroy = _T("PipeExtensionServiceDestroy");
const tstring NamePipeExtensionServiceSend = _T("PipeExtensionServiceSend");
const tstring NamePipeExtensionServiceReceive = _T("PipeExtensionServiceReceive");
const tstring NamePipeExtensionServiceGetChildNodes = _T("PipeExtensionServiceGetChildNodes");
const tstring NamePipeExtensionServiceGetNodeType = _T("PipeExtensionServiceGetNodeType");
const tstring NamePipeExtensionServiceGetNodeMessageTypes = _T("PipeExtensionServiceGetNodeMessageTypes");


typedef void(*FktPipeExtensionGetServiceProviders)(PipeExtensionCbContext, PipeExtensionCbStrList);
typedef void(*FktPipeExtensionGetServiceProviderSettingTypes)(PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbProviderSettingTypes);
typedef void(*FktPipeExtensionServiceCreate)(PipeExtensionStr, PipeExtensionStr, PipeExtensionServiceSettingData*, PipeExtensionEleCnt, HPipeExtensionService*);
typedef void(*FktPipeExtensionServiceDestroy)(HPipeExtensionService);
typedef void(*FktPipeExtensionServiceSend)(HPipeExtensionService, PipeExtensionMessageData*, PipeExtensionEleCnt);
typedef void(*FktPipeExtensionServiceReceive)(HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbMessages);
typedef void(*FktPipeExtensionServiceGetChildNodes)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStrList);
typedef void(*FktPipeExtensionServiceGetNodeType)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeMessageTypes)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbMessageTypes);

//======================================================================================================================


struct PipeExtensionFunctions {
	FktPipeExtensionGetServiceProviders					fktPipeExtensionGetServiceProviders = nullptr;
	FktPipeExtensionGetServiceProviderSettingTypes		fktPipeExtensionGetServiceProviderSettingTypes = nullptr;
	FktPipeExtensionServiceCreate						fktPipeExtensionServiceCreate = nullptr;
	FktPipeExtensionServiceDestroy						fktPipeExtensionServiceDestroy = nullptr;
	FktPipeExtensionServiceSend							fktPipeExtensionServiceSend = nullptr;
	FktPipeExtensionServiceReceive						fktPipeExtensionServiceReceive = nullptr;
	FktPipeExtensionServiceGetChildNodes				fktPipeExtensionServiceGetChildNodes = nullptr;
	FktPipeExtensionServiceGetNodeType					fktPipeExtensionServiceGetNodeType = nullptr;
	FktPipeExtensionServiceGetNodeMessageTypes			fktPipeExtensionServiceGetNodeMessageTypes = nullptr;
};

//======================================================================================================================

class PipeExtensionServiceInstance : public IPipeExtensionService {
private:
	PipeExtensionFunctions _functions;
	HPipeExtensionService _service;
	tstring _id;
public:
	PipeExtensionServiceInstance(PipeExtensionFunctions functions, HPipeExtensionService service, tstring id) : _functions(functions), _service(service), _id(id) {}

	virtual ~PipeExtensionServiceInstance() {
		_functions.fktPipeExtensionServiceDestroy(_service);
	}

public:
	virtual tstring id() {
		return _id;
	}

	virtual void send(const std::vector<LibPipeMessage>& messages) {
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
		_functions.fktPipeExtensionServiceSend(_service, messagePointers.data(), messagePointers.size());
	}

	virtual std::vector<LibPipeMessage> receive() {
		std::vector<LibPipeMessage> messageList;
		_functions.fktPipeExtensionServiceReceive(_service, &messageList, [](PipeExtensionCbContext context, PipeExtensionMessageData* messages, PipeExtensionEleCnt messageCount) {
			std::vector<LibPipeMessage>* pMessages = static_cast<std::vector<LibPipeMessage>*>(context);
			for(auto idxMessage = 0; idxMessage < messageCount; idxMessage++) {
				std::vector<tstring> parameters;
				for(auto idxParameter = 0; idxParameter < messages[idxMessage].parameterCount; idxParameter++) {
					parameters.push_back(tstring(
						messages[idxMessage].parameterData[idxParameter],
						messages[idxMessage].parameterData[idxParameter] + messages[idxMessage].parameterLength[idxParameter]
						));
				}

				pMessages->push_back({
					tstring(messages[idxMessage].address),
					tstring(messages[idxMessage].type),
					parameters
				});
			}
		});
		return messageList;
	}

	virtual std::vector<tstring> childNodes(tstring address) {
		std::vector<tstring> childNodes;

		_functions.fktPipeExtensionServiceGetChildNodes(_service, address.c_str(), &childNodes, [](PipeExtensionCbContext context, PipeExtensionStr* providers, PipeExtensionEleCnt providerCount) {
			std::vector<tstring>* pList = static_cast<std::vector<tstring>*>(context);
			for(auto i = 0; i < providerCount; i++) {
				pList->push_back(tstring(providers[i]));
			}
		});

		return childNodes;
	}

	virtual tstring nodeType(tstring address) {
		tstring nodeType;

		_functions.fktPipeExtensionServiceGetNodeType(_service, address.c_str(), &nodeType, [](PipeExtensionCbContext context, PipeExtensionStr type) {
			(*(static_cast<tstring*>(context))) = tstring(type); // TODO - CHECK FOR ERRORS
		});

		return nodeType;
	}

	virtual std::vector<PipeExtensionMessageType> nodeMessagesTypes(tstring address) {
		std::vector<PipeExtensionMessageType> messageTypeList;
		_functions.fktPipeExtensionServiceGetNodeMessageTypes(_service, address.c_str(), &messageTypeList, [](PipeExtensionCbContext context, PipeExtensionMessageTypeData* messageTypes, PipeExtensionEleCnt messageTypeCount) {
			std::vector<PipeExtensionMessageType>* pMessageTypeList = static_cast<std::vector<PipeExtensionMessageType>*>(context);
			for(auto idxMessageType = 0; idxMessageType < messageTypeCount; idxMessageType++) {
				std::vector<PipeExtensionMessageParameterType> parameters;
				for(auto idxParameter = 0; idxParameter < messageTypes[idxMessageType].parameterCount; idxParameter++) {
					parameters.push_back({ 
						tstring(messageTypes[idxMessageType].parameterTypes[idxParameter].id),
						tstring(messageTypes[idxMessageType].parameterTypes[idxParameter].description),
						messageTypes[idxMessageType].parameterTypes[idxParameter].optional,
						messageTypes[idxMessageType].parameterTypes[idxParameter].binary
					});
				}
				pMessageTypeList->push_back({
					tstring(messageTypes[idxMessageType].id),
					tstring(messageTypes[idxMessageType].description),
					messageTypes[idxMessageType].receiving,
					parameters
				});
			}
		});
		return messageTypeList;
	}
};

//======================================================================================================================

class PipeExtensionInstance : public IPipeExtension {
private:
	PipeExtensionFunctions _functions;

public:
	PipeExtensionInstance(PipeExtensionFunctions functions) : _functions(functions) {}
	virtual ~PipeExtensionInstance() {}

public:
	virtual std::vector<tstring> providers() {
		std::vector<tstring> serviceProviders;

		_functions.fktPipeExtensionGetServiceProviders(&serviceProviders, [](PipeExtensionCbContext context, PipeExtensionStr* providers, PipeExtensionEleCnt providerCount) {
			std::vector<tstring>* pList = static_cast<std::vector<tstring>*>(context);
			for(auto i = 0; i < providerCount; i++) {
				pList->push_back(tstring(providers[i]));
			}
		});

		return serviceProviders;
	}

	virtual std::map<tstring, tstring> providerSettings(tstring provider) {
		std::map<tstring, tstring> providerSettings;

		_functions.fktPipeExtensionGetServiceProviderSettingTypes(provider.c_str(), &providerSettings, [](PipeExtensionCbContext context, PipeExtensionProviderSettingTypeData* settingTypeData, PipeExtensionEleCnt settingTypeDataCount) {
			std::map<tstring, tstring>* pList = static_cast<std::map<tstring, tstring>*>(context);
			for(auto i = 0; i < settingTypeDataCount; i++) {
				(*pList)[settingTypeData[i].id] = tstring(settingTypeData[i].description);
			}
		});

		return providerSettings;
	}

	virtual std::shared_ptr<IPipeExtensionService> createService(tstring provider, tstring name, std::map<tstring, tstring> settings) {
		HPipeExtensionService service = 0;

		std::vector<PipeExtensionServiceSettingData> settingList;

		for(auto it = begin(settings); it != end(settings); it++) {
			settingList.push_back({ it->first.c_str(), it->second.c_str() });
		}

		_functions.fktPipeExtensionServiceCreate(provider.c_str(), name.c_str(), settingList.data(), settingList.size(), &service);
		return std::make_shared<PipeExtensionServiceInstance>(PipeExtensionServiceInstance(_functions, service, name));
	}
};

//======================================================================================================================
