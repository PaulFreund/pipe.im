//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"

//======================================================================================================================

class LibPipeInstance : public ILibPipe {
private:
	HLibPipe _instance;

public:
	LibPipeInstance(const tstring& path, const tstring& serviceTypes) {
		/* TODO
		std::vector<LibPipeStr> pointers;
		for(auto& Type : serviceTypes) {
			pointers.push_back(Type.c_str());
		}

		HLibPipe instance;
		LibPipeCreate(path.c_str(), pointers.data(), pointers.size(), &instance);
		_instance = instance;
		*/
	}

	virtual ~LibPipeInstance() {
		LibPipeDestroy(_instance);
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

		LibPipeMessageData messageData = { 
			message.address.c_str(),
			message.type.c_str(),
			message.parameters.size(),
			parameterLengthPointers.data(),
			parameterDataPointers.data()
		};

		LibPipeSend(_instance, &messageData);
		*/
	}

	virtual tstring receive() {
		/* TODO
		std::vector<LibPipeMessage> messageList;
		LibPipeReceive(_instance, &messageList, [](LibPipeCbContext context, LibPipeMessageData* messages, LibPipeEleCnt messageCount) {
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
		*/
		return _T("");
	}

public:
	static void loadExtensions(const tstring& path) {
		LibPipeLoadExtensions(path.c_str());
	}

	static tstring serviceTypes() {
		tstring serviceTypes;
		/* TODO
		LibPipeGetServiceTypes(&serviceTypes, [](LibPipeCbContext context, LibPipeStr* Types, LibPipeEleCnt TypeCount) {
			std::vector<tstring>* pList = static_cast<std::vector<tstring>*>(context);
			for(auto i = 0; i < TypeCount; i++) {
				pList->push_back(tstring(Types[i]));
			}
		});
		*/

		return serviceTypes;
	}
};