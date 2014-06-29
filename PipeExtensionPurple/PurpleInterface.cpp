//======================================================================================================================

#include "CommonHeader.h"
#include "PurpleInterface.h"
#include "PurpleInterfaceAccount.h"
#include "PurpleInterfaceContact.h"
#include "PipeExtensionPurple.h"

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

const tstring PurpleInterface::InterfaceID = _T("pipe.im");
PipeExtensionPurple* PurpleInterface::InstanceContext = nullptr;

//======================================================================================================================

inline PurpleInterfaceAccount* accountService(void* data, PurpleAccount* account) {
	if(data == nullptr) { return nullptr; }
	PipeExtensionPurple* itf = nullptr;
	try {
		itf = reinterpret_cast<PipeExtensionPurple*>(data);
	} catch(...) {}

	if(itf != nullptr)
		return itf->account(account);

	return nullptr;
}

//======================================================================================================================

void* purple_cb_ops_request_input(const TCHAR*title, const TCHAR*primary, const TCHAR*secondary, const TCHAR*default_value, gboolean multiline, gboolean masked, gchar* hint, const TCHAR*ok_text, GCallback ok_cb, const TCHAR*cancel_text, GCallback cancel_cb, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data) {
	PurpleInterfaceAccount* service = accountService(PurpleInterface::InstanceContext, account);
	if(service == nullptr) { return nullptr; }

	// TODO: Call ITF
	return nullptr;
}

void* purple_cb_ops_request_choice(const TCHAR*title, const TCHAR*primary, const TCHAR*secondary, int default_value, const TCHAR*ok_text, GCallback ok_cb, const TCHAR*cancel_text, GCallback cancel_cb, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data, va_list choices) {
	PurpleInterfaceAccount* service = accountService(PurpleInterface::InstanceContext, account);
	if(service == nullptr) { return nullptr; }

	// TODO: Call ITF
	return nullptr;
}

void* purple_cb_ops_request_action(const TCHAR*title, const TCHAR*primary, const TCHAR*secondary, int default_action, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data, size_t action_count, va_list actions) {
	PurpleInterfaceAccount* service = accountService(PurpleInterface::InstanceContext, account);
	if(service == nullptr) { return nullptr; }

	// TODO: Call ITF
	return nullptr;
}

void* purple_cb_ops_request_fields(const TCHAR*title, const TCHAR*primary, const TCHAR*secondary, PurpleRequestFields* fields, const TCHAR*ok_text, GCallback ok_cb, const TCHAR*cancel_text, GCallback cancel_cb, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data) {
	PurpleInterfaceAccount* service = accountService(PurpleInterface::InstanceContext, account);
	if(service == nullptr) { return nullptr; }

	// TODO: Call ITF
	return nullptr;
}

void* purple_cb_ops_request_file(const TCHAR*title, const TCHAR*filename, gboolean savedialog, GCallback ok_cb, GCallback cancel_cb, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data) {
	PurpleInterfaceAccount* service = accountService(PurpleInterface::InstanceContext, account);
	if(service == nullptr) { return nullptr; }

	// TODO: Call ITF
	return nullptr;
}

void purple_cb_ops_close_request(PurpleRequestType type, void* ui_handle) {
}

void* purple_cb_ops_request_folder(const TCHAR*title, const TCHAR*dirname, GCallback ok_cb, GCallback cancel_cb, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, void* user_data) {
	PurpleInterfaceAccount* service = accountService(PurpleInterface::InstanceContext, account);
	if(service == nullptr) { return nullptr; }

	// TODO: Call ITF
	return nullptr;
}

void* purple_cb_ops_request_action_with_icon(const TCHAR*title, const TCHAR*primary, const TCHAR*secondary, int default_action, PurpleAccount* account, const TCHAR*who, PurpleConversation* conv, gconstpointer icon_data, gsize icon_size, void* user_data, size_t action_count, va_list actions) {
	PurpleInterfaceAccount* service = accountService(PurpleInterface::InstanceContext, account);
	if(service == nullptr) { return nullptr; }

	// TODO: Call ITF
	return nullptr;
}

//======================================================================================================================

