module derelict.glib.gmarkup;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gerror;
import derelict.glib.gquark;
import derelict.glib.gslist;
import core.stdc.config;
import std.c.stdarg;

extern (C):

alias _Anonymous_0 GMarkupError;
alias _Anonymous_1 GMarkupParseFlags;
alias _GMarkupParseContext GMarkupParseContext;
alias _GMarkupParser GMarkupParser;
alias _Anonymous_2 GMarkupCollectType;

enum _Anonymous_0
{
	G_MARKUP_ERROR_BAD_UTF8 = 0,
	G_MARKUP_ERROR_EMPTY = 1,
	G_MARKUP_ERROR_PARSE = 2,
	G_MARKUP_ERROR_UNKNOWN_ELEMENT = 3,
	G_MARKUP_ERROR_UNKNOWN_ATTRIBUTE = 4,
	G_MARKUP_ERROR_INVALID_CONTENT = 5,
	G_MARKUP_ERROR_MISSING_ATTRIBUTE = 6
}

enum _Anonymous_1
{
	G_MARKUP_DO_NOT_USE_THIS_UNSUPPORTED_FLAG = 1,
	G_MARKUP_TREAT_CDATA_AS_TEXT = 2,
	G_MARKUP_PREFIX_ERROR_POSITION = 4
}

enum _Anonymous_2
{
	G_MARKUP_COLLECT_INVALID = 0,
	G_MARKUP_COLLECT_STRING = 1,
	G_MARKUP_COLLECT_STRDUP = 2,
	G_MARKUP_COLLECT_BOOLEAN = 3,
	G_MARKUP_COLLECT_TRISTATE = 4,
	G_MARKUP_COLLECT_OPTIONAL = 65536
}

struct _GMarkupParser
{
	void function (GMarkupParseContext*, const(gchar)*, const(gchar*)*, const(gchar*)*, gpointer, GError**) start_element;
	void function (GMarkupParseContext*, const(gchar)*, gpointer, GError**) end_element;
	void function (GMarkupParseContext*, const(gchar)*, gsize, gpointer, GError**) text;
	void function (GMarkupParseContext*, const(gchar)*, gsize, gpointer, GError**) passthrough;
	void function (GMarkupParseContext*, GError*, gpointer) error;
}

struct _GMarkupParseContext;


alias da_g_markup_error_quark = GQuark function();																																																						/* da_g_markup_error_quark g_markup_error_quark; */
alias da_g_markup_parse_context_new = GMarkupParseContext* function(const(GMarkupParser)* parser, GMarkupParseFlags flags, gpointer user_data, GDestroyNotify user_data_dnotify);																																																						/* da_g_markup_parse_context_new g_markup_parse_context_new; */
alias da_g_markup_parse_context_free = void function(GMarkupParseContext* context);																																																						/* da_g_markup_parse_context_free g_markup_parse_context_free; */
alias da_g_markup_parse_context_parse = gboolean function(GMarkupParseContext* context, const(gchar)* text, gssize text_len, GError** error);																																																						/* da_g_markup_parse_context_parse g_markup_parse_context_parse; */
alias da_g_markup_parse_context_push = void function(GMarkupParseContext* context, const(GMarkupParser)* parser, gpointer user_data);																																																						/* da_g_markup_parse_context_push g_markup_parse_context_push; */
alias da_g_markup_parse_context_pop = gpointer function(GMarkupParseContext* context);																																																						/* da_g_markup_parse_context_pop g_markup_parse_context_pop; */
alias da_g_markup_parse_context_end_parse = gboolean function(GMarkupParseContext* context, GError** error);																																																						/* da_g_markup_parse_context_end_parse g_markup_parse_context_end_parse; */
alias da_g_markup_parse_context_get_element = const(gchar)* function(GMarkupParseContext* context);																																																						/* da_g_markup_parse_context_get_element g_markup_parse_context_get_element; */
alias da_g_markup_parse_context_get_element_stack = const(GSList)* function(GMarkupParseContext* context);																																																						/* da_g_markup_parse_context_get_element_stack g_markup_parse_context_get_element_stack; */
alias da_g_markup_parse_context_get_position = void function(GMarkupParseContext* context, gint* line_number, gint* char_number);																																																						/* da_g_markup_parse_context_get_position g_markup_parse_context_get_position; */
alias da_g_markup_parse_context_get_user_data = gpointer function(GMarkupParseContext* context);																																																						/* da_g_markup_parse_context_get_user_data g_markup_parse_context_get_user_data; */
alias da_g_markup_escape_text = gchar* function(const(gchar)* text, gssize length);																																																						/* da_g_markup_escape_text g_markup_escape_text; */
alias da_g_markup_printf_escaped = gchar* function(const(char)* format, ...);																																																						/* da_g_markup_printf_escaped g_markup_printf_escaped; */
alias da_g_markup_vprintf_escaped = gchar* function(const(char)* format, va_list args);																																																						/* da_g_markup_vprintf_escaped g_markup_vprintf_escaped; */
alias da_g_markup_collect_attributes = gboolean function(const(gchar)* element_name, const(gchar*)* attribute_names, const(gchar*)* attribute_values, GError** error, GMarkupCollectType first_type, const(gchar)* first_attr, ...);																																																						/* da_g_markup_collect_attributes g_markup_collect_attributes; */
