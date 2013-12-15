module derelict.glib.ghook;

extern (C):

alias _GHook GHook;
alias _GHookList GHookList;
alias int function (_GHook*, _GHook*) GHookCompareFunc;
alias int function (_GHook*, void*) GHookFindFunc;
alias void function (_GHook*, void*) GHookMarshaller;
alias int function (_GHook*, void*) GHookCheckMarshaller;
alias void function (void*) GHookFunc;
alias int function (void*) GHookCheckFunc;
alias void function (_GHookList*, _GHook*) GHookFinalizeFunc;
alias _Anonymous_0 GHookFlagMask;

enum _Anonymous_0
{
	G_HOOK_FLAG_ACTIVE = 1,
	G_HOOK_FLAG_IN_CALL = 2,
	G_HOOK_FLAG_MASK = 15
}

struct _GHookList
{
	gulong seq_id;
	guint hook_size;
	guint is_setup;
	GHook* hooks;
	gpointer dummy3;
	GHookFinalizeFunc finalize_hook;
	gpointer[2] dummy;
}

struct _GHook
{
	gpointer data;
	GHook* next;
	GHook* prev;
	guint ref_count;
	gulong hook_id;
	guint flags;
	gpointer func;
	GDestroyNotify destroy;
}

void g_hook_list_init (GHookList* hook_list, guint hook_size);
void g_hook_list_clear (GHookList* hook_list);
GHook* g_hook_alloc (GHookList* hook_list);
void g_hook_free (GHookList* hook_list, GHook* hook);
GHook* g_hook_ref (GHookList* hook_list, GHook* hook);
void g_hook_unref (GHookList* hook_list, GHook* hook);
gboolean g_hook_destroy (GHookList* hook_list, gulong hook_id);
void g_hook_destroy_link (GHookList* hook_list, GHook* hook);
void g_hook_prepend (GHookList* hook_list, GHook* hook);
void g_hook_insert_before (GHookList* hook_list, GHook* sibling, GHook* hook);
void g_hook_insert_sorted (GHookList* hook_list, GHook* hook, GHookCompareFunc func);
GHook* g_hook_get (GHookList* hook_list, gulong hook_id);
GHook* g_hook_find (GHookList* hook_list, gboolean need_valids, GHookFindFunc func, gpointer data);
GHook* g_hook_find_data (GHookList* hook_list, gboolean need_valids, gpointer data);
GHook* g_hook_find_func (GHookList* hook_list, gboolean need_valids, gpointer func);
GHook* g_hook_find_func_data (GHookList* hook_list, gboolean need_valids, gpointer func, gpointer data);
GHook* g_hook_first_valid (GHookList* hook_list, gboolean may_be_in_call);
GHook* g_hook_next_valid (GHookList* hook_list, GHook* hook, gboolean may_be_in_call);
gint g_hook_compare_ids (GHook* new_hook, GHook* sibling);
void g_hook_list_invoke (GHookList* hook_list, gboolean may_recurse);
void g_hook_list_invoke_check (GHookList* hook_list, gboolean may_recurse);
void g_hook_list_marshal (GHookList* hook_list, gboolean may_recurse, GHookMarshaller marshaller, gpointer marshal_data);
void g_hook_list_marshal_check (GHookList* hook_list, gboolean may_recurse, GHookCheckMarshaller marshaller, gpointer marshal_data);