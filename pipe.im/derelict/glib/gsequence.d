module derelict.glib.gsequence;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _GSequence GSequence;
alias _GSequenceNode GSequenceIter;
alias int function (_GSequenceNode*, _GSequenceNode*, void*) GSequenceIterCompareFunc;

struct _GSequence;


struct _GSequenceNode;


alias da_g_sequence_new = GSequence* function(GDestroyNotify data_destroy);																																																						/* da_g_sequence_new g_sequence_new; */
alias da_g_sequence_free = void function(GSequence* seq);																																																						/* da_g_sequence_free g_sequence_free; */
alias da_g_sequence_get_length = gint function(GSequence* seq);																																																						/* da_g_sequence_get_length g_sequence_get_length; */
alias da_g_sequence_foreach = void function(GSequence* seq, GFunc func, gpointer user_data);																																																						/* da_g_sequence_foreach g_sequence_foreach; */
alias da_g_sequence_foreach_range = void function(GSequenceIter* begin, GSequenceIter* end, GFunc func, gpointer user_data);																																																						/* da_g_sequence_foreach_range g_sequence_foreach_range; */
alias da_g_sequence_sort = void function(GSequence* seq, GCompareDataFunc cmp_func, gpointer cmp_data);																																																						/* da_g_sequence_sort g_sequence_sort; */
alias da_g_sequence_sort_iter = void function(GSequence* seq, GSequenceIterCompareFunc cmp_func, gpointer cmp_data);																																																						/* da_g_sequence_sort_iter g_sequence_sort_iter; */
alias da_g_sequence_get_begin_iter = GSequenceIter* function(GSequence* seq);																																																						/* da_g_sequence_get_begin_iter g_sequence_get_begin_iter; */
alias da_g_sequence_get_end_iter = GSequenceIter* function(GSequence* seq);																																																						/* da_g_sequence_get_end_iter g_sequence_get_end_iter; */
alias da_g_sequence_get_iter_at_pos = GSequenceIter* function(GSequence* seq, gint pos);																																																						/* da_g_sequence_get_iter_at_pos g_sequence_get_iter_at_pos; */
alias da_g_sequence_append = GSequenceIter* function(GSequence* seq, gpointer data);																																																						/* da_g_sequence_append g_sequence_append; */
alias da_g_sequence_prepend = GSequenceIter* function(GSequence* seq, gpointer data);																																																						/* da_g_sequence_prepend g_sequence_prepend; */
alias da_g_sequence_insert_before = GSequenceIter* function(GSequenceIter* iter, gpointer data);																																																						/* da_g_sequence_insert_before g_sequence_insert_before; */
alias da_g_sequence_move = void function(GSequenceIter* src, GSequenceIter* dest);																																																						/* da_g_sequence_move g_sequence_move; */
alias da_g_sequence_swap = void function(GSequenceIter* a, GSequenceIter* b);																																																						/* da_g_sequence_swap g_sequence_swap; */
alias da_g_sequence_insert_sorted = GSequenceIter* function(GSequence* seq, gpointer data, GCompareDataFunc cmp_func, gpointer cmp_data);																																																						/* da_g_sequence_insert_sorted g_sequence_insert_sorted; */
alias da_g_sequence_insert_sorted_iter = GSequenceIter* function(GSequence* seq, gpointer data, GSequenceIterCompareFunc iter_cmp, gpointer cmp_data);																																																						/* da_g_sequence_insert_sorted_iter g_sequence_insert_sorted_iter; */
alias da_g_sequence_sort_changed = void function(GSequenceIter* iter, GCompareDataFunc cmp_func, gpointer cmp_data);																																																						/* da_g_sequence_sort_changed g_sequence_sort_changed; */
alias da_g_sequence_sort_changed_iter = void function(GSequenceIter* iter, GSequenceIterCompareFunc iter_cmp, gpointer cmp_data);																																																						/* da_g_sequence_sort_changed_iter g_sequence_sort_changed_iter; */
alias da_g_sequence_remove = void function(GSequenceIter* iter);																																																						/* da_g_sequence_remove g_sequence_remove; */
alias da_g_sequence_remove_range = void function(GSequenceIter* begin, GSequenceIter* end);																																																						/* da_g_sequence_remove_range g_sequence_remove_range; */
alias da_g_sequence_move_range = void function(GSequenceIter* dest, GSequenceIter* begin, GSequenceIter* end);																																																						/* da_g_sequence_move_range g_sequence_move_range; */
alias da_g_sequence_search = GSequenceIter* function(GSequence* seq, gpointer data, GCompareDataFunc cmp_func, gpointer cmp_data);																																																						/* da_g_sequence_search g_sequence_search; */
alias da_g_sequence_search_iter = GSequenceIter* function(GSequence* seq, gpointer data, GSequenceIterCompareFunc iter_cmp, gpointer cmp_data);																																																						/* da_g_sequence_search_iter g_sequence_search_iter; */
alias da_g_sequence_lookup = GSequenceIter* function(GSequence* seq, gpointer data, GCompareDataFunc cmp_func, gpointer cmp_data);																																																						/* da_g_sequence_lookup g_sequence_lookup; */
alias da_g_sequence_lookup_iter = GSequenceIter* function(GSequence* seq, gpointer data, GSequenceIterCompareFunc iter_cmp, gpointer cmp_data);																																																						/* da_g_sequence_lookup_iter g_sequence_lookup_iter; */
alias da_g_sequence_get = gpointer function(GSequenceIter* iter);																																																						/* da_g_sequence_get g_sequence_get; */
alias da_g_sequence_set = void function(GSequenceIter* iter, gpointer data);																																																						/* da_g_sequence_set g_sequence_set; */
alias da_g_sequence_iter_is_begin = gboolean function(GSequenceIter* iter);																																																						/* da_g_sequence_iter_is_begin g_sequence_iter_is_begin; */
alias da_g_sequence_iter_is_end = gboolean function(GSequenceIter* iter);																																																						/* da_g_sequence_iter_is_end g_sequence_iter_is_end; */
alias da_g_sequence_iter_next = GSequenceIter* function(GSequenceIter* iter);																																																						/* da_g_sequence_iter_next g_sequence_iter_next; */
alias da_g_sequence_iter_prev = GSequenceIter* function(GSequenceIter* iter);																																																						/* da_g_sequence_iter_prev g_sequence_iter_prev; */
alias da_g_sequence_iter_get_position = gint function(GSequenceIter* iter);																																																						/* da_g_sequence_iter_get_position g_sequence_iter_get_position; */
alias da_g_sequence_iter_move = GSequenceIter* function(GSequenceIter* iter, gint delta);																																																						/* da_g_sequence_iter_move g_sequence_iter_move; */
alias da_g_sequence_iter_get_sequence = GSequence* function(GSequenceIter* iter);																																																						/* da_g_sequence_iter_get_sequence g_sequence_iter_get_sequence; */
alias da_g_sequence_iter_compare = gint function(GSequenceIter* a, GSequenceIter* b);																																																						/* da_g_sequence_iter_compare g_sequence_iter_compare; */
alias da_g_sequence_range_get_midpoint = GSequenceIter* function(GSequenceIter* begin, GSequenceIter* end);																																																						/* da_g_sequence_range_get_midpoint g_sequence_range_get_midpoint; */
