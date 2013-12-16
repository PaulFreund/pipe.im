module derelict.glib.genviron;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias da_g_getenv = const(gchar)* function(const(gchar)* variable);																																																						/* da_g_getenv g_getenv; */
alias da_g_setenv = gboolean function(const(gchar)* variable, const(gchar)* value, gboolean overwrite);																																																						/* da_g_setenv g_setenv; */
alias da_g_unsetenv = void function(const(gchar)* variable);																																																						/* da_g_unsetenv g_unsetenv; */
alias da_g_listenv = gchar** function();																																																						/* da_g_listenv g_listenv; */
alias da_g_get_environ = gchar** function();																																																						/* da_g_get_environ g_get_environ; */
alias da_g_environ_getenv = const(gchar)* function(gchar** envp, const(gchar)* variable);																																																						/* da_g_environ_getenv g_environ_getenv; */
alias da_g_environ_setenv = gchar** function(gchar** envp, const(gchar)* variable, const(gchar)* value, gboolean overwrite);																																																						/* da_g_environ_setenv g_environ_setenv; */
alias da_g_environ_unsetenv = gchar** function(gchar** envp, const(gchar)* variable);																																																						/* da_g_environ_unsetenv g_environ_unsetenv; */
