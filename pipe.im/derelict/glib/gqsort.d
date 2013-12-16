module derelict.glib.gqsort;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias da_g_qsort_with_data = void function(gconstpointer pbase, gint total_elems, gsize size, GCompareDataFunc compare_func, gpointer user_data);																																																						/* da_g_qsort_with_data g_qsort_with_data; */
