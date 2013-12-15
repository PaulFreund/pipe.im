module derelict.glib.giochannel;

import core.stdc.config;
import core.stdc.string;

extern (C):

alias _GIOChannel GIOChannel;
alias _GIOFuncs GIOFuncs;
alias _Anonymous_0 GIOError;
alias _Anonymous_1 GIOChannelError;
alias _Anonymous_2 GIOStatus;
alias _Anonymous_3 GSeekType;
alias _Anonymous_4 GIOCondition;
alias _Anonymous_5 GIOFlags;
alias int function (_GIOChannel*, _Anonymous_4, void*) GIOFunc;

extern __gshared GSourceFuncs g_io_watch_funcs;

enum _Anonymous_0
{
	G_IO_ERROR_NONE = 0,
	G_IO_ERROR_AGAIN = 1,
	G_IO_ERROR_INVAL = 2,
	G_IO_ERROR_UNKNOWN = 3
}

enum _Anonymous_1
{
	G_IO_CHANNEL_ERROR_FBIG = 0,
	G_IO_CHANNEL_ERROR_INVAL = 1,
	G_IO_CHANNEL_ERROR_IO = 2,
	G_IO_CHANNEL_ERROR_ISDIR = 3,
	G_IO_CHANNEL_ERROR_NOSPC = 4,
	G_IO_CHANNEL_ERROR_NXIO = 5,
	G_IO_CHANNEL_ERROR_OVERFLOW = 6,
	G_IO_CHANNEL_ERROR_PIPE = 7,
	G_IO_CHANNEL_ERROR_FAILED = 8
}

enum _Anonymous_2
{
	G_IO_STATUS_ERROR = 0,
	G_IO_STATUS_NORMAL = 1,
	G_IO_STATUS_EOF = 2,
	G_IO_STATUS_AGAIN = 3
}

enum _Anonymous_3
{
	G_SEEK_CUR = 0,
	G_SEEK_SET = 1,
	G_SEEK_END = 2
}

enum _Anonymous_4
{
	G_IO_IN = 1,
	G_IO_OUT = 4,
	G_IO_PRI = 2,
	G_IO_ERR = 8,
	G_IO_HUP = 16,
	G_IO_NVAL = 32
}

enum _Anonymous_5
{
	G_IO_FLAG_APPEND = 1,
	G_IO_FLAG_NONBLOCK = 2,
	G_IO_FLAG_IS_READABLE = 4,
	G_IO_FLAG_IS_WRITABLE = 8,
	G_IO_FLAG_IS_SEEKABLE = 16,
	G_IO_FLAG_MASK = 31,
	G_IO_FLAG_GET_MASK = 31,
	G_IO_FLAG_SET_MASK = 3
}

struct _GIOChannel
{
	gint ref_count;
	GIOFuncs* funcs;
	gchar* encoding;
	GIConv read_cd;
	GIConv write_cd;
	gchar* line_term;
	guint line_term_len;
	gsize buf_size;
	GString* read_buf;
	GString* encoded_read_buf;
	GString* write_buf;
	gchar[6] partial_write_buf;
	guint use_buffer;
	guint do_encode;
	guint close_on_unref;
	guint is_readable;
	guint is_writeable;
	guint is_seekable;
	gpointer reserved1;
	gpointer reserved2;
}

struct _GIOFuncs
{
	GIOStatus function (GIOChannel*, gchar*, gsize, gsize*, GError**) io_read;
	GIOStatus function (GIOChannel*, const(gchar)*, gsize, gsize*, GError**) io_write;
	GIOStatus function (GIOChannel*, gint64, GSeekType, GError**) io_seek;
	GIOStatus function (GIOChannel*, GError**) io_close;
	GSource* function (GIOChannel*, GIOCondition) io_create_watch;
	void function (GIOChannel*) io_free;
	GIOStatus function (GIOChannel*, GIOFlags, GError**) io_set_flags;
	GIOFlags function (GIOChannel*) io_get_flags;
}

void g_io_channel_init (GIOChannel* channel);
GIOChannel* g_io_channel_ref (GIOChannel* channel);
void g_io_channel_unref (GIOChannel* channel);
GIOError g_io_channel_read (GIOChannel* channel, gchar* buf, gsize count, gsize* bytes_read);
GIOError g_io_channel_write (GIOChannel* channel, const(gchar)* buf, gsize count, gsize* bytes_written);
GIOError g_io_channel_seek (GIOChannel* channel, gint64 offset, GSeekType type);
void g_io_channel_close (GIOChannel* channel);
GIOStatus g_io_channel_shutdown (GIOChannel* channel, gboolean flush, GError** err);
guint g_io_add_watch_full (GIOChannel* channel, gint priority, GIOCondition condition, GIOFunc func, gpointer user_data, GDestroyNotify notify);
GSource* g_io_create_watch (GIOChannel* channel, GIOCondition condition);
guint g_io_add_watch (GIOChannel* channel, GIOCondition condition, GIOFunc func, gpointer user_data);
void g_io_channel_set_buffer_size (GIOChannel* channel, gsize size);
gsize g_io_channel_get_buffer_size (GIOChannel* channel);
GIOCondition g_io_channel_get_buffer_condition (GIOChannel* channel);
GIOStatus g_io_channel_set_flags (GIOChannel* channel, GIOFlags flags, GError** error);
GIOFlags g_io_channel_get_flags (GIOChannel* channel);
void g_io_channel_set_line_term (GIOChannel* channel, const(gchar)* line_term, gint length);
const(gchar)* g_io_channel_get_line_term (GIOChannel* channel, gint* length);
void g_io_channel_set_buffered (GIOChannel* channel, gboolean buffered);
gboolean g_io_channel_get_buffered (GIOChannel* channel);
GIOStatus g_io_channel_set_encoding (GIOChannel* channel, const(gchar)* encoding, GError** error);
const(gchar)* g_io_channel_get_encoding (GIOChannel* channel);
void g_io_channel_set_close_on_unref (GIOChannel* channel, gboolean do_close);
gboolean g_io_channel_get_close_on_unref (GIOChannel* channel);
GIOStatus g_io_channel_flush (GIOChannel* channel, GError** error);
GIOStatus g_io_channel_read_line (GIOChannel* channel, gchar** str_return, gsize* length, gsize* terminator_pos, GError** error);
GIOStatus g_io_channel_read_line_string (GIOChannel* channel, GString* buffer, gsize* terminator_pos, GError** error);
GIOStatus g_io_channel_read_to_end (GIOChannel* channel, gchar** str_return, gsize* length, GError** error);
GIOStatus g_io_channel_read_chars (GIOChannel* channel, gchar* buf, gsize count, gsize* bytes_read, GError** error);
GIOStatus g_io_channel_read_unichar (GIOChannel* channel, gunichar* thechar, GError** error);
GIOStatus g_io_channel_write_chars (GIOChannel* channel, const(gchar)* buf, gssize count, gsize* bytes_written, GError** error);
GIOStatus g_io_channel_write_unichar (GIOChannel* channel, gunichar thechar, GError** error);
GIOStatus g_io_channel_seek_position (GIOChannel* channel, gint64 offset, GSeekType type, GError** error);
GIOChannel* g_io_channel_new_file (const(gchar)* filename, const(gchar)* mode, GError** error);
GQuark g_io_channel_error_quark ();
GIOChannelError g_io_channel_error_from_errno (gint en);
GIOChannel* g_io_channel_unix_new (int fd);
gint g_io_channel_unix_get_fd (GIOChannel* channel);