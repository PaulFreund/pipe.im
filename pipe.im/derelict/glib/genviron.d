module derelict.glib.genviron;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

const(gchar)* g_getenv (const(gchar)* variable);
gboolean g_setenv (const(gchar)* variable, const(gchar)* value, gboolean overwrite);
void g_unsetenv (const(gchar)* variable);
gchar** g_listenv ();
gchar** g_get_environ ();
const(gchar)* g_environ_getenv (gchar** envp, const(gchar)* variable);
gchar** g_environ_setenv (gchar** envp, const(gchar)* variable, const(gchar)* value, gboolean overwrite);
gchar** g_environ_unsetenv (gchar** envp, const(gchar)* variable);