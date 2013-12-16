module derelict.glib.gshell;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gquark;
import derelict.glib.gerror;

extern (C):

alias _Anonymous_0 GShellError;

enum _Anonymous_0
{
	G_SHELL_ERROR_BAD_QUOTING = 0,
	G_SHELL_ERROR_EMPTY_STRING = 1,
	G_SHELL_ERROR_FAILED = 2
}

alias da_g_shell_error_quark = GQuark function();																																																						/* da_g_shell_error_quark g_shell_error_quark; */
alias da_g_shell_quote = gchar* function(const(gchar)* unquoted_string);																																																						/* da_g_shell_quote g_shell_quote; */
alias da_g_shell_unquote = gchar* function(const(gchar)* quoted_string, GError** error);																																																						/* da_g_shell_unquote g_shell_unquote; */
alias da_g_shell_parse_argv = gboolean function(const(gchar)* command_line, gint* argcp, gchar*** argvp, GError** error);																																																						/* da_g_shell_parse_argv g_shell_parse_argv; */
