module derelict.glib.garray;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

import core.stdc.config;

extern (C):

alias _GBytes GBytes;
alias _GArray GArray;
alias _GByteArray GByteArray;
alias _GPtrArray GPtrArray;

struct _GArray
{
	gchar* data;
	guint len;
}

struct _GByteArray
{
	guint8* data;
	guint len;
}

struct _GPtrArray
{
	gpointer* pdata;
	guint len;
}

struct _GBytes;


GArray* g_array_new (gboolean zero_terminated, gboolean clear_, guint element_size);
GArray* g_array_sized_new (gboolean zero_terminated, gboolean clear_, guint element_size, guint reserved_size);
gchar* g_array_free (GArray* array, gboolean free_segment);
GArray* g_array_ref (GArray* array);
void g_array_unref (GArray* array);
guint g_array_get_element_size (GArray* array);
GArray* g_array_append_vals (GArray* array, gconstpointer data, guint len);
GArray* g_array_prepend_vals (GArray* array, gconstpointer data, guint len);
GArray* g_array_insert_vals (GArray* array, guint index_, gconstpointer data, guint len);
GArray* g_array_set_size (GArray* array, guint length);
GArray* g_array_remove_index (GArray* array, guint index_);
GArray* g_array_remove_index_fast (GArray* array, guint index_);
GArray* g_array_remove_range (GArray* array, guint index_, guint length);
void g_array_sort (GArray* array, GCompareFunc compare_func);
void g_array_sort_with_data (GArray* array, GCompareDataFunc compare_func, gpointer user_data);
void g_array_set_clear_func (GArray* array, GDestroyNotify clear_func);
GPtrArray* g_ptr_array_new ();
GPtrArray* g_ptr_array_new_with_free_func (GDestroyNotify element_free_func);
GPtrArray* g_ptr_array_sized_new (guint reserved_size);
GPtrArray* g_ptr_array_new_full (guint reserved_size, GDestroyNotify element_free_func);
gpointer* g_ptr_array_free (GPtrArray* array, gboolean free_seg);
GPtrArray* g_ptr_array_ref (GPtrArray* array);
void g_ptr_array_unref (GPtrArray* array);
void g_ptr_array_set_free_func (GPtrArray* array, GDestroyNotify element_free_func);
void g_ptr_array_set_size (GPtrArray* array, gint length);
gpointer g_ptr_array_remove_index (GPtrArray* array, guint index_);
gpointer g_ptr_array_remove_index_fast (GPtrArray* array, guint index_);
gboolean g_ptr_array_remove (GPtrArray* array, gpointer data);
gboolean g_ptr_array_remove_fast (GPtrArray* array, gpointer data);
void g_ptr_array_remove_range (GPtrArray* array, guint index_, guint length);
void g_ptr_array_add (GPtrArray* array, gpointer data);
void g_ptr_array_sort (GPtrArray* array, GCompareFunc compare_func);
void g_ptr_array_sort_with_data (GPtrArray* array, GCompareDataFunc compare_func, gpointer user_data);
void g_ptr_array_foreach (GPtrArray* array, GFunc func, gpointer user_data);
GByteArray* g_byte_array_new ();
GByteArray* g_byte_array_new_take (guint8* data, gsize len);
GByteArray* g_byte_array_sized_new (guint reserved_size);
guint8* g_byte_array_free (GByteArray* array, gboolean free_segment);
GBytes* g_byte_array_free_to_bytes (GByteArray* array);
GByteArray* g_byte_array_ref (GByteArray* array);
void g_byte_array_unref (GByteArray* array);
GByteArray* g_byte_array_append (GByteArray* array, const(guint8)* data, guint len);
GByteArray* g_byte_array_prepend (GByteArray* array, const(guint8)* data, guint len);
GByteArray* g_byte_array_set_size (GByteArray* array, guint length);
GByteArray* g_byte_array_remove_index (GByteArray* array, guint index_);
GByteArray* g_byte_array_remove_index_fast (GByteArray* array, guint index_);
GByteArray* g_byte_array_remove_range (GByteArray* array, guint index_, guint length);
void g_byte_array_sort (GByteArray* array, GCompareFunc compare_func);
void g_byte_array_sort_with_data (GByteArray* array, GCompareDataFunc compare_func, gpointer user_data);