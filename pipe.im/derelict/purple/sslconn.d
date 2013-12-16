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

gboolean purple_ssl_is_supported ();
const(gchar)* purple_ssl_strerror (PurpleSslErrorType error);
PurpleSslConnection* purple_ssl_connect (PurpleAccount* account, const(char)* host, int port, PurpleSslInputFunction func, PurpleSslErrorFunction error_func, void* data);
PurpleSslConnection* purple_ssl_connect_with_ssl_cn (PurpleAccount* account, const(char)* host, int port, PurpleSslInputFunction func, PurpleSslErrorFunction error_func, const(char)* ssl_host, void* data);
PurpleSslConnection* purple_ssl_connect_fd (PurpleAccount* account, int fd, PurpleSslInputFunction func, PurpleSslErrorFunction error_func, void* data);
PurpleSslConnection* purple_ssl_connect_with_host_fd (PurpleAccount* account, int fd, PurpleSslInputFunction func, PurpleSslErrorFunction error_func, const(char)* host, void* data);
void purple_ssl_input_add (PurpleSslConnection* gsc, PurpleSslInputFunction func, void* data);
void purple_ssl_close (PurpleSslConnection* gsc);
size_t purple_ssl_read (PurpleSslConnection* gsc, void* buffer, size_t len);
size_t purple_ssl_write (PurpleSslConnection* gsc, const(void)* buffer, size_t len);
GList* purple_ssl_get_peer_certificates (PurpleSslConnection* gsc);
void purple_ssl_set_ops (PurpleSslOps* ops);
PurpleSslOps* purple_ssl_get_ops ();
void purple_ssl_init ();
void purple_ssl_uninit ();