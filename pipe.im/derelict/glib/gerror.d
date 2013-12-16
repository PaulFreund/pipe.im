module derelict.glib.gerror;

import derelict.glib.gquark;
import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import std.c.stdarg;

extern (C):

alias _GError GError;

struct _GError
{
	GQuark domain;
	gint code;
	gchar* message;
}

alias da_g_error_new = GError* function(GQuark domain, gint code, const(gchar)* format, ...);																																																						/* da_g_error_new g_error_new; */
alias da_g_error_new_literal = GError* function(GQuark domain, gint code, const(gchar)* message);																																																						/* da_g_error_new_literal g_error_new_literal; */
alias da_g_error_new_valist = GError* function(GQuark domain, gint code, const(gchar)* format, va_list args);																																																						/* da_g_error_new_valist g_error_new_valist; */
alias da_g_error_free = void function(GError* error);																																																						/* da_g_error_free g_error_free; */
alias da_g_error_copy = GError* function(const(GError)* error);																																																						/* da_g_error_copy g_error_copy; */
alias da_g_error_matches = gboolean function(const(GError)* error, GQuark domain, gint code);																																																						/* da_g_error_matches g_error_matches; */
alias da_g_set_error = void function(GError** err, GQuark domain, gint code, const(gchar)* format, ...);																																																						/* da_g_set_error g_set_error; */
alias da_g_set_error_literal = void function(GError** err, GQuark domain, gint code, const(gchar)* message);																																																						/* da_g_set_error_literal g_set_error_literal; */
alias da_g_propagate_error = void function(GError** dest, GError* src);																																																						/* da_g_propagate_error g_propagate_error; */
alias da_g_clear_error = void function(GError** err);																																																						/* da_g_clear_error g_clear_error; */
alias da_g_prefix_error = void function(GError** err, const(gchar)* format, ...);																																																						/* da_g_prefix_error g_prefix_error; */
alias da_g_propagate_prefixed_error = void function(GError** dest, GError* src, const(gchar)* format, ...);																																																						/* da_g_propagate_prefixed_error g_propagate_prefixed_error; */
