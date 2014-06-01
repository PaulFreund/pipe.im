//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterface.h"
#include "PipeExtensionPurple.h"

#include <glib.h>

#ifndef _WIN32
#include <unistd.h>
#else
#pragma warning(push)
#pragma warning(disable:4005)
#include "win32/win32dep.h"
#pragma warning(pop)
#endif

using namespace std;

//======================================================================================================================


void* purple_cb_ops_request_input(const TCHAR*title, const TCHAR*primary, const TCHAR*secondary, const TCHAR*default_value, gboolean multiline, gboolean masked, gchar* hint, const TCHAR*ok_text, GCallback ok_cb, const TCHAR*cancel_text, GCallback cancel_cb, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(user_data);
	// TODO: Call ITF
	return nullptr;
}

void* purple_cb_ops_request_choice(const TCHAR*title, const TCHAR*primary, const TCHAR*secondary, int default_value, const TCHAR*ok_text, GCallback ok_cb, const TCHAR*cancel_text, GCallback cancel_cb, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data, va_list choices) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(user_data);
	// TODO: Call ITF
	return nullptr;
}

void* purple_cb_ops_request_action(const TCHAR*title, const TCHAR*primary, const TCHAR*secondary, int default_action, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data, size_t action_count, va_list actions) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(user_data);
	// TODO: Call ITF
	return nullptr;
}

void* purple_cb_ops_request_fields(const TCHAR*title, const TCHAR*primary, const TCHAR*secondary, PurpleRequestFields* fields, const TCHAR*ok_text, GCallback ok_cb, const TCHAR*cancel_text, GCallback cancel_cb, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(user_data);
	// TODO: Call ITF
	return nullptr;
}

void* purple_cb_ops_request_file(const TCHAR*title, const TCHAR*filename, gboolean savedialog, GCallback ok_cb, GCallback cancel_cb, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(user_data);
	// TODO: Call ITF
	return nullptr;
}

void purple_cb_ops_close_request(PurpleRequestType type, void* ui_handle) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(ui_handle);// not sure if right
	// TODO: Call ITF
}

void* purple_cb_ops_request_folder(const TCHAR*title, const TCHAR*dirname, GCallback ok_cb, GCallback cancel_cb, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(user_data);
	// TODO: Call ITF
	return nullptr;
}

void* purple_cb_ops_request_action_with_icon(const TCHAR*title, const TCHAR*primary, const TCHAR*secondary, int default_action, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, gconstpointer icon_data, gsize icon_size, void* user_data, size_t action_count, va_list actions) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(user_data);
	// TODO: Call ITF
	return nullptr;
}

//======================================================================================================================

