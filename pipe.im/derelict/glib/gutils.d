module derelict.glib.gutils;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;
import std.c.stdarg;

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

alias da_g_get_user_name = const(gchar)* function();																																																						/* da_g_get_user_name g_get_user_name; */
alias da_g_get_real_name = const(gchar)* function();																																																						/* da_g_get_real_name g_get_real_name; */
alias da_g_get_home_dir = const(gchar)* function();																																																						/* da_g_get_home_dir g_get_home_dir; */
alias da_g_get_tmp_dir = const(gchar)* function();																																																						/* da_g_get_tmp_dir g_get_tmp_dir; */
alias da_g_get_host_name = const(gchar)* function();																																																						/* da_g_get_host_name g_get_host_name; */
alias da_g_get_prgname = gchar* function();																																																						/* da_g_get_prgname g_get_prgname; */
alias da_g_set_prgname = void function(const(gchar)* prgname);																																																						/* da_g_set_prgname g_set_prgname; */
alias da_g_get_application_name = const(gchar)* function();																																																						/* da_g_get_application_name g_get_application_name; */
alias da_g_set_application_name = void function(const(gchar)* application_name);																																																						/* da_g_set_application_name g_set_application_name; */
alias da_g_reload_user_special_dirs_cache = void function();																																																						/* da_g_reload_user_special_dirs_cache g_reload_user_special_dirs_cache; */
alias da_g_get_user_data_dir = const(gchar)* function();																																																						/* da_g_get_user_data_dir g_get_user_data_dir; */
alias da_g_get_user_config_dir = const(gchar)* function();																																																						/* da_g_get_user_config_dir g_get_user_config_dir; */
alias da_g_get_user_cache_dir = const(gchar)* function();																																																						/* da_g_get_user_cache_dir g_get_user_cache_dir; */
alias da_g_get_system_data_dirs = const(gchar*)* function();																																																						/* da_g_get_system_data_dirs g_get_system_data_dirs; */
alias da_g_get_system_config_dirs = const(gchar*)* function();																																																						/* da_g_get_system_config_dirs g_get_system_config_dirs; */
alias da_g_get_user_runtime_dir = const(gchar)* function();																																																						/* da_g_get_user_runtime_dir g_get_user_runtime_dir; */
alias da_g_get_user_special_dir = const(gchar)* function(GUserDirectory directory);																																																						/* da_g_get_user_special_dir g_get_user_special_dir; */
alias da_g_parse_debug_string = guint function(const(gchar)* string, const(GDebugKey)* keys, guint nkeys);																																																						/* da_g_parse_debug_string g_parse_debug_string; */
alias da_g_snprintf = gint function(gchar* string, gulong n, const(gchar)* format, ...);																																																						/* da_g_snprintf g_snprintf; */
alias da_g_vsnprintf = gint function(gchar* string, gulong n, const(gchar)* format, va_list args);																																																						/* da_g_vsnprintf g_vsnprintf; */
alias da_g_nullify_pointer = void function(gpointer* nullify_location);																																																						/* da_g_nullify_pointer g_nullify_pointer; */
alias da_g_format_size_full = gchar* function(guint64 size, GFormatSizeFlags flags);																																																						/* da_g_format_size_full g_format_size_full; */
alias da_g_format_size = gchar* function(guint64 size);																																																						/* da_g_format_size g_format_size; */
alias da_g_format_size_for_display = gchar* function(goffset size);																																																						/* da_g_format_size_for_display g_format_size_for_display; */
alias da_g_atexit = void function(GVoidFunc func);																																																						/* da_g_atexit g_atexit; */
alias da_g_find_program_in_path = gchar* function(const(gchar)* program);																																																						/* da_g_find_program_in_path g_find_program_in_path; */
alias da_g_bit_nth_lsf = gint function(gulong mask, gint nth_bit);																																																						/* da_g_bit_nth_lsf g_bit_nth_lsf; */
alias da_g_bit_nth_msf = gint function(gulong mask, gint nth_bit);																																																						/* da_g_bit_nth_msf g_bit_nth_msf; */
alias da_g_bit_storage = guint function(gulong number);																																																						/* da_g_bit_storage g_bit_storage; */
