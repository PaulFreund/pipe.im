module derelict.glib.gstrfuncs;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;
import std.c.stdarg;

extern (C):

alias _Anonymous_0 GAsciiType;

extern __gshared const guint16* g_ascii_table;

enum _Anonymous_0
{
	G_ASCII_ALNUM = 1,
	G_ASCII_ALPHA = 2,
	G_ASCII_CNTRL = 4,
	G_ASCII_DIGIT = 8,
	G_ASCII_GRAPH = 16,
	G_ASCII_LOWER = 32,
	G_ASCII_PRINT = 64,
	G_ASCII_PUNCT = 128,
	G_ASCII_SPACE = 256,
	G_ASCII_UPPER = 512,
	G_ASCII_XDIGIT = 1024
}

alias da_g_ascii_tolower = gchar function(gchar c);																																																						/* da_g_ascii_tolower g_ascii_tolower; */
alias da_g_ascii_toupper = gchar function(gchar c);																																																						/* da_g_ascii_toupper g_ascii_toupper; */
alias da_g_ascii_digit_value = gint function(gchar c);																																																						/* da_g_ascii_digit_value g_ascii_digit_value; */
alias da_g_ascii_xdigit_value = gint function(gchar c);																																																						/* da_g_ascii_xdigit_value g_ascii_xdigit_value; */
alias da_g_strdelimit = gchar* function(gchar* string, const(gchar)* delimiters, gchar new_delimiter);																																																						/* da_g_strdelimit g_strdelimit; */
alias da_g_strcanon = gchar* function(gchar* string, const(gchar)* valid_chars, gchar substitutor);																																																						/* da_g_strcanon g_strcanon; */
alias da_g_strerror = const(gchar)* function(gint errnum);																																																						/* da_g_strerror g_strerror; */
alias da_g_strsignal = const(gchar)* function(gint signum);																																																						/* da_g_strsignal g_strsignal; */
alias da_g_strreverse = gchar* function(gchar* string);																																																						/* da_g_strreverse g_strreverse; */
alias da_g_strlcpy = gsize function(gchar* dest, const(gchar)* src, gsize dest_size);																																																						/* da_g_strlcpy g_strlcpy; */
alias da_g_strlcat = gsize function(gchar* dest, const(gchar)* src, gsize dest_size);																																																						/* da_g_strlcat g_strlcat; */
alias da_g_strstr_len = gchar* function(const(gchar)* haystack, gssize haystack_len, const(gchar)* needle);																																																						/* da_g_strstr_len g_strstr_len; */
alias da_g_strrstr = gchar* function(const(gchar)* haystack, const(gchar)* needle);																																																						/* da_g_strrstr g_strrstr; */
alias da_g_strrstr_len = gchar* function(const(gchar)* haystack, gssize haystack_len, const(gchar)* needle);																																																						/* da_g_strrstr_len g_strrstr_len; */
alias da_g_str_has_suffix = gboolean function(const(gchar)* str, const(gchar)* suffix);																																																						/* da_g_str_has_suffix g_str_has_suffix; */
alias da_g_str_has_prefix = gboolean function(const(gchar)* str, const(gchar)* prefix);																																																						/* da_g_str_has_prefix g_str_has_prefix; */
alias da_g_strtod = gdouble function(const(gchar)* nptr, gchar** endptr);																																																						/* da_g_strtod g_strtod; */
alias da_g_ascii_strtod = gdouble function(const(gchar)* nptr, gchar** endptr);																																																						/* da_g_ascii_strtod g_ascii_strtod; */
alias da_g_ascii_strtoull = guint64 function(const(gchar)* nptr, gchar** endptr, guint base);																																																						/* da_g_ascii_strtoull g_ascii_strtoull; */
alias da_g_ascii_strtoll = gint64 function(const(gchar)* nptr, gchar** endptr, guint base);																																																						/* da_g_ascii_strtoll g_ascii_strtoll; */
alias da_g_ascii_dtostr = gchar* function(gchar* buffer, gint buf_len, gdouble d);																																																						/* da_g_ascii_dtostr g_ascii_dtostr; */
alias da_g_ascii_formatd = gchar* function(gchar* buffer, gint buf_len, const(gchar)* format, gdouble d);																																																						/* da_g_ascii_formatd g_ascii_formatd; */
alias da_g_strchug = gchar* function(gchar* string);																																																						/* da_g_strchug g_strchug; */
alias da_g_strchomp = gchar* function(gchar* string);																																																						/* da_g_strchomp g_strchomp; */
alias da_g_ascii_strcasecmp = gint function(const(gchar)* s1, const(gchar)* s2);																																																						/* da_g_ascii_strcasecmp g_ascii_strcasecmp; */
alias da_g_ascii_strncasecmp = gint function(const(gchar)* s1, const(gchar)* s2, gsize n);																																																						/* da_g_ascii_strncasecmp g_ascii_strncasecmp; */
alias da_g_ascii_strdown = gchar* function(const(gchar)* str, gssize len);																																																						/* da_g_ascii_strdown g_ascii_strdown; */
alias da_g_ascii_strup = gchar* function(const(gchar)* str, gssize len);																																																						/* da_g_ascii_strup g_ascii_strup; */
alias da_g_strcasecmp = gint function(const(gchar)* s1, const(gchar)* s2);																																																						/* da_g_strcasecmp g_strcasecmp; */
alias da_g_strncasecmp = gint function(const(gchar)* s1, const(gchar)* s2, guint n);																																																						/* da_g_strncasecmp g_strncasecmp; */
alias da_g_strdown = gchar* function(gchar* string);																																																						/* da_g_strdown g_strdown; */
alias da_g_strup = gchar* function(gchar* string);																																																						/* da_g_strup g_strup; */
alias da_g_strdup = gchar* function(const(gchar)* str);																																																						/* da_g_strdup g_strdup; */
alias da_g_strdup_printf = gchar* function(const(gchar)* format, ...);																																																						/* da_g_strdup_printf g_strdup_printf; */
alias da_g_strdup_vprintf = gchar* function(const(gchar)* format, va_list args);																																																						/* da_g_strdup_vprintf g_strdup_vprintf; */
alias da_g_strndup = gchar* function(const(gchar)* str, gsize n);																																																						/* da_g_strndup g_strndup; */
alias da_g_strnfill = gchar* function(gsize length, gchar fill_char);																																																						/* da_g_strnfill g_strnfill; */
alias da_g_strconcat = gchar* function(const(gchar)* string1, ...);																																																						/* da_g_strconcat g_strconcat; */
alias da_g_strjoin = gchar* function(const(gchar)* separator, ...);																																																						/* da_g_strjoin g_strjoin; */
alias da_g_strcompress = gchar* function(const(gchar)* source);																																																						/* da_g_strcompress g_strcompress; */
alias da_g_strescape = gchar* function(const(gchar)* source, const(gchar)* exceptions);																																																						/* da_g_strescape g_strescape; */
alias da_g_memdup = gpointer function(gconstpointer mem, guint byte_size);																																																						/* da_g_memdup g_memdup; */
alias da_g_strsplit = gchar** function(const(gchar)* string, const(gchar)* delimiter, gint max_tokens);																																																						/* da_g_strsplit g_strsplit; */
alias da_g_strsplit_set = gchar** function(const(gchar)* string, const(gchar)* delimiters, gint max_tokens);																																																						/* da_g_strsplit_set g_strsplit_set; */
alias da_g_strjoinv = gchar* function(const(gchar)* separator, gchar** str_array);																																																						/* da_g_strjoinv g_strjoinv; */
alias da_g_strfreev = void function(gchar** str_array);																																																						/* da_g_strfreev g_strfreev; */
alias da_g_strdupv = gchar** function(gchar** str_array);																																																						/* da_g_strdupv g_strdupv; */
alias da_g_strv_length = guint function(gchar** str_array);																																																						/* da_g_strv_length g_strv_length; */
alias da_g_stpcpy = gchar* function(gchar* dest, const(char)* src);																																																						/* da_g_stpcpy g_stpcpy; */
