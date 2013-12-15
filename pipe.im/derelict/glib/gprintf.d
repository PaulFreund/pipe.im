module derelict.glib.gprintf;

import core.stdc.stdio;

extern (C):

gint g_printf (const(gchar)* format, ...);
gint g_fprintf (FILE* file, const(gchar)* format, ...);
gint g_sprintf (gchar* string, const(gchar)* format, ...);
gint g_vprintf (const(gchar)* format, __va_list_tag* args);
gint g_vfprintf (FILE* file, const(gchar)* format, __va_list_tag* args);
gint g_vsprintf (gchar* string, const(gchar)* format, __va_list_tag* args);
gint g_vasprintf (gchar** string, const(gchar)* format, __va_list_tag* args);