PurpleInterface::PurpleInterface(PipeExtensionPurple* instance, const tstring& path) {
	PurpleInterface::InstanceContext = instance;
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

		purple_util_set_user_dir(path.c_str());
		purple_debug_set_enabled(FALSE);

		_eventloopUIOps = { 
			g_timeout_add, 
			g_source_remove, 
			glib_input_add, 
			g_source_remove, 
			nullptr, 
			g_timeout_add_seconds, 
			nullptr, nullptr, nullptr};

		purple_eventloop_set_ui_ops(&_eventloopUIOps);

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


		if(!purple_core_init(PurpleInterface::InterfaceID.c_str())) {
			throw tstring(_T("libpurple initialization failed. Dumping core.\n" "Please report this!"));
		}

		purple_set_blist(purple_blist_new());
		purple_blist_load();

		initSignalCallbacks();
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
		def[_T("protocol_id")] = tstring(infoPlugin->id);
		def[_T("settings_schema")] = PipeSchema(PipeSchemaTypeObject);

		auto& settingsSchema = reinterpret_cast<PipeSchema&>(def[_T("settings_schema")].object_items());
		
		// Split defines the format of the usernam
		tstring usernameDescription = _T("Username");
		if(infoProtocol->user_splits != nullptr) {
			usernameDescription = _T("Username in format: Username");
			for(GList* split = infoProtocol->user_splits; split; split = split->next) {
				PurpleAccountUserSplit* splitData = reinterpret_cast<PurpleAccountUserSplit*>(split->data);
				usernameDescription += splitData->field_sep;
				usernameDescription += tstring(splitData->text);
			}
		}

		// Every account has a username
		settingsSchema.property(_T("base_user"), PipeSchemaTypeString).title(_T("User")).description(usernameDescription);

		// Some accounts have passwords
		if(!(infoProtocol->options & OPT_PROTO_NO_PASSWORD))
			settingsSchema.property(_T("base_password"), PipeSchemaTypeString).title(_T("Password")).description(_T("Password"));

		// Most accounts have options
		for(GList* protocolOption = infoProtocol->protocol_options; protocolOption; protocolOption = protocolOption->next) {
			PurpleAccountOption* option = (PurpleAccountOption *)protocolOption->data;

			PurplePrefType type = purple_account_option_get_type(option);
			tstring key(purple_account_option_get_setting(option));
			tstring description(purple_account_option_get_text(option));

			switch(type) {
				case PURPLE_PREF_BOOLEAN: {
					settingsSchema.property(key, PipeSchemaTypeBoolean).title(key).description(description).defaultValue(static_cast<bool>(option->default_value.boolean));
					break;
				}
				case PURPLE_PREF_INT: {
					settingsSchema.property(key, PipeSchemaTypeInteger).title(key).description(description).defaultValue(static_cast<int>(option->default_value.integer));
					break;
				}
				case PURPLE_PREF_STRING: {
					auto& prop = settingsSchema.property(key, PipeSchemaTypeString).title(key).description(description);
					if(option->default_value.string != nullptr) {
						tstring defaultValue(option->default_value.string);
						if(!defaultValue.empty()) { prop.defaultValue(defaultValue); }
					}
					break;
				}

				case PURPLE_PREF_STRING_LIST: {
					PipeArray defaults;
					tstring defaultValue = _T("");
					for(GList* def = purple_account_option_get_list(option); def; def = def->next) {
						PurpleKeyValuePair* defaultData = (PurpleKeyValuePair*)def->data;
						tstring currentValue = tstring(reinterpret_cast<char*>(defaultData->value));
						defaults.push_back(currentValue);
						if(def == option->default_value.list) {
							defaultValue = currentValue;
						}
					}
	
					settingsSchema.property(key, PipeSchemaTypeString).title(key).description(description).enumTypes(defaults).defaultValue(defaultValue);
					break;
				}
				default: { continue; }
			}
		}

		if(infoProtocol->options & OPT_PROTO_PASSWORD_OPTIONAL) {
			vector<tstring> required;
			for(auto& prop : settingsSchema.properties()) {
				if(prop.first != _T("base_password")) { required.push_back(prop.first); }
			}
			settingsSchema.required(required);
		}
		
		protocolsList->push_back(def);
	}

	return protocolsList;
}

//======================================================================================================================

