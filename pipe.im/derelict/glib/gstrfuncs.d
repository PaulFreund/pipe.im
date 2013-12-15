module derelict.glib.gstrfuncs;

import core.stdc.config;

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

gchar g_ascii_tolower (gchar c);
gchar g_ascii_toupper (gchar c);
gint g_ascii_digit_value (gchar c);
gint g_ascii_xdigit_value (gchar c);
gchar* g_strdelimit (gchar* string, const(gchar)* delimiters, gchar new_delimiter);
gchar* g_strcanon (gchar* string, const(gchar)* valid_chars, gchar substitutor);
const(gchar)* g_strerror (gint errnum);
const(gchar)* g_strsignal (gint signum);
gchar* g_strreverse (gchar* string);
gsize g_strlcpy (gchar* dest, const(gchar)* src, gsize dest_size);
gsize g_strlcat (gchar* dest, const(gchar)* src, gsize dest_size);
gchar* g_strstr_len (const(gchar)* haystack, gssize haystack_len, const(gchar)* needle);
gchar* g_strrstr (const(gchar)* haystack, const(gchar)* needle);
gchar* g_strrstr_len (const(gchar)* haystack, gssize haystack_len, const(gchar)* needle);
gboolean g_str_has_suffix (const(gchar)* str, const(gchar)* suffix);
gboolean g_str_has_prefix (const(gchar)* str, const(gchar)* prefix);
gdouble g_strtod (const(gchar)* nptr, gchar** endptr);
gdouble g_ascii_strtod (const(gchar)* nptr, gchar** endptr);
guint64 g_ascii_strtoull (const(gchar)* nptr, gchar** endptr, guint base);
gint64 g_ascii_strtoll (const(gchar)* nptr, gchar** endptr, guint base);
gchar* g_ascii_dtostr (gchar* buffer, gint buf_len, gdouble d);
gchar* g_ascii_formatd (gchar* buffer, gint buf_len, const(gchar)* format, gdouble d);
gchar* g_strchug (gchar* string);
gchar* g_strchomp (gchar* string);
gint g_ascii_strcasecmp (const(gchar)* s1, const(gchar)* s2);
gint g_ascii_strncasecmp (const(gchar)* s1, const(gchar)* s2, gsize n);
gchar* g_ascii_strdown (const(gchar)* str, gssize len);
gchar* g_ascii_strup (const(gchar)* str, gssize len);
gint g_strcasecmp (const(gchar)* s1, const(gchar)* s2);
gint g_strncasecmp (const(gchar)* s1, const(gchar)* s2, guint n);
gchar* g_strdown (gchar* string);
gchar* g_strup (gchar* string);
gchar* g_strdup (const(gchar)* str);
gchar* g_strdup_printf (const(gchar)* format, ...);
gchar* g_strdup_vprintf (const(gchar)* format, __va_list_tag* args);
gchar* g_strndup (const(gchar)* str, gsize n);
gchar* g_strnfill (gsize length, gchar fill_char);
gchar* g_strconcat (const(gchar)* string1, ...);
gchar* g_strjoin (const(gchar)* separator, ...);
gchar* g_strcompress (const(gchar)* source);
gchar* g_strescape (const(gchar)* source, const(gchar)* exceptions);
gpointer g_memdup (gconstpointer mem, guint byte_size);
gchar** g_strsplit (const(gchar)* string, const(gchar)* delimiter, gint max_tokens);
gchar** g_strsplit_set (const(gchar)* string, const(gchar)* delimiters, gint max_tokens);
gchar* g_strjoinv (const(gchar)* separator, gchar** str_array);
void g_strfreev (gchar** str_array);
gchar** g_strdupv (gchar** str_array);
guint g_strv_length (gchar** str_array);
gchar* g_stpcpy (gchar* dest, const(char)* src);