module derelict.glib.ghash;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;

extern (C):

alias _GHashTable GHashTable;
alias int function (void*, void*, void*) GHRFunc;
alias _GHashTableIter GHashTableIter;

struct _GHashTableIter
{
	gpointer dummy1;
	gpointer dummy2;
	gpointer dummy3;
	int dummy4;
	gboolean dummy5;
	gpointer dummy6;
}

struct _GHashTable;


alias da_g_hash_table_new = GHashTable* function(GHashFunc hash_func, GEqualFunc key_equal_func);																																																						/* da_g_hash_table_new g_hash_table_new; */
alias da_g_hash_table_new_full = GHashTable* function(GHashFunc hash_func, GEqualFunc key_equal_func, GDestroyNotify key_destroy_func, GDestroyNotify value_destroy_func);																																																						/* da_g_hash_table_new_full g_hash_table_new_full; */
alias da_g_hash_table_destroy = void function(GHashTable* hash_table);																																																						/* da_g_hash_table_destroy g_hash_table_destroy; */
alias da_g_hash_table_insert = void function(GHashTable* hash_table, gpointer key, gpointer value);																																																						/* da_g_hash_table_insert g_hash_table_insert; */
alias da_g_hash_table_replace = void function(GHashTable* hash_table, gpointer key, gpointer value);																																																						/* da_g_hash_table_replace g_hash_table_replace; */
alias da_g_hash_table_add = void function(GHashTable* hash_table, gpointer key);																																																						/* da_g_hash_table_add g_hash_table_add; */
alias da_g_hash_table_remove = gboolean function(GHashTable* hash_table, gconstpointer key);																																																						/* da_g_hash_table_remove g_hash_table_remove; */
alias da_g_hash_table_remove_all = void function(GHashTable* hash_table);																																																						/* da_g_hash_table_remove_all g_hash_table_remove_all; */
alias da_g_hash_table_steal = gboolean function(GHashTable* hash_table, gconstpointer key);																																																						/* da_g_hash_table_steal g_hash_table_steal; */
alias da_g_hash_table_steal_all = void function(GHashTable* hash_table);																																																						/* da_g_hash_table_steal_all g_hash_table_steal_all; */
alias da_g_hash_table_lookup = gpointer function(GHashTable* hash_table, gconstpointer key);																																																						/* da_g_hash_table_lookup g_hash_table_lookup; */
alias da_g_hash_table_contains = gboolean function(GHashTable* hash_table, gconstpointer key);																																																						/* da_g_hash_table_contains g_hash_table_contains; */
alias da_g_hash_table_lookup_extended = gboolean function(GHashTable* hash_table, gconstpointer lookup_key, gpointer* orig_key, gpointer* value);																																																						/* da_g_hash_table_lookup_extended g_hash_table_lookup_extended; */
alias da_g_hash_table_foreach = void function(GHashTable* hash_table, GHFunc func, gpointer user_data);																																																						/* da_g_hash_table_foreach g_hash_table_foreach; */
alias da_g_hash_table_find = gpointer function(GHashTable* hash_table, GHRFunc predicate, gpointer user_data);																																																						/* da_g_hash_table_find g_hash_table_find; */
alias da_g_hash_table_foreach_remove = guint function(GHashTable* hash_table, GHRFunc func, gpointer user_data);																																																						/* da_g_hash_table_foreach_remove g_hash_table_foreach_remove; */
alias da_g_hash_table_foreach_steal = guint function(GHashTable* hash_table, GHRFunc func, gpointer user_data);																																																						/* da_g_hash_table_foreach_steal g_hash_table_foreach_steal; */
alias da_g_hash_table_size = guint function(GHashTable* hash_table);																																																						/* da_g_hash_table_size g_hash_table_size; */
alias da_g_hash_table_get_keys = GList* function(GHashTable* hash_table);																																																						/* da_g_hash_table_get_keys g_hash_table_get_keys; */
alias da_g_hash_table_get_values = GList* function(GHashTable* hash_table);																																																						/* da_g_hash_table_get_values g_hash_table_get_values; */
alias da_g_hash_table_iter_init = void function(GHashTableIter* iter, GHashTable* hash_table);																																																						/* da_g_hash_table_iter_init g_hash_table_iter_init; */
alias da_g_hash_table_iter_next = gboolean function(GHashTableIter* iter, gpointer* key, gpointer* value);																																																						/* da_g_hash_table_iter_next g_hash_table_iter_next; */
alias da_g_hash_table_iter_get_hash_table = GHashTable* function(GHashTableIter* iter);																																																						/* da_g_hash_table_iter_get_hash_table g_hash_table_iter_get_hash_table; */
alias da_g_hash_table_iter_remove = void function(GHashTableIter* iter);																																																						/* da_g_hash_table_iter_remove g_hash_table_iter_remove; */
alias da_g_hash_table_iter_replace = void function(GHashTableIter* iter, gpointer value);																																																						/* da_g_hash_table_iter_replace g_hash_table_iter_replace; */
alias da_g_hash_table_iter_steal = void function(GHashTableIter* iter);																																																						/* da_g_hash_table_iter_steal g_hash_table_iter_steal; */
alias da_g_hash_table_ref = GHashTable* function(GHashTable* hash_table);																																																						/* da_g_hash_table_ref g_hash_table_ref; */
alias da_g_hash_table_unref = void function(GHashTable* hash_table);																																																						/* da_g_hash_table_unref g_hash_table_unref; */
alias da_g_str_equal = gboolean function(gconstpointer v1, gconstpointer v2);																																																						/* da_g_str_equal g_str_equal; */
alias da_g_str_hash = guint function(gconstpointer v);																																																						/* da_g_str_hash g_str_hash; */
alias da_g_int_equal = gboolean function(gconstpointer v1, gconstpointer v2);																																																						/* da_g_int_equal g_int_equal; */
alias da_g_int_hash = guint function(gconstpointer v);																																																						/* da_g_int_hash g_int_hash; */
alias da_g_int64_equal = gboolean function(gconstpointer v1, gconstpointer v2);																																																						/* da_g_int64_equal g_int64_equal; */
alias da_g_int64_hash = guint function(gconstpointer v);																																																						/* da_g_int64_hash g_int64_hash; */
alias da_g_double_equal = gboolean function(gconstpointer v1, gconstpointer v2);																																																						/* da_g_double_equal g_double_equal; */
alias da_g_double_hash = guint function(gconstpointer v);																																																						/* da_g_double_hash g_double_hash; */
alias da_g_direct_hash = guint function(gconstpointer v);																																																						/* da_g_direct_hash g_direct_hash; */
alias da_g_direct_equal = gboolean function(gconstpointer v1, gconstpointer v2);																																																						/* da_g_direct_equal g_direct_equal; */
