module derelict.purple.log;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.ghash;
import derelict.glib.glist;
import derelict.purple.conversation;
import derelict.purple.account;
import core.stdc.time;
import core.stdc.config;
import core.stdc.stdio;

extern (C):

alias _PurpleLog PurpleLog;
alias _PurpleLogLogger PurpleLogLogger;
alias _PurpleLogCommonLoggerData PurpleLogCommonLoggerData;
alias _PurpleLogSet PurpleLogSet;
alias _Anonymous_0 PurpleLogType;
alias _Anonymous_1 PurpleLogReadFlags;
alias void function (_GHashTable*, _PurpleLogSet*) PurpleLogSetCallback;

enum _Anonymous_0
{
	PURPLE_LOG_IM = 0,
	PURPLE_LOG_CHAT = 1,
	PURPLE_LOG_SYSTEM = 2
}

enum _Anonymous_1
{
	PURPLE_LOG_READ_NO_NEWLINE = 1
}

struct _PurpleLogLogger
{
	char* name;
	char* id;
	void function (PurpleLog*) create;
	gsize function (PurpleLog*, PurpleMessageFlags, const(char)*, time_t, const(char)*) write;
	void function (PurpleLog*) finalize;
	GList* function (PurpleLogType, const(char)*, PurpleAccount*) list;
	char* function (PurpleLog*, PurpleLogReadFlags*) read;
	int function (PurpleLog*) size;
	int function (PurpleLogType, const(char)*, PurpleAccount*) total_size;
	GList* function (PurpleAccount*) list_syslog;
	void function (PurpleLogSetCallback, GHashTable*) get_log_sets;
	gboolean function (PurpleLog*) remove;
	gboolean function (PurpleLog*) is_deletable;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurpleLog
{
	PurpleLogType type;
	char* name;
	PurpleAccount* account;
	PurpleConversation* conv;
	time_t time;
	PurpleLogLogger* logger;
	void* logger_data;
	tm* tm;
}

struct _PurpleLogCommonLoggerData
{
	char* path;
	FILE* file;
	void* extra_data;
}

struct _PurpleLogSet
{
	PurpleLogType type;
	char* name;
	PurpleAccount* account;
	gboolean buddy;
	char* normalized_name;
}

PurpleLog* purple_log_new (PurpleLogType type, const(char)* name, PurpleAccount* account, PurpleConversation* conv, time_t time, const(tm)* tm);
void purple_log_free (PurpleLog* log);
void purple_log_write (PurpleLog* log, PurpleMessageFlags type, const(char)* from, time_t time, const(char)* message);
char* purple_log_read (PurpleLog* log, PurpleLogReadFlags* flags);
GList* purple_log_get_logs (PurpleLogType type, const(char)* name, PurpleAccount* account);
GHashTable* purple_log_get_log_sets ();
GList* purple_log_get_system_logs (PurpleAccount* account);
int purple_log_get_size (PurpleLog* log);
int purple_log_get_total_size (PurpleLogType type, const(char)* name, PurpleAccount* account);
int purple_log_get_activity_score (PurpleLogType type, const(char)* name, PurpleAccount* account);
gboolean purple_log_is_deletable (PurpleLog* log);
gboolean purple_log_delete (PurpleLog* log);
char* purple_log_get_log_dir (PurpleLogType type, const(char)* name, PurpleAccount* account);
gint purple_log_compare (gconstpointer y, gconstpointer z);
gint purple_log_set_compare (gconstpointer y, gconstpointer z);
void purple_log_set_free (PurpleLogSet* set);
void purple_log_common_writer (PurpleLog* log, const(char)* ext);
GList* purple_log_common_lister (PurpleLogType type, const(char)* name, PurpleAccount* account, const(char)* ext, PurpleLogLogger* logger);
int purple_log_common_total_sizer (PurpleLogType type, const(char)* name, PurpleAccount* account, const(char)* ext);
int purple_log_common_sizer (PurpleLog* log);
gboolean purple_log_common_deleter (PurpleLog* log);
gboolean purple_log_common_is_deletable (PurpleLog* log);
PurpleLogLogger* purple_log_logger_new (const(char)* id, const(char)* name, int functions, ...);
void purple_log_logger_free (PurpleLogLogger* logger);
void purple_log_logger_add (PurpleLogLogger* logger);
void purple_log_logger_remove (PurpleLogLogger* logger);
void purple_log_logger_set (PurpleLogLogger* logger);
PurpleLogLogger* purple_log_logger_get ();
GList* purple_log_logger_get_options ();
void purple_log_init ();
void* purple_log_get_handle ();
void purple_log_uninit ();