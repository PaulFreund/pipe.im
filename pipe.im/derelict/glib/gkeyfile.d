module derelict.glib.gkeyfile;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gerror;
import derelict.glib.gquark;
import core.stdc.config;

extern (C):

alias _Anonymous_0 GKeyFileError;
alias _GKeyFile GKeyFile;
alias _Anonymous_1 GKeyFileFlags;

enum _Anonymous_0
{
	G_KEY_FILE_ERROR_UNKNOWN_ENCODING = 0,
	G_KEY_FILE_ERROR_PARSE = 1,
	G_KEY_FILE_ERROR_NOT_FOUND = 2,
	G_KEY_FILE_ERROR_KEY_NOT_FOUND = 3,
	G_KEY_FILE_ERROR_GROUP_NOT_FOUND = 4,
	G_KEY_FILE_ERROR_INVALID_VALUE = 5
}

enum _Anonymous_1
{
	G_KEY_FILE_NONE = 0,
	G_KEY_FILE_KEEP_COMMENTS = 1,
	G_KEY_FILE_KEEP_TRANSLATIONS = 2
}

struct _GKeyFile;


alias da_g_key_file_error_quark = GQuark function();																																																						/* da_g_key_file_error_quark g_key_file_error_quark; */
alias da_g_key_file_new = GKeyFile* function();																																																						/* da_g_key_file_new g_key_file_new; */
alias da_g_key_file_ref = GKeyFile* function(GKeyFile* key_file);																																																						/* da_g_key_file_ref g_key_file_ref; */
alias da_g_key_file_unref = void function(GKeyFile* key_file);																																																						/* da_g_key_file_unref g_key_file_unref; */
alias da_g_key_file_free = void function(GKeyFile* key_file);																																																						/* da_g_key_file_free g_key_file_free; */
alias da_g_key_file_set_list_separator = void function(GKeyFile* key_file, gchar separator);																																																						/* da_g_key_file_set_list_separator g_key_file_set_list_separator; */
alias da_g_key_file_load_from_file = gboolean function(GKeyFile* key_file, const(gchar)* file, GKeyFileFlags flags, GError** error);																																																						/* da_g_key_file_load_from_file g_key_file_load_from_file; */
alias da_g_key_file_load_from_data = gboolean function(GKeyFile* key_file, const(gchar)* data, gsize length, GKeyFileFlags flags, GError** error);																																																						/* da_g_key_file_load_from_data g_key_file_load_from_data; */
alias da_g_key_file_load_from_dirs = gboolean function(GKeyFile* key_file, const(gchar)* file, const(gchar*)* search_dirs, gchar** full_path, GKeyFileFlags flags, GError** error);																																																						/* da_g_key_file_load_from_dirs g_key_file_load_from_dirs; */
alias da_g_key_file_load_from_data_dirs = gboolean function(GKeyFile* key_file, const(gchar)* file, gchar** full_path, GKeyFileFlags flags, GError** error);																																																						/* da_g_key_file_load_from_data_dirs g_key_file_load_from_data_dirs; */
alias da_g_key_file_to_data = gchar* function(GKeyFile* key_file, gsize* length, GError** error);																																																						/* da_g_key_file_to_data g_key_file_to_data; */
alias da_g_key_file_get_start_group = gchar* function(GKeyFile* key_file);																																																						/* da_g_key_file_get_start_group g_key_file_get_start_group; */
alias da_g_key_file_get_groups = gchar** function(GKeyFile* key_file, gsize* length);																																																						/* da_g_key_file_get_groups g_key_file_get_groups; */
alias da_g_key_file_get_keys = gchar** function(GKeyFile* key_file, const(gchar)* group_name, gsize* length, GError** error);																																																						/* da_g_key_file_get_keys g_key_file_get_keys; */
alias da_g_key_file_has_group = gboolean function(GKeyFile* key_file, const(gchar)* group_name);																																																						/* da_g_key_file_has_group g_key_file_has_group; */
alias da_g_key_file_has_key = gboolean function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_has_key g_key_file_has_key; */
alias da_g_key_file_get_value = gchar* function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_get_value g_key_file_get_value; */
alias da_g_key_file_set_value = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* value);																																																						/* da_g_key_file_set_value g_key_file_set_value; */
alias da_g_key_file_get_string = gchar* function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_get_string g_key_file_get_string; */
alias da_g_key_file_set_string = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* string);																																																						/* da_g_key_file_set_string g_key_file_set_string; */
alias da_g_key_file_get_locale_string = gchar* function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* locale, GError** error);																																																						/* da_g_key_file_get_locale_string g_key_file_get_locale_string; */
alias da_g_key_file_set_locale_string = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* locale, const(gchar)* string);																																																						/* da_g_key_file_set_locale_string g_key_file_set_locale_string; */
alias da_g_key_file_get_boolean = gboolean function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_get_boolean g_key_file_get_boolean; */
alias da_g_key_file_set_boolean = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gboolean value);																																																						/* da_g_key_file_set_boolean g_key_file_set_boolean; */
alias da_g_key_file_get_integer = gint function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_get_integer g_key_file_get_integer; */
alias da_g_key_file_set_integer = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gint value);																																																						/* da_g_key_file_set_integer g_key_file_set_integer; */
alias da_g_key_file_get_int64 = gint64 function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_get_int64 g_key_file_get_int64; */
alias da_g_key_file_set_int64 = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gint64 value);																																																						/* da_g_key_file_set_int64 g_key_file_set_int64; */
alias da_g_key_file_get_uint64 = guint64 function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_get_uint64 g_key_file_get_uint64; */
alias da_g_key_file_set_uint64 = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, guint64 value);																																																						/* da_g_key_file_set_uint64 g_key_file_set_uint64; */
alias da_g_key_file_get_double = gdouble function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_get_double g_key_file_get_double; */
alias da_g_key_file_set_double = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gdouble value);																																																						/* da_g_key_file_set_double g_key_file_set_double; */
alias da_g_key_file_get_string_list = gchar** function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gsize* length, GError** error);																																																						/* da_g_key_file_get_string_list g_key_file_get_string_list; */
alias da_g_key_file_set_string_list = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar*)* list, gsize length);																																																						/* da_g_key_file_set_string_list g_key_file_set_string_list; */
alias da_g_key_file_get_locale_string_list = gchar** function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* locale, gsize* length, GError** error);																																																						/* da_g_key_file_get_locale_string_list g_key_file_get_locale_string_list; */
alias da_g_key_file_set_locale_string_list = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* locale, const(gchar*)* list, gsize length);																																																						/* da_g_key_file_set_locale_string_list g_key_file_set_locale_string_list; */
alias da_g_key_file_get_boolean_list = gboolean* function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gsize* length, GError** error);																																																						/* da_g_key_file_get_boolean_list g_key_file_get_boolean_list; */
alias da_g_key_file_set_boolean_list = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gboolean* list, gsize length);																																																						/* da_g_key_file_set_boolean_list g_key_file_set_boolean_list; */
alias da_g_key_file_get_integer_list = gint* function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gsize* length, GError** error);																																																						/* da_g_key_file_get_integer_list g_key_file_get_integer_list; */
alias da_g_key_file_set_double_list = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gdouble* list, gsize length);																																																						/* da_g_key_file_set_double_list g_key_file_set_double_list; */
alias da_g_key_file_get_double_list = gdouble* function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gsize* length, GError** error);																																																						/* da_g_key_file_get_double_list g_key_file_get_double_list; */
alias da_g_key_file_set_integer_list = void function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gint* list, gsize length);																																																						/* da_g_key_file_set_integer_list g_key_file_set_integer_list; */
alias da_g_key_file_set_comment = gboolean function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* comment, GError** error);																																																						/* da_g_key_file_set_comment g_key_file_set_comment; */
alias da_g_key_file_get_comment = gchar* function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_get_comment g_key_file_get_comment; */
alias da_g_key_file_remove_comment = gboolean function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_remove_comment g_key_file_remove_comment; */
alias da_g_key_file_remove_key = gboolean function(GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);																																																						/* da_g_key_file_remove_key g_key_file_remove_key; */
alias da_g_key_file_remove_group = gboolean function(GKeyFile* key_file, const(gchar)* group_name, GError** error);																																																						/* da_g_key_file_remove_group g_key_file_remove_group; */
