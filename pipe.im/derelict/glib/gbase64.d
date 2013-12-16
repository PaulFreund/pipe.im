module derelict.glib.gbase64;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

gsize g_base64_encode_step (const(guchar)* in_, gsize len, gboolean break_lines, gchar* out_, gint* state, gint* save);
gsize g_base64_encode_close (gboolean break_lines, gchar* out_, gint* state, gint* save);
gchar* g_base64_encode (const(guchar)* data, gsize len);
gsize g_base64_decode_step (const(gchar)* in_, gsize len, guchar* out_, gint* state, guint* save);
guchar* g_base64_decode (const(gchar)* text, gsize* out_len);
guchar* g_base64_decode_inplace (gchar* text, gsize* out_len);