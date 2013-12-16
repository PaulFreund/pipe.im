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


GQuark g_key_file_error_quark ();
GKeyFile* g_key_file_new ();
GKeyFile* g_key_file_ref (GKeyFile* key_file);
void g_key_file_unref (GKeyFile* key_file);
void g_key_file_free (GKeyFile* key_file);
void g_key_file_set_list_separator (GKeyFile* key_file, gchar separator);
gboolean g_key_file_load_from_file (GKeyFile* key_file, const(gchar)* file, GKeyFileFlags flags, GError** error);
gboolean g_key_file_load_from_data (GKeyFile* key_file, const(gchar)* data, gsize length, GKeyFileFlags flags, GError** error);
gboolean g_key_file_load_from_dirs (GKeyFile* key_file, const(gchar)* file, const(gchar*)* search_dirs, gchar** full_path, GKeyFileFlags flags, GError** error);
gboolean g_key_file_load_from_data_dirs (GKeyFile* key_file, const(gchar)* file, gchar** full_path, GKeyFileFlags flags, GError** error);
gchar* g_key_file_to_data (GKeyFile* key_file, gsize* length, GError** error);
gchar* g_key_file_get_start_group (GKeyFile* key_file);
gchar** g_key_file_get_groups (GKeyFile* key_file, gsize* length);
gchar** g_key_file_get_keys (GKeyFile* key_file, const(gchar)* group_name, gsize* length, GError** error);
gboolean g_key_file_has_group (GKeyFile* key_file, const(gchar)* group_name);
gboolean g_key_file_has_key (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
gchar* g_key_file_get_value (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
void g_key_file_set_value (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* value);
gchar* g_key_file_get_string (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
void g_key_file_set_string (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* string);
gchar* g_key_file_get_locale_string (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* locale, GError** error);
void g_key_file_set_locale_string (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* locale, const(gchar)* string);
gboolean g_key_file_get_boolean (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
void g_key_file_set_boolean (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gboolean value);
gint g_key_file_get_integer (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
void g_key_file_set_integer (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gint value);
gint64 g_key_file_get_int64 (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
void g_key_file_set_int64 (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gint64 value);
guint64 g_key_file_get_uint64 (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
void g_key_file_set_uint64 (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, guint64 value);
gdouble g_key_file_get_double (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
void g_key_file_set_double (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gdouble value);
gchar** g_key_file_get_string_list (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gsize* length, GError** error);
void g_key_file_set_string_list (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar*)* list, gsize length);
gchar** g_key_file_get_locale_string_list (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* locale, gsize* length, GError** error);
void g_key_file_set_locale_string_list (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* locale, const(gchar*)* list, gsize length);
gboolean* g_key_file_get_boolean_list (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gsize* length, GError** error);
void g_key_file_set_boolean_list (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gboolean* list, gsize length);
gint* g_key_file_get_integer_list (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gsize* length, GError** error);
void g_key_file_set_double_list (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gdouble* list, gsize length);
gdouble* g_key_file_get_double_list (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gsize* length, GError** error);
void g_key_file_set_integer_list (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, gint* list, gsize length);
gboolean g_key_file_set_comment (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, const(gchar)* comment, GError** error);
gchar* g_key_file_get_comment (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
gboolean g_key_file_remove_comment (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
gboolean g_key_file_remove_key (GKeyFile* key_file, const(gchar)* group_name, const(gchar)* key, GError** error);
gboolean g_key_file_remove_group (GKeyFile* key_file, const(gchar)* group_name, GError** error);