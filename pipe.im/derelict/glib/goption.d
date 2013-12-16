module derelict.glib.goption;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gerror;
import derelict.glib.gquark;

extern (C):

alias _GOptionContext GOptionContext;
alias _GOptionGroup GOptionGroup;
alias _GOptionEntry GOptionEntry;
alias _Anonymous_0 GOptionFlags;
alias _Anonymous_1 GOptionArg;
alias int function (const(char)*, const(char)*, void*, _GError**) GOptionArgFunc;
alias int function (_GOptionContext*, _GOptionGroup*, void*, _GError**) GOptionParseFunc;
alias void function (_GOptionContext*, _GOptionGroup*, void*, _GError**) GOptionErrorFunc;
alias _Anonymous_2 GOptionError;

enum _Anonymous_0
{
	G_OPTION_FLAG_HIDDEN = 1,
	G_OPTION_FLAG_IN_MAIN = 2,
	G_OPTION_FLAG_REVERSE = 4,
	G_OPTION_FLAG_NO_ARG = 8,
	G_OPTION_FLAG_FILENAME = 16,
	G_OPTION_FLAG_OPTIONAL_ARG = 32,
	G_OPTION_FLAG_NOALIAS = 64
}

enum _Anonymous_1
{
	G_OPTION_ARG_NONE = 0,
	G_OPTION_ARG_STRING = 1,
	G_OPTION_ARG_INT = 2,
	G_OPTION_ARG_CALLBACK = 3,
	G_OPTION_ARG_FILENAME = 4,
	G_OPTION_ARG_STRING_ARRAY = 5,
	G_OPTION_ARG_FILENAME_ARRAY = 6,
	G_OPTION_ARG_DOUBLE = 7,
	G_OPTION_ARG_INT64 = 8
}

enum _Anonymous_2
{
	G_OPTION_ERROR_UNKNOWN_OPTION = 0,
	G_OPTION_ERROR_BAD_VALUE = 1,
	G_OPTION_ERROR_FAILED = 2
}

struct _GOptionEntry
{
	const(gchar)* long_name;
	gchar short_name;
	gint flags;
	GOptionArg arg;
	gpointer arg_data;
	const(gchar)* description;
	const(gchar)* arg_description;
}

struct _GOptionContext;


struct _GOptionGroup;


alias da_g_option_error_quark = GQuark function();																																																						/* da_g_option_error_quark g_option_error_quark; */
alias da_g_option_context_new = GOptionContext* function(const(gchar)* parameter_string);																																																						/* da_g_option_context_new g_option_context_new; */
alias da_g_option_context_set_summary = void function(GOptionContext* context, const(gchar)* summary);																																																						/* da_g_option_context_set_summary g_option_context_set_summary; */
alias da_g_option_context_get_summary = const(gchar)* function(GOptionContext* context);																																																						/* da_g_option_context_get_summary g_option_context_get_summary; */
alias da_g_option_context_set_description = void function(GOptionContext* context, const(gchar)* description);																																																						/* da_g_option_context_set_description g_option_context_set_description; */
alias da_g_option_context_get_description = const(gchar)* function(GOptionContext* context);																																																						/* da_g_option_context_get_description g_option_context_get_description; */
alias da_g_option_context_free = void function(GOptionContext* context);																																																						/* da_g_option_context_free g_option_context_free; */
alias da_g_option_context_set_help_enabled = void function(GOptionContext* context, gboolean help_enabled);																																																						/* da_g_option_context_set_help_enabled g_option_context_set_help_enabled; */
alias da_g_option_context_get_help_enabled = gboolean function(GOptionContext* context);																																																						/* da_g_option_context_get_help_enabled g_option_context_get_help_enabled; */
alias da_g_option_context_set_ignore_unknown_options = void function(GOptionContext* context, gboolean ignore_unknown);																																																						/* da_g_option_context_set_ignore_unknown_options g_option_context_set_ignore_unknown_options; */
alias da_g_option_context_get_ignore_unknown_options = gboolean function(GOptionContext* context);																																																						/* da_g_option_context_get_ignore_unknown_options g_option_context_get_ignore_unknown_options; */
alias da_g_option_context_add_main_entries = void function(GOptionContext* context, const(GOptionEntry)* entries, const(gchar)* translation_domain);																																																						/* da_g_option_context_add_main_entries g_option_context_add_main_entries; */
alias da_g_option_context_parse = gboolean function(GOptionContext* context, gint* argc, gchar*** argv, GError** error);																																																						/* da_g_option_context_parse g_option_context_parse; */
alias da_g_option_context_set_translate_func = void function(GOptionContext* context, GTranslateFunc func, gpointer data, GDestroyNotify destroy_notify);																																																						/* da_g_option_context_set_translate_func g_option_context_set_translate_func; */
alias da_g_option_context_set_translation_domain = void function(GOptionContext* context, const(gchar)* domain);																																																						/* da_g_option_context_set_translation_domain g_option_context_set_translation_domain; */
alias da_g_option_context_add_group = void function(GOptionContext* context, GOptionGroup* group);																																																						/* da_g_option_context_add_group g_option_context_add_group; */
alias da_g_option_context_set_main_group = void function(GOptionContext* context, GOptionGroup* group);																																																						/* da_g_option_context_set_main_group g_option_context_set_main_group; */
alias da_g_option_context_get_main_group = GOptionGroup* function(GOptionContext* context);																																																						/* da_g_option_context_get_main_group g_option_context_get_main_group; */
alias da_g_option_context_get_help = gchar* function(GOptionContext* context, gboolean main_help, GOptionGroup* group);																																																						/* da_g_option_context_get_help g_option_context_get_help; */
alias da_g_option_group_new = GOptionGroup* function(const(gchar)* name, const(gchar)* description, const(gchar)* help_description, gpointer user_data, GDestroyNotify destroy);																																																						/* da_g_option_group_new g_option_group_new; */
alias da_g_option_group_set_parse_hooks = void function(GOptionGroup* group, GOptionParseFunc pre_parse_func, GOptionParseFunc post_parse_func);																																																						/* da_g_option_group_set_parse_hooks g_option_group_set_parse_hooks; */
alias da_g_option_group_set_error_hook = void function(GOptionGroup* group, GOptionErrorFunc error_func);																																																						/* da_g_option_group_set_error_hook g_option_group_set_error_hook; */
alias da_g_option_group_free = void function(GOptionGroup* group);																																																						/* da_g_option_group_free g_option_group_free; */
alias da_g_option_group_add_entries = void function(GOptionGroup* group, const(GOptionEntry)* entries);																																																						/* da_g_option_group_add_entries g_option_group_add_entries; */
alias da_g_option_group_set_translate_func = void function(GOptionGroup* group, GTranslateFunc func, gpointer data, GDestroyNotify destroy_notify);																																																						/* da_g_option_group_set_translate_func g_option_group_set_translate_func; */
alias da_g_option_group_set_translation_domain = void function(GOptionGroup* group, const(gchar)* domain);																																																						/* da_g_option_group_set_translation_domain g_option_group_set_translation_domain; */
