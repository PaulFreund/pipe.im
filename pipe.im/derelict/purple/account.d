module derelict.purple.account;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.ghash;
import derelict.glib.glist;
import derelict.glib.gslist;
import derelict.purple.log;
import derelict.purple.status;
import derelict.purple.connection;
import derelict.purple.proxy;
import derelict.purple.privacy;
import derelict.purple.blist;
import derelict.purple.status;

extern (C):

alias _PurpleAccountUiOps PurpleAccountUiOps;
alias _PurpleAccount PurpleAccount;
alias int function (_PurpleAccount*) PurpleFilterAccountFunc;
alias void function (void*) PurpleAccountRequestAuthorizationCb;
alias void function (_PurpleAccount*, int, void*) PurpleAccountRegistrationCb;
alias void function (_PurpleAccount*, int, void*) PurpleAccountUnregistrationCb;
alias void function (_PurpleAccount*, const(char)*) PurpleSetPublicAliasSuccessCallback;
alias void function (_PurpleAccount*, const(char)*) PurpleSetPublicAliasFailureCallback;
alias void function (_PurpleAccount*, const(char)*) PurpleGetPublicAliasSuccessCallback;
alias void function (_PurpleAccount*, const(char)*) PurpleGetPublicAliasFailureCallback;
alias _Anonymous_0 PurpleAccountRequestType;
alias _Anonymous_1 PurpleAccountRequestResponse;

enum _Anonymous_0
{
	PURPLE_ACCOUNT_REQUEST_AUTHORIZATION = 0
}

enum _Anonymous_1
{
	PURPLE_ACCOUNT_RESPONSE_IGNORE = -2,
	PURPLE_ACCOUNT_RESPONSE_DENY = -1,
	PURPLE_ACCOUNT_RESPONSE_PASS = 0,
	PURPLE_ACCOUNT_RESPONSE_ACCEPT = 1
}

