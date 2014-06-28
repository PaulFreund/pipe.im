//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterfaceAccount.h"
#include "PurpleInterfaceContact.h"

using namespace std;

//======================================================================================================================

PurpleInterfaceAccount::PurpleInterfaceAccount(const tstring& address, const tstring& path, PipeObjectPtr settings, const tstring& instance_name, const tstring& instance_description)
	: PipeServiceNodeBase(address, path, settings, _T("purple_account"), _T("A purple chat account"), instance_name, instance_description, _T("purple_account")) {

	auto cmdJoin = PipeSchema::Create(PipeSchemaTypeString).title(_T("Channel")).description(_T("Channel name"));
	addCommand(_T("join"), _T("Test"), cmdJoin, [&](PipeObject& message) {
		auto ref = message[_T("ref")].string_value();
		if(!message.count(_T("data")) || !message[_T("data")].is_string()) {
			pushOutgoing(ref, _T("error"), _T("Missing command data"));
			return;
		}

		tstring channel = message[_T("data")].string_value();

		PurpleConnection* connection = purple_account_get_connection(_account);
		PurplePluginProtocolInfo* info = PURPLE_PLUGIN_PROTOCOL_INFO(purple_connection_get_prpl(connection));
		//// TODO: This should be a command type later
		//for(GList* comp = info->chat_info(connection); comp; comp = comp->next) {
		//	proto_chat_entry* entry = reinterpret_cast<proto_chat_entry*>(comp->data);
		//}

		PurpleBuddy* channelBuddy = purple_buddy_new(_account, channel.c_str(), channel.c_str());

		tstring channelAddressName = timplode(texplode(channel, TokenAddressSeparator), _T('_'));
		tstring channelAddress = _address + TokenAddressSeparator + channelAddressName;
		addChild(channelAddress, make_shared<PurpleInterfaceContact>(channelAddress, _path, _settings, channel, _T(""), channelBuddy));

		GHashTable* components = info->chat_info_defaults(connection, channel.c_str());

		serv_join_chat(connection, components);

		g_hash_table_destroy(components);
	});
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

PurpleInterfaceContact* PurpleInterfaceAccount::contactService(PurpleBuddy* buddy) {
	auto& childNodes = children();
	for(auto it = begin(childNodes); it != end(childNodes); it++) {
		PurpleInterfaceContact* contact = reinterpret_cast<PurpleInterfaceContact*>(it->second.get());
		if(contact->buddyHandle() == buddy)
			return contact;
	}

	return nullptr;
}

PurpleInterfaceContact* PurpleInterfaceAccount::contactService(tstring name) {
	auto& childNodes = children();
	for(auto it = begin(childNodes); it != end(childNodes); it++) {
		PurpleInterfaceContact* contact = reinterpret_cast<PurpleInterfaceContact*>(it->second.get());
		if(contact->buddyName() == name)
			return contact;
	}

	// TODO: What to do when Contact does not exist ( IRC for example )
	return nullptr;
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
	tstring contactName = safe_tstring(buddy->name);
	contactName = timplode(texplode(contactName, TokenAddressSeparator), _T('_'));
	tstring contactAddress = _address + TokenAddressSeparator + contactName;
	addChild(contactAddress, make_shared<PurpleInterfaceContact>(contactAddress, _path, _settings, safe_tstring(buddy->name), _T(""), buddy));
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onBuddyRemoved(PurpleBuddy* buddy) {
	tstring contactName = safe_tstring(buddy->name);
	timplode(texplode(contactName, TokenAddressSeparator), _T('_'));
	tstring contactAddress = _address + TokenAddressSeparator + contactName;
	removeChild(contactAddress);
}

//----------------------------------------------------------------------------------------------------------------------
void PurpleInterfaceAccount::onMessageUnknownSender(tstring sender, tstring message) {
	// TODO
	pushOutgoing(_T(""), _T("message_unknown_sender"), sender + _T(": ") + message);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterfaceAccount::onInvited(tstring who, tstring where, tstring message, GHashTable* joinData) {
	// TODO
	pushOutgoing(_T(""), _T("invited"), _T("From: ") + who + _T(" to ") + where + _T(" (") + message + _T(")"));
}

//======================================================================================================================
