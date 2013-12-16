module derelict.glib.gthreadpool;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gquark;
import derelict.glib.gerror;

extern (C):

alias _GThreadPool GThreadPool;

struct _GThreadPool
{
	GFunc func;
	gpointer user_data;
	gboolean exclusive;
}

alias da_g_thread_pool_new = GThreadPool* function(GFunc func, gpointer user_data, gint max_threads, gboolean exclusive, GError** error);																																																						/* da_g_thread_pool_new g_thread_pool_new; */
alias da_g_thread_pool_free = void function(GThreadPool* pool, gboolean immediate, gboolean wait_);																																																						/* da_g_thread_pool_free g_thread_pool_free; */
alias da_g_thread_pool_push = gboolean function(GThreadPool* pool, gpointer data, GError** error);																																																						/* da_g_thread_pool_push g_thread_pool_push; */
alias da_g_thread_pool_unprocessed = guint function(GThreadPool* pool);																																																						/* da_g_thread_pool_unprocessed g_thread_pool_unprocessed; */
alias da_g_thread_pool_set_sort_function = void function(GThreadPool* pool, GCompareDataFunc func, gpointer user_data);																																																						/* da_g_thread_pool_set_sort_function g_thread_pool_set_sort_function; */
alias da_g_thread_pool_set_max_threads = gboolean function(GThreadPool* pool, gint max_threads, GError** error);																																																						/* da_g_thread_pool_set_max_threads g_thread_pool_set_max_threads; */
alias da_g_thread_pool_get_max_threads = gint function(GThreadPool* pool);																																																						/* da_g_thread_pool_get_max_threads g_thread_pool_get_max_threads; */
alias da_g_thread_pool_get_num_threads = guint function(GThreadPool* pool);																																																						/* da_g_thread_pool_get_num_threads g_thread_pool_get_num_threads; */
alias da_g_thread_pool_set_max_unused_threads = void function(gint max_threads);																																																						/* da_g_thread_pool_set_max_unused_threads g_thread_pool_set_max_unused_threads; */
alias da_g_thread_pool_get_max_unused_threads = gint function();																																																						/* da_g_thread_pool_get_max_unused_threads g_thread_pool_get_max_unused_threads; */
alias da_g_thread_pool_get_num_unused_threads = guint function();																																																						/* da_g_thread_pool_get_num_unused_threads g_thread_pool_get_num_unused_threads; */
alias da_g_thread_pool_stop_unused_threads = void function();																																																						/* da_g_thread_pool_stop_unused_threads g_thread_pool_stop_unused_threads; */
alias da_g_thread_pool_set_max_idle_time = void function(guint interval);																																																						/* da_g_thread_pool_set_max_idle_time g_thread_pool_set_max_idle_time; */
alias da_g_thread_pool_get_max_idle_time = guint function();																																																						/* da_g_thread_pool_get_max_idle_time g_thread_pool_get_max_idle_time; */
