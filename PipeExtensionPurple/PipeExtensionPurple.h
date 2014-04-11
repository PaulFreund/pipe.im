//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceIRC.h"

//======================================================================================================================

class PipeExtensionPurple : public IPipeExtension {
private:
	std::map<tstring, IPipeExtensionService*> _services;

public:
	PipeExtensionPurple() {}

	virtual ~PipeExtensionPurple() {
		for(auto it = begin(_services); it != end(_services); it++) {
			delete it->second;
		}
	}

public:
	virtual std::vector<tstring> providers() {
		return { "irc" };
	}

	virtual std::map<tstring, tstring> providerSettings(tstring provider) {
		if(provider == _T("irc")) {
			return ServiceIRC::settingTypes();
		}
	}

	virtual IPipeExtensionService* create(tstring provider, tstring id, std::map<tstring, tstring> settings) {
		if(provider == _T("irc")) {
			return (_services[id] = new ServiceIRC(id, settings));
		}
	}

	virtual void destroy(IPipeExtensionService* service) {
		for(auto it = begin(_services); it != end(_services); it++) {
			if(it->second == service) {
				delete it->second;
				_services.erase(it);
				return;
			}
		}
	}
};

//======================================================================================================================
