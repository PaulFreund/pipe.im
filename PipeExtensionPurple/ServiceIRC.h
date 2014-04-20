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
	tstring _settings;

public:
	ServiceIRC(tstring id, tstring path, tstring settings) : PipeServiceBase(id, path, settings) {}
	virtual ~ServiceIRC() {}

public:
	virtual void send(const tstring& message) {
	// TODO
	}

	virtual tstring receive() {
		return _T(""); // TODO
	}

	virtual tstring nodeChildren(tstring address) {
		return _T(""); // TODO
	}

	virtual tstring nodeMessageTypes(tstring address) {
		return _T(""); // TODO
	}

	virtual tstring nodeInfo(tstring address) {
		return _T(""); // TODO
	}
};

//======================================================================================================================
