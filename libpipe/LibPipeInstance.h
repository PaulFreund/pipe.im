//======================================================================================================================

#pragma once

//======================================================================================================================

#include "LibPipeInterface.h"

//======================================================================================================================

class LibPipeInstance : public ILibPipe {
private:
	HLibPipe _instance;

public:
	LibPipeInstance(const tstring& path, const std::vector<tstring>& serviceProviders) {

		std::vector<LibPipeStr> pointers;
		for(auto& provider : serviceProviders) {
			pointers.push_back(provider.c_str());
		}

		HLibPipe instance;
		LibPipeCreate(path.c_str(), pointers.data(), pointers.size(), &instance);
		_instance = instance;
	}

	virtual ~LibPipeInstance() {
		LibPipeDestroy(_instance);
	}

public:
	virtual void send(const std::vector<LibPipeMessage>& messages) {
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
		LibPipeSend(_instance, messagePointers.data(), messagePointers.size());
	}

	virtual std::vector<LibPipeMessage> receive() {
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
	}

public:
	static void loadExtensions(const tstring& path) {
		LibPipeLoadExtensions(path.c_str());
	}

	static std::vector<tstring> serviceProviders() {
		std::vector<tstring> serviceProviders;

		LibPipeGetServiceProviders(&serviceProviders, [](LibPipeCbContext context, LibPipeStr* providers, LibPipeEleCnt providerCount) {
			std::vector<tstring>* pList = static_cast<std::vector<tstring>*>(context);
			for(auto i = 0; i < providerCount; i++) {
				pList->push_back(tstring(providers[i]));
			}
		});

		return serviceProviders;
	}
};