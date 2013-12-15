extern (C):

alias _Anonymous_0 GModuleFlags;
alias _GModule GModule;
alias const(char)* function (_GModule*) GModuleCheckInit;
alias void function (_GModule*) GModuleUnload;

enum _Anonymous_0
{
	G_MODULE_BIND_LAZY = 1,
	G_MODULE_BIND_LOCAL = 2,
	G_MODULE_BIND_MASK = 3
}

struct _GModule;


gboolean g_module_supported ();
GModule* g_module_open (const(gchar)* file_name, GModuleFlags flags);
gboolean g_module_close (GModule* module_);
void g_module_make_resident (GModule* module_);
const(gchar)* g_module_error ();
gboolean g_module_symbol (GModule* module_, const(gchar)* symbol_name, gpointer* symbol);
const(gchar)* g_module_name (GModule* module_);
gchar* g_module_build_path (const(gchar)* directory, const(gchar)* module_name);