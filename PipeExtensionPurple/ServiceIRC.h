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

class ServiceIRC : public IPipeExtensionService {
private:
	tstring _id;
	std::map<tstring, tstring> _settings;

public:
	ServiceIRC(tstring id, std::map<tstring, tstring> settings) : _id(id), _settings(settings) {}
	virtual ~ServiceIRC() {}

public:
	virtual tstring id() {
		return _id;
	}

	virtual void send(const std::vector<LibPipeMessage>& messages) {
	
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
