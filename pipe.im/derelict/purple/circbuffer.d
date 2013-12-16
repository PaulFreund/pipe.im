module derelict.purple.circbuffer;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias _PurpleCircBuffer PurpleCircBuffer;

struct _PurpleCircBuffer
{
	gchar* buffer;
	gsize growsize;
	gsize buflen;
	gsize bufused;
	gchar* inptr;
	gchar* outptr;
}

PurpleCircBuffer* purple_circ_buffer_new (gsize growsize);
void purple_circ_buffer_destroy (PurpleCircBuffer* buf);
void purple_circ_buffer_append (PurpleCircBuffer* buf, gconstpointer src, gsize len);
gsize purple_circ_buffer_get_max_read (const(PurpleCircBuffer)* buf);
gboolean purple_circ_buffer_mark_read (PurpleCircBuffer* buf, gsize len);