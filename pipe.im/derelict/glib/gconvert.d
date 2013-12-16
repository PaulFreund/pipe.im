module derelict.glib.gconvert;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gquark;
import derelict.glib.gerror;
import core.stdc.config;

extern (C):

alias _Anonymous_0 GConvertError;
alias _GIConv* GIConv;

enum _Anonymous_0
{
	G_CONVERT_ERROR_NO_CONVERSION = 0,
	G_CONVERT_ERROR_ILLEGAL_SEQUENCE = 1,
	G_CONVERT_ERROR_FAILED = 2,
	G_CONVERT_ERROR_PARTIAL_INPUT = 3,
	G_CONVERT_ERROR_BAD_URI = 4,
	G_CONVERT_ERROR_NOT_ABSOLUTE_PATH = 5
}

struct _GIConv;


GQuark g_convert_error_quark ();
GIConv g_iconv_open (const(gchar)* to_codeset, const(gchar)* from_codeset);
gsize g_iconv (GIConv converter, gchar** inbuf, gsize* inbytes_left, gchar** outbuf, gsize* outbytes_left);
gint g_iconv_close (GIConv converter);
gchar* g_convert (const(gchar)* str, gssize len, const(gchar)* to_codeset, const(gchar)* from_codeset, gsize* bytes_read, gsize* bytes_written, GError** error);
gchar* g_convert_with_iconv (const(gchar)* str, gssize len, GIConv converter, gsize* bytes_read, gsize* bytes_written, GError** error);
gchar* g_convert_with_fallback (const(gchar)* str, gssize len, const(gchar)* to_codeset, const(gchar)* from_codeset, const(gchar)* fallback, gsize* bytes_read, gsize* bytes_written, GError** error);
gchar* g_locale_to_utf8 (const(gchar)* opsysstring, gssize len, gsize* bytes_read, gsize* bytes_written, GError** error);
gchar* g_locale_from_utf8 (const(gchar)* utf8string, gssize len, gsize* bytes_read, gsize* bytes_written, GError** error);
gchar* g_filename_to_utf8 (const(gchar)* opsysstring, gssize len, gsize* bytes_read, gsize* bytes_written, GError** error);
gchar* g_filename_from_utf8 (const(gchar)* utf8string, gssize len, gsize* bytes_read, gsize* bytes_written, GError** error);
gchar* g_filename_from_uri (const(gchar)* uri, gchar** hostname, GError** error);
gchar* g_filename_to_uri (const(gchar)* filename, const(gchar)* hostname, GError** error);
gchar* g_filename_display_name (const(gchar)* filename);
gboolean g_get_filename_charsets (const(gchar**)* charsets);
gchar* g_filename_display_basename (const(gchar)* filename);
gchar** g_uri_list_extract_uris (const(gchar)* uri_list);