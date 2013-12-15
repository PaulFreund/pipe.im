module derelict.glib.gshell;

extern (C):

alias _Anonymous_0 GShellError;

enum _Anonymous_0
{
	G_SHELL_ERROR_BAD_QUOTING = 0,
	G_SHELL_ERROR_EMPTY_STRING = 1,
	G_SHELL_ERROR_FAILED = 2
}

GQuark g_shell_error_quark ();
gchar* g_shell_quote (const(gchar)* unquoted_string);
gchar* g_shell_unquote (const(gchar)* quoted_string, GError** error);
gboolean g_shell_parse_argv (const(gchar)* command_line, gint* argcp, gchar*** argvp, GError** error);