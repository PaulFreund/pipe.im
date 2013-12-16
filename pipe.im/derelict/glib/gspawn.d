module derelict.glib.gspawn;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gquark;
import derelict.glib.gerror;

import core.stdc.config;

extern (C):

alias _Anonymous_0 GSpawnError;
alias void function (void*) GSpawnChildSetupFunc;
alias _Anonymous_1 GSpawnFlags;

enum _Anonymous_0
{
	G_SPAWN_ERROR_FORK = 0,
	G_SPAWN_ERROR_READ = 1,
	G_SPAWN_ERROR_CHDIR = 2,
	G_SPAWN_ERROR_ACCES = 3,
	G_SPAWN_ERROR_PERM = 4,
	G_SPAWN_ERROR_TOO_BIG = 5,
	G_SPAWN_ERROR_2BIG = 5,
	G_SPAWN_ERROR_NOEXEC = 6,
	G_SPAWN_ERROR_NAMETOOLONG = 7,
	G_SPAWN_ERROR_NOENT = 8,
	G_SPAWN_ERROR_NOMEM = 9,
	G_SPAWN_ERROR_NOTDIR = 10,
	G_SPAWN_ERROR_LOOP = 11,
	G_SPAWN_ERROR_TXTBUSY = 12,
	G_SPAWN_ERROR_IO = 13,
	G_SPAWN_ERROR_NFILE = 14,
	G_SPAWN_ERROR_MFILE = 15,
	G_SPAWN_ERROR_INVAL = 16,
	G_SPAWN_ERROR_ISDIR = 17,
	G_SPAWN_ERROR_LIBBAD = 18,
	G_SPAWN_ERROR_FAILED = 19
}

enum _Anonymous_1
{
	G_SPAWN_LEAVE_DESCRIPTORS_OPEN = 1,
	G_SPAWN_DO_NOT_REAP_CHILD = 2,
	G_SPAWN_SEARCH_PATH = 4,
	G_SPAWN_STDOUT_TO_DEV_NULL = 8,
	G_SPAWN_STDERR_TO_DEV_NULL = 16,
	G_SPAWN_CHILD_INHERITS_STDIN = 32,
	G_SPAWN_FILE_AND_ARGV_ZERO = 64
}

alias da_g_spawn_error_quark = GQuark function();																																																						/* da_g_spawn_error_quark g_spawn_error_quark; */
alias da_g_spawn_async = gboolean function(const(gchar)* working_directory, gchar** argv, gchar** envp, GSpawnFlags flags, GSpawnChildSetupFunc child_setup, gpointer user_data, GPid* child_pid, GError** error);																																																						/* da_g_spawn_async g_spawn_async; */
alias da_g_spawn_async_with_pipes = gboolean function(const(gchar)* working_directory, gchar** argv, gchar** envp, GSpawnFlags flags, GSpawnChildSetupFunc child_setup, gpointer user_data, GPid* child_pid, gint* standard_input, gint* standard_output, gint* standard_error, GError** error);																																																						/* da_g_spawn_async_with_pipes g_spawn_async_with_pipes; */
alias da_g_spawn_sync = gboolean function(const(gchar)* working_directory, gchar** argv, gchar** envp, GSpawnFlags flags, GSpawnChildSetupFunc child_setup, gpointer user_data, gchar** standard_output, gchar** standard_error, gint* exit_status, GError** error);																																																						/* da_g_spawn_sync g_spawn_sync; */
alias da_g_spawn_command_line_sync = gboolean function(const(gchar)* command_line, gchar** standard_output, gchar** standard_error, gint* exit_status, GError** error);																																																						/* da_g_spawn_command_line_sync g_spawn_command_line_sync; */
alias da_g_spawn_command_line_async = gboolean function(const(gchar)* command_line, GError** error);																																																						/* da_g_spawn_command_line_async g_spawn_command_line_async; */
alias da_g_spawn_close_pid = void function(GPid pid);																																																						/* da_g_spawn_close_pid g_spawn_close_pid; */
