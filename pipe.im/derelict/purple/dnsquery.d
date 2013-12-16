module derelict.purple.dnsquery;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gslist;
import derelict.purple.account;

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


alias da_purple_dnsquery_a_account = PurpleDnsQueryData* function(PurpleAccount* account, const(char)* hostname, int port, PurpleDnsQueryConnectFunction callback, gpointer data);																																																						/* da_purple_dnsquery_a_account purple_dnsquery_a_account; */
alias da_purple_dnsquery_a = PurpleDnsQueryData* function(const(char)* hostname, int port, PurpleDnsQueryConnectFunction callback, gpointer data);																																																						/* da_purple_dnsquery_a purple_dnsquery_a; */
alias da_purple_dnsquery_destroy = void function(PurpleDnsQueryData* query_data);																																																						/* da_purple_dnsquery_destroy purple_dnsquery_destroy; */
alias da_purple_dnsquery_set_ui_ops = void function(PurpleDnsQueryUiOps* ops);																																																						/* da_purple_dnsquery_set_ui_ops purple_dnsquery_set_ui_ops; */
alias da_purple_dnsquery_get_ui_ops = PurpleDnsQueryUiOps* function();																																																						/* da_purple_dnsquery_get_ui_ops purple_dnsquery_get_ui_ops; */
alias da_purple_dnsquery_get_host = char* function(PurpleDnsQueryData* query_data);																																																						/* da_purple_dnsquery_get_host purple_dnsquery_get_host; */
alias da_purple_dnsquery_get_port = ushort function(PurpleDnsQueryData* query_data);																																																						/* da_purple_dnsquery_get_port purple_dnsquery_get_port; */
alias da_purple_dnsquery_init = void function();																																																						/* da_purple_dnsquery_init purple_dnsquery_init; */
alias da_purple_dnsquery_uninit = void function();																																																						/* da_purple_dnsquery_uninit purple_dnsquery_uninit; */
