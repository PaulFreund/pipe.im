/*

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/ 

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

extern( C ) nothrow 
{
    alias da_g_get_user_name = const(gchar)* function();																
    alias da_g_get_real_name = const(gchar)* function();																
    alias da_g_get_home_dir = const(gchar)* function();																	
    alias da_g_get_tmp_dir = const(gchar)* function();																	
    alias da_g_get_host_name = const(gchar)* function();																
    alias da_g_get_prgname = gchar* function();																			
    alias da_g_set_prgname = void function(const(gchar)* prgname);														
    alias da_g_get_application_name = const(gchar)* function();															
    alias da_g_set_application_name = void function(const(gchar)* application_name);									
    alias da_g_reload_user_special_dirs_cache = void function();														
    alias da_g_get_user_data_dir = const(gchar)* function();															
    alias da_g_get_user_config_dir = const(gchar)* function();															
    alias da_g_get_user_cache_dir = const(gchar)* function();															
    alias da_g_get_system_data_dirs = const(gchar*)* function();														
    alias da_g_get_system_config_dirs = const(gchar*)* function();														
    alias da_g_get_user_runtime_dir = const(gchar)* function();															
    alias da_g_get_user_special_dir = const(gchar)* function(GUserDirectory directory);									
    alias da_g_parse_debug_string = guint function(const(gchar)* string, const(GDebugKey)* keys, guint nkeys);			
    alias da_g_snprintf = gint function(gchar* string, gulong n, const(gchar)* format, ...);							
    alias da_g_vsnprintf = gint function(gchar* string, gulong n, const(gchar)* format, va_list args);					
    alias da_g_nullify_pointer = void function(gpointer* nullify_location);												
    alias da_g_format_size_full = gchar* function(guint64 size, GFormatSizeFlags flags);								
    alias da_g_format_size = gchar* function(guint64 size);																
    alias da_g_format_size_for_display = gchar* function(goffset size);													
    alias da_g_atexit = void function(GVoidFunc func);																	
    alias da_g_find_program_in_path = gchar* function(const(gchar)* program);											
    alias da_g_bit_nth_lsf = gint function(gulong mask, gint nth_bit);													
    alias da_g_bit_nth_msf = gint function(gulong mask, gint nth_bit);													
    alias da_g_bit_storage = guint function(gulong number);		
}

__gshared
{
    da_g_get_user_name g_get_user_name; 
    da_g_get_real_name g_get_real_name; 
    da_g_get_home_dir g_get_home_dir; 
    da_g_get_tmp_dir g_get_tmp_dir; 
    da_g_get_host_name g_get_host_name; 
    da_g_get_prgname g_get_prgname; 
    da_g_set_prgname g_set_prgname; 
    da_g_get_application_name g_get_application_name; 
    da_g_set_application_name g_set_application_name; 
    da_g_reload_user_special_dirs_cache g_reload_user_special_dirs_cache; 
    da_g_get_user_data_dir g_get_user_data_dir; 
    da_g_get_user_config_dir g_get_user_config_dir; 
    da_g_get_user_cache_dir g_get_user_cache_dir; 
    da_g_get_system_data_dirs g_get_system_data_dirs; 
    da_g_get_system_config_dirs g_get_system_config_dirs; 
    da_g_get_user_runtime_dir g_get_user_runtime_dir; 
    da_g_get_user_special_dir g_get_user_special_dir; 
    da_g_parse_debug_string g_parse_debug_string; 
    da_g_snprintf g_snprintf; 
    da_g_vsnprintf g_vsnprintf; 
    da_g_nullify_pointer g_nullify_pointer; 
    da_g_format_size_full g_format_size_full; 
    da_g_format_size g_format_size; 
    da_g_format_size_for_display g_format_size_for_display; 
    da_g_atexit g_atexit; 
    da_g_find_program_in_path g_find_program_in_path; 
    da_g_bit_nth_lsf g_bit_nth_lsf; 
    da_g_bit_nth_msf g_bit_nth_msf; 
    da_g_bit_storage g_bit_storage;
}