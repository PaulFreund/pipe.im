module derelict.glib.gtree;

extern (C):

alias _GTree GTree;
alias int function (void*, void*, void*) GTraverseFunc;

struct _GTree;


GTree* g_tree_new (GCompareFunc key_compare_func);
GTree* g_tree_new_with_data (GCompareDataFunc key_compare_func, gpointer key_compare_data);
GTree* g_tree_new_full (GCompareDataFunc key_compare_func, gpointer key_compare_data, GDestroyNotify key_destroy_func, GDestroyNotify value_destroy_func);
GTree* g_tree_ref (GTree* tree);
void g_tree_unref (GTree* tree);
void g_tree_destroy (GTree* tree);
void g_tree_insert (GTree* tree, gpointer key, gpointer value);
void g_tree_replace (GTree* tree, gpointer key, gpointer value);
gboolean g_tree_remove (GTree* tree, gconstpointer key);
gboolean g_tree_steal (GTree* tree, gconstpointer key);
gpointer g_tree_lookup (GTree* tree, gconstpointer key);
gboolean g_tree_lookup_extended (GTree* tree, gconstpointer lookup_key, gpointer* orig_key, gpointer* value);
void g_tree_foreach (GTree* tree, GTraverseFunc func, gpointer user_data);
void g_tree_traverse (GTree* tree, GTraverseFunc traverse_func, GTraverseType traverse_type, gpointer user_data);
gpointer g_tree_search (GTree* tree, GCompareFunc search_func, gconstpointer user_data);
gint g_tree_height (GTree* tree);
gint g_tree_nnodes (GTree* tree);