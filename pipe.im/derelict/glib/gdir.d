module derelict.glib.gdir;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gerror;

extern (C):

alias _GDir GDir;

struct _GDir;


alias da_g_dir_open = GDir* function(const(gchar)* path, guint flags, GError** error);																																																						/* da_g_dir_open g_dir_open; */
alias da_g_dir_read_name = const(gchar)* function(GDir* dir);																																																						/* da_g_dir_read_name g_dir_read_name; */
alias da_g_dir_rewind = void function(GDir* dir);																																																						/* da_g_dir_rewind g_dir_rewind; */
alias da_g_dir_close = void function(GDir* dir);																																																						/* da_g_dir_close g_dir_close; */
