module derelict.purple.connection;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.glib.gslist;
import derelict.purple.plugin;
import derelict.purple.account;
import derelict.purple.sslconn;
import core.stdc.time;

extern (C):

alias _PurpleConnection PurpleConnection;
alias _Anonymous_0 PurpleConnectionFlags;
alias _Anonymous_1 PurpleConnectionState;
alias _Anonymous_2 PurpleConnectionError;
alias _Anonymous_3 PurpleConnectionErrorInfo;
alias _Anonymous_4 PurpleConnectionUiOps;

enum _Anonymous_0
{
	PURPLE_CONNECTION_HTML = 1,
	PURPLE_CONNECTION_NO_BGCOLOR = 2,
	PURPLE_CONNECTION_AUTO_RESP = 4,
	PURPLE_CONNECTION_FORMATTING_WBFO = 8,
	PURPLE_CONNECTION_NO_NEWLINES = 16,
	PURPLE_CONNECTION_NO_FONTSIZE = 32,
	PURPLE_CONNECTION_NO_URLDESC = 64,
	PURPLE_CONNECTION_NO_IMAGES = 128,
	PURPLE_CONNECTION_ALLOW_CUSTOM_SMILEY = 256,
	PURPLE_CONNECTION_SUPPORT_MOODS = 512,
	PURPLE_CONNECTION_SUPPORT_MOOD_MESSAGES = 1024
}

enum _Anonymous_1
{
	PURPLE_DISCONNECTED = 0,
	PURPLE_CONNECTED = 1,
	PURPLE_CONNECTING = 2
}

enum _Anonymous_2
{
	PURPLE_CONNECTION_ERROR_NETWORK_ERROR = 0,
	PURPLE_CONNECTION_ERROR_INVALID_USERNAME = 1,
	PURPLE_CONNECTION_ERROR_AUTHENTICATION_FAILED = 2,
	PURPLE_CONNECTION_ERROR_AUTHENTICATION_IMPOSSIBLE = 3,
	PURPLE_CONNECTION_ERROR_NO_SSL_SUPPORT = 4,
	PURPLE_CONNECTION_ERROR_ENCRYPTION_ERROR = 5,
	PURPLE_CONNECTION_ERROR_NAME_IN_USE = 6,
	PURPLE_CONNECTION_ERROR_INVALID_SETTINGS = 7,
	PURPLE_CONNECTION_ERROR_CERT_NOT_PROVIDED = 8,
	PURPLE_CONNECTION_ERROR_CERT_UNTRUSTED = 9,
	PURPLE_CONNECTION_ERROR_CERT_EXPIRED = 10,
	PURPLE_CONNECTION_ERROR_CERT_NOT_ACTIVATED = 11,
	PURPLE_CONNECTION_ERROR_CERT_HOSTNAME_MISMATCH = 12,
	PURPLE_CONNECTION_ERROR_CERT_FINGERPRINT_MISMATCH = 13,
	PURPLE_CONNECTION_ERROR_CERT_SELF_SIGNED = 14,
	PURPLE_CONNECTION_ERROR_CERT_OTHER_ERROR = 15,
	PURPLE_CONNECTION_ERROR_OTHER_ERROR = 16
}

struct _Anonymous_3
{
	PurpleConnectionError type;
	char* description;
}

struct _Anonymous_4
{
	void function (PurpleConnection*, const(char)*, size_t, size_t) connect_progress;
	void function (PurpleConnection*) connected;
	void function (PurpleConnection*) disconnected;
	void function (PurpleConnection*, const(char)*) notice;
	void function (PurpleConnection*, const(char)*) report_disconnect;
	void function () network_connected;
	void function () network_disconnected;
	void function (PurpleConnection*, PurpleConnectionError, const(char)*) report_disconnect_reason;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
}

struct _PurpleConnection
{
	PurplePlugin* prpl;
	PurpleConnectionFlags flags;
	PurpleConnectionState state;
	PurpleAccount* account;
	char* password;
	int inpa;
	GSList* buddy_chats;
	void* proto_data;
	char* display_name;
	guint keepalive;
	gboolean wants_to_die;
	guint disconnect_timeout;
	time_t last_received;
}