inline tstring connectionErrorString(PurpleConnectionError error) {
	switch(error) {
		case PURPLE_CONNECTION_ERROR_NETWORK_ERROR: { return _T("network_error"); break; }
		case PURPLE_CONNECTION_ERROR_INVALID_USERNAME: { return _T("invalid_username"); break; }
		case PURPLE_CONNECTION_ERROR_AUTHENTICATION_FAILED: { return _T("authentication_failed"); break; }
		case PURPLE_CONNECTION_ERROR_AUTHENTICATION_IMPOSSIBLE: { return _T("authentication_impossible"); break; }
		case PURPLE_CONNECTION_ERROR_NO_SSL_SUPPORT: { return _T("no_ssl_support"); break; }
		case PURPLE_CONNECTION_ERROR_ENCRYPTION_ERROR: { return _T("encryption_error"); break; }
		case PURPLE_CONNECTION_ERROR_NAME_IN_USE: { return _T("name_in_use"); break; }
		case PURPLE_CONNECTION_ERROR_INVALID_SETTINGS: { return _T("invalid_settings"); break; }
		case PURPLE_CONNECTION_ERROR_CERT_NOT_PROVIDED: { return _T("cert_not_provided"); break; }
		case PURPLE_CONNECTION_ERROR_CERT_UNTRUSTED: { return _T("cert_untrusted"); break; }
		case PURPLE_CONNECTION_ERROR_CERT_EXPIRED: { return _T("cert_expired"); break; }
		case PURPLE_CONNECTION_ERROR_CERT_NOT_ACTIVATED: { return _T("cert_not_activated"); break; }
		case PURPLE_CONNECTION_ERROR_CERT_HOSTNAME_MISMATCH: { return _T("cert_hostname_mismatch"); break; }
		case PURPLE_CONNECTION_ERROR_CERT_FINGERPRINT_MISMATCH: { return _T("cert_fingerprint_mismatch"); break; }
		case PURPLE_CONNECTION_ERROR_CERT_SELF_SIGNED: { return _T("cert_self_signed"); break; }
		case PURPLE_CONNECTION_ERROR_CERT_OTHER_ERROR: { return _T("cert_other_error"); break; }
		case PURPLE_CONNECTION_ERROR_OTHER_ERROR: { return _T("other_error"); break; }
	}
	return _T("");
}

void purple_cb_account_connecting(PurpleAccount* account, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	service->onConnecting();
}

void purple_cb_account_disabled(PurpleAccount* account, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	service->onDisabled();
}

void purple_cb_account_enabled(PurpleAccount* account, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	service->onEnabled();
}

void purple_cb_account_actions_changed(PurpleAccount* account, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	service->onActionsChanged();
}

gint purple_cb_account_authorization_requested(PurpleAccount* account, const TCHAR* remoteUser, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return 0; }
	service->onAuthRequest(safe_tstring(remoteUser));
	return PURPLE_ACCOUNT_RESPONSE_PASS;
}

gint purple_cb_account_authorization_requested_with_message(PurpleAccount* account, const TCHAR* remoteUser, const TCHAR* message, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return 0; }
	service->onAuthRequest(safe_tstring(remoteUser), safe_tstring(message));
	return PURPLE_ACCOUNT_RESPONSE_PASS;
}

void purple_cb_account_authorization_denied(PurpleAccount* account, const TCHAR* user, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	service->onAuthDenied(safe_tstring(user));
}

void purple_cb_account_authorization_granted(PurpleAccount* account, const TCHAR* user, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	service->onAuthGranted(safe_tstring(user));
}

void purple_cb_account_error_changed(PurpleAccount* account, const TCHAR* oldError, const TCHAR* newError, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	service->onErrorChanged(safe_tstring(oldError), safe_tstring(newError));
}

void purple_cb_account_signed_on(PurpleAccount* account, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	service->onSignedOn();
}

void purple_cb_account_signed_off(PurpleAccount* account, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	service->onSignedOff();
}

void purple_cb_account_connection_error(PurpleAccount* account, PurpleConnectionError type, const TCHAR* description, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	service->onConnectionError(connectionErrorString(type), safe_tstring(description));
}

void purple_cb_blist_node_added(PurpleBlistNode* node, gpointer data) {
	PurpleBlistNodeType type = purple_blist_node_get_type(node);
	PurpleInterfaceAccount* service = nullptr;

	if(type == PURPLE_BLIST_BUDDY_NODE) {
		PurpleBuddy* buddy = reinterpret_cast<PurpleBuddy*>(node);
		service = accountService(data, buddy->account);
	}
	else if(type == PURPLE_BLIST_CHAT_NODE) {
		PurpleChat* chat = reinterpret_cast<PurpleChat*>(node);
		service = accountService(data, chat->account);
	}

	if(service == nullptr) { return; }
	service->onContactAdded(node);
}

