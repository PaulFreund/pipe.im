//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterfaceAccount.h"

using namespace std;

//======================================================================================================================

PurpleInterfaceAccount::PurpleInterfaceAccount(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& instance_name, const tstring& instance_description)
	: PipeServiceNodeBase(address, path, settings, _T("purple_account"), _T("A purple chat account"), instance_name, instance_description, _T("purple_account")) {
	// TODO: (GENERIC) Add autojoin to IRC plugin settings?
}

//----------------------------------------------------------------------------------------------------------------------

PurpleInterfaceAccount::~PurpleInterfaceAccount() {
	if(_account != nullptr)
		purple_account_destroy(_account);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::init(const tstring& protocol_id) {
	_account = purple_account_new(_T(""), protocol_id.c_str());
	if(_account == nullptr) {
		pushOutgoing(_T(""), _T("error"), _T("Account could not be created"));
		return;
	}

	for(auto& setting : *_settings) {
		if(setting.first == _T("base_user")) {
			purple_account_set_username(_account, setting.second.string_value().c_str());
		}
		else if(setting.first == _T("base_password")) {
			purple_account_set_password(_account, setting.second.string_value().c_str());
		}
		else {
			if(setting.second.is_string())
				purple_account_set_string(_account, setting.first.c_str(), setting.second.string_value().c_str());
			else if(setting.second.is_bool())
				purple_account_set_bool(_account, setting.first.c_str(), setting.second.bool_value());
			else if(setting.second.is_integer())
				purple_account_set_int(_account, setting.first.c_str(), setting.second.int_value());
		}
	}

	purple_account_set_enabled(_account, PurpleInterface::InterfaceID.c_str(), true);

	// TODO: Error handling
}

//----------------------------------------------------------------------------------------------------------------------

PipeArrayPtr PurpleInterfaceAccount::receive() {
	// Trigger event loop
	if(_account != nullptr)
		g_main_context_iteration(g_main_context_default(), false);
	
	return PipeServiceNodeBase::receive();
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onConnecting() {
	// TODO
	pushOutgoing(_T(""), _T("connecting"), _T(""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onDisabled() {
	// TODO
	pushOutgoing(_T(""), _T("disabled"), _T(""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onEnabled() {
	// TODO
	pushOutgoing(_T(""), _T("enabled"), _T(""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onAuthRequest(tstring user, tstring message) {
	// TODO
	pushOutgoing(_T(""), _T("auth_request"), _T("From: ") + user + _T(" (") + message + _T(")"));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onAuthDenied(tstring user) {
	// TODO
	pushOutgoing(_T(""), _T("auth_denied"), user);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onAuthGranted(tstring user) {
	// TODO
	pushOutgoing(_T(""), _T("auth_granted"), user);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onSignedOn() {
	// TODO
	pushOutgoing(_T(""), _T("signed_on"), _T(""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onSignedOff() {
	// TODO
	pushOutgoing(_T(""), _T("signed_off"), _T(""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onStatusChanged() {
	// TODO
	pushOutgoing(_T(""), _T("status_changed"), _T(""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onActionsChanged() {
	// TODO
	pushOutgoing(_T(""), _T("actions_changed"), _T(""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onErrorChanged(tstring oldError, tstring newError) {
	// TODO
	pushOutgoing(_T(""), _T("error_changed"), _T("From \"") + oldError + _T("\" to \"") + newError + _T("\""));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onConnectionError(tstring error, tstring description) {
	// TODO
	pushOutgoing(_T(""), _T("connection_error"), error + _T(" (") + description + _T(")"));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onBuddyAdded(PurpleBuddy* buddy) {
	// TODO
//	pushOutgoing(_T(""), _T("buddy_added"), name + _T(" (") + alias + _T(")"));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onBuddyRemoved(PurpleBuddy* buddy) {
	// TODO
//	pushOutgoing(_T(""), _T("buddy_removed"), name);
}

//======================================================================================================================
