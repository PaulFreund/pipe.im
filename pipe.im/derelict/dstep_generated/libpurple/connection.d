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

void purple_connection_new (PurpleAccount* account, gboolean regist, const(char)* password);
void purple_connection_new_unregister (PurpleAccount* account, const(char)* password, PurpleAccountUnregistrationCb cb, void* user_data);
void purple_connection_destroy (PurpleConnection* gc);
void purple_connection_set_state (PurpleConnection* gc, PurpleConnectionState state);
void purple_connection_set_account (PurpleConnection* gc, PurpleAccount* account);
void purple_connection_set_display_name (PurpleConnection* gc, const(char)* name);
void purple_connection_set_protocol_data (PurpleConnection* connection, void* proto_data);
PurpleConnectionState purple_connection_get_state (const(PurpleConnection)* gc);
PurpleAccount* purple_connection_get_account (const(PurpleConnection)* gc);
PurplePlugin* purple_connection_get_prpl (const(PurpleConnection)* gc);
const(char)* purple_connection_get_password (const(PurpleConnection)* gc);
const(char)* purple_connection_get_display_name (const(PurpleConnection)* gc);
void* purple_connection_get_protocol_data (const(PurpleConnection)* connection);
void purple_connection_update_progress (PurpleConnection* gc, const(char)* text, size_t step, size_t count);
void purple_connection_notice (PurpleConnection* gc, const(char)* text);
void purple_connection_error (PurpleConnection* gc, const(char)* reason);
void purple_connection_error_reason (PurpleConnection* gc, PurpleConnectionError reason, const(char)* description);
void purple_connection_ssl_error (PurpleConnection* gc, PurpleSslErrorType ssl_error);
gboolean purple_connection_error_is_fatal (PurpleConnectionError reason);
void purple_connections_disconnect_all ();
GList* purple_connections_get_all ();
GList* purple_connections_get_connecting ();
void purple_connections_set_ui_ops (PurpleConnectionUiOps* ops);
PurpleConnectionUiOps* purple_connections_get_ui_ops ();
void purple_connections_init ();
void purple_connections_uninit ();
void* purple_connections_get_handle ();