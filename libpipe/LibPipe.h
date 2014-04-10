//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

class LibPipe : public ILibPipe {
private:
	tstring _path;
	std::vector<tstring> _providers; 

	std::vector<LibPipeMessage> debugEchos;

public:
	LibPipe(tstring path, std::vector<tstring> providers) : _path(path), _providers(providers) {

	}

	virtual ~LibPipe() {

	}

	virtual void send(const std::vector<LibPipeMessage>& messages) {
		for(auto& message : messages) {
			debugEchos.push_back(message);
		}
	}

	virtual std::vector<LibPipeMessage> receive() {
		std::vector<LibPipeMessage> messages = {};
		messages.insert(messages.end(), debugEchos.begin(), debugEchos.end());
		debugEchos.clear();
		return messages;
	}
};

//======================================================================================================================