void purple_cb_blist_node_removed(PurpleBlistNode* node, gpointer data) {
	PurpleBlistNodeType type = purple_blist_node_get_type(node);
	PurpleInterfaceAccount* service = nullptr;

	if(type == PURPLE_BLIST_BUDDY_NODE) {
		PurpleBuddy* buddy = reinterpret_cast<PurpleBuddy*>(node);
		service = accountService(data, buddy->account);
	}
	else if(type == PURPLE_BLIST_CHAT_NODE) {
		PurpleChat* chat = reinterpret_cast<PurpleChat*>(node);
		service = accountService(data, chat->account);
	}

	if(service == nullptr) { return; }
	service->onContactRemoved(node);
}

void purple_cb_buddy_status_changed(PurpleBuddy* buddy, PurpleStatus* oldStatus, PurpleStatus* newStatus, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, buddy->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(reinterpret_cast<PurpleBlistNode*>(buddy));
	if(contact == nullptr) { return; }	

	contact->onStatusChanged(newStatus);
}

void purple_cb_buddy_idle_changed(PurpleBuddy* buddy, gboolean oldIdle, gboolean newIdle, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, buddy->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(reinterpret_cast<PurpleBlistNode*>(buddy));
	if(contact == nullptr) { return; }

	contact->onIdleChanged(newIdle);
}

void purple_cb_buddy_signed_on(PurpleBuddy* buddy, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, buddy->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(reinterpret_cast<PurpleBlistNode*>(buddy));
	if(contact == nullptr) { return; }

	if(buddy == nullptr) { return; }
	PurplePresence* presence = purple_buddy_get_presence(buddy);
	if(presence == nullptr) { return; }

	contact->onStatusChanged(purple_presence_get_active_status(presence));
}

void purple_cb_buddy_signed_off(PurpleBuddy* buddy, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, buddy->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(reinterpret_cast<PurpleBlistNode*>(buddy));
	if(contact == nullptr) { return; }

	if(buddy == nullptr) { return; }
	PurplePresence* presence = purple_buddy_get_presence(buddy);
	if(presence == nullptr) { return; }

	contact->onStatusChanged(purple_presence_get_active_status(presence));
}

void purple_cb_buddy_icon_changed(PurpleBuddy* buddy, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, buddy->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(reinterpret_cast<PurpleBlistNode*>(buddy));
	if(contact == nullptr) { return; }
	contact->onIconChanged();
}

void purple_cb_received_msg(PurpleAccount* account, const TCHAR* sender, const TCHAR* message, PurpleConversation *conv, PurpleMessageFlags flags, gpointer data) {
	if(!(flags & PURPLE_MESSAGE_RECV)) { return; }
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(safe_tstring(conv->name));
	if(contact == nullptr) { 
		service->onMessageUnknownSender(safe_tstring(sender), safe_tstring(message));
		return; 
	}

	contact->onMessage(safe_tstring(sender), safe_tstring(message));
}

void purple_cb_received_im_msg(PurpleAccount* account, const TCHAR* sender, const TCHAR* message, PurpleConversation *conv, PurpleMessageFlags flags, gpointer data) {
	if(conv == nullptr) { conv = purple_conversation_new(PURPLE_CONV_TYPE_IM, account, sender); }
	purple_cb_received_msg(account, sender, message, conv, flags, data);
}

void purple_cb_received_chat_msg(PurpleAccount* account, const TCHAR* sender, const TCHAR* message, PurpleConversation *conv, PurpleMessageFlags flags, gpointer data) {
	if(conv == nullptr) { conv = purple_conversation_new(PURPLE_CONV_TYPE_CHAT, account, sender); }
	purple_cb_received_msg(account, sender, message, conv, flags, data);
}

void purple_cb_conversation_created(PurpleConversation *conv, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, conv->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(safe_tstring(conv->name));
	if(contact == nullptr) { return; }
	contact->onConversationChanged(conv);	
}

