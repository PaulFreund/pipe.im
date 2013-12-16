module derelict.glib.giochannel;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gstring;
import derelict.glib.gerror;
import derelict.glib.gquark;
import derelict.glib.gunicode;
import derelict.glib.gmain;
import derelict.glib.gconvert;
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

alias da_g_io_channel_init = void function(GIOChannel* channel);																																																						/* da_g_io_channel_init g_io_channel_init; */
alias da_g_io_channel_ref = GIOChannel* function(GIOChannel* channel);																																																						/* da_g_io_channel_ref g_io_channel_ref; */
alias da_g_io_channel_unref = void function(GIOChannel* channel);																																																						/* da_g_io_channel_unref g_io_channel_unref; */
alias da_g_io_channel_read = GIOError function(GIOChannel* channel, gchar* buf, gsize count, gsize* bytes_read);																																																						/* da_g_io_channel_read g_io_channel_read; */
alias da_g_io_channel_write = GIOError function(GIOChannel* channel, const(gchar)* buf, gsize count, gsize* bytes_written);																																																						/* da_g_io_channel_write g_io_channel_write; */
alias da_g_io_channel_seek = GIOError function(GIOChannel* channel, gint64 offset, GSeekType type);																																																						/* da_g_io_channel_seek g_io_channel_seek; */
alias da_g_io_channel_close = void function(GIOChannel* channel);																																																						/* da_g_io_channel_close g_io_channel_close; */
alias da_g_io_channel_shutdown = GIOStatus function(GIOChannel* channel, gboolean flush, GError** err);																																																						/* da_g_io_channel_shutdown g_io_channel_shutdown; */
alias da_g_io_add_watch_full = guint function(GIOChannel* channel, gint priority, GIOCondition condition, GIOFunc func, gpointer user_data, GDestroyNotify notify);																																																						/* da_g_io_add_watch_full g_io_add_watch_full; */
alias da_g_io_create_watch = GSource* function(GIOChannel* channel, GIOCondition condition);																																																						/* da_g_io_create_watch g_io_create_watch; */
alias da_g_io_add_watch = guint function(GIOChannel* channel, GIOCondition condition, GIOFunc func, gpointer user_data);																																																						/* da_g_io_add_watch g_io_add_watch; */
alias da_g_io_channel_set_buffer_size = void function(GIOChannel* channel, gsize size);																																																						/* da_g_io_channel_set_buffer_size g_io_channel_set_buffer_size; */
alias da_g_io_channel_get_buffer_size = gsize function(GIOChannel* channel);																																																						/* da_g_io_channel_get_buffer_size g_io_channel_get_buffer_size; */
alias da_g_io_channel_get_buffer_condition = GIOCondition function(GIOChannel* channel);																																																						/* da_g_io_channel_get_buffer_condition g_io_channel_get_buffer_condition; */
alias da_g_io_channel_set_flags = GIOStatus function(GIOChannel* channel, GIOFlags flags, GError** error);																																																						/* da_g_io_channel_set_flags g_io_channel_set_flags; */
alias da_g_io_channel_get_flags = GIOFlags function(GIOChannel* channel);																																																						/* da_g_io_channel_get_flags g_io_channel_get_flags; */
alias da_g_io_channel_set_line_term = void function(GIOChannel* channel, const(gchar)* line_term, gint length);																																																						/* da_g_io_channel_set_line_term g_io_channel_set_line_term; */
alias da_g_io_channel_get_line_term = const(gchar)* function(GIOChannel* channel, gint* length);																																																						/* da_g_io_channel_get_line_term g_io_channel_get_line_term; */
alias da_g_io_channel_set_buffered = void function(GIOChannel* channel, gboolean buffered);																																																						/* da_g_io_channel_set_buffered g_io_channel_set_buffered; */
alias da_g_io_channel_get_buffered = gboolean function(GIOChannel* channel);																																																						/* da_g_io_channel_get_buffered g_io_channel_get_buffered; */
alias da_g_io_channel_set_encoding = GIOStatus function(GIOChannel* channel, const(gchar)* encoding, GError** error);																																																						/* da_g_io_channel_set_encoding g_io_channel_set_encoding; */
alias da_g_io_channel_get_encoding = const(gchar)* function(GIOChannel* channel);																																																						/* da_g_io_channel_get_encoding g_io_channel_get_encoding; */
alias da_g_io_channel_set_close_on_unref = void function(GIOChannel* channel, gboolean do_close);																																																						/* da_g_io_channel_set_close_on_unref g_io_channel_set_close_on_unref; */
alias da_g_io_channel_get_close_on_unref = gboolean function(GIOChannel* channel);																																																						/* da_g_io_channel_get_close_on_unref g_io_channel_get_close_on_unref; */
alias da_g_io_channel_flush = GIOStatus function(GIOChannel* channel, GError** error);																																																						/* da_g_io_channel_flush g_io_channel_flush; */
alias da_g_io_channel_read_line = GIOStatus function(GIOChannel* channel, gchar** str_return, gsize* length, gsize* terminator_pos, GError** error);																																																						/* da_g_io_channel_read_line g_io_channel_read_line; */
alias da_g_io_channel_read_line_string = GIOStatus function(GIOChannel* channel, GString* buffer, gsize* terminator_pos, GError** error);																																																						/* da_g_io_channel_read_line_string g_io_channel_read_line_string; */
alias da_g_io_channel_read_to_end = GIOStatus function(GIOChannel* channel, gchar** str_return, gsize* length, GError** error);																																																						/* da_g_io_channel_read_to_end g_io_channel_read_to_end; */
alias da_g_io_channel_read_chars = GIOStatus function(GIOChannel* channel, gchar* buf, gsize count, gsize* bytes_read, GError** error);																																																						/* da_g_io_channel_read_chars g_io_channel_read_chars; */
alias da_g_io_channel_read_unichar = GIOStatus function(GIOChannel* channel, gunichar* thechar, GError** error);																																																						/* da_g_io_channel_read_unichar g_io_channel_read_unichar; */
alias da_g_io_channel_write_chars = GIOStatus function(GIOChannel* channel, const(gchar)* buf, gssize count, gsize* bytes_written, GError** error);																																																						/* da_g_io_channel_write_chars g_io_channel_write_chars; */
alias da_g_io_channel_write_unichar = GIOStatus function(GIOChannel* channel, gunichar thechar, GError** error);																																																						/* da_g_io_channel_write_unichar g_io_channel_write_unichar; */
alias da_g_io_channel_seek_position = GIOStatus function(GIOChannel* channel, gint64 offset, GSeekType type, GError** error);																																																						/* da_g_io_channel_seek_position g_io_channel_seek_position; */
alias da_g_io_channel_new_file = GIOChannel* function(const(gchar)* filename, const(gchar)* mode, GError** error);																																																						/* da_g_io_channel_new_file g_io_channel_new_file; */
alias da_g_io_channel_error_quark = GQuark function();																																																						/* da_g_io_channel_error_quark g_io_channel_error_quark; */
alias da_g_io_channel_error_from_errno = GIOChannelError function(gint en);																																																						/* da_g_io_channel_error_from_errno g_io_channel_error_from_errno; */
alias da_g_io_channel_unix_new = GIOChannel* function(int fd);																																																						/* da_g_io_channel_unix_new g_io_channel_unix_new; */
alias da_g_io_channel_unix_get_fd = gint function(GIOChannel* channel);																																																						/* da_g_io_channel_unix_get_fd g_io_channel_unix_get_fd; */
