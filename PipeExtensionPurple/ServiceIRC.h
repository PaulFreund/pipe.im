//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"

//======================================================================================================================

	/*
		Build something like this?:

		class CommandProcessor : public IPipeExtensionService {
		private:
			

		public:
			virtual void process();
		
		private:
			virtual void commands();
			virtual void status();
			virtual void about();
			virtual void messages();
			virtual void children();
		};	
	*/

class ServiceIRC : public PipeServiceBase {
private:
	tstring _id;
	std::map<tstring, tstring> _settings;

public:
	ServiceIRC(tstring id, tstring path, std::map<tstring, tstring> settings) : PipeServiceBase(id, path, settings) {}
	virtual ~ServiceIRC() {}

public:
	virtual void send(const LibPipeMessage& message) {
	
	}

	virtual std::vector<LibPipeMessage> receive() {
		return {};
	}

	virtual std::vector<tstring> children(tstring address) {
		return {};
	}

	virtual PipeExtensionServiceNodeInfo info(tstring address) {
		return {};
	}
};

//======================================================================================================================
