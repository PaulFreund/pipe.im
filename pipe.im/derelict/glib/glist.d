module derelict.glib.glist;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _GList GList;

struct _GList
{
	gpointer data;
	GList* next;
	GList* prev;
}

GList* g_list_alloc ();
void g_list_free (GList* list);
void g_list_free_1 (GList* list);
void g_list_free_full (GList* list, GDestroyNotify free_func);
GList* g_list_append (GList* list, gpointer data);
GList* g_list_prepend (GList* list, gpointer data);
GList* g_list_insert (GList* list, gpointer data, gint position);
GList* g_list_insert_sorted (GList* list, gpointer data, GCompareFunc func);
GList* g_list_insert_sorted_with_data (GList* list, gpointer data, GCompareDataFunc func, gpointer user_data);
GList* g_list_insert_before (GList* list, GList* sibling, gpointer data);
GList* g_list_concat (GList* list1, GList* list2);
GList* g_list_remove (GList* list, gconstpointer data);
GList* g_list_remove_all (GList* list, gconstpointer data);
GList* g_list_remove_link (GList* list, GList* llink);
GList* g_list_delete_link (GList* list, GList* link_);
GList* g_list_reverse (GList* list);
GList* g_list_copy (GList* list);
GList* g_list_nth (GList* list, guint n);
GList* g_list_nth_prev (GList* list, guint n);
GList* g_list_find (GList* list, gconstpointer data);
GList* g_list_find_custom (GList* list, gconstpointer data, GCompareFunc func);
gint g_list_position (GList* list, GList* llink);
gint g_list_index (GList* list, gconstpointer data);
GList* g_list_last (GList* list);
GList* g_list_first (GList* list);
guint g_list_length (GList* list);
void g_list_foreach (GList* list, GFunc func, gpointer user_data);
GList* g_list_sort (GList* list, GCompareFunc compare_func);
GList* g_list_sort_with_data (GList* list, GCompareDataFunc compare_func, gpointer user_data);
gpointer g_list_nth_data (GList* list, guint n);