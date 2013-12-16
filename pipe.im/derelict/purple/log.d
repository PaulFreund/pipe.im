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
	core.stdc.time.tm* tm;
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

alias da_purple_log_new = PurpleLog* function(PurpleLogType type, const(char)* name, PurpleAccount* account, PurpleConversation* conv, time_t time, const(tm)* tm);																																																						/* da_purple_log_new purple_log_new; */
alias da_purple_log_free = void function(PurpleLog* log);																																																						/* da_purple_log_free purple_log_free; */
alias da_purple_log_write = void function(PurpleLog* log, PurpleMessageFlags type, const(char)* from, time_t time, const(char)* message);																																																						/* da_purple_log_write purple_log_write; */
alias da_purple_log_read = char* function(PurpleLog* log, PurpleLogReadFlags* flags);																																																						/* da_purple_log_read purple_log_read; */
alias da_purple_log_get_logs = GList* function(PurpleLogType type, const(char)* name, PurpleAccount* account);																																																						/* da_purple_log_get_logs purple_log_get_logs; */
alias da_purple_log_get_log_sets = GHashTable* function();																																																						/* da_purple_log_get_log_sets purple_log_get_log_sets; */
alias da_purple_log_get_system_logs = GList* function(PurpleAccount* account);																																																						/* da_purple_log_get_system_logs purple_log_get_system_logs; */
alias da_purple_log_get_size = int function(PurpleLog* log);																																																						/* da_purple_log_get_size purple_log_get_size; */
alias da_purple_log_get_total_size = int function(PurpleLogType type, const(char)* name, PurpleAccount* account);																																																						/* da_purple_log_get_total_size purple_log_get_total_size; */
alias da_purple_log_get_activity_score = int function(PurpleLogType type, const(char)* name, PurpleAccount* account);																																																						/* da_purple_log_get_activity_score purple_log_get_activity_score; */
alias da_purple_log_is_deletable = gboolean function(PurpleLog* log);																																																						/* da_purple_log_is_deletable purple_log_is_deletable; */
alias da_purple_log_delete = gboolean function(PurpleLog* log);																																																						/* da_purple_log_delete purple_log_delete; */
alias da_purple_log_get_log_dir = char* function(PurpleLogType type, const(char)* name, PurpleAccount* account);																																																						/* da_purple_log_get_log_dir purple_log_get_log_dir; */
alias da_purple_log_compare = gint function(gconstpointer y, gconstpointer z);																																																						/* da_purple_log_compare purple_log_compare; */
alias da_purple_log_set_compare = gint function(gconstpointer y, gconstpointer z);																																																						/* da_purple_log_set_compare purple_log_set_compare; */
alias da_purple_log_set_free = void function(PurpleLogSet* set);																																																						/* da_purple_log_set_free purple_log_set_free; */
alias da_purple_log_common_writer = void function(PurpleLog* log, const(char)* ext);																																																						/* da_purple_log_common_writer purple_log_common_writer; */
alias da_purple_log_common_lister = GList* function(PurpleLogType type, const(char)* name, PurpleAccount* account, const(char)* ext, PurpleLogLogger* logger);																																																						/* da_purple_log_common_lister purple_log_common_lister; */
alias da_purple_log_common_total_sizer = int function(PurpleLogType type, const(char)* name, PurpleAccount* account, const(char)* ext);																																																						/* da_purple_log_common_total_sizer purple_log_common_total_sizer; */
alias da_purple_log_common_sizer = int function(PurpleLog* log);																																																						/* da_purple_log_common_sizer purple_log_common_sizer; */
alias da_purple_log_common_deleter = gboolean function(PurpleLog* log);																																																						/* da_purple_log_common_deleter purple_log_common_deleter; */
alias da_purple_log_common_is_deletable = gboolean function(PurpleLog* log);																																																						/* da_purple_log_common_is_deletable purple_log_common_is_deletable; */
alias da_purple_log_logger_new = PurpleLogLogger* function(const(char)* id, const(char)* name, int functions, ...);																																																						/* da_purple_log_logger_new purple_log_logger_new; */
alias da_purple_log_logger_free = void function(PurpleLogLogger* logger);																																																						/* da_purple_log_logger_free purple_log_logger_free; */
alias da_purple_log_logger_add = void function(PurpleLogLogger* logger);																																																						/* da_purple_log_logger_add purple_log_logger_add; */
alias da_purple_log_logger_remove = void function(PurpleLogLogger* logger);																																																						/* da_purple_log_logger_remove purple_log_logger_remove; */
alias da_purple_log_logger_set = void function(PurpleLogLogger* logger);																																																						/* da_purple_log_logger_set purple_log_logger_set; */
alias da_purple_log_logger_get = PurpleLogLogger* function();																																																						/* da_purple_log_logger_get purple_log_logger_get; */
alias da_purple_log_logger_get_options = GList* function();																																																						/* da_purple_log_logger_get_options purple_log_logger_get_options; */
alias da_purple_log_init = void function();																																																						/* da_purple_log_init purple_log_init; */
alias da_purple_log_get_handle = void* function();																																																						/* da_purple_log_get_handle purple_log_get_handle; */
alias da_purple_log_uninit = void function();																																																						/* da_purple_log_uninit purple_log_uninit; */
