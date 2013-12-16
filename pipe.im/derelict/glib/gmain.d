module derelict.glib.gmain;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gslist;
import derelict.glib.gpoll;
import derelict.glib.gthread;
import core.sys.posix.poll;
import core.stdc.config;

extern (C):

alias _GMainContext GMainContext;
alias _GMainLoop GMainLoop;
alias _GSource GSource;
alias _GSourcePrivate GSourcePrivate;
alias _GSourceCallbackFuncs GSourceCallbackFuncs;
alias _GSourceFuncs GSourceFuncs;
alias int function (void*) GSourceFunc;
alias void function (int, int, void*) GChildWatchFunc;
alias void function () GSourceDummyMarshal;

extern __gshared GSourceFuncs g_timeout_funcs;
extern __gshared GSourceFuncs g_child_watch_funcs;
extern __gshared GSourceFuncs g_idle_funcs;

struct _GSource
{
	gpointer callback_data;
	GSourceCallbackFuncs* callback_funcs;
	GSourceFuncs* source_funcs;
	guint ref_count;
	GMainContext* context;
	gint priority;
	guint flags;
	guint source_id;
	GSList* poll_fds;
	GSource* prev;
	GSource* next;
	char* name;
	GSourcePrivate* priv;
}

struct _GSourceCallbackFuncs
{
	void function (gpointer) ref_;
	void function (gpointer) unref;
	void function (gpointer, GSource*, GSourceFunc*, gpointer*) get;
}

struct _GSourceFuncs
{
	gboolean function (GSource*, gint*) prepare;
	gboolean function (GSource*) check;
	gboolean function (GSource*, GSourceFunc, gpointer) dispatch;
	void function (GSource*) finalize;
	GSourceFunc closure_callback;
	GSourceDummyMarshal closure_marshal;
}

struct _GSourcePrivate;


struct _GMainLoop;


struct _GMainContext;


