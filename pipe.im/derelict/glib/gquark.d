module derelict.glib.gquark;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias uint GQuark;

GQuark g_quark_try_string (const(gchar)* string);
GQuark g_quark_from_static_string (const(gchar)* string);
GQuark g_quark_from_string (const(gchar)* string);
const(gchar)* g_quark_to_string (GQuark quark);
const(gchar)* g_intern_string (const(gchar)* string);
const(gchar)* g_intern_static_string (const(gchar)* string);