module derelict.glib.ghook;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

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

alias da_g_hook_list_init = void function(GHookList* hook_list, guint hook_size);																																																						/* da_g_hook_list_init g_hook_list_init; */
alias da_g_hook_list_clear = void function(GHookList* hook_list);																																																						/* da_g_hook_list_clear g_hook_list_clear; */
alias da_g_hook_alloc = GHook* function(GHookList* hook_list);																																																						/* da_g_hook_alloc g_hook_alloc; */
alias da_g_hook_free = void function(GHookList* hook_list, GHook* hook);																																																						/* da_g_hook_free g_hook_free; */
alias da_g_hook_ref = GHook* function(GHookList* hook_list, GHook* hook);																																																						/* da_g_hook_ref g_hook_ref; */
alias da_g_hook_unref = void function(GHookList* hook_list, GHook* hook);																																																						/* da_g_hook_unref g_hook_unref; */
alias da_g_hook_destroy = gboolean function(GHookList* hook_list, gulong hook_id);																																																						/* da_g_hook_destroy g_hook_destroy; */
alias da_g_hook_destroy_link = void function(GHookList* hook_list, GHook* hook);																																																						/* da_g_hook_destroy_link g_hook_destroy_link; */
alias da_g_hook_prepend = void function(GHookList* hook_list, GHook* hook);																																																						/* da_g_hook_prepend g_hook_prepend; */
alias da_g_hook_insert_before = void function(GHookList* hook_list, GHook* sibling, GHook* hook);																																																						/* da_g_hook_insert_before g_hook_insert_before; */
alias da_g_hook_insert_sorted = void function(GHookList* hook_list, GHook* hook, GHookCompareFunc func);																																																						/* da_g_hook_insert_sorted g_hook_insert_sorted; */
alias da_g_hook_get = GHook* function(GHookList* hook_list, gulong hook_id);																																																						/* da_g_hook_get g_hook_get; */
alias da_g_hook_find = GHook* function(GHookList* hook_list, gboolean need_valids, GHookFindFunc func, gpointer data);																																																						/* da_g_hook_find g_hook_find; */
alias da_g_hook_find_data = GHook* function(GHookList* hook_list, gboolean need_valids, gpointer data);																																																						/* da_g_hook_find_data g_hook_find_data; */
alias da_g_hook_find_func = GHook* function(GHookList* hook_list, gboolean need_valids, gpointer func);																																																						/* da_g_hook_find_func g_hook_find_func; */
alias da_g_hook_find_func_data = GHook* function(GHookList* hook_list, gboolean need_valids, gpointer func, gpointer data);																																																						/* da_g_hook_find_func_data g_hook_find_func_data; */
alias da_g_hook_first_valid = GHook* function(GHookList* hook_list, gboolean may_be_in_call);																																																						/* da_g_hook_first_valid g_hook_first_valid; */
alias da_g_hook_next_valid = GHook* function(GHookList* hook_list, GHook* hook, gboolean may_be_in_call);																																																						/* da_g_hook_next_valid g_hook_next_valid; */
alias da_g_hook_compare_ids = gint function(GHook* new_hook, GHook* sibling);																																																						/* da_g_hook_compare_ids g_hook_compare_ids; */
alias da_g_hook_list_invoke = void function(GHookList* hook_list, gboolean may_recurse);																																																						/* da_g_hook_list_invoke g_hook_list_invoke; */
alias da_g_hook_list_invoke_check = void function(GHookList* hook_list, gboolean may_recurse);																																																						/* da_g_hook_list_invoke_check g_hook_list_invoke_check; */
alias da_g_hook_list_marshal = void function(GHookList* hook_list, gboolean may_recurse, GHookMarshaller marshaller, gpointer marshal_data);																																																						/* da_g_hook_list_marshal g_hook_list_marshal; */
alias da_g_hook_list_marshal_check = void function(GHookList* hook_list, gboolean may_recurse, GHookCheckMarshaller marshaller, gpointer marshal_data);																																																						/* da_g_hook_list_marshal_check g_hook_list_marshal_check; */
