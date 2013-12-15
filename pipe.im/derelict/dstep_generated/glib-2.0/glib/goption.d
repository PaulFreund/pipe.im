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


GQuark g_option_error_quark ();
GOptionContext* g_option_context_new (const(gchar)* parameter_string);
void g_option_context_set_summary (GOptionContext* context, const(gchar)* summary);
const(gchar)* g_option_context_get_summary (GOptionContext* context);
void g_option_context_set_description (GOptionContext* context, const(gchar)* description);
const(gchar)* g_option_context_get_description (GOptionContext* context);
void g_option_context_free (GOptionContext* context);
void g_option_context_set_help_enabled (GOptionContext* context, gboolean help_enabled);
gboolean g_option_context_get_help_enabled (GOptionContext* context);
void g_option_context_set_ignore_unknown_options (GOptionContext* context, gboolean ignore_unknown);
gboolean g_option_context_get_ignore_unknown_options (GOptionContext* context);
void g_option_context_add_main_entries (GOptionContext* context, const(GOptionEntry)* entries, const(gchar)* translation_domain);
gboolean g_option_context_parse (GOptionContext* context, gint* argc, gchar*** argv, GError** error);
void g_option_context_set_translate_func (GOptionContext* context, GTranslateFunc func, gpointer data, GDestroyNotify destroy_notify);
void g_option_context_set_translation_domain (GOptionContext* context, const(gchar)* domain);
void g_option_context_add_group (GOptionContext* context, GOptionGroup* group);
void g_option_context_set_main_group (GOptionContext* context, GOptionGroup* group);
GOptionGroup* g_option_context_get_main_group (GOptionContext* context);
gchar* g_option_context_get_help (GOptionContext* context, gboolean main_help, GOptionGroup* group);
GOptionGroup* g_option_group_new (const(gchar)* name, const(gchar)* description, const(gchar)* help_description, gpointer user_data, GDestroyNotify destroy);
void g_option_group_set_parse_hooks (GOptionGroup* group, GOptionParseFunc pre_parse_func, GOptionParseFunc post_parse_func);
void g_option_group_set_error_hook (GOptionGroup* group, GOptionErrorFunc error_func);
void g_option_group_free (GOptionGroup* group);
void g_option_group_add_entries (GOptionGroup* group, const(GOptionEntry)* entries);
void g_option_group_set_translate_func (GOptionGroup* group, GTranslateFunc func, gpointer data, GDestroyNotify destroy_notify);
void g_option_group_set_translation_domain (GOptionGroup* group, const(gchar)* domain);