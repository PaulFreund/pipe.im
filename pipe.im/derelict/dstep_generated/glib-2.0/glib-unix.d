extern (C):

GQuark g_unix_error_quark ();
gboolean g_unix_open_pipe (gint* fds, gint flags, GError** error);
gboolean g_unix_set_fd_nonblocking (gint fd, gboolean nonblock, GError** error);
GSource* g_unix_signal_source_new (gint signum);
guint g_unix_signal_add_full (gint priority, gint signum, GSourceFunc handler, gpointer user_data, GDestroyNotify notify);
guint g_unix_signal_add (gint signum, GSourceFunc handler, gpointer user_data);