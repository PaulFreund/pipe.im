module derelict.glib.gnode;

extern (C):

alias _GNode GNode;
alias _Anonymous_0 GTraverseFlags;
alias _Anonymous_1 GTraverseType;
alias int function (_GNode*, void*) GNodeTraverseFunc;
alias void function (_GNode*, void*) GNodeForeachFunc;
alias void* function (const(void)*, void*) GCopyFunc;

enum _Anonymous_0
{
	G_TRAVERSE_LEAVES = 1,
	G_TRAVERSE_NON_LEAVES = 2,
	G_TRAVERSE_ALL = 3,
	G_TRAVERSE_MASK = 3,
	G_TRAVERSE_LEAFS = 1,
	G_TRAVERSE_NON_LEAFS = 2
}

enum _Anonymous_1
{
	G_IN_ORDER = 0,
	G_PRE_ORDER = 1,
	G_POST_ORDER = 2,
	G_LEVEL_ORDER = 3
}

struct _GNode
{
	gpointer data;
	GNode* next;
	GNode* prev;
	GNode* parent;
	GNode* children;
}

GNode* g_node_new (gpointer data);
void g_node_destroy (GNode* root);
void g_node_unlink (GNode* node);
GNode* g_node_copy_deep (GNode* node, GCopyFunc copy_func, gpointer data);
GNode* g_node_copy (GNode* node);
GNode* g_node_insert (GNode* parent, gint position, GNode* node);
GNode* g_node_insert_before (GNode* parent, GNode* sibling, GNode* node);
GNode* g_node_insert_after (GNode* parent, GNode* sibling, GNode* node);
GNode* g_node_prepend (GNode* parent, GNode* node);
guint g_node_n_nodes (GNode* root, GTraverseFlags flags);
GNode* g_node_get_root (GNode* node);
gboolean g_node_is_ancestor (GNode* node, GNode* descendant);
guint g_node_depth (GNode* node);
GNode* g_node_find (GNode* root, GTraverseType order, GTraverseFlags flags, gpointer data);
void g_node_traverse (GNode* root, GTraverseType order, GTraverseFlags flags, gint max_depth, GNodeTraverseFunc func, gpointer data);
guint g_node_max_height (GNode* root);
void g_node_children_foreach (GNode* node, GTraverseFlags flags, GNodeForeachFunc func, gpointer data);
void g_node_reverse_children (GNode* node);
guint g_node_n_children (GNode* node);
GNode* g_node_nth_child (GNode* node, guint n);
GNode* g_node_last_child (GNode* node);
GNode* g_node_find_child (GNode* node, GTraverseFlags flags, gpointer data);
gint g_node_child_position (GNode* node, GNode* child);
gint g_node_child_index (GNode* node, gpointer data);
GNode* g_node_first_sibling (GNode* node);
GNode* g_node_last_sibling (GNode* node);