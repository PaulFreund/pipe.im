module derelict.purple.ft;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.account;
import core.stdc.config;
import core.stdc.stdio;
import core.stdc.time;

extern (C):

alias _PurpleXfer PurpleXfer;
alias _Anonymous_0 PurpleXferType;
alias _Anonymous_1 PurpleXferStatusType;
alias _Anonymous_2 PurpleXferUiOps;

enum _Anonymous_0
{
	PURPLE_XFER_UNKNOWN = 0,
	PURPLE_XFER_SEND = 1,
	PURPLE_XFER_RECEIVE = 2
}

enum _Anonymous_1
{
	PURPLE_XFER_STATUS_UNKNOWN = 0,
	PURPLE_XFER_STATUS_NOT_STARTED = 1,
	PURPLE_XFER_STATUS_ACCEPTED = 2,
	PURPLE_XFER_STATUS_STARTED = 3,
	PURPLE_XFER_STATUS_DONE = 4,
	PURPLE_XFER_STATUS_CANCEL_LOCAL = 5,
	PURPLE_XFER_STATUS_CANCEL_REMOTE = 6
}

struct _Anonymous_2
{
	void function (PurpleXfer*) new_xfer;
	void function (PurpleXfer*) destroy;
	void function (PurpleXfer*) add_xfer;
	void function (PurpleXfer*, double) update_progress;
	void function (PurpleXfer*) cancel_local;
	void function (PurpleXfer*) cancel_remote;
	gssize function (PurpleXfer*, const(guchar)*, gssize) ui_write;
	gssize function (PurpleXfer*, guchar**, gssize) ui_read;
	void function (PurpleXfer*, const(guchar)*, gsize) data_not_sent;
	void function (PurpleXfer*, const(gchar)*) add_thumbnail;
}

struct _PurpleXfer
{
	guint ref_;
	PurpleXferType type;
	PurpleAccount* account;
	char* who;
	char* message;
	char* filename;
	char* local_filename;
	size_t size;
	FILE* dest_fp;
	char* remote_ip;
	int local_port;
	int remote_port;
	int fd;
	int watcher;
	size_t bytes_sent;
	size_t bytes_remaining;
	time_t start_time;
	time_t end_time;
	size_t current_buffer_size;
	PurpleXferStatusType status;
	struct
	{
		void function (PurpleXfer*) init;
		void function (PurpleXfer*) request_denied;
		void function (PurpleXfer*) start;
		void function (PurpleXfer*) end;
		void function (PurpleXfer*) cancel_send;
		void function (PurpleXfer*) cancel_recv;
		gssize function (guchar**, PurpleXfer*) read;
		gssize function (const(guchar)*, size_t, PurpleXfer*) write;
		void function (PurpleXfer*, const(guchar)*, size_t) ack;
	}
	PurpleXferUiOps* ui_ops;
	void* ui_data;
	void* data;
}

