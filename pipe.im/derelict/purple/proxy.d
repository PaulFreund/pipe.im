module derelict.purple.proxy;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.purple.account;
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


alias da_purple_proxy_info_new = PurpleProxyInfo* function();																																																						/* da_purple_proxy_info_new purple_proxy_info_new; */
alias da_purple_proxy_info_destroy = void function(PurpleProxyInfo* info);																																																						/* da_purple_proxy_info_destroy purple_proxy_info_destroy; */
alias da_purple_proxy_info_set_type = void function(PurpleProxyInfo* info, PurpleProxyType type);																																																						/* da_purple_proxy_info_set_type purple_proxy_info_set_type; */
alias da_purple_proxy_info_set_host = void function(PurpleProxyInfo* info, const(char)* host);																																																						/* da_purple_proxy_info_set_host purple_proxy_info_set_host; */
alias da_purple_proxy_info_set_port = void function(PurpleProxyInfo* info, int port);																																																						/* da_purple_proxy_info_set_port purple_proxy_info_set_port; */
alias da_purple_proxy_info_set_username = void function(PurpleProxyInfo* info, const(char)* username);																																																						/* da_purple_proxy_info_set_username purple_proxy_info_set_username; */
alias da_purple_proxy_info_set_password = void function(PurpleProxyInfo* info, const(char)* password);																																																						/* da_purple_proxy_info_set_password purple_proxy_info_set_password; */
alias da_purple_proxy_info_get_type = PurpleProxyType function(const(PurpleProxyInfo)* info);																																																						/* da_purple_proxy_info_get_type purple_proxy_info_get_type; */
alias da_purple_proxy_info_get_host = const(char)* function(const(PurpleProxyInfo)* info);																																																						/* da_purple_proxy_info_get_host purple_proxy_info_get_host; */
alias da_purple_proxy_info_get_port = int function(const(PurpleProxyInfo)* info);																																																						/* da_purple_proxy_info_get_port purple_proxy_info_get_port; */
alias da_purple_proxy_info_get_username = const(char)* function(const(PurpleProxyInfo)* info);																																																						/* da_purple_proxy_info_get_username purple_proxy_info_get_username; */
alias da_purple_proxy_info_get_password = const(char)* function(const(PurpleProxyInfo)* info);																																																						/* da_purple_proxy_info_get_password purple_proxy_info_get_password; */
alias da_purple_global_proxy_get_info = PurpleProxyInfo* function();																																																						/* da_purple_global_proxy_get_info purple_global_proxy_get_info; */
alias da_purple_global_proxy_set_info = void function(PurpleProxyInfo* info);																																																						/* da_purple_global_proxy_set_info purple_global_proxy_set_info; */
alias da_purple_proxy_get_handle = void* function();																																																						/* da_purple_proxy_get_handle purple_proxy_get_handle; */
alias da_purple_proxy_init = void function();																																																						/* da_purple_proxy_init purple_proxy_init; */
alias da_purple_proxy_uninit = void function();																																																						/* da_purple_proxy_uninit purple_proxy_uninit; */
alias da_purple_proxy_get_setup = PurpleProxyInfo* function(PurpleAccount* account);																																																						/* da_purple_proxy_get_setup purple_proxy_get_setup; */
alias da_purple_proxy_connect = PurpleProxyConnectData* function(void* handle, PurpleAccount* account, const(char)* host, int port, PurpleProxyConnectFunction connect_cb, gpointer data);																																																						/* da_purple_proxy_connect purple_proxy_connect; */
alias da_purple_proxy_connect_udp = PurpleProxyConnectData* function(void* handle, PurpleAccount* account, const(char)* host, int port, PurpleProxyConnectFunction connect_cb, gpointer data);																																																						/* da_purple_proxy_connect_udp purple_proxy_connect_udp; */
alias da_purple_proxy_connect_socks5_account = PurpleProxyConnectData* function(void* handle, PurpleAccount* account, PurpleProxyInfo* gpi, const(char)* host, int port, PurpleProxyConnectFunction connect_cb, gpointer data);																																																						/* da_purple_proxy_connect_socks5_account purple_proxy_connect_socks5_account; */
alias da_purple_proxy_connect_socks5 = PurpleProxyConnectData* function(void* handle, PurpleProxyInfo* gpi, const(char)* host, int port, PurpleProxyConnectFunction connect_cb, gpointer data);																																																						/* da_purple_proxy_connect_socks5 purple_proxy_connect_socks5; */
alias da_purple_proxy_connect_cancel = void function(PurpleProxyConnectData* connect_data);																																																						/* da_purple_proxy_connect_cancel purple_proxy_connect_cancel; */
alias da_purple_proxy_connect_cancel_with_handle = void function(void* handle);																																																						/* da_purple_proxy_connect_cancel_with_handle purple_proxy_connect_cancel_with_handle; */
