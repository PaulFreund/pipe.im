module derelict.glib.gvariant;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gvarianttype;
import derelict.glib.gstring;
import derelict.glib.gerror;
import derelict.glib.gquark;
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


alias da_g_variant_unref = void function(GVariant* value);																																																						/* da_g_variant_unref g_variant_unref; */
alias da_g_variant_ref = GVariant* function(GVariant* value);																																																						/* da_g_variant_ref g_variant_ref; */
alias da_g_variant_ref_sink = GVariant* function(GVariant* value);																																																						/* da_g_variant_ref_sink g_variant_ref_sink; */
alias da_g_variant_is_floating = gboolean function(GVariant* value);																																																						/* da_g_variant_is_floating g_variant_is_floating; */
alias da_g_variant_take_ref = GVariant* function(GVariant* value);																																																						/* da_g_variant_take_ref g_variant_take_ref; */
alias da_g_variant_get_type = const(GVariantType)* function(GVariant* value);																																																						/* da_g_variant_get_type g_variant_get_type; */
alias da_g_variant_get_type_string = const(gchar)* function(GVariant* value);																																																						/* da_g_variant_get_type_string g_variant_get_type_string; */
alias da_g_variant_is_of_type = gboolean function(GVariant* value, const(GVariantType)* type);																																																						/* da_g_variant_is_of_type g_variant_is_of_type; */
alias da_g_variant_is_container = gboolean function(GVariant* value);																																																						/* da_g_variant_is_container g_variant_is_container; */
alias da_g_variant_classify = GVariantClass function(GVariant* value);																																																						/* da_g_variant_classify g_variant_classify; */
alias da_g_variant_new_boolean = GVariant* function(gboolean value);																																																						/* da_g_variant_new_boolean g_variant_new_boolean; */
alias da_g_variant_new_byte = GVariant* function(guchar value);																																																						/* da_g_variant_new_byte g_variant_new_byte; */
alias da_g_variant_new_int16 = GVariant* function(gint16 value);																																																						/* da_g_variant_new_int16 g_variant_new_int16; */
alias da_g_variant_new_uint16 = GVariant* function(guint16 value);																																																						/* da_g_variant_new_uint16 g_variant_new_uint16; */
alias da_g_variant_new_int32 = GVariant* function(gint32 value);																																																						/* da_g_variant_new_int32 g_variant_new_int32; */
alias da_g_variant_new_uint32 = GVariant* function(guint32 value);																																																						/* da_g_variant_new_uint32 g_variant_new_uint32; */
alias da_g_variant_new_int64 = GVariant* function(gint64 value);																																																						/* da_g_variant_new_int64 g_variant_new_int64; */
alias da_g_variant_new_uint64 = GVariant* function(guint64 value);																																																						/* da_g_variant_new_uint64 g_variant_new_uint64; */
alias da_g_variant_new_handle = GVariant* function(gint32 value);																																																						/* da_g_variant_new_handle g_variant_new_handle; */
alias da_g_variant_new_double = GVariant* function(gdouble value);																																																						/* da_g_variant_new_double g_variant_new_double; */
alias da_g_variant_new_string = GVariant* function(const(gchar)* string);																																																						/* da_g_variant_new_string g_variant_new_string; */
alias da_g_variant_new_object_path = GVariant* function(const(gchar)* object_path);																																																						/* da_g_variant_new_object_path g_variant_new_object_path; */
alias da_g_variant_is_object_path = gboolean function(const(gchar)* string);																																																						/* da_g_variant_is_object_path g_variant_is_object_path; */
alias da_g_variant_new_signature = GVariant* function(const(gchar)* signature);																																																						/* da_g_variant_new_signature g_variant_new_signature; */
alias da_g_variant_is_signature = gboolean function(const(gchar)* string);																																																						/* da_g_variant_is_signature g_variant_is_signature; */
alias da_g_variant_new_variant = GVariant* function(GVariant* value);																																																						/* da_g_variant_new_variant g_variant_new_variant; */
alias da_g_variant_new_strv = GVariant* function(const(gchar*)* strv, gssize length);																																																						/* da_g_variant_new_strv g_variant_new_strv; */
alias da_g_variant_new_objv = GVariant* function(const(gchar*)* strv, gssize length);																																																						/* da_g_variant_new_objv g_variant_new_objv; */
alias da_g_variant_new_bytestring = GVariant* function(const(gchar)* string);																																																						/* da_g_variant_new_bytestring g_variant_new_bytestring; */
alias da_g_variant_new_bytestring_array = GVariant* function(const(gchar*)* strv, gssize length);																																																						/* da_g_variant_new_bytestring_array g_variant_new_bytestring_array; */
alias da_g_variant_new_fixed_array = GVariant* function(const(GVariantType)* element_type, gconstpointer elements, gsize n_elements, gsize element_size);																																																						/* da_g_variant_new_fixed_array g_variant_new_fixed_array; */
alias da_g_variant_get_boolean = gboolean function(GVariant* value);																																																						/* da_g_variant_get_boolean g_variant_get_boolean; */
alias da_g_variant_get_byte = guchar function(GVariant* value);																																																						/* da_g_variant_get_byte g_variant_get_byte; */
alias da_g_variant_get_int16 = gint16 function(GVariant* value);																																																						/* da_g_variant_get_int16 g_variant_get_int16; */
alias da_g_variant_get_uint16 = guint16 function(GVariant* value);																																																						/* da_g_variant_get_uint16 g_variant_get_uint16; */
alias da_g_variant_get_int32 = gint32 function(GVariant* value);																																																						/* da_g_variant_get_int32 g_variant_get_int32; */
alias da_g_variant_get_uint32 = guint32 function(GVariant* value);																																																						/* da_g_variant_get_uint32 g_variant_get_uint32; */
alias da_g_variant_get_int64 = gint64 function(GVariant* value);																																																						/* da_g_variant_get_int64 g_variant_get_int64; */
alias da_g_variant_get_uint64 = guint64 function(GVariant* value);																																																						/* da_g_variant_get_uint64 g_variant_get_uint64; */
alias da_g_variant_get_handle = gint32 function(GVariant* value);																																																						/* da_g_variant_get_handle g_variant_get_handle; */
alias da_g_variant_get_double = gdouble function(GVariant* value);																																																						/* da_g_variant_get_double g_variant_get_double; */
alias da_g_variant_get_variant = GVariant* function(GVariant* value);																																																						/* da_g_variant_get_variant g_variant_get_variant; */
alias da_g_variant_get_string = const(gchar)* function(GVariant* value, gsize* length);																																																						/* da_g_variant_get_string g_variant_get_string; */
alias da_g_variant_dup_string = gchar* function(GVariant* value, gsize* length);																																																						/* da_g_variant_dup_string g_variant_dup_string; */
alias da_g_variant_get_strv = const(gchar*)* function(GVariant* value, gsize* length);																																																						/* da_g_variant_get_strv g_variant_get_strv; */
alias da_g_variant_dup_strv = gchar** function(GVariant* value, gsize* length);																																																						/* da_g_variant_dup_strv g_variant_dup_strv; */
alias da_g_variant_get_objv = const(gchar*)* function(GVariant* value, gsize* length);																																																						/* da_g_variant_get_objv g_variant_get_objv; */
alias da_g_variant_dup_objv = gchar** function(GVariant* value, gsize* length);																																																						/* da_g_variant_dup_objv g_variant_dup_objv; */
alias da_g_variant_get_bytestring = const(gchar)* function(GVariant* value);																																																						/* da_g_variant_get_bytestring g_variant_get_bytestring; */
alias da_g_variant_dup_bytestring = gchar* function(GVariant* value, gsize* length);																																																						/* da_g_variant_dup_bytestring g_variant_dup_bytestring; */
alias da_g_variant_get_bytestring_array = const(gchar*)* function(GVariant* value, gsize* length);																																																						/* da_g_variant_get_bytestring_array g_variant_get_bytestring_array; */
alias da_g_variant_dup_bytestring_array = gchar** function(GVariant* value, gsize* length);																																																						/* da_g_variant_dup_bytestring_array g_variant_dup_bytestring_array; */
alias da_g_variant_new_maybe = GVariant* function(const(GVariantType)* child_type, GVariant* child);																																																						/* da_g_variant_new_maybe g_variant_new_maybe; */
alias da_g_variant_new_array = GVariant* function(const(GVariantType)* child_type, GVariant** children, gsize n_children);																																																						/* da_g_variant_new_array g_variant_new_array; */
alias da_g_variant_new_tuple = GVariant* function(GVariant** children, gsize n_children);																																																						/* da_g_variant_new_tuple g_variant_new_tuple; */
alias da_g_variant_new_dict_entry = GVariant* function(GVariant* key, GVariant* value);																																																						/* da_g_variant_new_dict_entry g_variant_new_dict_entry; */
alias da_g_variant_get_maybe = GVariant* function(GVariant* value);																																																						/* da_g_variant_get_maybe g_variant_get_maybe; */
alias da_g_variant_n_children = gsize function(GVariant* value);																																																						/* da_g_variant_n_children g_variant_n_children; */
alias da_g_variant_get_child = void function(GVariant* value, gsize index_, const(gchar)* format_string, ...);																																																						/* da_g_variant_get_child g_variant_get_child; */
alias da_g_variant_get_child_value = GVariant* function(GVariant* value, gsize index_);																																																						/* da_g_variant_get_child_value g_variant_get_child_value; */
alias da_g_variant_lookup = gboolean function(GVariant* dictionary, const(gchar)* key, const(gchar)* format_string, ...);																																																						/* da_g_variant_lookup g_variant_lookup; */
alias da_g_variant_lookup_value = GVariant* function(GVariant* dictionary, const(gchar)* key, const(GVariantType)* expected_type);																																																						/* da_g_variant_lookup_value g_variant_lookup_value; */
alias da_g_variant_get_fixed_array = gconstpointer function(GVariant* value, gsize* n_elements, gsize element_size);																																																						/* da_g_variant_get_fixed_array g_variant_get_fixed_array; */
alias da_g_variant_get_size = gsize function(GVariant* value);																																																						/* da_g_variant_get_size g_variant_get_size; */
alias da_g_variant_get_data = gconstpointer function(GVariant* value);																																																						/* da_g_variant_get_data g_variant_get_data; */
alias da_g_variant_store = void function(GVariant* value, gpointer data);																																																						/* da_g_variant_store g_variant_store; */
alias da_g_variant_print = gchar* function(GVariant* value, gboolean type_annotate);																																																						/* da_g_variant_print g_variant_print; */
alias da_g_variant_print_string = GString* function(GVariant* value, GString* string, gboolean type_annotate);																																																						/* da_g_variant_print_string g_variant_print_string; */
alias da_g_variant_hash = guint function(gconstpointer value);																																																						/* da_g_variant_hash g_variant_hash; */
alias da_g_variant_equal = gboolean function(gconstpointer one, gconstpointer two);																																																						/* da_g_variant_equal g_variant_equal; */
alias da_g_variant_get_normal_form = GVariant* function(GVariant* value);																																																						/* da_g_variant_get_normal_form g_variant_get_normal_form; */
alias da_g_variant_is_normal_form = gboolean function(GVariant* value);																																																						/* da_g_variant_is_normal_form g_variant_is_normal_form; */
alias da_g_variant_byteswap = GVariant* function(GVariant* value);																																																						/* da_g_variant_byteswap g_variant_byteswap; */
alias da_g_variant_new_from_data = GVariant* function(const(GVariantType)* type, gconstpointer data, gsize size, gboolean trusted, GDestroyNotify notify, gpointer user_data);																																																						/* da_g_variant_new_from_data g_variant_new_from_data; */
alias da_g_variant_iter_new = GVariantIter* function(GVariant* value);																																																						/* da_g_variant_iter_new g_variant_iter_new; */
alias da_g_variant_iter_init = gsize function(GVariantIter* iter, GVariant* value);																																																						/* da_g_variant_iter_init g_variant_iter_init; */
alias da_g_variant_iter_copy = GVariantIter* function(GVariantIter* iter);																																																						/* da_g_variant_iter_copy g_variant_iter_copy; */
alias da_g_variant_iter_n_children = gsize function(GVariantIter* iter);																																																						/* da_g_variant_iter_n_children g_variant_iter_n_children; */
alias da_g_variant_iter_free = void function(GVariantIter* iter);																																																						/* da_g_variant_iter_free g_variant_iter_free; */
alias da_g_variant_iter_next_value = GVariant* function(GVariantIter* iter);																																																						/* da_g_variant_iter_next_value g_variant_iter_next_value; */
alias da_g_variant_iter_next = gboolean function(GVariantIter* iter, const(gchar)* format_string, ...);																																																						/* da_g_variant_iter_next g_variant_iter_next; */
alias da_g_variant_iter_loop = gboolean function(GVariantIter* iter, const(gchar)* format_string, ...);																																																						/* da_g_variant_iter_loop g_variant_iter_loop; */
alias da_g_variant_parser_get_error_quark = GQuark function();																																																						/* da_g_variant_parser_get_error_quark g_variant_parser_get_error_quark; */
alias da_g_variant_builder_new = GVariantBuilder* function(const(GVariantType)* type);																																																						/* da_g_variant_builder_new g_variant_builder_new; */
alias da_g_variant_builder_unref = void function(GVariantBuilder* builder);																																																						/* da_g_variant_builder_unref g_variant_builder_unref; */
alias da_g_variant_builder_ref = GVariantBuilder* function(GVariantBuilder* builder);																																																						/* da_g_variant_builder_ref g_variant_builder_ref; */
alias da_g_variant_builder_init = void function(GVariantBuilder* builder, const(GVariantType)* type);																																																						/* da_g_variant_builder_init g_variant_builder_init; */
alias da_g_variant_builder_end = GVariant* function(GVariantBuilder* builder);																																																						/* da_g_variant_builder_end g_variant_builder_end; */
alias da_g_variant_builder_clear = void function(GVariantBuilder* builder);																																																						/* da_g_variant_builder_clear g_variant_builder_clear; */
alias da_g_variant_builder_open = void function(GVariantBuilder* builder, const(GVariantType)* type);																																																						/* da_g_variant_builder_open g_variant_builder_open; */
alias da_g_variant_builder_close = void function(GVariantBuilder* builder);																																																						/* da_g_variant_builder_close g_variant_builder_close; */
alias da_g_variant_builder_add_value = void function(GVariantBuilder* builder, GVariant* value);																																																						/* da_g_variant_builder_add_value g_variant_builder_add_value; */
alias da_g_variant_builder_add = void function(GVariantBuilder* builder, const(gchar)* format_string, ...);																																																						/* da_g_variant_builder_add g_variant_builder_add; */
alias da_g_variant_builder_add_parsed = void function(GVariantBuilder* builder, const(gchar)* format, ...);																																																						/* da_g_variant_builder_add_parsed g_variant_builder_add_parsed; */
alias da_g_variant_new = GVariant* function(const(gchar)* format_string, ...);																																																						/* da_g_variant_new g_variant_new; */
alias da_g_variant_get = void function(GVariant* value, const(gchar)* format_string, ...);																																																						/* da_g_variant_get g_variant_get; */
alias da_g_variant_new_va = GVariant* function(const(gchar)* format_string, const(gchar*)* endptr, va_list* app);																																																						/* da_g_variant_new_va g_variant_new_va; */
alias da_g_variant_get_va = void function(GVariant* value, const(gchar)* format_string, const(gchar*)* endptr, va_list* app);																																																						/* da_g_variant_get_va g_variant_get_va; */
alias da_g_variant_parse = GVariant* function(const(GVariantType)* type, const(gchar)* text, const(gchar)* limit, const(gchar*)* endptr, GError** error);																																																						/* da_g_variant_parse g_variant_parse; */
alias da_g_variant_new_parsed = GVariant* function(const(gchar)* format, ...);																																																						/* da_g_variant_new_parsed g_variant_new_parsed; */
alias da_g_variant_new_parsed_va = GVariant* function(const(gchar)* format, va_list* app);																																																						/* da_g_variant_new_parsed_va g_variant_new_parsed_va; */
alias da_g_variant_compare = gint function(gconstpointer one, gconstpointer two);																																																						/* da_g_variant_compare g_variant_compare; */
