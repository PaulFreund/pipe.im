module derelict.glib.gprintf;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.stdio;
import std.c.stdarg;

extern (C):

alias da_g_printf = gint function(const(gchar)* format, ...);																																																						/* da_g_printf g_printf; */
alias da_g_fprintf = gint function(FILE* file, const(gchar)* format, ...);																																																						/* da_g_fprintf g_fprintf; */
alias da_g_sprintf = gint function(gchar* string, const(gchar)* format, ...);																																																						/* da_g_sprintf g_sprintf; */
alias da_g_vprintf = gint function(const(gchar)* format, va_list args);																																																						/* da_g_vprintf g_vprintf; */
alias da_g_vfprintf = gint function(FILE* file, const(gchar)* format, va_list args);																																																						/* da_g_vfprintf g_vfprintf; */
alias da_g_vsprintf = gint function(gchar* string, const(gchar)* format, va_list args);																																																						/* da_g_vsprintf g_vsprintf; */
alias da_g_vasprintf = gint function(gchar** string, const(gchar)* format, va_list args);																																																						/* da_g_vasprintf g_vasprintf; */
