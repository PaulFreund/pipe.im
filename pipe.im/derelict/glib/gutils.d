module derelict.glib.gutils;

import core.stdc.config;

extern (C):

alias _Anonymous_0 GUserDirectory;
alias _GDebugKey GDebugKey;
alias _Anonymous_1 GFormatSizeFlags;
alias void function () GVoidFunc;

enum _Anonymous_0
{
	G_USER_DIRECTORY_DESKTOP = 0,
	G_USER_DIRECTORY_DOCUMENTS = 1,
	G_USER_DIRECTORY_DOWNLOAD = 2,
	G_USER_DIRECTORY_MUSIC = 3,
	G_USER_DIRECTORY_PICTURES = 4,
	G_USER_DIRECTORY_PUBLIC_SHARE = 5,
	G_USER_DIRECTORY_TEMPLATES = 6,
	G_USER_DIRECTORY_VIDEOS = 7,
	G_USER_N_DIRECTORIES = 8
}

enum _Anonymous_1
{
	G_FORMAT_SIZE_DEFAULT = 0,
	G_FORMAT_SIZE_LONG_FORMAT = 1,
	G_FORMAT_SIZE_IEC_UNITS = 2
}

struct _GDebugKey
{
	const(gchar)* key;
	guint value;
}

const(gchar)* g_get_user_name ();
const(gchar)* g_get_real_name ();
const(gchar)* g_get_home_dir ();
const(gchar)* g_get_tmp_dir ();
const(gchar)* g_get_host_name ();
gchar* g_get_prgname ();
void g_set_prgname (const(gchar)* prgname);
const(gchar)* g_get_application_name ();
void g_set_application_name (const(gchar)* application_name);
void g_reload_user_special_dirs_cache ();
const(gchar)* g_get_user_data_dir ();
const(gchar)* g_get_user_config_dir ();
const(gchar)* g_get_user_cache_dir ();
const(gchar*)* g_get_system_data_dirs ();
const(gchar*)* g_get_system_config_dirs ();
const(gchar)* g_get_user_runtime_dir ();
const(gchar)* g_get_user_special_dir (GUserDirectory directory);
guint g_parse_debug_string (const(gchar)* string, const(GDebugKey)* keys, guint nkeys);
gint g_snprintf (gchar* string, gulong n, const(gchar)* format, ...);
gint g_vsnprintf (gchar* string, gulong n, const(gchar)* format, __va_list_tag* args);
void g_nullify_pointer (gpointer* nullify_location);
gchar* g_format_size_full (guint64 size, GFormatSizeFlags flags);
gchar* g_format_size (guint64 size);
gchar* g_format_size_for_display (goffset size);
void g_atexit (GVoidFunc func);
gchar* g_find_program_in_path (const(gchar)* program);
gint g_bit_nth_lsf (gulong mask, gint nth_bit);
gint g_bit_nth_msf (gulong mask, gint nth_bit);
guint g_bit_storage (gulong number);
gint g_bit_nth_lsf (gulong mask, gint nth_bit);
gint g_bit_nth_msf (gulong mask, gint nth_bit);
guint g_bit_storage (gulong number);