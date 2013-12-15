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

PurpleAccount* purple_account_new (const(char)* username, const(char)* protocol_id);
void purple_account_destroy (PurpleAccount* account);
void purple_account_connect (PurpleAccount* account);
void purple_account_set_register_callback (PurpleAccount* account, PurpleAccountRegistrationCb cb, void* user_data);
void purple_account_register (PurpleAccount* account);
void purple_account_unregister (PurpleAccount* account, PurpleAccountUnregistrationCb cb, void* user_data);
void purple_account_disconnect (PurpleAccount* account);
void purple_account_notify_added (PurpleAccount* account, const(char)* remote_user, const(char)* id, const(char)* alias_, const(char)* message);
void purple_account_request_add (PurpleAccount* account, const(char)* remote_user, const(char)* id, const(char)* alias_, const(char)* message);
void* purple_account_request_authorization (PurpleAccount* account, const(char)* remote_user, const(char)* id, const(char)* alias_, const(char)* message, gboolean on_list, PurpleAccountRequestAuthorizationCb auth_cb, PurpleAccountRequestAuthorizationCb deny_cb, void* user_data);
void purple_account_request_close_with_account (PurpleAccount* account);
void purple_account_request_close (void* ui_handle);
void purple_account_request_password (PurpleAccount* account, GCallback ok_cb, GCallback cancel_cb, void* user_data);
void purple_account_request_change_password (PurpleAccount* account);
void purple_account_request_change_user_info (PurpleAccount* account);
void purple_account_set_username (PurpleAccount* account, const(char)* username);
void purple_account_set_password (PurpleAccount* account, const(char)* password);
void purple_account_set_alias (PurpleAccount* account, const(char)* alias_);
void purple_account_set_user_info (PurpleAccount* account, const(char)* user_info);
void purple_account_set_buddy_icon_path (PurpleAccount* account, const(char)* path);
void purple_account_set_protocol_id (PurpleAccount* account, const(char)* protocol_id);
void purple_account_set_connection (PurpleAccount* account, PurpleConnection* gc);
void purple_account_set_remember_password (PurpleAccount* account, gboolean value);
void purple_account_set_check_mail (PurpleAccount* account, gboolean value);
void purple_account_set_enabled (PurpleAccount* account, const(char)* ui, gboolean value);
void purple_account_set_proxy_info (PurpleAccount* account, PurpleProxyInfo* info);
void purple_account_set_privacy_type (PurpleAccount* account, PurplePrivacyType privacy_type);
void purple_account_set_status_types (PurpleAccount* account, GList* status_types);
void purple_account_set_status (PurpleAccount* account, const(char)* status_id, gboolean active, ...);
void purple_account_set_status_list (PurpleAccount* account, const(char)* status_id, gboolean active, GList* attrs);
void purple_account_set_public_alias (PurpleAccount* account, const(char)* alias_, PurpleSetPublicAliasSuccessCallback success_cb, PurpleSetPublicAliasFailureCallback failure_cb);
void purple_account_get_public_alias (PurpleAccount* account, PurpleGetPublicAliasSuccessCallback success_cb, PurpleGetPublicAliasFailureCallback failure_cb);
gboolean purple_account_get_silence_suppression (const(PurpleAccount)* account);
void purple_account_set_silence_suppression (PurpleAccount* account, gboolean value);
void purple_account_clear_settings (PurpleAccount* account);
void purple_account_remove_setting (PurpleAccount* account, const(char)* setting);
void purple_account_set_int (PurpleAccount* account, const(char)* name, int value);
void purple_account_set_string (PurpleAccount* account, const(char)* name, const(char)* value);
void purple_account_set_bool (PurpleAccount* account, const(char)* name, gboolean value);
void purple_account_set_ui_int (PurpleAccount* account, const(char)* ui, const(char)* name, int value);
void purple_account_set_ui_string (PurpleAccount* account, const(char)* ui, const(char)* name, const(char)* value);
void purple_account_set_ui_bool (PurpleAccount* account, const(char)* ui, const(char)* name, gboolean value);
gboolean purple_account_is_connected (const(PurpleAccount)* account);
gboolean purple_account_is_connecting (const(PurpleAccount)* account);
gboolean purple_account_is_disconnected (const(PurpleAccount)* account);
const(char)* purple_account_get_username (const(PurpleAccount)* account);
const(char)* purple_account_get_password (const(PurpleAccount)* account);
const(char)* purple_account_get_alias (const(PurpleAccount)* account);
const(char)* purple_account_get_user_info (const(PurpleAccount)* account);
const(char)* purple_account_get_buddy_icon_path (const(PurpleAccount)* account);
const(char)* purple_account_get_protocol_id (const(PurpleAccount)* account);
const(char)* purple_account_get_protocol_name (const(PurpleAccount)* account);
PurpleConnection* purple_account_get_connection (const(PurpleAccount)* account);
const(gchar)* purple_account_get_name_for_display (const(PurpleAccount)* account);
gboolean purple_account_get_remember_password (const(PurpleAccount)* account);
gboolean purple_account_get_check_mail (const(PurpleAccount)* account);
gboolean purple_account_get_enabled (const(PurpleAccount)* account, const(char)* ui);
PurpleProxyInfo* purple_account_get_proxy_info (const(PurpleAccount)* account);
PurplePrivacyType purple_account_get_privacy_type (const(PurpleAccount)* account);
PurpleStatus* purple_account_get_active_status (const(PurpleAccount)* account);
PurpleStatus* purple_account_get_status (const(PurpleAccount)* account, const(char)* status_id);
PurpleStatusType* purple_account_get_status_type (const(PurpleAccount)* account, const(char)* id);
PurpleStatusType* purple_account_get_status_type_with_primitive (const(PurpleAccount)* account, PurpleStatusPrimitive primitive);
PurplePresence* purple_account_get_presence (const(PurpleAccount)* account);
gboolean purple_account_is_status_active (const(PurpleAccount)* account, const(char)* status_id);
GList* purple_account_get_status_types (const(PurpleAccount)* account);
int purple_account_get_int (const(PurpleAccount)* account, const(char)* name, int default_value);
const(char)* purple_account_get_string (const(PurpleAccount)* account, const(char)* name, const(char)* default_value);
gboolean purple_account_get_bool (const(PurpleAccount)* account, const(char)* name, gboolean default_value);
int purple_account_get_ui_int (const(PurpleAccount)* account, const(char)* ui, const(char)* name, int default_value);
const(char)* purple_account_get_ui_string (const(PurpleAccount)* account, const(char)* ui, const(char)* name, const(char)* default_value);
gboolean purple_account_get_ui_bool (const(PurpleAccount)* account, const(char)* ui, const(char)* name, gboolean default_value);
PurpleLog* purple_account_get_log (PurpleAccount* account, gboolean create);
void purple_account_destroy_log (PurpleAccount* account);
void purple_account_add_buddy (PurpleAccount* account, PurpleBuddy* buddy);
void purple_account_add_buddy_with_invite (PurpleAccount* account, PurpleBuddy* buddy, const(char)* message);
void purple_account_add_buddies (PurpleAccount* account, GList* buddies);
void purple_account_add_buddies_with_invite (PurpleAccount* account, GList* buddies, const(char)* message);
void purple_account_remove_buddy (PurpleAccount* account, PurpleBuddy* buddy, PurpleGroup* group);
void purple_account_remove_buddies (PurpleAccount* account, GList* buddies, GList* groups);
void purple_account_remove_group (PurpleAccount* account, PurpleGroup* group);
void purple_account_change_password (PurpleAccount* account, const(char)* orig_pw, const(char)* new_pw);
gboolean purple_account_supports_offline_message (PurpleAccount* account, PurpleBuddy* buddy);
const(PurpleConnectionErrorInfo)* purple_account_get_current_error (PurpleAccount* account);
void purple_account_clear_current_error (PurpleAccount* account);
void purple_accounts_add (PurpleAccount* account);
void purple_accounts_remove (PurpleAccount* account);
void purple_accounts_delete (PurpleAccount* account);
void purple_accounts_reorder (PurpleAccount* account, gint new_index);
GList* purple_accounts_get_all ();
GList* purple_accounts_get_all_active ();
PurpleAccount* purple_accounts_find (const(char)* name, const(char)* protocol);
void purple_accounts_restore_current_statuses ();
void purple_accounts_set_ui_ops (PurpleAccountUiOps* ops);
PurpleAccountUiOps* purple_accounts_get_ui_ops ();
void* purple_accounts_get_handle ();
void purple_accounts_init ();
void purple_accounts_uninit ();