void purple_cb_deleting_conversation(PurpleConversation *conv, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, conv->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(safe_tstring(conv->name));
	if(contact == nullptr) { return; }
	contact->onConversationChanged(nullptr);
}

void purple_typing_state_updated(PurpleAccount* account, const TCHAR* name, gpointer data, PurpleTypingState type) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(safe_tstring(name));
	if(contact == nullptr) { return; }
	contact->onTypingStateChanged(type);
}

void purple_cb_buddy_typing(PurpleAccount* account, const TCHAR* name, gpointer data) {
	purple_typing_state_updated(account, name, data, PURPLE_TYPING);
}

void purple_cb_buddy_typed(PurpleAccount* account, const TCHAR* name, gpointer data) {
	purple_typing_state_updated(account, name, data, PURPLE_TYPED);
}

void purple_cb_buddy_typing_stopped(PurpleAccount* account, const TCHAR* name, gpointer data) {
	purple_typing_state_updated(account, name, data, PURPLE_NOT_TYPING);
}

void purple_cb_chat_buddy_joined(PurpleConversation *conv, const TCHAR* name, PurpleConvChatBuddyFlags flags, gboolean newArrivals, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, conv->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(safe_tstring(conv->name));
	if(contact == nullptr) { return; }
	contact->onChatBuddyOnline(safe_tstring(name), flags);
}

void purple_cb_chat_buddy_flags(PurpleConversation *conv, const TCHAR* name, PurpleConvChatBuddyFlags oldFlags, PurpleConvChatBuddyFlags newFlags, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, conv->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(safe_tstring(conv->name));
	if(contact == nullptr) { return; }
	contact->onChatBuddyOnline(safe_tstring(name), newFlags);
}

void purple_cb_chat_buddy_left(PurpleConversation *conv, const TCHAR* name, const TCHAR* reason, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, conv->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(safe_tstring(conv->name));
	if(contact == nullptr) { return; }
	contact->onChatBuddyOffline(safe_tstring(name), safe_tstring(reason));
}

int purple_cb_chat_invited(PurpleAccount* account, const TCHAR* inviter, const TCHAR* chat, const TCHAR* invite_message, GHashTable* components, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, account);
	if(service == nullptr) { return PURPLE_ACCOUNT_RESPONSE_PASS; }
	service->onInvited(safe_tstring(inviter), safe_tstring(chat), safe_tstring(invite_message), components);
	return PURPLE_ACCOUNT_RESPONSE_PASS;
}

void purple_cb_chat_joined(PurpleConversation *conv, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, conv->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(safe_tstring(conv->name));
	if(contact == nullptr) { return; }
	contact->onChatStatusChanged(true);
}

void purple_cb_chat_left(PurpleConversation *conv, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, conv->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(safe_tstring(conv->name));
	if(contact == nullptr) { return; }
	contact->onChatStatusChanged(false);
}

void purple_cb_chat_topic_changed(PurpleConversation *conv, const TCHAR* user, const TCHAR* newTopic, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, conv->account);
	if(service == nullptr) { return; }
	PurpleInterfaceContact* contact = service->contactService(safe_tstring(conv->name));
	if(contact == nullptr) { return; }
	contact->onTopicChanged(safe_tstring(user), safe_tstring(newTopic));
}

void purple_cb_file_recv_accept(PurpleXfer *xfer, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, xfer->account);
	if(service == nullptr) { return; }
	service->onFileRecvUpdate(xfer);
}

void purple_cb_file_recv_start(PurpleXfer *xfer, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, xfer->account);
	if(service == nullptr) { return; }
	service->onFileRecvUpdate(xfer);
}

void purple_cb_file_recv_cancel(PurpleXfer *xfer, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, xfer->account);
	if(service == nullptr) { return; }
	service->onFileRecvUpdate(xfer);
}

void purple_cb_file_recv_complete(PurpleXfer *xfer, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, xfer->account);
	if(service == nullptr) { return; }
	service->onFileRecvUpdate(xfer);
}

void purple_cb_file_recv_request(PurpleXfer *xfer, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, xfer->account);
	if(service == nullptr) { return; }
	service->onFileRecvUpdate(xfer);
}

void purple_cb_file_send_accept(PurpleXfer *xfer, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, xfer->account);
	if(service == nullptr) { return; }
	service->onFileSendUpdate(xfer);
}