PurpleInterface::PurpleInterface(const tstring& path) {
	try {
		typedef struct _PurpleGLibIOClosure { PurpleInputFunction function; guint result; gpointer data; } PurpleGLibIOClosure;

		auto glib_input_add = [](gint fd, PurpleInputCondition condition, PurpleInputFunction function, gpointer data) -> guint {
#if defined _WIN32 && !defined WINPIDGIN_USE_GLIB_IO_CHANNEL
			GIOChannel* channel = wpurple_g_io_channel_win32_new_socket(fd);
#else
			GIOChannel* channel = g_io_channel_unix_new(fd);
#endif

			GIOCondition cond = static_cast<GIOCondition>(0);
			if(condition & PURPLE_INPUT_READ) { cond = static_cast<GIOCondition>(cond | (G_IO_IN | G_IO_HUP | G_IO_ERR)); }
			if(condition & PURPLE_INPUT_WRITE) { cond = static_cast<GIOCondition>(cond | (G_IO_OUT | G_IO_HUP | G_IO_ERR | G_IO_NVAL)); }

			auto purple_glib_io_invoke = [](GIOChannel *source, GIOCondition condition, gpointer data) -> gboolean {
				PurpleGLibIOClosure* closure = reinterpret_cast<PurpleGLibIOClosure*>(data);
				PurpleInputCondition purple_cond = static_cast<PurpleInputCondition>(0);

				if(condition & (G_IO_IN | G_IO_HUP | G_IO_ERR)) { purple_cond = static_cast<PurpleInputCondition>(purple_cond | PURPLE_INPUT_READ); }
				if(condition & (G_IO_OUT | G_IO_HUP | G_IO_ERR | G_IO_NVAL)) { purple_cond = static_cast<PurpleInputCondition>(purple_cond | PURPLE_INPUT_WRITE); }

				closure->function(closure->data, g_io_channel_unix_get_fd(source), purple_cond);

				return TRUE;
			};

			auto purple_glib_io_destroy = [](gpointer data) {
				g_free(data);
			};

			PurpleGLibIOClosure *closure = g_new0(PurpleGLibIOClosure, 1);
			closure->function = function;
			closure->data = data;
			closure->result = g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, cond, purple_glib_io_invoke, closure, purple_glib_io_destroy);

			g_io_channel_unref(channel);
			return closure->result;
		};


		// TODO: Clear config dir?
		purple_util_set_user_dir(path.c_str());
		purple_debug_set_enabled(FALSE);

		// ERROR: Local scope
		_eventloopUIOps = { 
			g_timeout_add, 
			g_source_remove, 
			glib_input_add, 
			g_source_remove, 
			nullptr, 
			g_timeout_add_seconds, 
			nullptr, nullptr, nullptr};

		purple_eventloop_set_ui_ops(&_eventloopUIOps);

		// TODO: Request UI Ops
		_requestUIOps = PurpleRequestUiOps { 
			&purple_cb_ops_request_input, 
			&purple_cb_ops_request_choice, 
			&purple_cb_ops_request_action, 
			&purple_cb_ops_request_fields, 
			&purple_cb_ops_request_file, 
			&purple_cb_ops_close_request, 
			&purple_cb_ops_request_folder, 
			&purple_cb_ops_request_action_with_icon,
			nullptr, 
			nullptr, 
			nullptr 
		};

		purple_request_set_ui_ops(&_requestUIOps);


		if(!purple_core_init(_T("pipe.im"))) {
			throw tstring(_T("libpurple initialization failed. Dumping core.\n" "Please report this!"));
		}

		initSignalCallbacks();

		purple_set_blist(purple_blist_new());
	}
	
	catch(tstring error) { if(PipeExtensionPurple::ErrorCallback != nullptr) { PipeExtensionPurple::ErrorCallback(error.c_str()); } }
	catch(...) { if(PipeExtensionPurple::ErrorCallback != nullptr) { PipeExtensionPurple::ErrorCallback(_T("PipeExtensionSetPath: Unknown error")); } }
}

//----------------------------------------------------------------------------------------------------------------------

PurpleInterface::~PurpleInterface() {
}

//----------------------------------------------------------------------------------------------------------------------

PipeArrayPtr PurpleInterface::getProtocols() {
	PipeArrayPtr protocolsList = newArray();

	for(GList* protocols = purple_plugins_get_protocols() ; protocols; protocols = protocols->next) {
		PurplePlugin* plugin = reinterpret_cast<PurplePlugin*>(protocols->data);
		PurplePluginInfo* infoPlugin = plugin->info;
		PurplePluginProtocolInfo* infoProtocol = PURPLE_PLUGIN_PROTOCOL_INFO(plugin);


		PipeObject def;
		tstring defTypeName = timplode(texplode(infoPlugin->name, _T(' ')), _T('_'));
		transform(begin(defTypeName), end(defTypeName), begin(defTypeName), ::tolower);
		def[_T("type")] = tstring(defTypeName);
		def[_T("description")] = tstring(infoPlugin->description);
		def[_T("settings_schema")] = PipeSchema(PipeSchemaTypeObject);

		auto& settingsSchema = reinterpret_cast<PipeSchema&>(def[_T("settings_schema")].object_items());
		
		for(GList* protocolOption = infoProtocol->protocol_options; protocolOption; protocolOption = protocolOption->next) {
			PurpleAccountOption* option = (PurpleAccountOption *)protocolOption->data;

			PurplePrefType type = purple_account_option_get_type(option);
			tstring key(purple_account_option_get_setting(option));
			tstring description(purple_account_option_get_text(option));

			switch(type) {
				case PURPLE_PREF_BOOLEAN: {
					settingsSchema.property(key, PipeSchemaTypeBoolean).title(key).description(description);
					break;
				}
				case PURPLE_PREF_INT: {
					settingsSchema.property(key, PipeSchemaTypeInteger).title(key).description(description);
					break;
				}
				case PURPLE_PREF_STRING: {
					settingsSchema.property(key, PipeSchemaTypeString).title(key).description(description);
					break;
				}

				case PURPLE_PREF_STRING_LIST: {
					PipeArray defaults;
					for(GList* def = purple_account_option_get_list(option); def; def = def->next) {
						PurpleKeyValuePair* defaultData = (PurpleKeyValuePair*)def->data;
						defaults.push_back(defaultData->key);
					}
					settingsSchema.property(key, PipeSchemaTypeString).title(key).description(description).enumTypes(defaults);
					break;
				}
				default: { continue; }
			}
		}
		
		protocolsList->push_back(def);
	}

	return protocolsList;
}

