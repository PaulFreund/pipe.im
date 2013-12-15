module derelict.glib.gfileutils;

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

GQuark g_file_error_quark ();
GFileError g_file_error_from_errno (gint err_no);
gboolean g_file_test (const(gchar)* filename, GFileTest test);
gboolean g_file_get_contents (const(gchar)* filename, gchar** contents, gsize* length, GError** error);
gboolean g_file_set_contents (const(gchar)* filename, const(gchar)* contents, gssize length, GError** error);
gchar* g_file_read_link (const(gchar)* filename, GError** error);
gchar* g_mkdtemp (gchar* tmpl);
gchar* g_mkdtemp_full (gchar* tmpl, gint mode);
gint g_mkstemp (gchar* tmpl);
gint g_mkstemp_full (gchar* tmpl, gint flags, gint mode);
gint g_file_open_tmp (const(gchar)* tmpl, gchar** name_used, GError** error);
gchar* g_dir_make_tmp (const(gchar)* tmpl, GError** error);
gchar* g_build_path (const(gchar)* separator, const(gchar)* first_element, ...);
gchar* g_build_pathv (const(gchar)* separator, gchar** args);
gchar* g_build_filename (const(gchar)* first_element, ...);
gchar* g_build_filenamev (gchar** args);
gint g_mkdir_with_parents (const(gchar)* pathname, gint mode);
gboolean g_path_is_absolute (const(gchar)* file_name);
const(gchar)* g_path_skip_root (const(gchar)* file_name);
const(gchar)* g_basename (const(gchar)* file_name);
gchar* g_get_current_dir ();
gchar* g_path_get_basename (const(gchar)* file_name);
gchar* g_path_get_dirname (const(gchar)* file_name);