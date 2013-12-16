module derelict.glib.gthread;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gquark;
import derelict.glib.gerror;
import core.stdc.config;

extern (C):

alias _Anonymous_0 GThreadError;
alias void* function (void*) GThreadFunc;
alias _GThread GThread;
alias _GMutex GMutex;
alias _GRecMutex GRecMutex;
alias _GRWLock GRWLock;
alias _GCond GCond;
alias _GPrivate GPrivate;
alias _GOnce GOnce;
alias _Anonymous_1 GOnceStatus;

enum _Anonymous_0
{
	G_THREAD_ERROR_AGAIN = 0
}

enum _Anonymous_1
{
	G_ONCE_STATUS_NOTCALLED = 0,
	G_ONCE_STATUS_PROGRESS = 1,
	G_ONCE_STATUS_READY = 2
}

struct _GRWLock
{
	gpointer p;
	guint[2] i;
}

struct _GCond
{
	gpointer p;
	guint[2] i;
}

struct _GRecMutex
{
	gpointer p;
	guint[2] i;
}

struct _GPrivate
{
	gpointer p;
	GDestroyNotify notify;
	gpointer[2] future;
}

struct _GOnce
{
	GOnceStatus status;
	gpointer retval;
}

struct _GThread;


//union _GMutex;


union _GMutex
{
	gpointer p;
	guint[2] i;
}

alias da_g_thread_error_quark = GQuark function();																																																						/* da_g_thread_error_quark g_thread_error_quark; */
alias da_g_thread_ref = GThread* function(GThread* thread);																																																						/* da_g_thread_ref g_thread_ref; */
alias da_g_thread_unref = void function(GThread* thread);																																																						/* da_g_thread_unref g_thread_unref; */
alias da_g_thread_new = GThread* function(const(gchar)* name, GThreadFunc func, gpointer data);																																																						/* da_g_thread_new g_thread_new; */
alias da_g_thread_try_new = GThread* function(const(gchar)* name, GThreadFunc func, gpointer data, GError** error);																																																						/* da_g_thread_try_new g_thread_try_new; */
alias da_g_thread_self = GThread* function();																																																						/* da_g_thread_self g_thread_self; */
alias da_g_thread_exit = void function(gpointer retval);																																																						/* da_g_thread_exit g_thread_exit; */
alias da_g_thread_join = gpointer function(GThread* thread);																																																						/* da_g_thread_join g_thread_join; */
alias da_g_thread_yield = void function();																																																						/* da_g_thread_yield g_thread_yield; */
alias da_g_mutex_init = void function(GMutex* mutex);																																																						/* da_g_mutex_init g_mutex_init; */
alias da_g_mutex_clear = void function(GMutex* mutex);																																																						/* da_g_mutex_clear g_mutex_clear; */
alias da_g_mutex_lock = void function(GMutex* mutex);																																																						/* da_g_mutex_lock g_mutex_lock; */
alias da_g_mutex_trylock = gboolean function(GMutex* mutex);																																																						/* da_g_mutex_trylock g_mutex_trylock; */
alias da_g_mutex_unlock = void function(GMutex* mutex);																																																						/* da_g_mutex_unlock g_mutex_unlock; */
alias da_g_rw_lock_init = void function(GRWLock* rw_lock);																																																						/* da_g_rw_lock_init g_rw_lock_init; */
alias da_g_rw_lock_clear = void function(GRWLock* rw_lock);																																																						/* da_g_rw_lock_clear g_rw_lock_clear; */
alias da_g_rw_lock_writer_lock = void function(GRWLock* rw_lock);																																																						/* da_g_rw_lock_writer_lock g_rw_lock_writer_lock; */
alias da_g_rw_lock_writer_trylock = gboolean function(GRWLock* rw_lock);																																																						/* da_g_rw_lock_writer_trylock g_rw_lock_writer_trylock; */
alias da_g_rw_lock_writer_unlock = void function(GRWLock* rw_lock);																																																						/* da_g_rw_lock_writer_unlock g_rw_lock_writer_unlock; */
alias da_g_rw_lock_reader_lock = void function(GRWLock* rw_lock);																																																						/* da_g_rw_lock_reader_lock g_rw_lock_reader_lock; */
alias da_g_rw_lock_reader_trylock = gboolean function(GRWLock* rw_lock);																																																						/* da_g_rw_lock_reader_trylock g_rw_lock_reader_trylock; */
alias da_g_rw_lock_reader_unlock = void function(GRWLock* rw_lock);																																																						/* da_g_rw_lock_reader_unlock g_rw_lock_reader_unlock; */
alias da_g_rec_mutex_init = void function(GRecMutex* rec_mutex);																																																						/* da_g_rec_mutex_init g_rec_mutex_init; */
alias da_g_rec_mutex_clear = void function(GRecMutex* rec_mutex);																																																						/* da_g_rec_mutex_clear g_rec_mutex_clear; */
alias da_g_rec_mutex_lock = void function(GRecMutex* rec_mutex);																																																						/* da_g_rec_mutex_lock g_rec_mutex_lock; */
alias da_g_rec_mutex_trylock = gboolean function(GRecMutex* rec_mutex);																																																						/* da_g_rec_mutex_trylock g_rec_mutex_trylock; */
alias da_g_rec_mutex_unlock = void function(GRecMutex* rec_mutex);																																																						/* da_g_rec_mutex_unlock g_rec_mutex_unlock; */
alias da_g_cond_init = void function(GCond* cond);																																																						/* da_g_cond_init g_cond_init; */
alias da_g_cond_clear = void function(GCond* cond);																																																						/* da_g_cond_clear g_cond_clear; */
alias da_g_cond_wait = void function(GCond* cond, GMutex* mutex);																																																						/* da_g_cond_wait g_cond_wait; */
alias da_g_cond_signal = void function(GCond* cond);																																																						/* da_g_cond_signal g_cond_signal; */
alias da_g_cond_broadcast = void function(GCond* cond);																																																						/* da_g_cond_broadcast g_cond_broadcast; */
alias da_g_cond_wait_until = gboolean function(GCond* cond, GMutex* mutex, gint64 end_time);																																																						/* da_g_cond_wait_until g_cond_wait_until; */
alias da_g_private_get = gpointer function(GPrivate* key);																																																						/* da_g_private_get g_private_get; */
alias da_g_private_set = void function(GPrivate* key, gpointer value);																																																						/* da_g_private_set g_private_set; */
alias da_g_private_replace = void function(GPrivate* key, gpointer value);																																																						/* da_g_private_replace g_private_replace; */
alias da_g_once_impl = gpointer function(GOnce* once, GThreadFunc func, gpointer arg);																																																						/* da_g_once_impl g_once_impl; */
alias da_g_once_init_enter = gboolean function(void* location);																																																						/* da_g_once_init_enter g_once_init_enter; */
alias da_g_once_init_leave = void function(void* location, gsize result);																																																						/* da_g_once_init_leave g_once_init_leave; */
