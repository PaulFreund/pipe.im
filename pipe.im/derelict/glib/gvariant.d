module derelict.glib.gvariant;

import core.stdc.config;
import core.stdc.string;
import core.stdc.stdarg;

extern (C):

alias _GVariant GVariant;
alias _Anonymous_0 GVariantClass;
alias _GVariantIter GVariantIter;
alias _GVariantBuilder GVariantBuilder;
alias _Anonymous_1 GVariantParseError;

enum _Anonymous_0
{
	G_VARIANT_CLASS_BOOLEAN = 98,
	G_VARIANT_CLASS_BYTE = 121,
	G_VARIANT_CLASS_INT16 = 110,
	G_VARIANT_CLASS_UINT16 = 113,
	G_VARIANT_CLASS_INT32 = 105,
	G_VARIANT_CLASS_UINT32 = 117,
	G_VARIANT_CLASS_INT64 = 120,
	G_VARIANT_CLASS_UINT64 = 116,
	G_VARIANT_CLASS_HANDLE = 104,
	G_VARIANT_CLASS_DOUBLE = 100,
	G_VARIANT_CLASS_STRING = 115,
	G_VARIANT_CLASS_OBJECT_PATH = 111,
	G_VARIANT_CLASS_SIGNATURE = 103,
	G_VARIANT_CLASS_VARIANT = 118,
	G_VARIANT_CLASS_MAYBE = 109,
	G_VARIANT_CLASS_ARRAY = 97,
	G_VARIANT_CLASS_TUPLE = 40,
	G_VARIANT_CLASS_DICT_ENTRY = 123
}

enum _Anonymous_1
{
	G_VARIANT_PARSE_ERROR_FAILED = 0,
	G_VARIANT_PARSE_ERROR_BASIC_TYPE_EXPECTED = 1,
	G_VARIANT_PARSE_ERROR_CANNOT_INFER_TYPE = 2,
	G_VARIANT_PARSE_ERROR_DEFINITE_TYPE_EXPECTED = 3,
	G_VARIANT_PARSE_ERROR_INPUT_NOT_AT_END = 4,
	G_VARIANT_PARSE_ERROR_INVALID_CHARACTER = 5,
	G_VARIANT_PARSE_ERROR_INVALID_FORMAT_STRING = 6,
	G_VARIANT_PARSE_ERROR_INVALID_OBJECT_PATH = 7,
	G_VARIANT_PARSE_ERROR_INVALID_SIGNATURE = 8,
	G_VARIANT_PARSE_ERROR_INVALID_TYPE_STRING = 9,
	G_VARIANT_PARSE_ERROR_NO_COMMON_TYPE = 10,
	G_VARIANT_PARSE_ERROR_NUMBER_OUT_OF_RANGE = 11,
	G_VARIANT_PARSE_ERROR_NUMBER_TOO_BIG = 12,
	G_VARIANT_PARSE_ERROR_TYPE_ERROR = 13,
	G_VARIANT_PARSE_ERROR_UNEXPECTED_TOKEN = 14,
	G_VARIANT_PARSE_ERROR_UNKNOWN_KEYWORD = 15,
	G_VARIANT_PARSE_ERROR_UNTERMINATED_STRING_CONSTANT = 16,
	G_VARIANT_PARSE_ERROR_VALUE_EXPECTED = 17
}

struct _GVariantIter
{
	gsize[16] x;
}

struct _GVariantBuilder
{
	gsize[16] x;
}

struct _GVariant;


