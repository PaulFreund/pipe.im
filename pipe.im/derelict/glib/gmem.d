module derelict.glib.gmem;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
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

alias da_g_free = void function(gpointer mem);																																																						/* da_g_free g_free; */
alias da_g_malloc = gpointer function(gsize n_bytes);																																																						/* da_g_malloc g_malloc; */
alias da_g_malloc0 = gpointer function(gsize n_bytes);																																																						/* da_g_malloc0 g_malloc0; */
alias da_g_realloc = gpointer function(gpointer mem, gsize n_bytes);																																																						/* da_g_realloc g_realloc; */
alias da_g_try_malloc = gpointer function(gsize n_bytes);																																																						/* da_g_try_malloc g_try_malloc; */
alias da_g_try_malloc0 = gpointer function(gsize n_bytes);																																																						/* da_g_try_malloc0 g_try_malloc0; */
alias da_g_try_realloc = gpointer function(gpointer mem, gsize n_bytes);																																																						/* da_g_try_realloc g_try_realloc; */
alias da_g_malloc_n = gpointer function(gsize n_blocks, gsize n_block_bytes);																																																						/* da_g_malloc_n g_malloc_n; */
alias da_g_malloc0_n = gpointer function(gsize n_blocks, gsize n_block_bytes);																																																						/* da_g_malloc0_n g_malloc0_n; */
alias da_g_realloc_n = gpointer function(gpointer mem, gsize n_blocks, gsize n_block_bytes);																																																						/* da_g_realloc_n g_realloc_n; */
alias da_g_try_malloc_n = gpointer function(gsize n_blocks, gsize n_block_bytes);																																																						/* da_g_try_malloc_n g_try_malloc_n; */
alias da_g_try_malloc0_n = gpointer function(gsize n_blocks, gsize n_block_bytes);																																																						/* da_g_try_malloc0_n g_try_malloc0_n; */
alias da_g_try_realloc_n = gpointer function(gpointer mem, gsize n_blocks, gsize n_block_bytes);																																																						/* da_g_try_realloc_n g_try_realloc_n; */
alias da_g_mem_set_vtable = void function(GMemVTable* vtable);																																																						/* da_g_mem_set_vtable g_mem_set_vtable; */
alias da_g_mem_is_system_malloc = gboolean function();																																																						/* da_g_mem_is_system_malloc g_mem_is_system_malloc; */
alias da_g_mem_profile = void function();																																																						/* da_g_mem_profile g_mem_profile; */
