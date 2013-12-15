import core.stdc.config;

extern (C):

alias _GAllocator GAllocator;
alias _GMemChunk GMemChunk;

struct _GMemChunk;


struct _GAllocator;


GMemChunk* g_mem_chunk_new (const(gchar)* name, gint atom_size, gsize area_size, gint type);
void g_mem_chunk_destroy (GMemChunk* mem_chunk);
gpointer g_mem_chunk_alloc (GMemChunk* mem_chunk);
gpointer g_mem_chunk_alloc0 (GMemChunk* mem_chunk);
void g_mem_chunk_free (GMemChunk* mem_chunk, gpointer mem);
void g_mem_chunk_clean (GMemChunk* mem_chunk);
void g_mem_chunk_reset (GMemChunk* mem_chunk);
void g_mem_chunk_print (GMemChunk* mem_chunk);
void g_mem_chunk_info ();
void g_blow_chunks ();
GAllocator* g_allocator_new (const(gchar)* name, guint n_preallocs);
void g_allocator_free (GAllocator* allocator);
void g_list_push_allocator (GAllocator* allocator);
void g_list_pop_allocator ();
void g_slist_push_allocator (GAllocator* allocator);
void g_slist_pop_allocator ();
void g_node_push_allocator (GAllocator* allocator);
void g_node_pop_allocator ();