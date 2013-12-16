module derelict.glib.gprintf;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.stdio;
import std.c.stdarg;

extern (C):

gint g_printf (const(gchar)* format, ...);
gint g_fprintf (FILE* file, const(gchar)* format, ...);
gint g_sprintf (gchar* string, const(gchar)* format, ...);
gint g_vprintf (const(gchar)* format, va_list args);
gint g_vfprintf (FILE* file, const(gchar)* format, va_list args);
gint g_vsprintf (gchar* string, const(gchar)* format, va_list args);
gint g_vasprintf (gchar** string, const(gchar)* format, va_list args);