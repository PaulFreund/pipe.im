//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterfaceAccount.h"
#include <purple.h>

using namespace std;

//======================================================================================================================

PurpleInterfaceAccount::PurpleInterfaceAccount(const tstring& protocol_id, const tstring& type, const tstring& description, const tstring& address, const tstring& path, PipeObjectPtr settings)
	: PipeServiceNodeBase(type, description, address, path, settings) {

	cout << PipeJson(*settings).dump();

	PurpleAccount* account = purple_account_new(_T(""), protocol_id.c_str());

	const tstring tokenSplit = _T("split_");
	for(auto& setting : *settings) {
		if(setting.first == _T("base_user")) {
			purple_account_set_username(account, setting.second.string_value().c_str());
		}
		else if(setting.first == _T("base_password")) {
			purple_account_set_password(account, setting.second.string_value().c_str());
		}
		else {
			if(setting.second.is_string())
				purple_account_set_string(account, setting.first.c_str(), setting.second.string_value().c_str());
			else if(setting.second.is_bool())
				purple_account_set_bool(account, setting.first.c_str(), setting.second.bool_value());
			else if(setting.second.is_integer())
				purple_account_set_int(account, setting.first.c_str(), setting.second.int_value());
		}
	}

	purple_account_set_enabled(account, PurpleInterface::InterfaceID.c_str(), true);
	
	// TODO: Error handling
}

//----------------------------------------------------------------------------------------------------------------------

PurpleInterfaceAccount::~PurpleInterfaceAccount() {
	// TODO: Disconnecting
}

//----------------------------------------------------------------------------------------------------------------------

PipeArrayPtr PurpleInterfaceAccount::receive() {
	// Trigger event loop
	g_main_context_iteration(g_main_context_default(), false);
	
	return PipeServiceNodeBase::receive();
}


//======================================================================================================================