struct _PurpleAccountUiOps
{
	void function (PurpleAccount*, const(char)*, const(char)*, const(char)*, const(char)*) notify_added;
	void function (PurpleAccount*, PurpleStatus*) status_changed;
	void function (PurpleAccount*, const(char)*, const(char)*, const(char)*, const(char)*) request_add;
	void* function (PurpleAccount*, const(char)*, const(char)*, const(char)*, const(char)*, gboolean, PurpleAccountRequestAuthorizationCb, PurpleAccountRequestAuthorizationCb, void*) request_authorize;
	void function (void*) close_account_request;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurpleAccount
{
	char* username;
	char* alias_;
	char* password;
	char* user_info;
	char* buddy_icon_path;
	gboolean remember_pass;
	char* protocol_id;
	PurpleConnection* gc;
	gboolean disconnecting;
	GHashTable* settings;
	GHashTable* ui_settings;
	PurpleProxyInfo* proxy_info;
	GSList* permit;
	GSList* deny;
	PurplePrivacyType perm_deny;
	GList* status_types;
	PurplePresence* presence;
	PurpleLog* system_log;
	void* ui_data;
	PurpleAccountRegistrationCb registration_cb;
	void* registration_cb_user_data;
	gpointer priv;
}

alias da_purple_account_new = PurpleAccount* function(const(char)* username, const(char)* protocol_id);																																																						/* da_purple_account_new purple_account_new; */
alias da_purple_account_destroy = void function(PurpleAccount* account);																																																						/* da_purple_account_destroy purple_account_destroy; */
alias da_purple_account_connect = void function(PurpleAccount* account);																																																						/* da_purple_account_connect purple_account_connect; */
alias da_purple_account_set_register_callback = void function(PurpleAccount* account, PurpleAccountRegistrationCb cb, void* user_data);																																																						/* da_purple_account_set_register_callback purple_account_set_register_callback; */
alias da_purple_account_register = void function(PurpleAccount* account);																																																						/* da_purple_account_register purple_account_register; */
alias da_purple_account_unregister = void function(PurpleAccount* account, PurpleAccountUnregistrationCb cb, void* user_data);																																																						/* da_purple_account_unregister purple_account_unregister; */
alias da_purple_account_disconnect = void function(PurpleAccount* account);																																																						/* da_purple_account_disconnect purple_account_disconnect; */
alias da_purple_account_notify_added = void function(PurpleAccount* account, const(char)* remote_user, const(char)* id, const(char)* alias_, const(char)* message);																																																						/* da_purple_account_notify_added purple_account_notify_added; */
alias da_purple_account_request_add = void function(PurpleAccount* account, const(char)* remote_user, const(char)* id, const(char)* alias_, const(char)* message);																																																						/* da_purple_account_request_add purple_account_request_add; */
alias da_purple_account_request_authorization = void* function(PurpleAccount* account, const(char)* remote_user, const(char)* id, const(char)* alias_, const(char)* message, gboolean on_list, PurpleAccountRequestAuthorizationCb auth_cb, PurpleAccountRequestAuthorizationCb deny_cb, void* user_data);																																																						/* da_purple_account_request_authorization purple_account_request_authorization; */
alias da_purple_account_request_close_with_account = void function(PurpleAccount* account);																																																						/* da_purple_account_request_close_with_account purple_account_request_close_with_account; */
alias da_purple_account_request_close = void function(void* ui_handle);																																																						/* da_purple_account_request_close purple_account_request_close; */
alias da_purple_account_request_password = void function(PurpleAccount* account, GCallback ok_cb, GCallback cancel_cb, void* user_data);																																																						/* da_purple_account_request_password purple_account_request_password; */
alias da_purple_account_request_change_password = void function(PurpleAccount* account);																																																						/* da_purple_account_request_change_password purple_account_request_change_password; */
alias da_purple_account_request_change_user_info = void function(PurpleAccount* account);																																																						/* da_purple_account_request_change_user_info purple_account_request_change_user_info; */
alias da_purple_account_set_username = void function(PurpleAccount* account, const(char)* username);																																																						/* da_purple_account_set_username purple_account_set_username; */
alias da_purple_account_set_password = void function(PurpleAccount* account, const(char)* password);																																																						/* da_purple_account_set_password purple_account_set_password; */
alias da_purple_account_set_alias = void function(PurpleAccount* account, const(char)* alias_);																																																						/* da_purple_account_set_alias purple_account_set_alias; */
alias da_purple_account_set_user_info = void function(PurpleAccount* account, const(char)* user_info);																																																						/* da_purple_account_set_user_info purple_account_set_user_info; */
alias da_purple_account_set_buddy_icon_path = void function(PurpleAccount* account, const(char)* path);																																																						/* da_purple_account_set_buddy_icon_path purple_account_set_buddy_icon_path; */
alias da_purple_account_set_protocol_id = void function(PurpleAccount* account, const(char)* protocol_id);																																																						/* da_purple_account_set_protocol_id purple_account_set_protocol_id; */
alias da_purple_account_set_connection = void function(PurpleAccount* account, PurpleConnection* gc);																																																						/* da_purple_account_set_connection purple_account_set_connection; */
alias da_purple_account_set_remember_password = void function(PurpleAccount* account, gboolean value);																																																						/* da_purple_account_set_remember_password purple_account_set_remember_password; */
alias da_purple_account_set_check_mail = void function(PurpleAccount* account, gboolean value);																																																						/* da_purple_account_set_check_mail purple_account_set_check_mail; */
alias da_purple_account_set_enabled = void function(PurpleAccount* account, const(char)* ui, gboolean value);																																																						/* da_purple_account_set_enabled purple_account_set_enabled; */
alias da_purple_account_set_proxy_info = void function(PurpleAccount* account, PurpleProxyInfo* info);																																																						/* da_purple_account_set_proxy_info purple_account_set_proxy_info; */
alias da_purple_account_set_privacy_type = void function(PurpleAccount* account, PurplePrivacyType privacy_type);																																																						/* da_purple_account_set_privacy_type purple_account_set_privacy_type; */
alias da_purple_account_set_status_types = void function(PurpleAccount* account, GList* status_types);																																																						/* da_purple_account_set_status_types purple_account_set_status_types; */
alias da_purple_account_set_status = void function(PurpleAccount* account, const(char)* status_id, gboolean active, ...);																																																						/* da_purple_account_set_status purple_account_set_status; */
alias da_purple_account_set_status_list = void function(PurpleAccount* account, const(char)* status_id, gboolean active, GList* attrs);																																																						/* da_purple_account_set_status_list purple_account_set_status_list; */
alias da_purple_account_set_public_alias = void function(PurpleAccount* account, const(char)* alias_, PurpleSetPublicAliasSuccessCallback success_cb, PurpleSetPublicAliasFailureCallback failure_cb);																																																						/* da_purple_account_set_public_alias purple_account_set_public_alias; */
alias da_purple_account_get_public_alias = void function(PurpleAccount* account, PurpleGetPublicAliasSuccessCallback success_cb, PurpleGetPublicAliasFailureCallback failure_cb);																																																						/* da_purple_account_get_public_alias purple_account_get_public_alias; */
alias da_purple_account_get_silence_suppression = gboolean function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_silence_suppression purple_account_get_silence_suppression; */
alias da_purple_account_set_silence_suppression = void function(PurpleAccount* account, gboolean value);																																																						/* da_purple_account_set_silence_suppression purple_account_set_silence_suppression; */
alias da_purple_account_clear_settings = void function(PurpleAccount* account);																																																						/* da_purple_account_clear_settings purple_account_clear_settings; */
alias da_purple_account_remove_setting = void function(PurpleAccount* account, const(char)* setting);																																																						/* da_purple_account_remove_setting purple_account_remove_setting; */
alias da_purple_account_set_int = void function(PurpleAccount* account, const(char)* name, int value);																																																						/* da_purple_account_set_int purple_account_set_int; */
alias da_purple_account_set_string = void function(PurpleAccount* account, const(char)* name, const(char)* value);																																																						/* da_purple_account_set_string purple_account_set_string; */
alias da_purple_account_set_bool = void function(PurpleAccount* account, const(char)* name, gboolean value);																																																						/* da_purple_account_set_bool purple_account_set_bool; */
alias da_purple_account_set_ui_int = void function(PurpleAccount* account, const(char)* ui, const(char)* name, int value);																																																						/* da_purple_account_set_ui_int purple_account_set_ui_int; */
alias da_purple_account_set_ui_string = void function(PurpleAccount* account, const(char)* ui, const(char)* name, const(char)* value);																																																						/* da_purple_account_set_ui_string purple_account_set_ui_string; */
alias da_purple_account_set_ui_bool = void function(PurpleAccount* account, const(char)* ui, const(char)* name, gboolean value);																																																						/* da_purple_account_set_ui_bool purple_account_set_ui_bool; */
alias da_purple_account_is_connected = gboolean function(const(PurpleAccount)* account);																																																						/* da_purple_account_is_connected purple_account_is_connected; */
alias da_purple_account_is_connecting = gboolean function(const(PurpleAccount)* account);																																																						/* da_purple_account_is_connecting purple_account_is_connecting; */
alias da_purple_account_is_disconnected = gboolean function(const(PurpleAccount)* account);																																																						/* da_purple_account_is_disconnected purple_account_is_disconnected; */
alias da_purple_account_get_username = const(char)* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_username purple_account_get_username; */
alias da_purple_account_get_password = const(char)* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_password purple_account_get_password; */
alias da_purple_account_get_alias = const(char)* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_alias purple_account_get_alias; */
alias da_purple_account_get_user_info = const(char)* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_user_info purple_account_get_user_info; */
alias da_purple_account_get_buddy_icon_path = const(char)* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_buddy_icon_path purple_account_get_buddy_icon_path; */
alias da_purple_account_get_protocol_id = const(char)* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_protocol_id purple_account_get_protocol_id; */
alias da_purple_account_get_protocol_name = const(char)* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_protocol_name purple_account_get_protocol_name; */
alias da_purple_account_get_connection = PurpleConnection* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_connection purple_account_get_connection; */
alias da_purple_account_get_name_for_display = const(gchar)* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_name_for_display purple_account_get_name_for_display; */
alias da_purple_account_get_remember_password = gboolean function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_remember_password purple_account_get_remember_password; */
alias da_purple_account_get_check_mail = gboolean function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_check_mail purple_account_get_check_mail; */
alias da_purple_account_get_enabled = gboolean function(const(PurpleAccount)* account, const(char)* ui);																																																						/* da_purple_account_get_enabled purple_account_get_enabled; */
alias da_purple_account_get_proxy_info = PurpleProxyInfo* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_proxy_info purple_account_get_proxy_info; */
alias da_purple_account_get_privacy_type = PurplePrivacyType function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_privacy_type purple_account_get_privacy_type; */
alias da_purple_account_get_active_status = PurpleStatus* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_active_status purple_account_get_active_status; */
alias da_purple_account_get_status = PurpleStatus* function(const(PurpleAccount)* account, const(char)* status_id);																																																						/* da_purple_account_get_status purple_account_get_status; */
alias da_purple_account_get_status_type = PurpleStatusType* function(const(PurpleAccount)* account, const(char)* id);																																																						/* da_purple_account_get_status_type purple_account_get_status_type; */
alias da_purple_account_get_status_type_with_primitive = PurpleStatusType* function(const(PurpleAccount)* account, PurpleStatusPrimitive primitive);																																																						/* da_purple_account_get_status_type_with_primitive purple_account_get_status_type_with_primitive; */
alias da_purple_account_get_presence = PurplePresence* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_presence purple_account_get_presence; */
alias da_purple_account_is_status_active = gboolean function(const(PurpleAccount)* account, const(char)* status_id);																																																						/* da_purple_account_is_status_active purple_account_is_status_active; */
alias da_purple_account_get_status_types = GList* function(const(PurpleAccount)* account);																																																						/* da_purple_account_get_status_types purple_account_get_status_types; */
alias da_purple_account_get_int = int function(const(PurpleAccount)* account, const(char)* name, int default_value);																																																						/* da_purple_account_get_int purple_account_get_int; */
alias da_purple_account_get_string = const(char)* function(const(PurpleAccount)* account, const(char)* name, const(char)* default_value);																																																						/* da_purple_account_get_string purple_account_get_string; */
alias da_purple_account_get_bool = gboolean function(const(PurpleAccount)* account, const(char)* name, gboolean default_value);																																																						/* da_purple_account_get_bool purple_account_get_bool; */
alias da_purple_account_get_ui_int = int function(const(PurpleAccount)* account, const(char)* ui, const(char)* name, int default_value);																																																						/* da_purple_account_get_ui_int purple_account_get_ui_int; */
alias da_purple_account_get_ui_string = const(char)* function(const(PurpleAccount)* account, const(char)* ui, const(char)* name, const(char)* default_value);																																																						/* da_purple_account_get_ui_string purple_account_get_ui_string; */
alias da_purple_account_get_ui_bool = gboolean function(const(PurpleAccount)* account, const(char)* ui, const(char)* name, gboolean default_value);																																																						/* da_purple_account_get_ui_bool purple_account_get_ui_bool; */
alias da_purple_account_get_log = PurpleLog* function(PurpleAccount* account, gboolean create);																																																						/* da_purple_account_get_log purple_account_get_log; */
alias da_purple_account_destroy_log = void function(PurpleAccount* account);																																																						/* da_purple_account_destroy_log purple_account_destroy_log; */
alias da_purple_account_add_buddy = void function(PurpleAccount* account, PurpleBuddy* buddy);																																																						/* da_purple_account_add_buddy purple_account_add_buddy; */
alias da_purple_account_add_buddy_with_invite = void function(PurpleAccount* account, PurpleBuddy* buddy, const(char)* message);																																																						/* da_purple_account_add_buddy_with_invite purple_account_add_buddy_with_invite; */
alias da_purple_account_add_buddies = void function(PurpleAccount* account, GList* buddies);																																																						/* da_purple_account_add_buddies purple_account_add_buddies; */
alias da_purple_account_add_buddies_with_invite = void function(PurpleAccount* account, GList* buddies, const(char)* message);																																																						/* da_purple_account_add_buddies_with_invite purple_account_add_buddies_with_invite; */
alias da_purple_account_remove_buddy = void function(PurpleAccount* account, PurpleBuddy* buddy, PurpleGroup* group);																																																						/* da_purple_account_remove_buddy purple_account_remove_buddy; */
alias da_purple_account_remove_buddies = void function(PurpleAccount* account, GList* buddies, GList* groups);																																																						/* da_purple_account_remove_buddies purple_account_remove_buddies; */
alias da_purple_account_remove_group = void function(PurpleAccount* account, PurpleGroup* group);																																																						/* da_purple_account_remove_group purple_account_remove_group; */
alias da_purple_account_change_password = void function(PurpleAccount* account, const(char)* orig_pw, const(char)* new_pw);																																																						/* da_purple_account_change_password purple_account_change_password; */
alias da_purple_account_supports_offline_message = gboolean function(PurpleAccount* account, PurpleBuddy* buddy);																																																						/* da_purple_account_supports_offline_message purple_account_supports_offline_message; */
alias da_purple_account_get_current_error = const(PurpleConnectionErrorInfo)* function(PurpleAccount* account);																																																						/* da_purple_account_get_current_error purple_account_get_current_error; */
alias da_purple_account_clear_current_error = void function(PurpleAccount* account);																																																						/* da_purple_account_clear_current_error purple_account_clear_current_error; */
alias da_purple_accounts_add = void function(PurpleAccount* account);																																																						/* da_purple_accounts_add purple_accounts_add; */
alias da_purple_accounts_remove = void function(PurpleAccount* account);																																																						/* da_purple_accounts_remove purple_accounts_remove; */
alias da_purple_accounts_delete = void function(PurpleAccount* account);																																																						/* da_purple_accounts_delete purple_accounts_delete; */
alias da_purple_accounts_reorder = void function(PurpleAccount* account, gint new_index);																																																						/* da_purple_accounts_reorder purple_accounts_reorder; */
alias da_purple_accounts_get_all = GList* function();																																																						/* da_purple_accounts_get_all purple_accounts_get_all; */
alias da_purple_accounts_get_all_active = GList* function();																																																						/* da_purple_accounts_get_all_active purple_accounts_get_all_active; */
alias da_purple_accounts_find = PurpleAccount* function(const(char)* name, const(char)* protocol);																																																						/* da_purple_accounts_find purple_accounts_find; */
alias da_purple_accounts_restore_current_statuses = void function();																																																						/* da_purple_accounts_restore_current_statuses purple_accounts_restore_current_statuses; */
alias da_purple_accounts_set_ui_ops = void function(PurpleAccountUiOps* ops);																																																						/* da_purple_accounts_set_ui_ops purple_accounts_set_ui_ops; */
alias da_purple_accounts_get_ui_ops = PurpleAccountUiOps* function();																																																						/* da_purple_accounts_get_ui_ops purple_accounts_get_ui_ops; */
alias da_purple_accounts_get_handle = void* function();																																																						/* da_purple_accounts_get_handle purple_accounts_get_handle; */
alias da_purple_accounts_init = void function();																																																						/* da_purple_accounts_init purple_accounts_init; */
alias da_purple_accounts_uninit = void function();																																																						/* da_purple_accounts_uninit purple_accounts_uninit; */
