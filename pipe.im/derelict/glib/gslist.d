module derelict.glib.gslist;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _GSList GSList;

struct _GSList
{
	gpointer data;
	GSList* next;
}

alias da_g_slist_alloc = GSList* function();																																																						/* da_g_slist_alloc g_slist_alloc; */
alias da_g_slist_free = void function(GSList* list);																																																						/* da_g_slist_free g_slist_free; */
alias da_g_slist_free_1 = void function(GSList* list);																																																						/* da_g_slist_free_1 g_slist_free_1; */
alias da_g_slist_free_full = void function(GSList* list, GDestroyNotify free_func);																																																						/* da_g_slist_free_full g_slist_free_full; */
alias da_g_slist_append = GSList* function(GSList* list, gpointer data);																																																						/* da_g_slist_append g_slist_append; */
alias da_g_slist_prepend = GSList* function(GSList* list, gpointer data);																																																						/* da_g_slist_prepend g_slist_prepend; */
alias da_g_slist_insert = GSList* function(GSList* list, gpointer data, gint position);																																																						/* da_g_slist_insert g_slist_insert; */
alias da_g_slist_insert_sorted = GSList* function(GSList* list, gpointer data, GCompareFunc func);																																																						/* da_g_slist_insert_sorted g_slist_insert_sorted; */
alias da_g_slist_insert_sorted_with_data = GSList* function(GSList* list, gpointer data, GCompareDataFunc func, gpointer user_data);																																																						/* da_g_slist_insert_sorted_with_data g_slist_insert_sorted_with_data; */
alias da_g_slist_insert_before = GSList* function(GSList* slist, GSList* sibling, gpointer data);																																																						/* da_g_slist_insert_before g_slist_insert_before; */
alias da_g_slist_concat = GSList* function(GSList* list1, GSList* list2);																																																						/* da_g_slist_concat g_slist_concat; */
alias da_g_slist_remove = GSList* function(GSList* list, gconstpointer data);																																																						/* da_g_slist_remove g_slist_remove; */
alias da_g_slist_remove_all = GSList* function(GSList* list, gconstpointer data);																																																						/* da_g_slist_remove_all g_slist_remove_all; */
alias da_g_slist_remove_link = GSList* function(GSList* list, GSList* link_);																																																						/* da_g_slist_remove_link g_slist_remove_link; */
alias da_g_slist_delete_link = GSList* function(GSList* list, GSList* link_);																																																						/* da_g_slist_delete_link g_slist_delete_link; */
alias da_g_slist_reverse = GSList* function(GSList* list);																																																						/* da_g_slist_reverse g_slist_reverse; */
alias da_g_slist_copy = GSList* function(GSList* list);																																																						/* da_g_slist_copy g_slist_copy; */
alias da_g_slist_nth = GSList* function(GSList* list, guint n);																																																						/* da_g_slist_nth g_slist_nth; */
alias da_g_slist_find = GSList* function(GSList* list, gconstpointer data);																																																						/* da_g_slist_find g_slist_find; */
alias da_g_slist_find_custom = GSList* function(GSList* list, gconstpointer data, GCompareFunc func);																																																						/* da_g_slist_find_custom g_slist_find_custom; */
alias da_g_slist_position = gint function(GSList* list, GSList* llink);																																																						/* da_g_slist_position g_slist_position; */
alias da_g_slist_index = gint function(GSList* list, gconstpointer data);																																																						/* da_g_slist_index g_slist_index; */
alias da_g_slist_last = GSList* function(GSList* list);																																																						/* da_g_slist_last g_slist_last; */
alias da_g_slist_length = guint function(GSList* list);																																																						/* da_g_slist_length g_slist_length; */
alias da_g_slist_foreach = void function(GSList* list, GFunc func, gpointer user_data);																																																						/* da_g_slist_foreach g_slist_foreach; */
alias da_g_slist_sort = GSList* function(GSList* list, GCompareFunc compare_func);																																																						/* da_g_slist_sort g_slist_sort; */
alias da_g_slist_sort_with_data = GSList* function(GSList* list, GCompareDataFunc compare_func, gpointer user_data);																																																						/* da_g_slist_sort_with_data g_slist_sort_with_data; */
alias da_g_slist_nth_data = gpointer function(GSList* list, guint n);																																																						/* da_g_slist_nth_data g_slist_nth_data; */