void purple_cb_file_send_start(PurpleXfer *xfer, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, xfer->account);
	if(service == nullptr) { return; }
	service->onFileSendUpdate(xfer);
}

void purple_cb_file_send_cancel(PurpleXfer *xfer, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, xfer->account);
	if(service == nullptr) { return; }
	service->onFileSendUpdate(xfer);
}

void purple_cb_file_send_complete(PurpleXfer *xfer, gpointer data) {
	PurpleInterfaceAccount* service = accountService(data, xfer->account);
	if(service == nullptr) { return; }
	service->onFileSendUpdate(xfer);
}

//----------------------------------------------------------------------------------------------------------------------

void PurpleInterface::initSignalCallbacks() {
	void* cbData = reinterpret_cast<void*>(PurpleInterface::InstanceContext);
	void* cbHandle = cbData;

	// Accounts
	auto hAccounts = purple_accounts_get_handle();
	purple_signal_connect(hAccounts, "account-connecting", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_connecting), cbData);
	purple_signal_connect(hAccounts, "account-disabled", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_disabled), cbData);
	purple_signal_connect(hAccounts, "account-enabled", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_enabled), cbData);
	purple_signal_connect(hAccounts, "account-actions-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_account_actions_changed), cbData);
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
	purple_signal_connect(hBuddyList, "blist-node-added", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_blist_node_added), cbData);
	purple_signal_connect(hBuddyList, "blist-node-removed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_blist_node_removed), cbData);
	purple_signal_connect(hBuddyList, "buddy-status-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_status_changed), cbData);
	purple_signal_connect(hBuddyList, "buddy-idle-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_idle_changed), cbData);
	purple_signal_connect(hBuddyList, "buddy-signed-on", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_signed_on), cbData);
	purple_signal_connect(hBuddyList, "buddy-signed-off", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_signed_off), cbData);
	purple_signal_connect(hBuddyList, "buddy-icon-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_icon_changed), cbData);

	// Conversation
	auto hConversations = purple_conversations_get_handle();
	purple_signal_connect(hConversations, "received-im-msg", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_received_im_msg), cbData);
	purple_signal_connect(hConversations, "received-chat-msg", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_received_chat_msg), cbData);
	purple_signal_connect(hConversations, "conversation-created", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_conversation_created), cbData);
	purple_signal_connect(hConversations, "deleting-conversation", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_deleting_conversation), cbData);
	purple_signal_connect(hConversations, "buddy-typing", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_typing), cbData);
	purple_signal_connect(hConversations, "buddy-typed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_typed), cbData);
	purple_signal_connect(hConversations, "buddy-typing-stopped", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_buddy_typing_stopped), cbData);
	purple_signal_connect(hConversations, "chat-buddy-joined", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_buddy_joined), cbData);
	purple_signal_connect(hConversations, "chat-buddy-flags", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_buddy_flags), cbData);
	purple_signal_connect(hConversations, "chat-buddy-left", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_buddy_left), cbData);
	purple_signal_connect(hConversations, "chat-invited", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_invited), cbData);
	purple_signal_connect(hConversations, "chat-joined", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_joined), cbData);
	purple_signal_connect(hConversations, "chat-left", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_left), cbData);
	purple_signal_connect(hConversations, "chat-topic-changed", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_chat_topic_changed), cbData);

	// FUTURE: File signals
	auto hXfers = purple_xfers_get_handle();
	purple_signal_connect(hXfers, "file-recv-accept", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_file_recv_accept), cbData);
	purple_signal_connect(hXfers, "file-recv-start", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_file_recv_start), cbData);
	purple_signal_connect(hXfers, "file-recv-cancel", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_file_recv_cancel), cbData);
	purple_signal_connect(hXfers, "file-recv-complete", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_file_recv_complete), cbData);
	purple_signal_connect(hXfers, "file-recv-request", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_file_recv_request), cbData);
	purple_signal_connect(hXfers, "file-send-accept", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_file_send_accept), cbData);
	purple_signal_connect(hXfers, "file-send-start", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_file_send_start), cbData);
	purple_signal_connect(hXfers, "file-send-cancel", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_file_send_cancel), cbData);
	purple_signal_connect(hXfers, "file-send-complete", cbHandle, reinterpret_cast<PurpleCallback>(&purple_cb_file_send_complete), cbData);
}

//======================================================================================================================
