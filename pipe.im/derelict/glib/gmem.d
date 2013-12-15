module derelict.glib.gmem;

import core.stdc.config;

extern (C):

alias _GMemVTable GMemVTable;

extern __gshared gboolean g_mem_gc_friendly;
extern __gshared GMemVTable* glib_mem_profiler_table;

struct _GMemVTable
{
	gpointer function (gsize) malloc;
	gpointer function (gpointer, gsize) realloc;
	void function (gpointer) free;
	gpointer function (gsize, gsize) calloc;
	gpointer function (gsize) try_malloc;
	gpointer function (gpointer, gsize) try_realloc;
}

void g_free (gpointer mem);
gpointer g_malloc (gsize n_bytes);
gpointer g_malloc0 (gsize n_bytes);
gpointer g_realloc (gpointer mem, gsize n_bytes);
gpointer g_try_malloc (gsize n_bytes);
gpointer g_try_malloc0 (gsize n_bytes);
gpointer g_try_realloc (gpointer mem, gsize n_bytes);
gpointer g_malloc_n (gsize n_blocks, gsize n_block_bytes);
gpointer g_malloc0_n (gsize n_blocks, gsize n_block_bytes);
gpointer g_realloc_n (gpointer mem, gsize n_blocks, gsize n_block_bytes);
gpointer g_try_malloc_n (gsize n_blocks, gsize n_block_bytes);
gpointer g_try_malloc0_n (gsize n_blocks, gsize n_block_bytes);
gpointer g_try_realloc_n (gpointer mem, gsize n_blocks, gsize n_block_bytes);
void g_mem_set_vtable (GMemVTable* vtable);
gboolean g_mem_is_system_malloc ();
void g_mem_profile ();