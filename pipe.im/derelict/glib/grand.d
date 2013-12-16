module derelict.glib.grand;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias _GRand GRand;

struct _GRand;


GRand* g_rand_new_with_seed (guint32 seed);
GRand* g_rand_new_with_seed_array (const(guint32)* seed, guint seed_length);
GRand* g_rand_new ();
void g_rand_free (GRand* rand_);
GRand* g_rand_copy (GRand* rand_);
void g_rand_set_seed (GRand* rand_, guint32 seed);
void g_rand_set_seed_array (GRand* rand_, const(guint32)* seed, guint seed_length);
guint32 g_rand_int (GRand* rand_);
gint32 g_rand_int_range (GRand* rand_, gint32 begin, gint32 end);
gdouble g_rand_double (GRand* rand_);
gdouble g_rand_double_range (GRand* rand_, gdouble begin, gdouble end);
void g_random_set_seed (guint32 seed);
guint32 g_random_int ();
gint32 g_random_int_range (gint32 begin, gint32 end);
gdouble g_random_double ();
gdouble g_random_double_range (gdouble begin, gdouble end);