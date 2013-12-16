module derelict.glib.gnode;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

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

alias da_g_node_new = GNode* function(gpointer data);																																																						/* da_g_node_new g_node_new; */
alias da_g_node_destroy = void function(GNode* root);																																																						/* da_g_node_destroy g_node_destroy; */
alias da_g_node_unlink = void function(GNode* node);																																																						/* da_g_node_unlink g_node_unlink; */
alias da_g_node_copy_deep = GNode* function(GNode* node, GCopyFunc copy_func, gpointer data);																																																						/* da_g_node_copy_deep g_node_copy_deep; */
alias da_g_node_copy = GNode* function(GNode* node);																																																						/* da_g_node_copy g_node_copy; */
alias da_g_node_insert = GNode* function(GNode* parent, gint position, GNode* node);																																																						/* da_g_node_insert g_node_insert; */
alias da_g_node_insert_before = GNode* function(GNode* parent, GNode* sibling, GNode* node);																																																						/* da_g_node_insert_before g_node_insert_before; */
alias da_g_node_insert_after = GNode* function(GNode* parent, GNode* sibling, GNode* node);																																																						/* da_g_node_insert_after g_node_insert_after; */
alias da_g_node_prepend = GNode* function(GNode* parent, GNode* node);																																																						/* da_g_node_prepend g_node_prepend; */
alias da_g_node_n_nodes = guint function(GNode* root, GTraverseFlags flags);																																																						/* da_g_node_n_nodes g_node_n_nodes; */
alias da_g_node_get_root = GNode* function(GNode* node);																																																						/* da_g_node_get_root g_node_get_root; */
alias da_g_node_is_ancestor = gboolean function(GNode* node, GNode* descendant);																																																						/* da_g_node_is_ancestor g_node_is_ancestor; */
alias da_g_node_depth = guint function(GNode* node);																																																						/* da_g_node_depth g_node_depth; */
alias da_g_node_find = GNode* function(GNode* root, GTraverseType order, GTraverseFlags flags, gpointer data);																																																						/* da_g_node_find g_node_find; */
alias da_g_node_traverse = void function(GNode* root, GTraverseType order, GTraverseFlags flags, gint max_depth, GNodeTraverseFunc func, gpointer data);																																																						/* da_g_node_traverse g_node_traverse; */
alias da_g_node_max_height = guint function(GNode* root);																																																						/* da_g_node_max_height g_node_max_height; */
alias da_g_node_children_foreach = void function(GNode* node, GTraverseFlags flags, GNodeForeachFunc func, gpointer data);																																																						/* da_g_node_children_foreach g_node_children_foreach; */
alias da_g_node_reverse_children = void function(GNode* node);																																																						/* da_g_node_reverse_children g_node_reverse_children; */
alias da_g_node_n_children = guint function(GNode* node);																																																						/* da_g_node_n_children g_node_n_children; */
alias da_g_node_nth_child = GNode* function(GNode* node, guint n);																																																						/* da_g_node_nth_child g_node_nth_child; */
alias da_g_node_last_child = GNode* function(GNode* node);																																																						/* da_g_node_last_child g_node_last_child; */
alias da_g_node_find_child = GNode* function(GNode* node, GTraverseFlags flags, gpointer data);																																																						/* da_g_node_find_child g_node_find_child; */
alias da_g_node_child_position = gint function(GNode* node, GNode* child);																																																						/* da_g_node_child_position g_node_child_position; */
alias da_g_node_child_index = gint function(GNode* node, gpointer data);																																																						/* da_g_node_child_index g_node_child_index; */
alias da_g_node_first_sibling = GNode* function(GNode* node);																																																						/* da_g_node_first_sibling g_node_first_sibling; */
alias da_g_node_last_sibling = GNode* function(GNode* node);																																																						/* da_g_node_last_sibling g_node_last_sibling; */
