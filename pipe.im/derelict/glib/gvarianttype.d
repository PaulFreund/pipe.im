module derelict.glib.gvarianttype;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias _GVariantType GVariantType;

struct _GVariantType;


gboolean g_variant_type_string_is_valid (const(gchar)* type_string);
gboolean g_variant_type_string_scan (const(gchar)* string, const(gchar)* limit, const(gchar*)* endptr);
void g_variant_type_free (GVariantType* type);
GVariantType* g_variant_type_copy (const(GVariantType)* type);
GVariantType* g_variant_type_new (const(gchar)* type_string);
gsize g_variant_type_get_string_length (const(GVariantType)* type);
const(gchar)* g_variant_type_peek_string (const(GVariantType)* type);
gchar* g_variant_type_dup_string (const(GVariantType)* type);
gboolean g_variant_type_is_definite (const(GVariantType)* type);
gboolean g_variant_type_is_container (const(GVariantType)* type);
gboolean g_variant_type_is_basic (const(GVariantType)* type);
gboolean g_variant_type_is_maybe (const(GVariantType)* type);
gboolean g_variant_type_is_array (const(GVariantType)* type);
gboolean g_variant_type_is_tuple (const(GVariantType)* type);
gboolean g_variant_type_is_dict_entry (const(GVariantType)* type);
gboolean g_variant_type_is_variant (const(GVariantType)* type);
guint g_variant_type_hash (gconstpointer type);
gboolean g_variant_type_equal (gconstpointer type1, gconstpointer type2);
gboolean g_variant_type_is_subtype_of (const(GVariantType)* type, const(GVariantType)* supertype);
const(GVariantType)* g_variant_type_element (const(GVariantType)* type);
const(GVariantType)* g_variant_type_first (const(GVariantType)* type);
const(GVariantType)* g_variant_type_next (const(GVariantType)* type);
gsize g_variant_type_n_items (const(GVariantType)* type);
const(GVariantType)* g_variant_type_key (const(GVariantType)* type);
const(GVariantType)* g_variant_type_value (const(GVariantType)* type);
GVariantType* g_variant_type_new_array (const(GVariantType)* element);
GVariantType* g_variant_type_new_maybe (const(GVariantType)* element);
GVariantType* g_variant_type_new_tuple (const(GVariantType*)* items, gint length);
GVariantType* g_variant_type_new_dict_entry (const(GVariantType)* key, const(GVariantType)* value);
const(GVariantType)* g_variant_type_checked_ (const(gchar)*);