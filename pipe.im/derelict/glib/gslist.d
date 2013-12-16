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

module derelict.glib.gslist;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _GSList GSList;

struct _GSList
{
	gpointer data;
	GSList* next;
}


extern( C ) nothrow 
{
    alias da_g_slist_alloc = GSList* function();																																														
    alias da_g_slist_free = void function(GSList* list);																																												
    alias da_g_slist_free_1 = void function(GSList* list);																																												
    alias da_g_slist_free_full = void function(GSList* list, GDestroyNotify free_func);																																					
    alias da_g_slist_append = GSList* function(GSList* list, gpointer data);																																							
    alias da_g_slist_prepend = GSList* function(GSList* list, gpointer data);																																							
    alias da_g_slist_insert = GSList* function(GSList* list, gpointer data, gint position);																																				
    alias da_g_slist_insert_sorted = GSList* function(GSList* list, gpointer data, GCompareFunc func);																																	
    alias da_g_slist_insert_sorted_with_data = GSList* function(GSList* list, gpointer data, GCompareDataFunc func, gpointer user_data);																								
    alias da_g_slist_insert_before = GSList* function(GSList* slist, GSList* sibling, gpointer data);																																	
    alias da_g_slist_concat = GSList* function(GSList* list1, GSList* list2);																																							
    alias da_g_slist_remove = GSList* function(GSList* list, gconstpointer data);																																						
    alias da_g_slist_remove_all = GSList* function(GSList* list, gconstpointer data);																																					
    alias da_g_slist_remove_link = GSList* function(GSList* list, GSList* link_);																																						
    alias da_g_slist_delete_link = GSList* function(GSList* list, GSList* link_);																																						
    alias da_g_slist_reverse = GSList* function(GSList* list);																																											
    alias da_g_slist_copy = GSList* function(GSList* list);																																												
    alias da_g_slist_nth = GSList* function(GSList* list, guint n);																																										
    alias da_g_slist_find = GSList* function(GSList* list, gconstpointer data);																																							
    alias da_g_slist_find_custom = GSList* function(GSList* list, gconstpointer data, GCompareFunc func);																																
    alias da_g_slist_position = gint function(GSList* list, GSList* llink);																																								
    alias da_g_slist_index = gint function(GSList* list, gconstpointer data);																																							
    alias da_g_slist_last = GSList* function(GSList* list);																																												
    alias da_g_slist_length = guint function(GSList* list);																																												
    alias da_g_slist_foreach = void function(GSList* list, GFunc func, gpointer user_data);																																				
    alias da_g_slist_sort = GSList* function(GSList* list, GCompareFunc compare_func);																																					
    alias da_g_slist_sort_with_data = GSList* function(GSList* list, GCompareDataFunc compare_func, gpointer user_data);																												
    alias da_g_slist_nth_data = gpointer function(GSList* list, guint n);																																								
}

__gshared
{
    da_g_slist_alloc g_slist_alloc; 
    da_g_slist_free g_slist_free; 
    da_g_slist_free_1 g_slist_free_1; 
    da_g_slist_free_full g_slist_free_full; 
    da_g_slist_append g_slist_append; 
    da_g_slist_prepend g_slist_prepend; 
    da_g_slist_insert g_slist_insert; 
    da_g_slist_insert_sorted g_slist_insert_sorted; 
    da_g_slist_insert_sorted_with_data g_slist_insert_sorted_with_data; 
    da_g_slist_insert_before g_slist_insert_before; 
    da_g_slist_concat g_slist_concat; 
    da_g_slist_remove g_slist_remove; 
    da_g_slist_remove_all g_slist_remove_all; 
    da_g_slist_remove_link g_slist_remove_link; 
    da_g_slist_delete_link g_slist_delete_link; 
    da_g_slist_reverse g_slist_reverse; 
    da_g_slist_copy g_slist_copy; 
    da_g_slist_nth g_slist_nth; 
    da_g_slist_find g_slist_find; 
    da_g_slist_find_custom g_slist_find_custom; 
    da_g_slist_position g_slist_position; 
    da_g_slist_index g_slist_index; 
    da_g_slist_last g_slist_last; 
    da_g_slist_length g_slist_length; 
    da_g_slist_foreach g_slist_foreach; 
    da_g_slist_sort g_slist_sort; 
    da_g_slist_sort_with_data g_slist_sort_with_data; 
    da_g_slist_nth_data g_slist_nth_data; 
}