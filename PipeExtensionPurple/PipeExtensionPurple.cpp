//======================================================================================================================

#include "CommonHeader.h"
#include "PipeExtensionPurple.h"
#include "PurpleService.h"
#include "ServiceIRC.h"

using namespace std;

//======================================================================================================================

PipeExtensionPurple PipeExtensionPurple::ExtensionInstance;
PipeExtensionCbErr  PipeExtensionPurple::ErrorCallback = nullptr;

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
	PipeArrayPtr serviceTypes = newArray();

	// TODO: This is fake
	PipeObject def;
	tstring defTypeName = timplode(texplode(_T("irc"), _T(' ')), _T('_'));
	transform(begin(defTypeName), end(defTypeName), begin(defTypeName), ::tolower);
	def[_T("type")] = tstring(defTypeName);
	def[_T("description")] = tstring(_T("desc"));
	def[_T("settings_schema")] = PipeObject();
	auto& settingsSchema = def[_T("settings_schema")].object_items();
	schemaAddValue(settingsSchema, _T("testvalue"), SchemaValueTypeString, _T("test setting"), false);
	serviceTypes->push_back(def);

	return serviceTypes;
}

//----------------------------------------------------------------------------------------------------------------------

IPipeExtensionService* PipeExtensionPurple::create(const tstring& serviceType, const tstring& address, const tstring& path, PipeObjectPtr settings) {
	if(serviceType == _T("irc")) {
		return (_services[address] = new ServiceIRC(address, path, settings));
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
