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

alias da_purple_xfer_new = PurpleXfer* function(PurpleAccount* account, PurpleXferType type, const(char)* who);																																																						/* da_purple_xfer_new purple_xfer_new; */
alias da_purple_xfers_get_all = GList* function();																																																						/* da_purple_xfers_get_all purple_xfers_get_all; */
alias da_purple_xfer_ref = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_ref purple_xfer_ref; */
alias da_purple_xfer_unref = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_unref purple_xfer_unref; */
alias da_purple_xfer_request = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_request purple_xfer_request; */
alias da_purple_xfer_request_accepted = void function(PurpleXfer* xfer, const(char)* filename);																																																						/* da_purple_xfer_request_accepted purple_xfer_request_accepted; */
alias da_purple_xfer_request_denied = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_request_denied purple_xfer_request_denied; */
alias da_purple_xfer_get_type = PurpleXferType function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_type purple_xfer_get_type; */
alias da_purple_xfer_get_account = PurpleAccount* function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_account purple_xfer_get_account; */
alias da_purple_xfer_get_remote_user = const(char)* function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_remote_user purple_xfer_get_remote_user; */
alias da_purple_xfer_get_status = PurpleXferStatusType function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_status purple_xfer_get_status; */
alias da_purple_xfer_is_canceled = gboolean function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_is_canceled purple_xfer_is_canceled; */
alias da_purple_xfer_is_completed = gboolean function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_is_completed purple_xfer_is_completed; */
alias da_purple_xfer_get_filename = const(char)* function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_filename purple_xfer_get_filename; */
alias da_purple_xfer_get_local_filename = const(char)* function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_local_filename purple_xfer_get_local_filename; */
alias da_purple_xfer_get_bytes_sent = size_t function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_bytes_sent purple_xfer_get_bytes_sent; */
alias da_purple_xfer_get_bytes_remaining = size_t function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_bytes_remaining purple_xfer_get_bytes_remaining; */
alias da_purple_xfer_get_size = size_t function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_size purple_xfer_get_size; */
alias da_purple_xfer_get_progress = double function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_progress purple_xfer_get_progress; */
alias da_purple_xfer_get_local_port = uint function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_local_port purple_xfer_get_local_port; */
alias da_purple_xfer_get_remote_ip = const(char)* function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_remote_ip purple_xfer_get_remote_ip; */
alias da_purple_xfer_get_remote_port = uint function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_remote_port purple_xfer_get_remote_port; */
alias da_purple_xfer_get_start_time = time_t function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_start_time purple_xfer_get_start_time; */
alias da_purple_xfer_get_end_time = time_t function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_end_time purple_xfer_get_end_time; */
alias da_purple_xfer_set_completed = void function(PurpleXfer* xfer, gboolean completed);																																																						/* da_purple_xfer_set_completed purple_xfer_set_completed; */
alias da_purple_xfer_set_message = void function(PurpleXfer* xfer, const(char)* message);																																																						/* da_purple_xfer_set_message purple_xfer_set_message; */
alias da_purple_xfer_set_filename = void function(PurpleXfer* xfer, const(char)* filename);																																																						/* da_purple_xfer_set_filename purple_xfer_set_filename; */
alias da_purple_xfer_set_local_filename = void function(PurpleXfer* xfer, const(char)* filename);																																																						/* da_purple_xfer_set_local_filename purple_xfer_set_local_filename; */
alias da_purple_xfer_set_size = void function(PurpleXfer* xfer, size_t size);																																																						/* da_purple_xfer_set_size purple_xfer_set_size; */
alias da_purple_xfer_set_bytes_sent = void function(PurpleXfer* xfer, size_t bytes_sent);																																																						/* da_purple_xfer_set_bytes_sent purple_xfer_set_bytes_sent; */
alias da_purple_xfer_get_ui_ops = PurpleXferUiOps* function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_ui_ops purple_xfer_get_ui_ops; */
alias da_purple_xfer_set_read_fnc = void function(PurpleXfer* xfer, gssize function (guchar**, PurpleXfer*) fnc);																																																						/* da_purple_xfer_set_read_fnc purple_xfer_set_read_fnc; */
alias da_purple_xfer_set_write_fnc = void function(PurpleXfer* xfer, gssize function (const(guchar)*, size_t, PurpleXfer*) fnc);																																																						/* da_purple_xfer_set_write_fnc purple_xfer_set_write_fnc; */
alias da_purple_xfer_set_ack_fnc = void function(PurpleXfer* xfer, void function (PurpleXfer*, const(guchar)*, size_t) fnc);																																																						/* da_purple_xfer_set_ack_fnc purple_xfer_set_ack_fnc; */
alias da_purple_xfer_set_request_denied_fnc = void function(PurpleXfer* xfer, void function (PurpleXfer*) fnc);																																																						/* da_purple_xfer_set_request_denied_fnc purple_xfer_set_request_denied_fnc; */
alias da_purple_xfer_set_init_fnc = void function(PurpleXfer* xfer, void function (PurpleXfer*) fnc);																																																						/* da_purple_xfer_set_init_fnc purple_xfer_set_init_fnc; */
alias da_purple_xfer_set_start_fnc = void function(PurpleXfer* xfer, void function (PurpleXfer*) fnc);																																																						/* da_purple_xfer_set_start_fnc purple_xfer_set_start_fnc; */
alias da_purple_xfer_set_end_fnc = void function(PurpleXfer* xfer, void function (PurpleXfer*) fnc);																																																						/* da_purple_xfer_set_end_fnc purple_xfer_set_end_fnc; */
alias da_purple_xfer_set_cancel_send_fnc = void function(PurpleXfer* xfer, void function (PurpleXfer*) fnc);																																																						/* da_purple_xfer_set_cancel_send_fnc purple_xfer_set_cancel_send_fnc; */
alias da_purple_xfer_set_cancel_recv_fnc = void function(PurpleXfer* xfer, void function (PurpleXfer*) fnc);																																																						/* da_purple_xfer_set_cancel_recv_fnc purple_xfer_set_cancel_recv_fnc; */
alias da_purple_xfer_read = gssize function(PurpleXfer* xfer, guchar** buffer);																																																						/* da_purple_xfer_read purple_xfer_read; */
alias da_purple_xfer_write = gssize function(PurpleXfer* xfer, const(guchar)* buffer, gsize size);																																																						/* da_purple_xfer_write purple_xfer_write; */
alias da_purple_xfer_start = void function(PurpleXfer* xfer, int fd, const(char)* ip, uint port);																																																						/* da_purple_xfer_start purple_xfer_start; */
alias da_purple_xfer_end = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_end purple_xfer_end; */
alias da_purple_xfer_add = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_add purple_xfer_add; */
alias da_purple_xfer_cancel_local = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_cancel_local purple_xfer_cancel_local; */
alias da_purple_xfer_cancel_remote = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_cancel_remote purple_xfer_cancel_remote; */
alias da_purple_xfer_error = void function(PurpleXferType type, PurpleAccount* account, const(char)* who, const(char)* msg);																																																						/* da_purple_xfer_error purple_xfer_error; */
alias da_purple_xfer_update_progress = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_update_progress purple_xfer_update_progress; */
alias da_purple_xfer_conversation_write = void function(PurpleXfer* xfer, char* message, gboolean is_error);																																																						/* da_purple_xfer_conversation_write purple_xfer_conversation_write; */
alias da_purple_xfer_ui_ready = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_ui_ready purple_xfer_ui_ready; */
alias da_purple_xfer_prpl_ready = void function(PurpleXfer* xfer);																																																						/* da_purple_xfer_prpl_ready purple_xfer_prpl_ready; */
alias da_purple_xfer_get_thumbnail = gconstpointer function(const(PurpleXfer)* xfer, gsize* len);																																																						/* da_purple_xfer_get_thumbnail purple_xfer_get_thumbnail; */
alias da_purple_xfer_get_thumbnail_mimetype = const(gchar)* function(const(PurpleXfer)* xfer);																																																						/* da_purple_xfer_get_thumbnail_mimetype purple_xfer_get_thumbnail_mimetype; */
alias da_purple_xfer_set_thumbnail = void function(PurpleXfer* xfer, gconstpointer thumbnail, gsize size, const(gchar)* mimetype);																																																						/* da_purple_xfer_set_thumbnail purple_xfer_set_thumbnail; */
alias da_purple_xfer_prepare_thumbnail = void function(PurpleXfer* xfer, const(gchar)* formats);																																																						/* da_purple_xfer_prepare_thumbnail purple_xfer_prepare_thumbnail; */
alias da_purple_xfers_get_handle = void* function();																																																						/* da_purple_xfers_get_handle purple_xfers_get_handle; */
alias da_purple_xfers_init = void function();																																																						/* da_purple_xfers_init purple_xfers_init; */
alias da_purple_xfers_uninit = void function();																																																						/* da_purple_xfers_uninit purple_xfers_uninit; */
alias da_purple_xfers_set_ui_ops = void function(PurpleXferUiOps* ops);																																																						/* da_purple_xfers_set_ui_ops purple_xfers_set_ui_ops; */
alias da_purple_xfers_get_ui_ops = PurpleXferUiOps* function();																																																						/* da_purple_xfers_get_ui_ops purple_xfers_get_ui_ops; */
