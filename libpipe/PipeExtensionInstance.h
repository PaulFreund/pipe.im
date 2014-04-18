//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

const tstring NamePipeExtensionGetServiceTypes = _T("PipeExtensionGetServiceTypes");
const tstring NamePipeExtensionServiceCreate = _T("PipeExtensionServiceCreate");
const tstring NamePipeExtensionServiceDestroy = _T("PipeExtensionServiceDestroy");
const tstring NamePipeExtensionServiceSend = _T("PipeExtensionServiceSend");
const tstring NamePipeExtensionServiceReceive = _T("PipeExtensionServiceReceive");
const tstring NamePipeExtensionServiceGetNodeChildren = _T("PipeExtensionServiceGetNodeChildren");
const tstring NamePipeExtensionServiceGetNodeInfo = _T("PipeExtensionServiceGetNodeInfo");


typedef void(*FktPipeExtensionGetServiceTypes)(PipeExtensionCbContext, PipeExtensionCbServiceType);
typedef void(*FktPipeExtensionServiceCreate)(PipeExtensionStr, PipeExtensionStr, PipeExtensionServiceSettingData*, PipeExtensionEleCnt, HPipeExtensionService*);
typedef void(*FktPipeExtensionServiceDestroy)(HPipeExtensionService);
typedef void(*FktPipeExtensionServiceSend)(HPipeExtensionService, PipeExtensionMessageData*, PipeExtensionEleCnt);
typedef void(*FktPipeExtensionServiceReceive)(HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbMessages);
typedef void(*FktPipeExtensionServiceGetNodeChildren)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStrList);
typedef void(*FktPipeExtensionServiceGetNodeInfo)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbServiceNodeInfo);

//======================================================================================================================

struct PipeExtensionFunctions {
	FktPipeExtensionGetServiceTypes						fktPipeExtensionGetServiceTypes = nullptr;
	FktPipeExtensionServiceCreate						fktPipeExtensionServiceCreate = nullptr;
	FktPipeExtensionServiceDestroy						fktPipeExtensionServiceDestroy = nullptr;
	FktPipeExtensionServiceSend							fktPipeExtensionServiceSend = nullptr;
	FktPipeExtensionServiceReceive						fktPipeExtensionServiceReceive = nullptr;
	FktPipeExtensionServiceGetNodeChildren				fktPipeExtensionServiceGetNodeChildren = nullptr;
	FktPipeExtensionServiceGetNodeInfo					fktPipeExtensionServiceGetNodeInfo = nullptr;
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

	virtual std::vector<tstring> children(tstring address) {
		std::vector<tstring> childNodes;

		_functions.fktPipeExtensionServiceGetNodeChildren(_service, address.c_str(), &childNodes, [](PipeExtensionCbContext context, PipeExtensionStr* childrenData, PipeExtensionEleCnt childrenCount) {
			std::vector<tstring>* pList = static_cast<std::vector<tstring>*>(context);
			for(auto i = 0; i < childrenCount; i++) {
				pList->push_back(tstring(childrenData[i]));
			}
		});

		return childNodes;
	}

	virtual PipeExtensionServiceNodeInfo info(tstring address) {
		PipeExtensionServiceNodeInfo info;
		
		_functions.fktPipeExtensionServiceGetNodeInfo(_service, address.c_str(), &info, [](PipeExtensionCbContext context, PipeExtensionServiceNodeInfoData* infoData) {
			PipeExtensionServiceNodeInfo* pInfo = static_cast<PipeExtensionServiceNodeInfo*>(context);

			pInfo->id = infoData->id;

			for(auto i = 0; i < infoData->metaInfoCount; i++) {
				pInfo->meta[infoData->metaInfoKeys[i]] = infoData->metaInfoValues[i];
			}

			pInfo->type.id = infoData->type.id;
			pInfo->type.description = infoData->type.description;

			for(auto idxMessageType = 0; idxMessageType < infoData->type.messageTypeCount; idxMessageType++) {
				std::vector<PipeExtensionMessageParameterType> parameters;
				for(auto idxParameter = 0; idxParameter < infoData->type.messageTypes[idxMessageType].parameterCount; idxParameter++) {
					parameters.push_back({ 
						tstring(infoData->type.messageTypes[idxMessageType].parameterTypes[idxParameter].id),
						tstring(infoData->type.messageTypes[idxMessageType].parameterTypes[idxParameter].description),
						infoData->type.messageTypes[idxMessageType].parameterTypes[idxParameter].optional,
						infoData->type.messageTypes[idxMessageType].parameterTypes[idxParameter].binary
					});
				}
				pInfo->type.messageTypes.push_back({
					tstring(infoData->type.messageTypes[idxMessageType].id),
					tstring(infoData->type.messageTypes[idxMessageType].description),
					infoData->type.messageTypes[idxMessageType].command,
					parameters
				});
			}
		});
		
		return info;
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
	virtual std::vector<PipeExtensionServiceType> serviceTypes() {
		std::vector<PipeExtensionServiceType> serviceTypeList;
		
		_functions.fktPipeExtensionGetServiceTypes(&serviceTypeList, [](PipeExtensionCbContext context, PipeExtensionServiceTypeData* serviceTypesData, PipeExtensionEleCnt serviceTypesCount) {
			std::vector<PipeExtensionServiceType>* pList = static_cast<std::vector<PipeExtensionServiceType>*>(context);
			for(auto i = 0; i < serviceTypesCount; i++) {
				PipeExtensionServiceTypeData* pServiceType = &serviceTypesData[i];
				PipeExtensionServiceType curServiceType;

				curServiceType.id = pServiceType->id;
				curServiceType.description = pServiceType->description;
				for(auto j = 0; j < pServiceType->settingTypeCount; j++) {
					curServiceType.settings[pServiceType->settingTypeIdData[j]] = pServiceType->settingTypeDescriptionData[j];
				}

				pList->push_back(curServiceType);
			}
		});
		
		return serviceTypeList;
	}

	virtual IPipeExtensionService* create(tstring serviceTypeId, tstring id, std::map<tstring, tstring> settings) {
		HPipeExtensionService service = 0;

		std::vector<PipeExtensionServiceSettingData> settingList;

		for(auto it = begin(settings); it != end(settings); it++) {
			settingList.push_back({ it->first.c_str(), it->second.c_str() });
		}

		_functions.fktPipeExtensionServiceCreate(serviceTypeId.c_str(), id.c_str(), settingList.data(), settingList.size(), &service);
		return new PipeExtensionServiceInstance(_functions, service, id);
	}

	virtual void destroy(IPipeExtensionService* service) {
		_functions.fktPipeExtensionServiceDestroy(reinterpret_cast<HPipeExtensionService>(service));
	}
};

//======================================================================================================================
