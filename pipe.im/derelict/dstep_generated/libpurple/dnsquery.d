extern (C):

alias _PurpleDnsQueryData PurpleDnsQueryData;
alias void function (_GSList*, void*, const(char)*) PurpleDnsQueryConnectFunction;
alias void function (_PurpleDnsQueryData*, _GSList*) PurpleDnsQueryResolvedCallback;
alias void function (_PurpleDnsQueryData*, const(char)*) PurpleDnsQueryFailedCallback;
alias _Anonymous_0 PurpleDnsQueryUiOps;

struct _Anonymous_0
{
	gboolean function (PurpleDnsQueryData*, PurpleDnsQueryResolvedCallback, PurpleDnsQueryFailedCallback) resolve_host;
	void function (PurpleDnsQueryData*) destroy;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurpleDnsQueryData;


PurpleDnsQueryData* purple_dnsquery_a_account (PurpleAccount* account, const(char)* hostname, int port, PurpleDnsQueryConnectFunction callback, gpointer data);
PurpleDnsQueryData* purple_dnsquery_a (const(char)* hostname, int port, PurpleDnsQueryConnectFunction callback, gpointer data);
void purple_dnsquery_destroy (PurpleDnsQueryData* query_data);
void purple_dnsquery_set_ui_ops (PurpleDnsQueryUiOps* ops);
PurpleDnsQueryUiOps* purple_dnsquery_get_ui_ops ();
char* purple_dnsquery_get_host (PurpleDnsQueryData* query_data);
ushort purple_dnsquery_get_port (PurpleDnsQueryData* query_data);
void purple_dnsquery_init ();
void purple_dnsquery_uninit ();