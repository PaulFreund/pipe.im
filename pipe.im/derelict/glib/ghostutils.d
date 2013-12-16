module derelict.glib.ghostutils;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

gboolean g_hostname_is_non_ascii (const(gchar)* hostname);
gboolean g_hostname_is_ascii_encoded (const(gchar)* hostname);
gboolean g_hostname_is_ip_address (const(gchar)* hostname);
gchar* g_hostname_to_ascii (const(gchar)* hostname);
gchar* g_hostname_to_unicode (const(gchar)* hostname);