/*

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/ 

module derelict.glib.gtree;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gnode;

extern (C):

alias _GTree GTree;
alias int function (void*, void*, void*) GTraverseFunc;

struct _GTree;

extern( C ) nothrow 
{
    alias da_g_tree_new = GTree* function(GCompareFunc key_compare_func);																											
    alias da_g_tree_new_with_data = GTree* function(GCompareDataFunc key_compare_func, gpointer key_compare_data);																	
    alias da_g_tree_new_full = GTree* function(GCompareDataFunc key_compare_func, gpointer key_compare_data, GDestroyNotify key_destroy_func, GDestroyNotify value_destroy_func);	
    alias da_g_tree_ref = GTree* function(GTree* tree);																																
    alias da_g_tree_unref = void function(GTree* tree);																																
    alias da_g_tree_destroy = void function(GTree* tree);																															
    alias da_g_tree_insert = void function(GTree* tree, gpointer key, gpointer value);																								
    alias da_g_tree_replace = void function(GTree* tree, gpointer key, gpointer value);																								
    alias da_g_tree_remove = gboolean function(GTree* tree, gconstpointer key);																										
    alias da_g_tree_steal = gboolean function(GTree* tree, gconstpointer key);																										
    alias da_g_tree_lookup = gpointer function(GTree* tree, gconstpointer key);																										
    alias da_g_tree_lookup_extended = gboolean function(GTree* tree, gconstpointer lookup_key, gpointer* orig_key, gpointer* value);												
    alias da_g_tree_foreach = void function(GTree* tree, GTraverseFunc func, gpointer user_data);																					
    alias da_g_tree_traverse = void function(GTree* tree, GTraverseFunc traverse_func, GTraverseType traverse_type, gpointer user_data);											
    alias da_g_tree_search = gpointer function(GTree* tree, GCompareFunc search_func, gconstpointer user_data);																		
    alias da_g_tree_height = gint function(GTree* tree);																															
    alias da_g_tree_nnodes = gint function(GTree* tree);		
}

__gshared
{
    da_g_tree_new g_tree_new; 
    da_g_tree_new_with_data g_tree_new_with_data; 
    da_g_tree_new_full g_tree_new_full; 
    da_g_tree_ref g_tree_ref; 
    da_g_tree_unref g_tree_unref; 
    da_g_tree_destroy g_tree_destroy; 
    da_g_tree_insert g_tree_insert; 
    da_g_tree_replace g_tree_replace; 
    da_g_tree_remove g_tree_remove; 
    da_g_tree_steal g_tree_steal; 
    da_g_tree_lookup g_tree_lookup; 
    da_g_tree_lookup_extended g_tree_lookup_extended; 
    da_g_tree_foreach g_tree_foreach; 
    da_g_tree_traverse g_tree_traverse; 
    da_g_tree_search g_tree_search; 
    da_g_tree_height g_tree_height; 
    da_g_tree_nnodes g_tree_nnodes; 
}