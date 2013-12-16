module derelict.purple.dnssrv;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.account;

extern (C):

alias _PurpleSrvTxtQueryData PurpleSrvTxtQueryData;
alias _PurpleSrvResponse PurpleSrvResponse;
alias _PurpleTxtResponse PurpleTxtResponse;
alias _PurpleSrvTxtQueryData PurpleSrvQueryData;
alias void function (_PurpleSrvTxtQueryData*, _GList*) PurpleSrvTxtQueryResolvedCallback;
alias void function (_PurpleSrvTxtQueryData*, const(char)*) PurpleSrvTxtQueryFailedCallback;
alias _Anonymous_0 PurpleSrvTxtQueryUiOps;
alias void function (_PurpleSrvResponse*, int, void*) PurpleSrvCallback;
alias void function (_GList*, void*) PurpleTxtCallback;

enum PurpleDnsType
{
	PurpleDnsTypeTxt = 16,
	PurpleDnsTypeSrv = 33
}

struct _PurpleSrvResponse
{
	char[256] hostname;
	int port;
	int weight;
	int pref;
}

struct _PurpleTxtResponse
{
	char* content;
}

struct _Anonymous_0
{
	gboolean function (PurpleSrvTxtQueryData*, PurpleSrvTxtQueryResolvedCallback, PurpleSrvTxtQueryFailedCallback) resolve;
	void function (PurpleSrvTxtQueryData*) destroy;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurpleSrvTxtQueryData;


alias da_purple_srv_resolve_account = PurpleSrvTxtQueryData* function(PurpleAccount* account, const(char)* protocol, const(char)* transport, const(char)* domain, PurpleSrvCallback cb, gpointer extradata);																																																						/* da_purple_srv_resolve_account purple_srv_resolve_account; */
alias da_purple_srv_resolve = PurpleSrvTxtQueryData* function(const(char)* protocol, const(char)* transport, const(char)* domain, PurpleSrvCallback cb, gpointer extradata);																																																						/* da_purple_srv_resolve purple_srv_resolve; */
alias da_purple_srv_cancel = void function(PurpleSrvTxtQueryData* query_data);																																																						/* da_purple_srv_cancel purple_srv_cancel; */
alias da_purple_txt_resolve_account = PurpleSrvTxtQueryData* function(PurpleAccount* account, const(char)* owner, const(char)* domain, PurpleTxtCallback cb, gpointer extradata);																																																						/* da_purple_txt_resolve_account purple_txt_resolve_account; */
alias da_purple_txt_resolve = PurpleSrvTxtQueryData* function(const(char)* owner, const(char)* domain, PurpleTxtCallback cb, gpointer extradata);																																																						/* da_purple_txt_resolve purple_txt_resolve; */
alias da_purple_txt_cancel = void function(PurpleSrvTxtQueryData* query_data);																																																						/* da_purple_txt_cancel purple_txt_cancel; */
alias da_purple_txt_response_get_content = const(gchar)* function(PurpleTxtResponse* response);																																																						/* da_purple_txt_response_get_content purple_txt_response_get_content; */
alias da_purple_txt_response_destroy = void function(PurpleTxtResponse* response);																																																						/* da_purple_txt_response_destroy purple_txt_response_destroy; */
alias da_purple_srv_txt_query_destroy = void function(PurpleSrvTxtQueryData* query_data);																																																						/* da_purple_srv_txt_query_destroy purple_srv_txt_query_destroy; */
alias da_purple_srv_txt_query_set_ui_ops = void function(PurpleSrvTxtQueryUiOps* ops);																																																						/* da_purple_srv_txt_query_set_ui_ops purple_srv_txt_query_set_ui_ops; */
alias da_purple_srv_txt_query_get_ui_ops = PurpleSrvTxtQueryUiOps* function();																																																						/* da_purple_srv_txt_query_get_ui_ops purple_srv_txt_query_get_ui_ops; */
alias da_purple_srv_txt_query_get_query = char* function(PurpleSrvTxtQueryData* query_data);																																																						/* da_purple_srv_txt_query_get_query purple_srv_txt_query_get_query; */
alias da_purple_srv_txt_query_get_type = int function(PurpleSrvTxtQueryData* query_data);																																																						/* da_purple_srv_txt_query_get_type purple_srv_txt_query_get_type; */
