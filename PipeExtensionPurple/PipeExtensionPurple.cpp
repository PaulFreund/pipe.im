//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
#include "PurpleInterface.h"
#include "PurpleInterfaceAccount.h"

using namespace std;

//======================================================================================================================

PipeExtensionPurple         PipeExtensionPurple::ExtensionInstance;
tstring                     PipeExtensionPurple::ExtensionInstancePath;
PipeExtensionCbErr          PipeExtensionPurple::ErrorCallback = nullptr;
shared_ptr<PurpleInterface> PipeExtensionPurple::Purple = shared_ptr<PurpleInterface>(nullptr);

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
	auto types = serviceTypes();
	auto provider = find_if(begin(*types), end(*types), [&serviceType](PipeJson& ele) {
		if(ele.is_object() && ele.object_items()[_T("type")].string_value() == serviceType)
		   return true;

		return false;
	});

	if(provider == end(*types))
		throw tstring(_T("PipeExtensionPurple::create: Could not create service ") + serviceType + _T(" with address ") + address);

	tstring description = _T("");
	tstring id = _T("");
	if(provider->is_object()) {
		auto& props = provider->object_items();
		if(props.count(_T("description")) && props[_T("description")].is_string())
			description = props[_T("description")].string_value();

		if(props.count(_T("protocol_id")) && props[_T("protocol_id")].is_string())
			id = props[_T("protocol_id")].string_value();
		else
			throw tstring(_T("PipeExtensionPurple::create: Could not create service ") + serviceType + _T(", missing protocol id"));
	}

	PurpleInterfaceAccount* result = new PurpleInterfaceAccount(serviceType, description, address, path, settings);
	_services[address] = result;
	result->init(id);
	return reinterpret_cast<IPipeExtensionService*>(result);
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

//----------------------------------------------------------------------------------------------------------------------

PurpleInterfaceAccount* PipeExtensionPurple::account(PurpleAccount* account) {
	for(auto it = begin(_services); it != end(_services); it++) {
		if(it->second->accountHandle() == account) { return it->second; }
	}

	return nullptr;
}

//======================================================================================================================
