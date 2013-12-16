module derelict.glib.gmappedfile;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gerror;
import core.stdc.config;

extern (C):

alias _GMappedFile GMappedFile;

struct _GMappedFile;


alias da_g_mapped_file_new = GMappedFile* function(const(gchar)* filename, gboolean writable, GError** error);																																																						/* da_g_mapped_file_new g_mapped_file_new; */
alias da_g_mapped_file_new_from_fd = GMappedFile* function(gint fd, gboolean writable, GError** error);																																																						/* da_g_mapped_file_new_from_fd g_mapped_file_new_from_fd; */
alias da_g_mapped_file_get_length = gsize function(GMappedFile* file);																																																						/* da_g_mapped_file_get_length g_mapped_file_get_length; */
alias da_g_mapped_file_get_contents = gchar* function(GMappedFile* file);																																																						/* da_g_mapped_file_get_contents g_mapped_file_get_contents; */
alias da_g_mapped_file_ref = GMappedFile* function(GMappedFile* file);																																																						/* da_g_mapped_file_ref g_mapped_file_ref; */
alias da_g_mapped_file_unref = void function(GMappedFile* file);																																																						/* da_g_mapped_file_unref g_mapped_file_unref; */
alias da_g_mapped_file_free = void function(GMappedFile* file);																																																						/* da_g_mapped_file_free g_mapped_file_free; */
