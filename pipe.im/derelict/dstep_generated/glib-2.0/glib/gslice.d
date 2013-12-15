import core.stdc.config;

extern (C):

alias _Anonymous_0 GSliceConfig;

enum _Anonymous_0
{
	G_SLICE_CONFIG_ALWAYS_MALLOC = 1,
	G_SLICE_CONFIG_BYPASS_MAGAZINES = 2,
	G_SLICE_CONFIG_WORKING_SET_MSECS = 3,
	G_SLICE_CONFIG_COLOR_INCREMENT = 4,
	G_SLICE_CONFIG_CHUNK_SIZES = 5,
	G_SLICE_CONFIG_CONTENTION_COUNTER = 6
}

gpointer g_slice_alloc (gsize block_size);
gpointer g_slice_alloc0 (gsize block_size);
gpointer g_slice_copy (gsize block_size, gconstpointer mem_block);
void g_slice_free1 (gsize block_size, gpointer mem_block);
void g_slice_free_chain_with_offset (gsize block_size, gpointer mem_chain, gsize next_offset);
void g_slice_set_config (GSliceConfig ckey, gint64 value);
gint64 g_slice_get_config (GSliceConfig ckey);
gint64* g_slice_get_config_state (GSliceConfig ckey, gint64 address, guint* n_values);