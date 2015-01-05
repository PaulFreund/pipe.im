//======================================================================================================================
/*
	Copyright (c) since 2015 - Paul Freund (freund.paul@lvl3.org)
	
	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:
	
	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/
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

	PurpleInterfaceAccount* result = new PurpleInterfaceAccount(address, path, settings, serviceType, description);
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

//----------------------------------------------------------------------------------------------------------------------

PurpleInterfaceAccount* PipeExtensionPurple::accountByRequestHandle(void* requestHandle) {
	for(auto it = begin(_services); it != end(_services); it++) {
		if(it->second->hasRequestHandle(requestHandle)) { return it->second; }
	}

	return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------

void PipeExtensionPurple::process() {
	g_main_context_iteration(g_main_context_default(), false);
}

//======================================================================================================================
