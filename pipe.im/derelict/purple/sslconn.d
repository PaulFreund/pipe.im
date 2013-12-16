module derelict.purple.sslconn;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.account;
import derelict.purple.proxy;
import derelict.purple.certificate;

extern (C):

alias _Anonymous_0 PurpleSslErrorType;
alias _PurpleSslConnection PurpleSslConnection;
alias void function (void*, _PurpleSslConnection*, ) PurpleSslInputFunction;
alias void function (_PurpleSslConnection*, _Anonymous_0, void*) PurpleSslErrorFunction;
alias _Anonymous_1 PurpleSslOps;

enum _Anonymous_0
{
	PURPLE_SSL_HANDSHAKE_FAILED = 1,
	PURPLE_SSL_CONNECT_FAILED = 2,
	PURPLE_SSL_CERTIFICATE_INVALID = 3
}

struct _PurpleSslConnection
{
	char* host;
	int port;
	void* connect_cb_data;
	PurpleSslInputFunction connect_cb;
	PurpleSslErrorFunction error_cb;
	void* recv_cb_data;
	PurpleSslInputFunction recv_cb;
	int fd;
	guint inpa;
	PurpleProxyConnectData* connect_data;
	void* private_data;
	PurpleCertificateVerifier* verifier;
}

struct _Anonymous_1
{
	gboolean function () init;
	void function () uninit;
	void function (PurpleSslConnection*) connectfunc;
	void function (PurpleSslConnection*) close;
	size_t function (PurpleSslConnection*, void*, size_t) read;
	size_t function (PurpleSslConnection*, const(void)*, size_t) write;
	GList* function (PurpleSslConnection*) get_peer_certificates;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

alias da_purple_ssl_is_supported = gboolean function();																																																						/* da_purple_ssl_is_supported purple_ssl_is_supported; */
alias da_purple_ssl_strerror = const(gchar)* function(PurpleSslErrorType error);																																																						/* da_purple_ssl_strerror purple_ssl_strerror; */
alias da_purple_ssl_connect = PurpleSslConnection* function(PurpleAccount* account, const(char)* host, int port, PurpleSslInputFunction func, PurpleSslErrorFunction error_func, void* data);																																																						/* da_purple_ssl_connect purple_ssl_connect; */
alias da_purple_ssl_connect_with_ssl_cn = PurpleSslConnection* function(PurpleAccount* account, const(char)* host, int port, PurpleSslInputFunction func, PurpleSslErrorFunction error_func, const(char)* ssl_host, void* data);																																																						/* da_purple_ssl_connect_with_ssl_cn purple_ssl_connect_with_ssl_cn; */
alias da_purple_ssl_connect_fd = PurpleSslConnection* function(PurpleAccount* account, int fd, PurpleSslInputFunction func, PurpleSslErrorFunction error_func, void* data);																																																						/* da_purple_ssl_connect_fd purple_ssl_connect_fd; */
alias da_purple_ssl_connect_with_host_fd = PurpleSslConnection* function(PurpleAccount* account, int fd, PurpleSslInputFunction func, PurpleSslErrorFunction error_func, const(char)* host, void* data);																																																						/* da_purple_ssl_connect_with_host_fd purple_ssl_connect_with_host_fd; */
alias da_purple_ssl_input_add = void function(PurpleSslConnection* gsc, PurpleSslInputFunction func, void* data);																																																						/* da_purple_ssl_input_add purple_ssl_input_add; */
alias da_purple_ssl_close = void function(PurpleSslConnection* gsc);																																																						/* da_purple_ssl_close purple_ssl_close; */
alias da_purple_ssl_read = size_t function(PurpleSslConnection* gsc, void* buffer, size_t len);																																																						/* da_purple_ssl_read purple_ssl_read; */
alias da_purple_ssl_write = size_t function(PurpleSslConnection* gsc, const(void)* buffer, size_t len);																																																						/* da_purple_ssl_write purple_ssl_write; */
alias da_purple_ssl_get_peer_certificates = GList* function(PurpleSslConnection* gsc);																																																						/* da_purple_ssl_get_peer_certificates purple_ssl_get_peer_certificates; */
alias da_purple_ssl_set_ops = void function(PurpleSslOps* ops);																																																						/* da_purple_ssl_set_ops purple_ssl_set_ops; */
alias da_purple_ssl_get_ops = PurpleSslOps* function();																																																						/* da_purple_ssl_get_ops purple_ssl_get_ops; */
alias da_purple_ssl_init = void function();																																																						/* da_purple_ssl_init purple_ssl_init; */
alias da_purple_ssl_uninit = void function();																																																						/* da_purple_ssl_uninit purple_ssl_uninit; */