void g_variant_unref (GVariant* value);
GVariant* g_variant_ref (GVariant* value);
GVariant* g_variant_ref_sink (GVariant* value);
gboolean g_variant_is_floating (GVariant* value);
GVariant* g_variant_take_ref (GVariant* value);
const(GVariantType)* g_variant_get_type (GVariant* value);
const(gchar)* g_variant_get_type_string (GVariant* value);
gboolean g_variant_is_of_type (GVariant* value, const(GVariantType)* type);
gboolean g_variant_is_container (GVariant* value);
GVariantClass g_variant_classify (GVariant* value);
GVariant* g_variant_new_boolean (gboolean value);
GVariant* g_variant_new_byte (guchar value);
GVariant* g_variant_new_int16 (gint16 value);
GVariant* g_variant_new_uint16 (guint16 value);
GVariant* g_variant_new_int32 (gint32 value);
GVariant* g_variant_new_uint32 (guint32 value);
GVariant* g_variant_new_int64 (gint64 value);
GVariant* g_variant_new_uint64 (guint64 value);
GVariant* g_variant_new_handle (gint32 value);
GVariant* g_variant_new_double (gdouble value);
GVariant* g_variant_new_string (const(gchar)* string);
GVariant* g_variant_new_object_path (const(gchar)* object_path);
gboolean g_variant_is_object_path (const(gchar)* string);
GVariant* g_variant_new_signature (const(gchar)* signature);
gboolean g_variant_is_signature (const(gchar)* string);
GVariant* g_variant_new_variant (GVariant* value);
GVariant* g_variant_new_strv (const(gchar*)* strv, gssize length);
GVariant* g_variant_new_objv (const(gchar*)* strv, gssize length);
GVariant* g_variant_new_bytestring (const(gchar)* string);
GVariant* g_variant_new_bytestring_array (const(gchar*)* strv, gssize length);
GVariant* g_variant_new_fixed_array (const(GVariantType)* element_type, gconstpointer elements, gsize n_elements, gsize element_size);
gboolean g_variant_get_boolean (GVariant* value);
guchar g_variant_get_byte (GVariant* value);
gint16 g_variant_get_int16 (GVariant* value);
guint16 g_variant_get_uint16 (GVariant* value);
gint32 g_variant_get_int32 (GVariant* value);
guint32 g_variant_get_uint32 (GVariant* value);
gint64 g_variant_get_int64 (GVariant* value);
guint64 g_variant_get_uint64 (GVariant* value);
gint32 g_variant_get_handle (GVariant* value);
gdouble g_variant_get_double (GVariant* value);
GVariant* g_variant_get_variant (GVariant* value);
const(gchar)* g_variant_get_string (GVariant* value, gsize* length);
gchar* g_variant_dup_string (GVariant* value, gsize* length);
const(gchar*)* g_variant_get_strv (GVariant* value, gsize* length);
gchar** g_variant_dup_strv (GVariant* value, gsize* length);
const(gchar*)* g_variant_get_objv (GVariant* value, gsize* length);
gchar** g_variant_dup_objv (GVariant* value, gsize* length);
const(gchar)* g_variant_get_bytestring (GVariant* value);
gchar* g_variant_dup_bytestring (GVariant* value, gsize* length);
const(gchar*)* g_variant_get_bytestring_array (GVariant* value, gsize* length);
gchar** g_variant_dup_bytestring_array (GVariant* value, gsize* length);
GVariant* g_variant_new_maybe (const(GVariantType)* child_type, GVariant* child);
GVariant* g_variant_new_array (const(GVariantType)* child_type, GVariant** children, gsize n_children);
GVariant* g_variant_new_tuple (GVariant** children, gsize n_children);
GVariant* g_variant_new_dict_entry (GVariant* key, GVariant* value);
GVariant* g_variant_get_maybe (GVariant* value);
gsize g_variant_n_children (GVariant* value);
void g_variant_get_child (GVariant* value, gsize index_, const(gchar)* format_string, ...);
GVariant* g_variant_get_child_value (GVariant* value, gsize index_);
gboolean g_variant_lookup (GVariant* dictionary, const(gchar)* key, const(gchar)* format_string, ...);
GVariant* g_variant_lookup_value (GVariant* dictionary, const(gchar)* key, const(GVariantType)* expected_type);
gconstpointer g_variant_get_fixed_array (GVariant* value, gsize* n_elements, gsize element_size);
gsize g_variant_get_size (GVariant* value);
gconstpointer g_variant_get_data (GVariant* value);
void g_variant_store (GVariant* value, gpointer data);
gchar* g_variant_print (GVariant* value, gboolean type_annotate);
GString* g_variant_print_string (GVariant* value, GString* string, gboolean type_annotate);
guint g_variant_hash (gconstpointer value);
gboolean g_variant_equal (gconstpointer one, gconstpointer two);
GVariant* g_variant_get_normal_form (GVariant* value);
gboolean g_variant_is_normal_form (GVariant* value);
GVariant* g_variant_byteswap (GVariant* value);
GVariant* g_variant_new_from_data (const(GVariantType)* type, gconstpointer data, gsize size, gboolean trusted, GDestroyNotify notify, gpointer user_data);
GVariantIter* g_variant_iter_new (GVariant* value);
gsize g_variant_iter_init (GVariantIter* iter, GVariant* value);
GVariantIter* g_variant_iter_copy (GVariantIter* iter);
gsize g_variant_iter_n_children (GVariantIter* iter);
void g_variant_iter_free (GVariantIter* iter);
GVariant* g_variant_iter_next_value (GVariantIter* iter);
gboolean g_variant_iter_next (GVariantIter* iter, const(gchar)* format_string, ...);
gboolean g_variant_iter_loop (GVariantIter* iter, const(gchar)* format_string, ...);
GQuark g_variant_parser_get_error_quark ();
GVariantBuilder* g_variant_builder_new (const(GVariantType)* type);
void g_variant_builder_unref (GVariantBuilder* builder);
GVariantBuilder* g_variant_builder_ref (GVariantBuilder* builder);
void g_variant_builder_init (GVariantBuilder* builder, const(GVariantType)* type);
GVariant* g_variant_builder_end (GVariantBuilder* builder);
void g_variant_builder_clear (GVariantBuilder* builder);
void g_variant_builder_open (GVariantBuilder* builder, const(GVariantType)* type);
void g_variant_builder_close (GVariantBuilder* builder);
void g_variant_builder_add_value (GVariantBuilder* builder, GVariant* value);
void g_variant_builder_add (GVariantBuilder* builder, const(gchar)* format_string, ...);
void g_variant_builder_add_parsed (GVariantBuilder* builder, const(gchar)* format, ...);
GVariant* g_variant_new (const(gchar)* format_string, ...);
void g_variant_get (GVariant* value, const(gchar)* format_string, ...);
GVariant* g_variant_new_va (const(gchar)* format_string, const(gchar*)* endptr, va_list* app);
void g_variant_get_va (GVariant* value, const(gchar)* format_string, const(gchar*)* endptr, va_list* app);
GVariant* g_variant_parse (const(GVariantType)* type, const(gchar)* text, const(gchar)* limit, const(gchar*)* endptr, GError** error);
GVariant* g_variant_new_parsed (const(gchar)* format, ...);
GVariant* g_variant_new_parsed_va (const(gchar)* format, va_list* app);
gint g_variant_compare (gconstpointer one, gconstpointer two);