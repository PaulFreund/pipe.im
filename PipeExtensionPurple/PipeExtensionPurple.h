//======================================================================================================================

#pragma once

//======================================================================================================================

#include "CommonHeader.h"
#include "ServiceIRC.h"

#include <iostream>
#include <purple.h>

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
		purple_debug_set_enabled(FALSE);
		purple_plugins_init();
		
		GList * list = purple_plugins_get_all();
		GList * list2 = purple_plugins_get_protocols();

		std::cout << _T("Plugins: ") << list << std::endl;
		std::cout << _T("Protocols: ") << list2 << std::endl;

		return { _T("irc") };
	}

	virtual std::map<tstring, tstring> providerSettings(tstring provider) {
		if(provider == _T("irc")) {
			return ServiceIRC::settingTypes();
		}

		return {};
	}

	virtual IPipeExtensionService* create(tstring provider, tstring id, std::map<tstring, tstring> settings) {
		if(provider == _T("irc")) {
			return (_services[id] = new ServiceIRC(id, settings));
		}

		return nullptr;
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