//======================================================================================================================

gboolean purple_cb_autojoin(PurpleConnection* connection, PurpleConnectionError reason, const TCHAR* description, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
	return false;
}

void purple_cb_account_connecting(PurpleAccount* account, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_account_disabled(PurpleAccount* account, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_account_enabled(PurpleAccount* account, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_account_added(PurpleAccount* account, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_account_removed(PurpleAccount* account, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

gboolean purple_cb_account_status_changed(PurpleAccount* account, PurpleStatus* oldStatus, PurpleStatus* newStatus, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
	return false;
}

void purple_cb_account_actions_changed(PurpleAccount* account, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_account_alias_changed(PurpleAccount* account, const TCHAR* oldAlias, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

gint purple_cb_account_authorization_requested(PurpleAccount* account, const TCHAR* remoteUser, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
	return 0;
}

gint purple_cb_account_authorization_requested_with_message(PurpleAccount* account, const TCHAR* remoteUser, const TCHAR* message, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
	return 0;
}

void purple_cb_account_authorization_denied(PurpleAccount* account, const TCHAR* message, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_account_authorization_granted(PurpleAccount* account, const TCHAR* message, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_account_error_changed(PurpleAccount* account, const TCHAR* oldError, const TCHAR* newError, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_account_signed_on(PurpleAccount* account, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_account_signed_off(PurpleAccount* account, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_account_connection_error(PurpleAccount* account, PurpleConnectionError type, const TCHAR* description, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_status_changed(PurpleBuddy* buddy, PurpleStatus* oldStatus, PurpleStatus* newStatus, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_privacy_changed(PurpleBuddy* buddy, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_idle_changed(PurpleBuddy* buddy, gboolean oldIdle, gboolean newIdle, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_signed_on(PurpleBuddy* buddy, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_signed_off(PurpleBuddy* buddy, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_got_login_time(PurpleBuddy* buddy, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_blist_node_added(PurpleBlistNode* buddy, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_blist_node_removed(PurpleBlistNode* buddy, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_added(PurpleBuddy* buddy, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_removed(PurpleBuddy* buddy, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_icon_changed(PurpleBuddy* buddy, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_blist_node_extended_menu(PurpleBlistNode* buddy, GList** menu, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_blist_node_aliased(PurpleBlistNode* buddy, const TCHAR* oldAlias, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_caps_changed(PurpleBuddy* buddy, PurpleMediaCaps oldCaps, PurpleMediaCaps newCaps, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_sent_attention(PurpleAccount* account, const TCHAR* sender, PurpleConversation* conversation, guint type, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_got_attention(PurpleAccount* account, const TCHAR* sender, PurpleConversation* conversation, guint type, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_received_im_msg(PurpleAccount* account, const TCHAR* sender, const TCHAR* message, PurpleConversation *conv, PurpleMessageFlags flags, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
	//if(conv == null) {
	//	conv = purple_conversation_new(PurpleConversationType.PURPLE_CONV_TYPE_IM, account, sender);
	//}

	//client.outputString ~= "(" ~ to!string(purple_utf8_strftime("%H:%M:%S", null)) ~ ") ";
	//client.outputString ~= to!string(sender);
	//client.outputString ~= "(" ~ to!string(purple_conversation_get_name(conv)) ~ "): ";
	//client.outputString ~= to!string(message);
}

void purple_cb_blocked_im_msg(PurpleAccount* account, const TCHAR* sender, const TCHAR* message, PurpleMessageFlags flags, guint mtime, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_received_chat_msg(PurpleAccount* account, const TCHAR* sender, const TCHAR* message, PurpleConversation *conv, PurpleMessageFlags flags, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_conversation_created(PurpleConversation *conv, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_conversation_updated(PurpleConversation *conv, PurpleConvUpdateType type, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_deleting_conversation(PurpleConversation *conv, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_typing(PurpleAccount* account, const TCHAR* name, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_typed(PurpleAccount* account, const TCHAR* name, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_buddy_typing_stopped(PurpleAccount* account, const TCHAR* name, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_chat_buddy_joined(PurpleConversation *conv, const TCHAR* name, PurpleConvChatBuddyFlags flags, gboolean newArrivals, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_chat_buddy_flags(PurpleConversation *conv, const TCHAR* name, PurpleConvChatBuddyFlags oldFlags, PurpleConvChatBuddyFlags newFlags, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_chat_buddy_left(PurpleConversation *conv, const TCHAR* name, const TCHAR* reason, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_deleting_chat_buddy(PurpleConvChatBuddy* buddy, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

int purple_cb_chat_invited(PurpleAccount* account, const TCHAR* sender, const TCHAR* name, const TCHAR* message, GHashTable* inviteData, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
	return 0;
}

void purple_cb_chat_invite_blocked(PurpleAccount* account, const TCHAR* sender, const TCHAR* name, const TCHAR* message, GHashTable* inviteData, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_chat_joined(PurpleConversation *conv, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_chat_join_failed(PurpleConnection *connection, GHashTable* joinData, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_chat_left(PurpleConversation *conv, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_chat_topic_changed(PurpleConversation *conv, const TCHAR* user, const TCHAR* newTopic, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_conversation_extended_menu(PurpleConversation *conv, GList** menuData, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

void purple_cb_displaying_userinfo(PurpleAccount* account, const TCHAR* who, PurpleNotifyUserInfo* user_info, gpointer data) {
	PurpleInterface* itf = reinterpret_cast<PurpleInterface*>(data);
	// TODO: Call ITF
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterface::initSignalCallbacks() {
	void* cbData = reinterpret_cast<void*>(this);
	void* cbHandle = cbData;

	// Connection
	auto hConnections = purple_connections_get_handle();
	purple_signal_connect(hConnections, "autojoin", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_autojoin), cbData);

	// Accounts
	auto hAccounts = purple_accounts_get_handle();
	purple_signal_connect(hAccounts, "account-connecting", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_connecting), cbData);
	purple_signal_connect(hAccounts, "account-disabled", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_disabled), cbData);
	purple_signal_connect(hAccounts, "account-enabled", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_enabled), cbData);
	purple_signal_connect(hAccounts, "account-added", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_added), cbData);
	purple_signal_connect(hAccounts, "account-removed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_removed), cbData);
	purple_signal_connect(hAccounts, "account-status-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_status_changed), cbData);
	purple_signal_connect(hAccounts, "account-actions-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_actions_changed), cbData);
	purple_signal_connect(hAccounts, "account-alias-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_alias_changed), cbData);
	purple_signal_connect(hAccounts, "account-authorization-requested", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_authorization_requested), cbData);
	purple_signal_connect(hAccounts, "account-authorization-requested-with-message", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_authorization_requested_with_message), cbData);
	purple_signal_connect(hAccounts, "account-authorization-denied", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_authorization_denied), cbData);
	purple_signal_connect(hAccounts, "account-authorization-granted", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_authorization_granted), cbData);
	purple_signal_connect(hAccounts, "account-error-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_error_changed), cbData);
	purple_signal_connect(hAccounts, "account-signed-on", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_signed_on), cbData);
	purple_signal_connect(hAccounts, "account-signed-off", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_signed_off), cbData);
	purple_signal_connect(hAccounts, "account-connection-error", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_connection_error), cbData);

	// BuddyList
	auto hBuddyList = purple_blist_get_handle();
	purple_signal_connect(hBuddyList, "buddy-status-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_status_changed), cbData);
	purple_signal_connect(hBuddyList, "buddy-privacy-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_privacy_changed), cbData);
	purple_signal_connect(hBuddyList, "buddy-idle-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_idle_changed), cbData);
	purple_signal_connect(hBuddyList, "buddy-signed-on", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_signed_on), cbData);
	purple_signal_connect(hBuddyList, "buddy-signed-off", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_signed_off), cbData);
	purple_signal_connect(hBuddyList, "buddy-got-login-time", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_got_login_time), cbData);
	purple_signal_connect(hBuddyList, "blist-node-added", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_blist_node_added), cbData);
	purple_signal_connect(hBuddyList, "blist-node-removed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_blist_node_removed), cbData);
	purple_signal_connect(hBuddyList, "buddy-added", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_added), cbData);
	purple_signal_connect(hBuddyList, "buddy-removed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_removed), cbData);
	purple_signal_connect(hBuddyList, "buddy-icon-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_icon_changed), cbData);
	purple_signal_connect(hBuddyList, "blist-node-extended-menu", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_blist_node_extended_menu), cbData);
	purple_signal_connect(hBuddyList, "blist-node-aliased", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_blist_node_aliased), cbData);
	purple_signal_connect(hBuddyList, "buddy-caps-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_caps_changed), cbData);

	// Conversation
	auto hConversations = purple_conversations_get_handle();
	purple_signal_connect(hConversations, "sent-attention", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_sent_attention), cbData);
	purple_signal_connect(hConversations, "got-attention", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_got_attention), cbData);
	purple_signal_connect(hConversations, "received-im-msg", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_received_im_msg), cbData);
	purple_signal_connect(hConversations, "blocked-im-msg", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_blocked_im_msg), cbData);
	purple_signal_connect(hConversations, "received-chat-msg", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_received_chat_msg), cbData);
	purple_signal_connect(hConversations, "conversation-created", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_conversation_created), cbData);
	purple_signal_connect(hConversations, "conversation-updated", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_conversation_updated), cbData);
	purple_signal_connect(hConversations, "deleting-conversation", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_deleting_conversation), cbData);
	purple_signal_connect(hConversations, "buddy-typing", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_typing), cbData);
	purple_signal_connect(hConversations, "buddy-typed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_typed), cbData);
	purple_signal_connect(hConversations, "buddy-typing-stopped", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_typing_stopped), cbData);
	purple_signal_connect(hConversations, "chat-buddy-joined", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_buddy_joined), cbData);
	purple_signal_connect(hConversations, "chat-buddy-flags", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_buddy_flags), cbData);
	purple_signal_connect(hConversations, "chat-buddy-left", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_buddy_left), cbData);
	purple_signal_connect(hConversations, "deleting-chat-buddy", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_deleting_chat_buddy), cbData);
	purple_signal_connect(hConversations, "chat-invited", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_invited), cbData);
	purple_signal_connect(hConversations, "chat-invite-blocked", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_invite_blocked), cbData);
	purple_signal_connect(hConversations, "chat-joined", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_joined), cbData);
	purple_signal_connect(hConversations, "chat-join-failed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_join_failed), cbData);
	purple_signal_connect(hConversations, "chat-left", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_left), cbData);
	purple_signal_connect(hConversations, "chat-topic-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_topic_changed), cbData);
	purple_signal_connect(hConversations, "conversation-extended-menu", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_conversation_extended_menu), cbData);

	// Notify
	auto hNotify = purple_notify_get_handle();
	purple_signal_connect(hNotify, "displaying-userinfo", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_displaying_userinfo), cbData);
}

//======================================================================================================================
