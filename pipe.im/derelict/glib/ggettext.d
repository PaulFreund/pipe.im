module derelict.glib.ggettext;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias da_g_strip_context = const(gchar)* function(const(gchar)* msgid, const(gchar)* msgval);																																																						/* da_g_strip_context g_strip_context; */
alias da_g_dgettext = const(gchar)* function(const(gchar)* domain, const(gchar)* msgid);																																																						/* da_g_dgettext g_dgettext; */
alias da_g_dcgettext = const(gchar)* function(const(gchar)* domain, const(gchar)* msgid, gint category);																																																						/* da_g_dcgettext g_dcgettext; */
alias da_g_dngettext = const(gchar)* function(const(gchar)* domain, const(gchar)* msgid, const(gchar)* msgid_plural, gulong n);																																																						/* da_g_dngettext g_dngettext; */
alias da_g_dpgettext = const(gchar)* function(const(gchar)* domain, const(gchar)* msgctxtid, gsize msgidoffset);																																																						/* da_g_dpgettext g_dpgettext; */
alias da_g_dpgettext2 = const(gchar)* function(const(gchar)* domain, const(gchar)* context, const(gchar)* msgid);																																																						/* da_g_dpgettext2 g_dpgettext2; */
