import core.stdc.config;

extern (C):

alias _GStringChunk GStringChunk;

struct _GStringChunk;


GStringChunk* g_string_chunk_new (gsize size);
void g_string_chunk_free (GStringChunk* chunk);
void g_string_chunk_clear (GStringChunk* chunk);
gchar* g_string_chunk_insert (GStringChunk* chunk, const(gchar)* string);
gchar* g_string_chunk_insert_len (GStringChunk* chunk, const(gchar)* string, gssize len);
gchar* g_string_chunk_insert_const (GStringChunk* chunk, const(gchar)* string);