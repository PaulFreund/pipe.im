module derelict.glib.gstring;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gunicode;
import std.c.stdarg;

import core.stdc.string;
import core.stdc.config;

extern (C):

alias _GString GString;

struct _GString
{
	gchar* str;
	gsize len;
	gsize allocated_len;
}

alias da_g_string_new = GString* function(const(gchar)* init);																																																						/* da_g_string_new g_string_new; */
alias da_g_string_new_len = GString* function(const(gchar)* init, gssize len);																																																						/* da_g_string_new_len g_string_new_len; */
alias da_g_string_sized_new = GString* function(gsize dfl_size);																																																						/* da_g_string_sized_new g_string_sized_new; */
alias da_g_string_free = gchar* function(GString* string, gboolean free_segment);																																																						/* da_g_string_free g_string_free; */
alias da_g_string_equal = gboolean function(const(GString)* v, const(GString)* v2);																																																						/* da_g_string_equal g_string_equal; */
alias da_g_string_hash = guint function(const(GString)* str);																																																						/* da_g_string_hash g_string_hash; */
alias da_g_string_assign = GString* function(GString* string, const(gchar)* rval);																																																						/* da_g_string_assign g_string_assign; */
alias da_g_string_truncate = GString* function(GString* string, gsize len);																																																						/* da_g_string_truncate g_string_truncate; */
alias da_g_string_set_size = GString* function(GString* string, gsize len);																																																						/* da_g_string_set_size g_string_set_size; */
alias da_g_string_insert_len = GString* function(GString* string, gssize pos, const(gchar)* val, gssize len);																																																						/* da_g_string_insert_len g_string_insert_len; */
alias da_g_string_append = GString* function(GString* string, const(gchar)* val);																																																						/* da_g_string_append g_string_append; */
alias da_g_string_append_len = GString* function(GString* string, const(gchar)* val, gssize len);																																																						/* da_g_string_append_len g_string_append_len; */
alias da_g_string_append_c = GString* function(GString* string, gchar c);																																																						/* da_g_string_append_c g_string_append_c; */
alias da_g_string_append_unichar = GString* function(GString* string, gunichar wc);																																																						/* da_g_string_append_unichar g_string_append_unichar; */
alias da_g_string_prepend = GString* function(GString* string, const(gchar)* val);																																																						/* da_g_string_prepend g_string_prepend; */
alias da_g_string_prepend_c = GString* function(GString* string, gchar c);																																																						/* da_g_string_prepend_c g_string_prepend_c; */
alias da_g_string_prepend_unichar = GString* function(GString* string, gunichar wc);																																																						/* da_g_string_prepend_unichar g_string_prepend_unichar; */
alias da_g_string_prepend_len = GString* function(GString* string, const(gchar)* val, gssize len);																																																						/* da_g_string_prepend_len g_string_prepend_len; */
alias da_g_string_insert = GString* function(GString* string, gssize pos, const(gchar)* val);																																																						/* da_g_string_insert g_string_insert; */
alias da_g_string_insert_c = GString* function(GString* string, gssize pos, gchar c);																																																						/* da_g_string_insert_c g_string_insert_c; */
alias da_g_string_insert_unichar = GString* function(GString* string, gssize pos, gunichar wc);																																																						/* da_g_string_insert_unichar g_string_insert_unichar; */
alias da_g_string_overwrite = GString* function(GString* string, gsize pos, const(gchar)* val);																																																						/* da_g_string_overwrite g_string_overwrite; */
alias da_g_string_overwrite_len = GString* function(GString* string, gsize pos, const(gchar)* val, gssize len);																																																						/* da_g_string_overwrite_len g_string_overwrite_len; */
alias da_g_string_erase = GString* function(GString* string, gssize pos, gssize len);																																																						/* da_g_string_erase g_string_erase; */
alias da_g_string_ascii_down = GString* function(GString* string);																																																						/* da_g_string_ascii_down g_string_ascii_down; */
alias da_g_string_ascii_up = GString* function(GString* string);																																																						/* da_g_string_ascii_up g_string_ascii_up; */
alias da_g_string_vprintf = void function(GString* string, const(gchar)* format, va_list args);																																																						/* da_g_string_vprintf g_string_vprintf; */
alias da_g_string_printf = void function(GString* string, const(gchar)* format, ...);																																																						/* da_g_string_printf g_string_printf; */
alias da_g_string_append_vprintf = void function(GString* string, const(gchar)* format, va_list args);																																																						/* da_g_string_append_vprintf g_string_append_vprintf; */
alias da_g_string_append_printf = void function(GString* string, const(gchar)* format, ...);																																																						/* da_g_string_append_printf g_string_append_printf; */
alias da_g_string_append_uri_escaped = GString* function(GString* string, const(gchar)* unescaped, const(gchar)* reserved_chars_allowed, gboolean allow_utf8);																																																						/* da_g_string_append_uri_escaped g_string_append_uri_escaped; */
alias da_g_string_append_c_inline = GString* function(GString* gstring, gchar c);																																																						/* da_g_string_append_c_inline g_string_append_c_inline; */
alias da_g_string_down = GString* function(GString* string);																																																						/* da_g_string_down g_string_down; */
alias da_g_string_up = GString* function(GString* string);																																																						/* da_g_string_up g_string_up; */
