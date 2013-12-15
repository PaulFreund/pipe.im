import core.stdc.config;

extern (C):

alias _Anonymous_0 GLogLevelFlags;
alias void function (const(char)*, _Anonymous_0, const(char)*, void*) GLogFunc;
alias void function (const(char)*) GPrintFunc;

enum _Anonymous_0
{
	G_LOG_FLAG_RECURSION = 1,
	G_LOG_FLAG_FATAL = 2,
	G_LOG_LEVEL_ERROR = 4,
	G_LOG_LEVEL_CRITICAL = 8,
	G_LOG_LEVEL_WARNING = 16,
	G_LOG_LEVEL_MESSAGE = 32,
	G_LOG_LEVEL_INFO = 64,
	G_LOG_LEVEL_DEBUG = 128,
	G_LOG_LEVEL_MASK = -4
}

gsize g_printf_string_upper_bound (const(gchar)* format, __va_list_tag* args);
guint g_log_set_handler (const(gchar)* log_domain, GLogLevelFlags log_levels, GLogFunc log_func, gpointer user_data);
void g_log_remove_handler (const(gchar)* log_domain, guint handler_id);
void g_log_default_handler (const(gchar)* log_domain, GLogLevelFlags log_level, const(gchar)* message, gpointer unused_data);
GLogFunc g_log_set_default_handler (GLogFunc log_func, gpointer user_data);
void g_log (const(gchar)* log_domain, GLogLevelFlags log_level, const(gchar)* format, ...);
void g_logv (const(gchar)* log_domain, GLogLevelFlags log_level, const(gchar)* format, __va_list_tag* args);
GLogLevelFlags g_log_set_fatal_mask (const(gchar)* log_domain, GLogLevelFlags fatal_mask);
GLogLevelFlags g_log_set_always_fatal (GLogLevelFlags fatal_mask);
void _g_log_fallback_handler (const(gchar)* log_domain, GLogLevelFlags log_level, const(gchar)* message, gpointer unused_data);
void g_return_if_fail_warning (const(char)* log_domain, const(char)* pretty_function, const(char)* expression);
void g_warn_message (const(char)* domain, const(char)* file, int line, const(char)* func, const(char)* warnexpr);
void g_assert_warning (const(char)* log_domain, const(char)* file, const int line, const(char)* pretty_function, const(char)* expression);
void g_print (const(gchar)* format, ...);
GPrintFunc g_set_print_handler (GPrintFunc func);
void g_printerr (const(gchar)* format, ...);
GPrintFunc g_set_printerr_handler (GPrintFunc func);