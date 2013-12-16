module derelict.glib.gfileutils;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gquark;
import derelict.glib.gerror;
import core.stdc.config;

extern (C):

alias _Anonymous_0 GFileError;
alias _Anonymous_1 GFileTest;

enum _Anonymous_0
{
	G_FILE_ERROR_EXIST = 0,
	G_FILE_ERROR_ISDIR = 1,
	G_FILE_ERROR_ACCES = 2,
	G_FILE_ERROR_NAMETOOLONG = 3,
	G_FILE_ERROR_NOENT = 4,
	G_FILE_ERROR_NOTDIR = 5,
	G_FILE_ERROR_NXIO = 6,
	G_FILE_ERROR_NODEV = 7,
	G_FILE_ERROR_ROFS = 8,
	G_FILE_ERROR_TXTBSY = 9,
	G_FILE_ERROR_FAULT = 10,
	G_FILE_ERROR_LOOP = 11,
	G_FILE_ERROR_NOSPC = 12,
	G_FILE_ERROR_NOMEM = 13,
	G_FILE_ERROR_MFILE = 14,
	G_FILE_ERROR_NFILE = 15,
	G_FILE_ERROR_BADF = 16,
	G_FILE_ERROR_INVAL = 17,
	G_FILE_ERROR_PIPE = 18,
	G_FILE_ERROR_AGAIN = 19,
	G_FILE_ERROR_INTR = 20,
	G_FILE_ERROR_IO = 21,
	G_FILE_ERROR_PERM = 22,
	G_FILE_ERROR_NOSYS = 23,
	G_FILE_ERROR_FAILED = 24
}

enum _Anonymous_1
{
	G_FILE_TEST_IS_REGULAR = 1,
	G_FILE_TEST_IS_SYMLINK = 2,
	G_FILE_TEST_IS_DIR = 4,
	G_FILE_TEST_IS_EXECUTABLE = 8,
	G_FILE_TEST_EXISTS = 16
}

alias da_g_file_error_quark = GQuark function();																																																						/* da_g_file_error_quark g_file_error_quark; */
alias da_g_file_error_from_errno = GFileError function(gint err_no);																																																						/* da_g_file_error_from_errno g_file_error_from_errno; */
alias da_g_file_test = gboolean function(const(gchar)* filename, GFileTest test);																																																						/* da_g_file_test g_file_test; */
alias da_g_file_get_contents = gboolean function(const(gchar)* filename, gchar** contents, gsize* length, GError** error);																																																						/* da_g_file_get_contents g_file_get_contents; */
alias da_g_file_set_contents = gboolean function(const(gchar)* filename, const(gchar)* contents, gssize length, GError** error);																																																						/* da_g_file_set_contents g_file_set_contents; */
alias da_g_file_read_link = gchar* function(const(gchar)* filename, GError** error);																																																						/* da_g_file_read_link g_file_read_link; */
alias da_g_mkdtemp = gchar* function(gchar* tmpl);																																																						/* da_g_mkdtemp g_mkdtemp; */
alias da_g_mkdtemp_full = gchar* function(gchar* tmpl, gint mode);																																																						/* da_g_mkdtemp_full g_mkdtemp_full; */
alias da_g_mkstemp = gint function(gchar* tmpl);																																																						/* da_g_mkstemp g_mkstemp; */
alias da_g_mkstemp_full = gint function(gchar* tmpl, gint flags, gint mode);																																																						/* da_g_mkstemp_full g_mkstemp_full; */
alias da_g_file_open_tmp = gint function(const(gchar)* tmpl, gchar** name_used, GError** error);																																																						/* da_g_file_open_tmp g_file_open_tmp; */
alias da_g_dir_make_tmp = gchar* function(const(gchar)* tmpl, GError** error);																																																						/* da_g_dir_make_tmp g_dir_make_tmp; */
alias da_g_build_path = gchar* function(const(gchar)* separator, const(gchar)* first_element, ...);																																																						/* da_g_build_path g_build_path; */
alias da_g_build_pathv = gchar* function(const(gchar)* separator, gchar** args);																																																						/* da_g_build_pathv g_build_pathv; */
alias da_g_build_filename = gchar* function(const(gchar)* first_element, ...);																																																						/* da_g_build_filename g_build_filename; */
alias da_g_build_filenamev = gchar* function(gchar** args);																																																						/* da_g_build_filenamev g_build_filenamev; */
alias da_g_mkdir_with_parents = gint function(const(gchar)* pathname, gint mode);																																																						/* da_g_mkdir_with_parents g_mkdir_with_parents; */
alias da_g_path_is_absolute = gboolean function(const(gchar)* file_name);																																																						/* da_g_path_is_absolute g_path_is_absolute; */
alias da_g_path_skip_root = const(gchar)* function(const(gchar)* file_name);																																																						/* da_g_path_skip_root g_path_skip_root; */
alias da_g_basename = const(gchar)* function(const(gchar)* file_name);																																																						/* da_g_basename g_basename; */
alias da_g_get_current_dir = gchar* function();																																																						/* da_g_get_current_dir g_get_current_dir; */
alias da_g_path_get_basename = gchar* function(const(gchar)* file_name);																																																						/* da_g_path_get_basename g_path_get_basename; */
alias da_g_path_get_dirname = gchar* function(const(gchar)* file_name);																																																						/* da_g_path_get_dirname g_path_get_dirname; */
