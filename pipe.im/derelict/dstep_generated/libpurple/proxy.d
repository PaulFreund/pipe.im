extern (C):

alias _Anonymous_0 PurpleProxyType;
alias _Anonymous_1 PurpleProxyInfo;
alias _PurpleProxyConnectData PurpleProxyConnectData;
alias void function (void*, int, const(char)*) PurpleProxyConnectFunction;

enum _Anonymous_0
{
	PURPLE_PROXY_USE_GLOBAL = -1,
	PURPLE_PROXY_NONE = 0,
	PURPLE_PROXY_HTTP = 1,
	PURPLE_PROXY_SOCKS4 = 2,
	PURPLE_PROXY_SOCKS5 = 3,
	PURPLE_PROXY_USE_ENVVAR = 4,
	PURPLE_PROXY_TOR = 5
}

struct _Anonymous_1
{
	PurpleProxyType type;
	char* host;
	int port;
	char* username;
	char* password;
}

struct _PurpleProxyConnectData;


PurpleProxyInfo* purple_proxy_info_new ();
void purple_proxy_info_destroy (PurpleProxyInfo* info);
void purple_proxy_info_set_type (PurpleProxyInfo* info, PurpleProxyType type);
void purple_proxy_info_set_host (PurpleProxyInfo* info, const(char)* host);
void purple_proxy_info_set_port (PurpleProxyInfo* info, int port);
void purple_proxy_info_set_username (PurpleProxyInfo* info, const(char)* username);
void purple_proxy_info_set_password (PurpleProxyInfo* info, const(char)* password);
PurpleProxyType purple_proxy_info_get_type (const(PurpleProxyInfo)* info);
const(char)* purple_proxy_info_get_host (const(PurpleProxyInfo)* info);
int purple_proxy_info_get_port (const(PurpleProxyInfo)* info);
const(char)* purple_proxy_info_get_username (const(PurpleProxyInfo)* info);
const(char)* purple_proxy_info_get_password (const(PurpleProxyInfo)* info);
PurpleProxyInfo* purple_global_proxy_get_info ();
void purple_global_proxy_set_info (PurpleProxyInfo* info);
void* purple_proxy_get_handle ();
void purple_proxy_init ();
void purple_proxy_uninit ();
PurpleProxyInfo* purple_proxy_get_setup (PurpleAccount* account);
PurpleProxyConnectData* purple_proxy_connect (void* handle, PurpleAccount* account, const(char)* host, int port, PurpleProxyConnectFunction connect_cb, gpointer data);
PurpleProxyConnectData* purple_proxy_connect_udp (void* handle, PurpleAccount* account, const(char)* host, int port, PurpleProxyConnectFunction connect_cb, gpointer data);
PurpleProxyConnectData* purple_proxy_connect_socks5_account (void* handle, PurpleAccount* account, PurpleProxyInfo* gpi, const(char)* host, int port, PurpleProxyConnectFunction connect_cb, gpointer data);
PurpleProxyConnectData* purple_proxy_connect_socks5 (void* handle, PurpleProxyInfo* gpi, const(char)* host, int port, PurpleProxyConnectFunction connect_cb, gpointer data);
void purple_proxy_connect_cancel (PurpleProxyConnectData* connect_data);
void purple_proxy_connect_cancel_with_handle (void* handle);