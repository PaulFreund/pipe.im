module derelict.glib.gstdio;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import std.stdio;
import std.file;

extern (C):

//alias statBuf GStatBuf;

int g_access (const(gchar)* filename, int mode);
int g_chdir (const(gchar)* path);
int g_unlink (const(gchar)* filename);
int g_rmdir (const(gchar)* filename);