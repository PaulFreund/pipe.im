module derelict.glib.gstringchunk;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias _GStringChunk GStringChunk;

struct _GStringChunk;


alias da_g_string_chunk_new = GStringChunk* function(gsize size);																																																						/* da_g_string_chunk_new g_string_chunk_new; */
alias da_g_string_chunk_free = void function(GStringChunk* chunk);																																																						/* da_g_string_chunk_free g_string_chunk_free; */
alias da_g_string_chunk_clear = void function(GStringChunk* chunk);																																																						/* da_g_string_chunk_clear g_string_chunk_clear; */
alias da_g_string_chunk_insert = gchar* function(GStringChunk* chunk, const(gchar)* string);																																																						/* da_g_string_chunk_insert g_string_chunk_insert; */
alias da_g_string_chunk_insert_len = gchar* function(GStringChunk* chunk, const(gchar)* string, gssize len);																																																						/* da_g_string_chunk_insert_len g_string_chunk_insert_len; */
alias da_g_string_chunk_insert_const = gchar* function(GStringChunk* chunk, const(gchar)* string);																																																						/* da_g_string_chunk_insert_const g_string_chunk_insert_const; */
