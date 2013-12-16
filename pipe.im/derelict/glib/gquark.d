module derelict.glib.gquark;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias uint GQuark;

alias da_g_quark_try_string = GQuark function(const(gchar)* string);																																																						/* da_g_quark_try_string g_quark_try_string; */
alias da_g_quark_from_static_string = GQuark function(const(gchar)* string);																																																						/* da_g_quark_from_static_string g_quark_from_static_string; */
alias da_g_quark_from_string = GQuark function(const(gchar)* string);																																																						/* da_g_quark_from_string g_quark_from_string; */
alias da_g_quark_to_string = const(gchar)* function(GQuark quark);																																																						/* da_g_quark_to_string g_quark_to_string; */
alias da_g_intern_string = const(gchar)* function(const(gchar)* string);																																																						/* da_g_intern_string g_intern_string; */
alias da_g_intern_static_string = const(gchar)* function(const(gchar)* string);																																																						/* da_g_intern_static_string g_intern_static_string; */
