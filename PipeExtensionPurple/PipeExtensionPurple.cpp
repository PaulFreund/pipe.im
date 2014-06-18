//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
#include "PurpleDispatcher.h"
#include "ServiceIRC.h"

using namespace std;

//======================================================================================================================

PipeExtensionPurple         PipeExtensionPurple::ExtensionInstance;
tstring                     PipeExtensionPurple::ExtensionInstancePath;
PipeExtensionCbErr          PipeExtensionPurple::ErrorCallback = nullptr;
shared_ptr<PurpleDispatcher> PipeExtensionPurple::Purple = shared_ptr<PurpleDispatcher>(nullptr);

//======================================================================================================================

PipeExtensionPurple::PipeExtensionPurple() {

}

//----------------------------------------------------------------------------------------------------------------------

PipeExtensionPurple::~PipeExtensionPurple() {
	for(auto it = begin(_services); it != end(_services); it++) {
		delete it->second;
	}
}

//----------------------------------------------------------------------------------------------------------------------

PipeArrayPtr PipeExtensionPurple::serviceTypes() {
	return PipeExtensionPurple::Purple->getProtocols();
}

//----------------------------------------------------------------------------------------------------------------------

IPipeExtensionService* PipeExtensionPurple::create(const tstring& serviceType, const tstring& address, const tstring& path, PipeObjectPtr settings) {
	if(serviceType == _T("irc")) {
		return _services[address] = new ServiceIRC(address, path, settings);
	}

	throw tstring(_T("PipeExtensionPurple::create: Could not create service ") + serviceType + _T(" with address ") + address);
}

//----------------------------------------------------------------------------------------------------------------------

void PipeExtensionPurple::destroy(IPipeExtensionService* service) {
	for(auto it = begin(_services); it != end(_services); it++) {
		if(it->second == service) {
			delete it->second;
			_services.erase(it);
			return;
		}
	}

	throw tstring(_T("PipeExtensionPurple::destroy: Could not find service"));
}

//======================================================================================================================