alias da_g_main_context_new = GMainContext* function();																																																						/* da_g_main_context_new g_main_context_new; */
alias da_g_main_context_ref = GMainContext* function(GMainContext* context);																																																						/* da_g_main_context_ref g_main_context_ref; */
alias da_g_main_context_unref = void function(GMainContext* context);																																																						/* da_g_main_context_unref g_main_context_unref; */
alias da_g_main_context_default = GMainContext* function();																																																						/* da_g_main_context_default g_main_context_default; */
alias da_g_main_context_iteration = gboolean function(GMainContext* context, gboolean may_block);																																																						/* da_g_main_context_iteration g_main_context_iteration; */
alias da_g_main_context_pending = gboolean function(GMainContext* context);																																																						/* da_g_main_context_pending g_main_context_pending; */
alias da_g_main_context_find_source_by_id = GSource* function(GMainContext* context, guint source_id);																																																						/* da_g_main_context_find_source_by_id g_main_context_find_source_by_id; */
alias da_g_main_context_find_source_by_user_data = GSource* function(GMainContext* context, gpointer user_data);																																																						/* da_g_main_context_find_source_by_user_data g_main_context_find_source_by_user_data; */
alias da_g_main_context_find_source_by_funcs_user_data = GSource* function(GMainContext* context, GSourceFuncs* funcs, gpointer user_data);																																																						/* da_g_main_context_find_source_by_funcs_user_data g_main_context_find_source_by_funcs_user_data; */
alias da_g_main_context_wakeup = void function(GMainContext* context);																																																						/* da_g_main_context_wakeup g_main_context_wakeup; */
alias da_g_main_context_acquire = gboolean function(GMainContext* context);																																																						/* da_g_main_context_acquire g_main_context_acquire; */
alias da_g_main_context_release = void function(GMainContext* context);																																																						/* da_g_main_context_release g_main_context_release; */
alias da_g_main_context_is_owner = gboolean function(GMainContext* context);																																																						/* da_g_main_context_is_owner g_main_context_is_owner; */
alias da_g_main_context_wait = gboolean function(GMainContext* context, GCond* cond, GMutex* mutex);																																																						/* da_g_main_context_wait g_main_context_wait; */
alias da_g_main_context_prepare = gboolean function(GMainContext* context, gint* priority);																																																						/* da_g_main_context_prepare g_main_context_prepare; */
alias da_g_main_context_query = gint function(GMainContext* context, gint max_priority, gint* timeout_, GPollFD* fds, gint n_fds);																																																						/* da_g_main_context_query g_main_context_query; */
alias da_g_main_context_check = gint function(GMainContext* context, gint max_priority, GPollFD* fds, gint n_fds);																																																						/* da_g_main_context_check g_main_context_check; */
alias da_g_main_context_dispatch = void function(GMainContext* context);																																																						/* da_g_main_context_dispatch g_main_context_dispatch; */
alias da_g_main_context_set_poll_func = void function(GMainContext* context, GPollFunc func);																																																						/* da_g_main_context_set_poll_func g_main_context_set_poll_func; */
alias da_g_main_context_get_poll_func = GPollFunc function(GMainContext* context);																																																						/* da_g_main_context_get_poll_func g_main_context_get_poll_func; */
alias da_g_main_context_add_poll = void function(GMainContext* context, GPollFD* fd, gint priority);																																																						/* da_g_main_context_add_poll g_main_context_add_poll; */
alias da_g_main_context_remove_poll = void function(GMainContext* context, GPollFD* fd);																																																						/* da_g_main_context_remove_poll g_main_context_remove_poll; */
alias da_g_main_depth = gint function();																																																						/* da_g_main_depth g_main_depth; */
alias da_g_main_current_source = GSource* function();																																																						/* da_g_main_current_source g_main_current_source; */
alias da_g_main_context_push_thread_default = void function(GMainContext* context);																																																						/* da_g_main_context_push_thread_default g_main_context_push_thread_default; */
alias da_g_main_context_pop_thread_default = void function(GMainContext* context);																																																						/* da_g_main_context_pop_thread_default g_main_context_pop_thread_default; */
alias da_g_main_context_get_thread_default = GMainContext* function();																																																						/* da_g_main_context_get_thread_default g_main_context_get_thread_default; */
alias da_g_main_context_ref_thread_default = GMainContext* function();																																																						/* da_g_main_context_ref_thread_default g_main_context_ref_thread_default; */
alias da_g_main_loop_new = GMainLoop* function(GMainContext* context, gboolean is_running);																																																						/* da_g_main_loop_new g_main_loop_new; */
alias da_g_main_loop_run = void function(GMainLoop* loop);																																																						/* da_g_main_loop_run g_main_loop_run; */
alias da_g_main_loop_quit = void function(GMainLoop* loop);																																																						/* da_g_main_loop_quit g_main_loop_quit; */
alias da_g_main_loop_ref = GMainLoop* function(GMainLoop* loop);																																																						/* da_g_main_loop_ref g_main_loop_ref; */
alias da_g_main_loop_unref = void function(GMainLoop* loop);																																																						/* da_g_main_loop_unref g_main_loop_unref; */
alias da_g_main_loop_is_running = gboolean function(GMainLoop* loop);																																																						/* da_g_main_loop_is_running g_main_loop_is_running; */
alias da_g_main_loop_get_context = GMainContext* function(GMainLoop* loop);																																																						/* da_g_main_loop_get_context g_main_loop_get_context; */
alias da_g_source_new = GSource* function(GSourceFuncs* source_funcs, guint struct_size);																																																						/* da_g_source_new g_source_new; */
alias da_g_source_ref = GSource* function(GSource* source);																																																						/* da_g_source_ref g_source_ref; */
alias da_g_source_unref = void function(GSource* source);																																																						/* da_g_source_unref g_source_unref; */
alias da_g_source_attach = guint function(GSource* source, GMainContext* context);																																																						/* da_g_source_attach g_source_attach; */
alias da_g_source_destroy = void function(GSource* source);																																																						/* da_g_source_destroy g_source_destroy; */
alias da_g_source_set_priority = void function(GSource* source, gint priority);																																																						/* da_g_source_set_priority g_source_set_priority; */
alias da_g_source_get_priority = gint function(GSource* source);																																																						/* da_g_source_get_priority g_source_get_priority; */
alias da_g_source_set_can_recurse = void function(GSource* source, gboolean can_recurse);																																																						/* da_g_source_set_can_recurse g_source_set_can_recurse; */
alias da_g_source_get_can_recurse = gboolean function(GSource* source);																																																						/* da_g_source_get_can_recurse g_source_get_can_recurse; */
alias da_g_source_get_id = guint function(GSource* source);																																																						/* da_g_source_get_id g_source_get_id; */
alias da_g_source_get_context = GMainContext* function(GSource* source);																																																						/* da_g_source_get_context g_source_get_context; */
alias da_g_source_set_callback = void function(GSource* source, GSourceFunc func, gpointer data, GDestroyNotify notify);																																																						/* da_g_source_set_callback g_source_set_callback; */
alias da_g_source_set_funcs = void function(GSource* source, GSourceFuncs* funcs);																																																						/* da_g_source_set_funcs g_source_set_funcs; */
alias da_g_source_is_destroyed = gboolean function(GSource* source);																																																						/* da_g_source_is_destroyed g_source_is_destroyed; */
alias da_g_source_set_name = void function(GSource* source, const(char)* name);																																																						/* da_g_source_set_name g_source_set_name; */
alias da_g_source_get_name = const(char)* function(GSource* source);																																																						/* da_g_source_get_name g_source_get_name; */
alias da_g_source_set_name_by_id = void function(guint tag, const(char)* name);																																																						/* da_g_source_set_name_by_id g_source_set_name_by_id; */
alias da_g_source_set_callback_indirect = void function(GSource* source, gpointer callback_data, GSourceCallbackFuncs* callback_funcs);																																																						/* da_g_source_set_callback_indirect g_source_set_callback_indirect; */
alias da_g_source_add_poll = void function(GSource* source, GPollFD* fd);																																																						/* da_g_source_add_poll g_source_add_poll; */
alias da_g_source_remove_poll = void function(GSource* source, GPollFD* fd);																																																						/* da_g_source_remove_poll g_source_remove_poll; */
alias da_g_source_add_child_source = void function(GSource* source, GSource* child_source);																																																						/* da_g_source_add_child_source g_source_add_child_source; */
alias da_g_source_remove_child_source = void function(GSource* source, GSource* child_source);																																																						/* da_g_source_remove_child_source g_source_remove_child_source; */
alias da_g_source_get_current_time = void function(GSource* source, GTimeVal* timeval);																																																						/* da_g_source_get_current_time g_source_get_current_time; */
alias da_g_source_get_time = gint64 function(GSource* source);																																																						/* da_g_source_get_time g_source_get_time; */
alias da_g_idle_source_new = GSource* function();																																																						/* da_g_idle_source_new g_idle_source_new; */
alias da_g_child_watch_source_new = GSource* function(GPid pid);																																																						/* da_g_child_watch_source_new g_child_watch_source_new; */
alias da_g_timeout_source_new = GSource* function(guint interval);																																																						/* da_g_timeout_source_new g_timeout_source_new; */
alias da_g_timeout_source_new_seconds = GSource* function(guint interval);																																																						/* da_g_timeout_source_new_seconds g_timeout_source_new_seconds; */
alias da_g_get_current_time = void function(GTimeVal* result);																																																						/* da_g_get_current_time g_get_current_time; */
alias da_g_get_monotonic_time = gint64 function();																																																						/* da_g_get_monotonic_time g_get_monotonic_time; */
alias da_g_get_real_time = gint64 function();																																																						/* da_g_get_real_time g_get_real_time; */
alias da_g_source_remove = gboolean function(guint tag);																																																						/* da_g_source_remove g_source_remove; */
alias da_g_source_remove_by_user_data = gboolean function(gpointer user_data);																																																						/* da_g_source_remove_by_user_data g_source_remove_by_user_data; */
alias da_g_source_remove_by_funcs_user_data = gboolean function(GSourceFuncs* funcs, gpointer user_data);																																																						/* da_g_source_remove_by_funcs_user_data g_source_remove_by_funcs_user_data; */
alias da_g_timeout_add_full = guint function(gint priority, guint interval, GSourceFunc function_, gpointer data, GDestroyNotify notify);																																																						/* da_g_timeout_add_full g_timeout_add_full; */
alias da_g_timeout_add = guint function(guint interval, GSourceFunc function_, gpointer data);																																																						/* da_g_timeout_add g_timeout_add; */
alias da_g_timeout_add_seconds_full = guint function(gint priority, guint interval, GSourceFunc function_, gpointer data, GDestroyNotify notify);																																																						/* da_g_timeout_add_seconds_full g_timeout_add_seconds_full; */
alias da_g_timeout_add_seconds = guint function(guint interval, GSourceFunc function_, gpointer data);																																																						/* da_g_timeout_add_seconds g_timeout_add_seconds; */
alias da_g_child_watch_add_full = guint function(gint priority, GPid pid, GChildWatchFunc function_, gpointer data, GDestroyNotify notify);																																																						/* da_g_child_watch_add_full g_child_watch_add_full; */
alias da_g_child_watch_add = guint function(GPid pid, GChildWatchFunc function_, gpointer data);																																																						/* da_g_child_watch_add g_child_watch_add; */
alias da_g_idle_add = guint function(GSourceFunc function_, gpointer data);																																																						/* da_g_idle_add g_idle_add; */
alias da_g_idle_add_full = guint function(gint priority, GSourceFunc function_, gpointer data, GDestroyNotify notify);																																																						/* da_g_idle_add_full g_idle_add_full; */
alias da_g_idle_remove_by_data = gboolean function(gpointer data);																																																						/* da_g_idle_remove_by_data g_idle_remove_by_data; */
alias da_g_main_context_invoke_full = void function(GMainContext* context, gint priority, GSourceFunc function_, gpointer data, GDestroyNotify notify);																																																						/* da_g_main_context_invoke_full g_main_context_invoke_full; */
alias da_g_main_context_invoke = void function(GMainContext* context, GSourceFunc function_, gpointer data);																																																						/* da_g_main_context_invoke g_main_context_invoke; */
