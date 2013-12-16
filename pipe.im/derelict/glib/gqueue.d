module derelict.glib.gqueue;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
extern (C):

alias _GQueue GQueue;

struct _GQueue
{
	GList* head;
	GList* tail;
	guint length;
}

alias da_g_queue_new = GQueue* function();																																																						/* da_g_queue_new g_queue_new; */
alias da_g_queue_free = void function(GQueue* queue);																																																						/* da_g_queue_free g_queue_free; */
alias da_g_queue_free_full = void function(GQueue* queue, GDestroyNotify free_func);																																																						/* da_g_queue_free_full g_queue_free_full; */
alias da_g_queue_init = void function(GQueue* queue);																																																						/* da_g_queue_init g_queue_init; */
alias da_g_queue_clear = void function(GQueue* queue);																																																						/* da_g_queue_clear g_queue_clear; */
alias da_g_queue_is_empty = gboolean function(GQueue* queue);																																																						/* da_g_queue_is_empty g_queue_is_empty; */
alias da_g_queue_get_length = guint function(GQueue* queue);																																																						/* da_g_queue_get_length g_queue_get_length; */
alias da_g_queue_reverse = void function(GQueue* queue);																																																						/* da_g_queue_reverse g_queue_reverse; */
alias da_g_queue_copy = GQueue* function(GQueue* queue);																																																						/* da_g_queue_copy g_queue_copy; */
alias da_g_queue_foreach = void function(GQueue* queue, GFunc func, gpointer user_data);																																																						/* da_g_queue_foreach g_queue_foreach; */
alias da_g_queue_find = GList* function(GQueue* queue, gconstpointer data);																																																						/* da_g_queue_find g_queue_find; */
alias da_g_queue_find_custom = GList* function(GQueue* queue, gconstpointer data, GCompareFunc func);																																																						/* da_g_queue_find_custom g_queue_find_custom; */
alias da_g_queue_sort = void function(GQueue* queue, GCompareDataFunc compare_func, gpointer user_data);																																																						/* da_g_queue_sort g_queue_sort; */
alias da_g_queue_push_head = void function(GQueue* queue, gpointer data);																																																						/* da_g_queue_push_head g_queue_push_head; */
alias da_g_queue_push_tail = void function(GQueue* queue, gpointer data);																																																						/* da_g_queue_push_tail g_queue_push_tail; */
alias da_g_queue_push_nth = void function(GQueue* queue, gpointer data, gint n);																																																						/* da_g_queue_push_nth g_queue_push_nth; */
alias da_g_queue_pop_head = gpointer function(GQueue* queue);																																																						/* da_g_queue_pop_head g_queue_pop_head; */
alias da_g_queue_pop_tail = gpointer function(GQueue* queue);																																																						/* da_g_queue_pop_tail g_queue_pop_tail; */
alias da_g_queue_pop_nth = gpointer function(GQueue* queue, guint n);																																																						/* da_g_queue_pop_nth g_queue_pop_nth; */
alias da_g_queue_peek_head = gpointer function(GQueue* queue);																																																						/* da_g_queue_peek_head g_queue_peek_head; */
alias da_g_queue_peek_tail = gpointer function(GQueue* queue);																																																						/* da_g_queue_peek_tail g_queue_peek_tail; */
alias da_g_queue_peek_nth = gpointer function(GQueue* queue, guint n);																																																						/* da_g_queue_peek_nth g_queue_peek_nth; */
alias da_g_queue_index = gint function(GQueue* queue, gconstpointer data);																																																						/* da_g_queue_index g_queue_index; */
alias da_g_queue_remove = gboolean function(GQueue* queue, gconstpointer data);																																																						/* da_g_queue_remove g_queue_remove; */
alias da_g_queue_remove_all = guint function(GQueue* queue, gconstpointer data);																																																						/* da_g_queue_remove_all g_queue_remove_all; */
alias da_g_queue_insert_before = void function(GQueue* queue, GList* sibling, gpointer data);																																																						/* da_g_queue_insert_before g_queue_insert_before; */
alias da_g_queue_insert_after = void function(GQueue* queue, GList* sibling, gpointer data);																																																						/* da_g_queue_insert_after g_queue_insert_after; */
alias da_g_queue_insert_sorted = void function(GQueue* queue, gpointer data, GCompareDataFunc func, gpointer user_data);																																																						/* da_g_queue_insert_sorted g_queue_insert_sorted; */
alias da_g_queue_push_head_link = void function(GQueue* queue, GList* link_);																																																						/* da_g_queue_push_head_link g_queue_push_head_link; */
alias da_g_queue_push_tail_link = void function(GQueue* queue, GList* link_);																																																						/* da_g_queue_push_tail_link g_queue_push_tail_link; */
alias da_g_queue_push_nth_link = void function(GQueue* queue, gint n, GList* link_);																																																						/* da_g_queue_push_nth_link g_queue_push_nth_link; */
alias da_g_queue_pop_head_link = GList* function(GQueue* queue);																																																						/* da_g_queue_pop_head_link g_queue_pop_head_link; */
alias da_g_queue_pop_tail_link = GList* function(GQueue* queue);																																																						/* da_g_queue_pop_tail_link g_queue_pop_tail_link; */
alias da_g_queue_pop_nth_link = GList* function(GQueue* queue, guint n);																																																						/* da_g_queue_pop_nth_link g_queue_pop_nth_link; */
alias da_g_queue_peek_head_link = GList* function(GQueue* queue);																																																						/* da_g_queue_peek_head_link g_queue_peek_head_link; */
alias da_g_queue_peek_tail_link = GList* function(GQueue* queue);																																																						/* da_g_queue_peek_tail_link g_queue_peek_tail_link; */
alias da_g_queue_peek_nth_link = GList* function(GQueue* queue, guint n);																																																						/* da_g_queue_peek_nth_link g_queue_peek_nth_link; */
alias da_g_queue_link_index = gint function(GQueue* queue, GList* link_);																																																						/* da_g_queue_link_index g_queue_link_index; */
alias da_g_queue_unlink = void function(GQueue* queue, GList* link_);																																																						/* da_g_queue_unlink g_queue_unlink; */
alias da_g_queue_delete_link = void function(GQueue* queue, GList* link_);																																																						/* da_g_queue_delete_link g_queue_delete_link; */
