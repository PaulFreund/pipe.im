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


union _GMutex;


union _GMutex
{
	gpointer p;
	guint[2] i;
}

GQuark g_thread_error_quark ();
GThread* g_thread_ref (GThread* thread);
void g_thread_unref (GThread* thread);
GThread* g_thread_new (const(gchar)* name, GThreadFunc func, gpointer data);
GThread* g_thread_try_new (const(gchar)* name, GThreadFunc func, gpointer data, GError** error);
GThread* g_thread_self ();
void g_thread_exit (gpointer retval);
gpointer g_thread_join (GThread* thread);
void g_thread_yield ();
void g_mutex_init (GMutex* mutex);
void g_mutex_clear (GMutex* mutex);
void g_mutex_lock (GMutex* mutex);
gboolean g_mutex_trylock (GMutex* mutex);
void g_mutex_unlock (GMutex* mutex);
void g_rw_lock_init (GRWLock* rw_lock);
void g_rw_lock_clear (GRWLock* rw_lock);
void g_rw_lock_writer_lock (GRWLock* rw_lock);
gboolean g_rw_lock_writer_trylock (GRWLock* rw_lock);
void g_rw_lock_writer_unlock (GRWLock* rw_lock);
void g_rw_lock_reader_lock (GRWLock* rw_lock);
gboolean g_rw_lock_reader_trylock (GRWLock* rw_lock);
void g_rw_lock_reader_unlock (GRWLock* rw_lock);
void g_rec_mutex_init (GRecMutex* rec_mutex);
void g_rec_mutex_clear (GRecMutex* rec_mutex);
void g_rec_mutex_lock (GRecMutex* rec_mutex);
gboolean g_rec_mutex_trylock (GRecMutex* rec_mutex);
void g_rec_mutex_unlock (GRecMutex* rec_mutex);
void g_cond_init (GCond* cond);
void g_cond_clear (GCond* cond);
void g_cond_wait (GCond* cond, GMutex* mutex);
void g_cond_signal (GCond* cond);
void g_cond_broadcast (GCond* cond);
gboolean g_cond_wait_until (GCond* cond, GMutex* mutex, gint64 end_time);
gpointer g_private_get (GPrivate* key);
void g_private_set (GPrivate* key, gpointer value);
void g_private_replace (GPrivate* key, gpointer value);
gpointer g_once_impl (GOnce* once, GThreadFunc func, gpointer arg);
gboolean g_once_init_enter (void* location);
void g_once_init_leave (void* location, gsize result);