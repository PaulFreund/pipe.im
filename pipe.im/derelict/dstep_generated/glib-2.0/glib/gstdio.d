extern (C):

alias stat GStatBuf;

int g_access (const(gchar)* filename, int mode);
int g_chdir (const(gchar)* path);
int g_unlink (const(gchar)* filename);
int g_rmdir (const(gchar)* filename);