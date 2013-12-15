module derelict.glib.gmarkup;

import core.stdc.config;

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


GQuark g_markup_error_quark ();
GMarkupParseContext* g_markup_parse_context_new (const(GMarkupParser)* parser, GMarkupParseFlags flags, gpointer user_data, GDestroyNotify user_data_dnotify);
void g_markup_parse_context_free (GMarkupParseContext* context);
gboolean g_markup_parse_context_parse (GMarkupParseContext* context, const(gchar)* text, gssize text_len, GError** error);
void g_markup_parse_context_push (GMarkupParseContext* context, const(GMarkupParser)* parser, gpointer user_data);
gpointer g_markup_parse_context_pop (GMarkupParseContext* context);
gboolean g_markup_parse_context_end_parse (GMarkupParseContext* context, GError** error);
const(gchar)* g_markup_parse_context_get_element (GMarkupParseContext* context);
const(GSList)* g_markup_parse_context_get_element_stack (GMarkupParseContext* context);
void g_markup_parse_context_get_position (GMarkupParseContext* context, gint* line_number, gint* char_number);
gpointer g_markup_parse_context_get_user_data (GMarkupParseContext* context);
gchar* g_markup_escape_text (const(gchar)* text, gssize length);
gchar* g_markup_printf_escaped (const(char)* format, ...);
gchar* g_markup_vprintf_escaped (const(char)* format, __va_list_tag* args);
gboolean g_markup_collect_attributes (const(gchar)* element_name, const(gchar*)* attribute_names, const(gchar*)* attribute_values, GError** error, GMarkupCollectType first_type, const(gchar)* first_attr, ...);