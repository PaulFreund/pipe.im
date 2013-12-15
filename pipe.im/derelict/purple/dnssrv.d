module derelict.purple.dnssrv;

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


PurpleSrvTxtQueryData* purple_srv_resolve_account (PurpleAccount* account, const(char)* protocol, const(char)* transport, const(char)* domain, PurpleSrvCallback cb, gpointer extradata);
PurpleSrvTxtQueryData* purple_srv_resolve (const(char)* protocol, const(char)* transport, const(char)* domain, PurpleSrvCallback cb, gpointer extradata);
void purple_srv_cancel (PurpleSrvTxtQueryData* query_data);
PurpleSrvTxtQueryData* purple_txt_resolve_account (PurpleAccount* account, const(char)* owner, const(char)* domain, PurpleTxtCallback cb, gpointer extradata);
PurpleSrvTxtQueryData* purple_txt_resolve (const(char)* owner, const(char)* domain, PurpleTxtCallback cb, gpointer extradata);
void purple_txt_cancel (PurpleSrvTxtQueryData* query_data);
const(gchar)* purple_txt_response_get_content (PurpleTxtResponse* response);
void purple_txt_response_destroy (PurpleTxtResponse* response);
void purple_srv_txt_query_destroy (PurpleSrvTxtQueryData* query_data);
void purple_srv_txt_query_set_ui_ops (PurpleSrvTxtQueryUiOps* ops);
PurpleSrvTxtQueryUiOps* purple_srv_txt_query_get_ui_ops ();
char* purple_srv_txt_query_get_query (PurpleSrvTxtQueryData* query_data);
int purple_srv_txt_query_get_type (PurpleSrvTxtQueryData* query_data);