alias da_purple_connection_new = void function(PurpleAccount* account, gboolean regist, const(char)* password);																																																						/* da_purple_connection_new purple_connection_new; */
alias da_purple_connection_new_unregister = void function(PurpleAccount* account, const(char)* password, PurpleAccountUnregistrationCb cb, void* user_data);																																																						/* da_purple_connection_new_unregister purple_connection_new_unregister; */
alias da_purple_connection_destroy = void function(PurpleConnection* gc);																																																						/* da_purple_connection_destroy purple_connection_destroy; */
alias da_purple_connection_set_state = void function(PurpleConnection* gc, PurpleConnectionState state);																																																						/* da_purple_connection_set_state purple_connection_set_state; */
alias da_purple_connection_set_account = void function(PurpleConnection* gc, PurpleAccount* account);																																																						/* da_purple_connection_set_account purple_connection_set_account; */
alias da_purple_connection_set_display_name = void function(PurpleConnection* gc, const(char)* name);																																																						/* da_purple_connection_set_display_name purple_connection_set_display_name; */
alias da_purple_connection_set_protocol_data = void function(PurpleConnection* connection, void* proto_data);																																																						/* da_purple_connection_set_protocol_data purple_connection_set_protocol_data; */
alias da_purple_connection_get_state = PurpleConnectionState function(const(PurpleConnection)* gc);																																																						/* da_purple_connection_get_state purple_connection_get_state; */
alias da_purple_connection_get_account = PurpleAccount* function(const(PurpleConnection)* gc);																																																						/* da_purple_connection_get_account purple_connection_get_account; */
alias da_purple_connection_get_prpl = PurplePlugin* function(const(PurpleConnection)* gc);																																																						/* da_purple_connection_get_prpl purple_connection_get_prpl; */
alias da_purple_connection_get_password = const(char)* function(const(PurpleConnection)* gc);																																																						/* da_purple_connection_get_password purple_connection_get_password; */
alias da_purple_connection_get_display_name = const(char)* function(const(PurpleConnection)* gc);																																																						/* da_purple_connection_get_display_name purple_connection_get_display_name; */
alias da_purple_connection_get_protocol_data = void* function(const(PurpleConnection)* connection);																																																						/* da_purple_connection_get_protocol_data purple_connection_get_protocol_data; */
alias da_purple_connection_update_progress = void function(PurpleConnection* gc, const(char)* text, size_t step, size_t count);																																																						/* da_purple_connection_update_progress purple_connection_update_progress; */
alias da_purple_connection_notice = void function(PurpleConnection* gc, const(char)* text);																																																						/* da_purple_connection_notice purple_connection_notice; */
alias da_purple_connection_error = void function(PurpleConnection* gc, const(char)* reason);																																																						/* da_purple_connection_error purple_connection_error; */
alias da_purple_connection_error_reason = void function(PurpleConnection* gc, PurpleConnectionError reason, const(char)* description);																																																						/* da_purple_connection_error_reason purple_connection_error_reason; */
alias da_purple_connection_ssl_error = void function(PurpleConnection* gc, PurpleSslErrorType ssl_error);																																																						/* da_purple_connection_ssl_error purple_connection_ssl_error; */
alias da_purple_connection_error_is_fatal = gboolean function(PurpleConnectionError reason);																																																						/* da_purple_connection_error_is_fatal purple_connection_error_is_fatal; */
alias da_purple_connections_disconnect_all = void function();																																																						/* da_purple_connections_disconnect_all purple_connections_disconnect_all; */
alias da_purple_connections_get_all = GList* function();																																																						/* da_purple_connections_get_all purple_connections_get_all; */
alias da_purple_connections_get_connecting = GList* function();																																																						/* da_purple_connections_get_connecting purple_connections_get_connecting; */
alias da_purple_connections_set_ui_ops = void function(PurpleConnectionUiOps* ops);																																																						/* da_purple_connections_set_ui_ops purple_connections_set_ui_ops; */
alias da_purple_connections_get_ui_ops = PurpleConnectionUiOps* function();																																																						/* da_purple_connections_get_ui_ops purple_connections_get_ui_ops; */
alias da_purple_connections_init = void function();																																																						/* da_purple_connections_init purple_connections_init; */
alias da_purple_connections_uninit = void function();																																																						/* da_purple_connections_uninit purple_connections_uninit; */
alias da_purple_connections_get_handle = void* function();																																																						/* da_purple_connections_get_handle purple_connections_get_handle; */
