module derelict.glib.ghostutils;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias da_g_hostname_is_non_ascii = gboolean function(const(gchar)* hostname);																																																						/* da_g_hostname_is_non_ascii g_hostname_is_non_ascii; */
alias da_g_hostname_is_ascii_encoded = gboolean function(const(gchar)* hostname);																																																						/* da_g_hostname_is_ascii_encoded g_hostname_is_ascii_encoded; */
alias da_g_hostname_is_ip_address = gboolean function(const(gchar)* hostname);																																																						/* da_g_hostname_is_ip_address g_hostname_is_ip_address; */
alias da_g_hostname_to_ascii = gchar* function(const(gchar)* hostname);																																																						/* da_g_hostname_to_ascii g_hostname_to_ascii; */
alias da_g_hostname_to_unicode = gchar* function(const(gchar)* hostname);																																																						/* da_g_hostname_to_unicode g_hostname_to_unicode; */
