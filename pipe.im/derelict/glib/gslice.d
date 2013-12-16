module derelict.glib.gslice;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
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

alias da_g_slice_alloc = gpointer function(gsize block_size);																																																						/* da_g_slice_alloc g_slice_alloc; */
alias da_g_slice_alloc0 = gpointer function(gsize block_size);																																																						/* da_g_slice_alloc0 g_slice_alloc0; */
alias da_g_slice_copy = gpointer function(gsize block_size, gconstpointer mem_block);																																																						/* da_g_slice_copy g_slice_copy; */
alias da_g_slice_free1 = void function(gsize block_size, gpointer mem_block);																																																						/* da_g_slice_free1 g_slice_free1; */
alias da_g_slice_free_chain_with_offset = void function(gsize block_size, gpointer mem_chain, gsize next_offset);																																																						/* da_g_slice_free_chain_with_offset g_slice_free_chain_with_offset; */
alias da_g_slice_set_config = void function(GSliceConfig ckey, gint64 value);																																																						/* da_g_slice_set_config g_slice_set_config; */
alias da_g_slice_get_config = gint64 function(GSliceConfig ckey);																																																						/* da_g_slice_get_config g_slice_get_config; */
alias da_g_slice_get_config_state = gint64* function(GSliceConfig ckey, gint64 address, guint* n_values);																																																						/* da_g_slice_get_config_state g_slice_get_config_state; */
