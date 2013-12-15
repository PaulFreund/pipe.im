module derelict.glib.gatomic;

import core.stdc.config;

extern (C):

gint g_atomic_int_get (gint* atomic);
void g_atomic_int_set (gint* atomic, gint newval);
void g_atomic_int_inc (gint* atomic);
gboolean g_atomic_int_dec_and_test (gint* atomic);
gboolean g_atomic_int_compare_and_exchange (gint* atomic, gint oldval, gint newval);
gint g_atomic_int_add (gint* atomic, gint val);
guint g_atomic_int_and (guint* atomic, guint val);
guint g_atomic_int_or (guint* atomic, guint val);
guint g_atomic_int_xor (guint* atomic, guint val);
gpointer g_atomic_pointer_get (void* atomic);
void g_atomic_pointer_set (void* atomic, gpointer newval);
gboolean g_atomic_pointer_compare_and_exchange (void* atomic, gpointer oldval, gpointer newval);
gssize g_atomic_pointer_add (void* atomic, gssize val);
gsize g_atomic_pointer_and (void* atomic, gsize val);
gsize g_atomic_pointer_or (void* atomic, gsize val);
gsize g_atomic_pointer_xor (void* atomic, gsize val);
gint g_atomic_int_exchange_and_add (gint* atomic, gint val);