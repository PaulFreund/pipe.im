module derelict.glib.grand;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias _GRand GRand;

struct _GRand;


alias da_g_rand_new_with_seed = GRand* function(guint32 seed);																																																						/* da_g_rand_new_with_seed g_rand_new_with_seed; */
alias da_g_rand_new_with_seed_array = GRand* function(const(guint32)* seed, guint seed_length);																																																						/* da_g_rand_new_with_seed_array g_rand_new_with_seed_array; */
alias da_g_rand_new = GRand* function();																																																						/* da_g_rand_new g_rand_new; */
alias da_g_rand_free = void function(GRand* rand_);																																																						/* da_g_rand_free g_rand_free; */
alias da_g_rand_copy = GRand* function(GRand* rand_);																																																						/* da_g_rand_copy g_rand_copy; */
alias da_g_rand_set_seed = void function(GRand* rand_, guint32 seed);																																																						/* da_g_rand_set_seed g_rand_set_seed; */
alias da_g_rand_set_seed_array = void function(GRand* rand_, const(guint32)* seed, guint seed_length);																																																						/* da_g_rand_set_seed_array g_rand_set_seed_array; */
alias da_g_rand_int = guint32 function(GRand* rand_);																																																						/* da_g_rand_int g_rand_int; */
alias da_g_rand_int_range = gint32 function(GRand* rand_, gint32 begin, gint32 end);																																																						/* da_g_rand_int_range g_rand_int_range; */
alias da_g_rand_double = gdouble function(GRand* rand_);																																																						/* da_g_rand_double g_rand_double; */
alias da_g_rand_double_range = gdouble function(GRand* rand_, gdouble begin, gdouble end);																																																						/* da_g_rand_double_range g_rand_double_range; */
alias da_g_random_set_seed = void function(guint32 seed);																																																						/* da_g_random_set_seed g_random_set_seed; */
alias da_g_random_int = guint32 function();																																																						/* da_g_random_int g_random_int; */
alias da_g_random_int_range = gint32 function(gint32 begin, gint32 end);																																																						/* da_g_random_int_range g_random_int_range; */
alias da_g_random_double = gdouble function();																																																						/* da_g_random_double g_random_double; */
alias da_g_random_double_range = gdouble function(gdouble begin, gdouble end);																																																						/* da_g_random_double_range g_random_double_range; */
