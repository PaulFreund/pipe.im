module derelict.glib.gstdio;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import std.stdio;
import std.file;

extern (C):

//alias statBuf GStatBuf;

alias da_g_access = int function(const(gchar)* filename, int mode);																																																						/* da_g_access g_access; */
alias da_g_chdir = int function(const(gchar)* path);																																																						/* da_g_chdir g_chdir; */
alias da_g_unlink = int function(const(gchar)* filename);																																																						/* da_g_unlink g_unlink; */
alias da_g_rmdir = int function(const(gchar)* filename);																																																						/* da_g_rmdir g_rmdir; */
