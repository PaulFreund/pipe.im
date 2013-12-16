module derelict.glib.gbacktrace;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

void g_on_error_query (const(gchar)* prg_name);
void g_on_error_stack_trace (const(gchar)* prg_name);