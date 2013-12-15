import core.stdc.config;

extern (C):

alias _GMappedFile GMappedFile;

struct _GMappedFile;


GMappedFile* g_mapped_file_new (const(gchar)* filename, gboolean writable, GError** error);
GMappedFile* g_mapped_file_new_from_fd (gint fd, gboolean writable, GError** error);
gsize g_mapped_file_get_length (GMappedFile* file);
gchar* g_mapped_file_get_contents (GMappedFile* file);
GMappedFile* g_mapped_file_ref (GMappedFile* file);
void g_mapped_file_unref (GMappedFile* file);
void g_mapped_file_free (GMappedFile* file);