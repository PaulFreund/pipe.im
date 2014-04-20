//======================================================================================================================

#pragma once

//======================================================================================================================

#include "PipeExtensionInterface.h"

//======================================================================================================================

const tstring NamePipeExtensionGetServiceTypes = _T("PipeExtensionGetServiceTypes");
const tstring NamePipeExtensionGetServiceTypeSettings = _T("PipeExtensionGetServiceTypeSettings");
const tstring NamePipeExtensionServiceCreate = _T("PipeExtensionServiceCreate");
const tstring NamePipeExtensionServiceDestroy = _T("PipeExtensionServiceDestroy");
const tstring NamePipeExtensionServiceSend = _T("PipeExtensionServiceSend");
const tstring NamePipeExtensionServiceReceive = _T("PipeExtensionServiceReceive");
const tstring NamePipeExtensionServiceGetNodeChildren = _T("PipeExtensionServiceGetNodeChildren");
const tstring NamePipeExtensionServiceGetNodeMessageTypes = _T("PipeExtensionServiceGetNodeMessageTypes");
const tstring NamePipeExtensionServiceGetNodeInfo = _T("PipeExtensionServiceGetNodeInfo");

typedef void(*FktPipeExtensionGetServiceTypes)(PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionGetServiceTypeSettings)(PipeExtensionCbContext, PipeExtensionStr, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceCreate)(PipeExtensionStr, PipeExtensionStr, PipeExtensionStr, PipeExtensionStr, HPipeExtensionService*);
typedef void(*FktPipeExtensionServiceDestroy)(HPipeExtensionService);
typedef void(*FktPipeExtensionServiceSend)(HPipeExtensionService, PipeExtensionStr);
typedef void(*FktPipeExtensionServiceReceive)(HPipeExtensionService, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeChildren)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeMessageTypes)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);
typedef void(*FktPipeExtensionServiceGetNodeInfo)(HPipeExtensionService, PipeExtensionStr, PipeExtensionCbContext, PipeExtensionCbStr);

//======================================================================================================================

struct PipeExtensionFunctions {
	FktPipeExtensionGetServiceTypes							fktPipeExtensionGetServiceTypes				= nullptr;
	FktPipeExtensionGetServiceTypeSettings					fktPipeExtensionGetServiceTypeSettings		= nullptr;
	FktPipeExtensionServiceCreate							fktPipeExtensionServiceCreate				= nullptr;
	FktPipeExtensionServiceDestroy							fktPipeExtensionServiceDestroy				= nullptr;
	FktPipeExtensionServiceSend								fktPipeExtensionServiceSend					= nullptr;
	FktPipeExtensionServiceReceive							fktPipeExtensionServiceReceive				= nullptr;
	FktPipeExtensionServiceGetNodeChildren					fktPipeExtensionServiceGetNodeChildren		= nullptr;
	FktPipeExtensionServiceGetNodeMessageTypes				fktPipeExtensionServiceGetNodeMessageTypes	= nullptr;
	FktPipeExtensionServiceGetNodeInfo						fktPipeExtensionServiceGetNodeInfo			= nullptr;
};

//======================================================================================================================

class PipeExtensionServiceInstance : public IPipeExtensionService {
private:
	PipeExtensionFunctions _functions;
	HPipeExtensionService _service;

public:
	PipeExtensionServiceInstance(PipeExtensionFunctions functions, HPipeExtensionService service) : _functions(functions), _service(service) {}

	virtual ~PipeExtensionServiceInstance() {
		_functions.fktPipeExtensionServiceDestroy(_service);
	}

public:
	virtual void send(const tstring& message) {
		/* TODO
		std::vector<LibPipeEleCnt> parameterLengthPointers;
		std::vector<LibPipeStr> parameterDataPointers;

		for(auto& parameter : message.parameters) {
			parameterLengthPointers.push_back(parameter.length());
			parameterDataPointers.push_back(parameter.c_str());
		}

		PipeExtensionMessageData messageData = {
			message.address.c_str(),
			message.type.c_str(),
			message.parameters.size(),
			parameterLengthPointers.data(),
			parameterDataPointers.data()
		};

		_functions.fktPipeExtensionServiceSend(_service, &messageData);
		*/
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual tstring receive() {
		tstring messages;
		/* TODO
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
		*/
		return messages;
	}
	
	//------------------------------------------------------------------------------------------------------------------

	virtual tstring nodeChildren(tstring address) {
		tstring children;
		/* TODO
		_functions.fktPipeExtensionServiceGetNodeChildren(_service, address.c_str(), &childNodes, [](PipeExtensionCbContext context, PipeExtensionStr* childrenData, PipeExtensionEleCnt childrenCount) {
			std::vector<tstring>* pList = static_cast<std::vector<tstring>*>(context);
			for(auto i = 0; i < childrenCount; i++) {
				pList->push_back(tstring(childrenData[i]));
			}
		});
		*/
		return children;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual tstring nodeMessageTypes(tstring address) {
		tstring messageTypes;
		// TODO
		return messageTypes;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual tstring nodeInfo(tstring address) {
		tstring info;
		
		/* TODO
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
		*/
		
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
	virtual tstring serviceTypes() {
		tstring types;
		
		/* TODO
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
		*/

		return types;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual tstring serviceTypeSettings(tstring serviceType) {
		tstring typeSettings;
		// TODO
		return typeSettings;
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual IPipeExtensionService* create(tstring serviceType, tstring id, tstring path, tstring settings) {
		HPipeExtensionService service = 0;

		/* TODO
		std::vector<PipeExtensionServiceSettingData> settingList;

		for(auto it = begin(settings); it != end(settings); it++) {
			settingList.push_back({ it->first.c_str(), it->second.c_str() });
		}

		_functions.fktPipeExtensionServiceCreate(serviceTypeId.c_str(), id.c_str(), path.c_str(), settingList.data(), settingList.size(), &service);
		*/

		return new PipeExtensionServiceInstance(_functions, service);
	}

	//------------------------------------------------------------------------------------------------------------------

	virtual void destroy(IPipeExtensionService* service) {
		_functions.fktPipeExtensionServiceDestroy(reinterpret_cast<HPipeExtensionService>(service));
	}
};

//======================================================================================================================
