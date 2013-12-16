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

alias da_purple_circ_buffer_new = PurpleCircBuffer* function(gsize growsize);																																																						/* da_purple_circ_buffer_new purple_circ_buffer_new; */
alias da_purple_circ_buffer_destroy = void function(PurpleCircBuffer* buf);																																																						/* da_purple_circ_buffer_destroy purple_circ_buffer_destroy; */
alias da_purple_circ_buffer_append = void function(PurpleCircBuffer* buf, gconstpointer src, gsize len);																																																						/* da_purple_circ_buffer_append purple_circ_buffer_append; */
alias da_purple_circ_buffer_get_max_read = gsize function(const(PurpleCircBuffer)* buf);																																																						/* da_purple_circ_buffer_get_max_read purple_circ_buffer_get_max_read; */
alias da_purple_circ_buffer_mark_read = gboolean function(PurpleCircBuffer* buf, gsize len);																																																						/* da_purple_circ_buffer_mark_read purple_circ_buffer_mark_read; */
