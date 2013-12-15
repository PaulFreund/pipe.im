module derelict.glib.deprecated_gthread;

import core.stdc.config;

extern (C):

alias _Anonymous_0 GThreadPriority;
alias _GThreadFunctions GThreadFunctions;
alias _Anonymous_1 GStaticMutex;
alias _GStaticRecMutex GStaticRecMutex;
alias _GStaticRWLock GStaticRWLock;
alias _GStaticPrivate GStaticPrivate;

extern __gshared GThreadFunctions g_thread_functions_for_glib_use;
extern __gshared gboolean g_thread_use_default_impl;
extern __gshared guint64 function () g_thread_gettime;
extern __gshared gboolean g_threads_got_initialized;

enum _Anonymous_0
{
	G_THREAD_PRIORITY_LOW = 0,
	G_THREAD_PRIORITY_NORMAL = 1,
	G_THREAD_PRIORITY_HIGH = 2,
	G_THREAD_PRIORITY_URGENT = 3
}

struct _GThread
{
	GThreadFunc func;
	gpointer data;
	gboolean joinable;
	GThreadPriority priority;
}

struct _GThreadFunctions
{
	GMutex* function () mutex_new;
	void function (GMutex*) mutex_lock;
	gboolean function (GMutex*) mutex_trylock;
	void function (GMutex*) mutex_unlock;
	void function (GMutex*) mutex_free;
	GCond* function () cond_new;
	void function (GCond*) cond_signal;
	void function (GCond*) cond_broadcast;
	void function (GCond*, GMutex*) cond_wait;
	gboolean function (GCond*, GMutex*, GTimeVal*) cond_timed_wait;
	void function (GCond*) cond_free;
	GPrivate* function (GDestroyNotify) private_new;
	gpointer function (GPrivate*) private_get;
	void function (GPrivate*, gpointer) private_set;
	void function (GThreadFunc, gpointer, gulong, gboolean, gboolean, GThreadPriority, gpointer, GError**) thread_create;
	void function () thread_yield;
	void function (gpointer) thread_join;
	void function () thread_exit;
	void function (gpointer, GThreadPriority) thread_set_priority;
	void function (gpointer) thread_self;
	gboolean function (gpointer, gpointer) thread_equal;
}

struct _Anonymous_1
{
	GMutex* mutex;
	pthread_mutex_t unused;
}

struct _GStaticRecMutex
{
	GStaticMutex mutex;
	guint depth;
	union
	{
		pthread_t owner;
		gdouble dummy;
	}
}

struct _GStaticRWLock
{
	GStaticMutex mutex;
	GCond* read_cond;
	GCond* write_cond;
	guint read_counter;
	gboolean have_writer;
	guint want_to_read;
	guint want_to_write;
}

struct _GStaticPrivate
{
	guint index;
}

GThread* g_thread_create (GThreadFunc func, gpointer data, gboolean joinable, GError** error);
GThread* g_thread_create_full (GThreadFunc func, gpointer data, gulong stack_size, gboolean joinable, gboolean bound, GThreadPriority priority, GError** error);
void g_thread_set_priority (GThread* thread, GThreadPriority priority);
void g_thread_foreach (GFunc thread_func, gpointer user_data);
void g_static_mutex_init (GStaticMutex* mutex);
void g_static_mutex_free (GStaticMutex* mutex);
GMutex* g_static_mutex_get_mutex_impl (GStaticMutex* mutex);
void g_static_rec_mutex_init (GStaticRecMutex* mutex);
void g_static_rec_mutex_lock (GStaticRecMutex* mutex);
gboolean g_static_rec_mutex_trylock (GStaticRecMutex* mutex);
void g_static_rec_mutex_unlock (GStaticRecMutex* mutex);
void g_static_rec_mutex_lock_full (GStaticRecMutex* mutex, guint depth);
guint g_static_rec_mutex_unlock_full (GStaticRecMutex* mutex);
void g_static_rec_mutex_free (GStaticRecMutex* mutex);
void g_static_rw_lock_init (GStaticRWLock* lock);
void g_static_rw_lock_reader_lock (GStaticRWLock* lock);
gboolean g_static_rw_lock_reader_trylock (GStaticRWLock* lock);
void g_static_rw_lock_reader_unlock (GStaticRWLock* lock);
void g_static_rw_lock_writer_lock (GStaticRWLock* lock);
gboolean g_static_rw_lock_writer_trylock (GStaticRWLock* lock);
void g_static_rw_lock_writer_unlock (GStaticRWLock* lock);
void g_static_rw_lock_free (GStaticRWLock* lock);
GPrivate* g_private_new (GDestroyNotify notify);
void g_static_private_init (GStaticPrivate* private_key);
gpointer g_static_private_get (GStaticPrivate* private_key);
void g_static_private_set (GStaticPrivate* private_key, gpointer data, GDestroyNotify notify);
void g_static_private_free (GStaticPrivate* private_key);
gboolean g_once_init_enter_impl (gsize* location);
void g_thread_init (gpointer vtable);
void g_thread_init_with_errorcheck_mutexes (gpointer vtable);
gboolean g_thread_get_initialized ();
GMutex* g_mutex_new ();
void g_mutex_free (GMutex* mutex);
GCond* g_cond_new ();
void g_cond_free (GCond* cond);
gboolean g_cond_timed_wait (GCond* cond, GMutex* mutex, GTimeVal* timeval);