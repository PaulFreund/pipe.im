module derelict.glib.gdir;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gerror;

extern (C):

alias _GDir GDir;

struct _GDir;


GDir* g_dir_open (const(gchar)* path, guint flags, GError** error);
const(gchar)* g_dir_read_name (GDir* dir);
void g_dir_rewind (GDir* dir);
void g_dir_close (GDir* dir);