module derelict.glib.gtree;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gnode;

extern (C):

alias _GTree GTree;
alias int function (void*, void*, void*) GTraverseFunc;

struct _GTree;


alias da_g_tree_new = GTree* function(GCompareFunc key_compare_func);																																																						/* da_g_tree_new g_tree_new; */
alias da_g_tree_new_with_data = GTree* function(GCompareDataFunc key_compare_func, gpointer key_compare_data);																																																						/* da_g_tree_new_with_data g_tree_new_with_data; */
alias da_g_tree_new_full = GTree* function(GCompareDataFunc key_compare_func, gpointer key_compare_data, GDestroyNotify key_destroy_func, GDestroyNotify value_destroy_func);																																																						/* da_g_tree_new_full g_tree_new_full; */
alias da_g_tree_ref = GTree* function(GTree* tree);																																																						/* da_g_tree_ref g_tree_ref; */
alias da_g_tree_unref = void function(GTree* tree);																																																						/* da_g_tree_unref g_tree_unref; */
alias da_g_tree_destroy = void function(GTree* tree);																																																						/* da_g_tree_destroy g_tree_destroy; */
alias da_g_tree_insert = void function(GTree* tree, gpointer key, gpointer value);																																																						/* da_g_tree_insert g_tree_insert; */
alias da_g_tree_replace = void function(GTree* tree, gpointer key, gpointer value);																																																						/* da_g_tree_replace g_tree_replace; */
alias da_g_tree_remove = gboolean function(GTree* tree, gconstpointer key);																																																						/* da_g_tree_remove g_tree_remove; */
alias da_g_tree_steal = gboolean function(GTree* tree, gconstpointer key);																																																						/* da_g_tree_steal g_tree_steal; */
alias da_g_tree_lookup = gpointer function(GTree* tree, gconstpointer key);																																																						/* da_g_tree_lookup g_tree_lookup; */
alias da_g_tree_lookup_extended = gboolean function(GTree* tree, gconstpointer lookup_key, gpointer* orig_key, gpointer* value);																																																						/* da_g_tree_lookup_extended g_tree_lookup_extended; */
alias da_g_tree_foreach = void function(GTree* tree, GTraverseFunc func, gpointer user_data);																																																						/* da_g_tree_foreach g_tree_foreach; */
alias da_g_tree_traverse = void function(GTree* tree, GTraverseFunc traverse_func, GTraverseType traverse_type, gpointer user_data);																																																						/* da_g_tree_traverse g_tree_traverse; */
alias da_g_tree_search = gpointer function(GTree* tree, GCompareFunc search_func, gconstpointer user_data);																																																						/* da_g_tree_search g_tree_search; */
alias da_g_tree_height = gint function(GTree* tree);																																																						/* da_g_tree_height g_tree_height; */
alias da_g_tree_nnodes = gint function(GTree* tree);																																																						/* da_g_tree_nnodes g_tree_nnodes; */