PurpleXfer* purple_xfer_new (PurpleAccount* account, PurpleXferType type, const(char)* who);
GList* purple_xfers_get_all ();
void purple_xfer_ref (PurpleXfer* xfer);
void purple_xfer_unref (PurpleXfer* xfer);
void purple_xfer_request (PurpleXfer* xfer);
void purple_xfer_request_accepted (PurpleXfer* xfer, const(char)* filename);
void purple_xfer_request_denied (PurpleXfer* xfer);
PurpleXferType purple_xfer_get_type (const(PurpleXfer)* xfer);
PurpleAccount* purple_xfer_get_account (const(PurpleXfer)* xfer);
const(char)* purple_xfer_get_remote_user (const(PurpleXfer)* xfer);
PurpleXferStatusType purple_xfer_get_status (const(PurpleXfer)* xfer);
gboolean purple_xfer_is_canceled (const(PurpleXfer)* xfer);
gboolean purple_xfer_is_completed (const(PurpleXfer)* xfer);
const(char)* purple_xfer_get_filename (const(PurpleXfer)* xfer);
const(char)* purple_xfer_get_local_filename (const(PurpleXfer)* xfer);
size_t purple_xfer_get_bytes_sent (const(PurpleXfer)* xfer);
size_t purple_xfer_get_bytes_remaining (const(PurpleXfer)* xfer);
size_t purple_xfer_get_size (const(PurpleXfer)* xfer);
double purple_xfer_get_progress (const(PurpleXfer)* xfer);
uint purple_xfer_get_local_port (const(PurpleXfer)* xfer);
const(char)* purple_xfer_get_remote_ip (const(PurpleXfer)* xfer);
uint purple_xfer_get_remote_port (const(PurpleXfer)* xfer);
time_t purple_xfer_get_start_time (const(PurpleXfer)* xfer);
time_t purple_xfer_get_end_time (const(PurpleXfer)* xfer);
void purple_xfer_set_completed (PurpleXfer* xfer, gboolean completed);
void purple_xfer_set_message (PurpleXfer* xfer, const(char)* message);
void purple_xfer_set_filename (PurpleXfer* xfer, const(char)* filename);
void purple_xfer_set_local_filename (PurpleXfer* xfer, const(char)* filename);
void purple_xfer_set_size (PurpleXfer* xfer, size_t size);
void purple_xfer_set_bytes_sent (PurpleXfer* xfer, size_t bytes_sent);
PurpleXferUiOps* purple_xfer_get_ui_ops (const(PurpleXfer)* xfer);
void purple_xfer_set_read_fnc (PurpleXfer* xfer, gssize function (guchar**, PurpleXfer*) fnc);
void purple_xfer_set_write_fnc (PurpleXfer* xfer, gssize function (const(guchar)*, size_t, PurpleXfer*) fnc);
void purple_xfer_set_ack_fnc (PurpleXfer* xfer, void function (PurpleXfer*, const(guchar)*, size_t) fnc);
void purple_xfer_set_request_denied_fnc (PurpleXfer* xfer, void function (PurpleXfer*) fnc);
void purple_xfer_set_init_fnc (PurpleXfer* xfer, void function (PurpleXfer*) fnc);
void purple_xfer_set_start_fnc (PurpleXfer* xfer, void function (PurpleXfer*) fnc);
void purple_xfer_set_end_fnc (PurpleXfer* xfer, void function (PurpleXfer*) fnc);
void purple_xfer_set_cancel_send_fnc (PurpleXfer* xfer, void function (PurpleXfer*) fnc);
void purple_xfer_set_cancel_recv_fnc (PurpleXfer* xfer, void function (PurpleXfer*) fnc);
gssize purple_xfer_read (PurpleXfer* xfer, guchar** buffer);
gssize purple_xfer_write (PurpleXfer* xfer, const(guchar)* buffer, gsize size);
void purple_xfer_start (PurpleXfer* xfer, int fd, const(char)* ip, uint port);
void purple_xfer_end (PurpleXfer* xfer);
void purple_xfer_add (PurpleXfer* xfer);
void purple_xfer_cancel_local (PurpleXfer* xfer);
void purple_xfer_cancel_remote (PurpleXfer* xfer);
void purple_xfer_error (PurpleXferType type, PurpleAccount* account, const(char)* who, const(char)* msg);
void purple_xfer_update_progress (PurpleXfer* xfer);
void purple_xfer_conversation_write (PurpleXfer* xfer, char* message, gboolean is_error);
void purple_xfer_ui_ready (PurpleXfer* xfer);
void purple_xfer_prpl_ready (PurpleXfer* xfer);
gconstpointer purple_xfer_get_thumbnail (const(PurpleXfer)* xfer, gsize* len);
const(gchar)* purple_xfer_get_thumbnail_mimetype (const(PurpleXfer)* xfer);
void purple_xfer_set_thumbnail (PurpleXfer* xfer, gconstpointer thumbnail, gsize size, const(gchar)* mimetype);
void purple_xfer_prepare_thumbnail (PurpleXfer* xfer, const(gchar)* formats);
void* purple_xfers_get_handle ();
void purple_xfers_init ();
void purple_xfers_uninit ();
void purple_xfers_set_ui_ops (PurpleXferUiOps* ops);
PurpleXferUiOps* purple_xfers_get_ui_ops ();