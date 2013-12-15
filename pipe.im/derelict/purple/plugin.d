module derelict.purple.plugin;

import core.stdc.config;

extern (C):

alias _PurplePlugin PurplePlugin;
alias _PurplePluginInfo PurplePluginInfo;
alias _PurplePluginUiInfo PurplePluginUiInfo;
alias _PurplePluginLoaderInfo PurplePluginLoaderInfo;
alias _PurplePluginAction PurplePluginAction;
alias int PurplePluginPriority;
alias _Anonymous_0 PurplePluginType;

enum _Anonymous_0
{
	PURPLE_PLUGIN_UNKNOWN = -1,
	PURPLE_PLUGIN_STANDARD = 0,
	PURPLE_PLUGIN_LOADER = 1,
	PURPLE_PLUGIN_PROTOCOL = 2
}

struct _PurplePluginInfo
{
	uint magic;
	uint major_version;
	uint minor_version;
	PurplePluginType type;
	char* ui_requirement;
	c_ulong flags;
	GList* dependencies;
	PurplePluginPriority priority;
	char* id;
	char* name;
	char* version_;
	char* summary;
	char* description;
	char* author;
	char* homepage;
	gboolean function (PurplePlugin*) load;
	gboolean function (PurplePlugin*) unload;
	void function (PurplePlugin*) destroy;
	void* ui_info;
	void* extra_info;
	PurplePluginUiInfo* prefs_info;
	GList* function (PurplePlugin*, gpointer) actions;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurplePluginLoaderInfo
{
	GList* exts;
	gboolean function (PurplePlugin*) probe;
	gboolean function (PurplePlugin*) load;
	gboolean function (PurplePlugin*) unload;
	void function (PurplePlugin*) destroy;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurplePlugin
{
	gboolean native_plugin;
	gboolean loaded;
	void* handle;
	char* path;
	PurplePluginInfo* info;
	char* error;
	void* ipc_data;
	void* extra;
	gboolean unloadable;
	GList* dependent_plugins;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurplePluginUiInfo
{
	PurplePluginPrefFrame* function (PurplePlugin*) get_plugin_pref_frame;
	int page_num;
	PurplePluginPrefFrame* frame;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurplePluginAction
{
	char* label;
	void function (PurplePluginAction*) callback;
	PurplePlugin* plugin;
	gpointer context;
	gpointer user_data;
}

PurplePlugin* purple_plugin_new (gboolean native, const(char)* path);
PurplePlugin* purple_plugin_probe (const(char)* filename);
gboolean purple_plugin_register (PurplePlugin* plugin);
gboolean purple_plugin_load (PurplePlugin* plugin);
gboolean purple_plugin_unload (PurplePlugin* plugin);
void purple_plugin_disable (PurplePlugin* plugin);
gboolean purple_plugin_reload (PurplePlugin* plugin);
void purple_plugin_destroy (PurplePlugin* plugin);
gboolean purple_plugin_is_loaded (const(PurplePlugin)* plugin);
gboolean purple_plugin_is_unloadable (const(PurplePlugin)* plugin);
const(gchar)* purple_plugin_get_id (const(PurplePlugin)* plugin);
const(gchar)* purple_plugin_get_name (const(PurplePlugin)* plugin);
const(gchar)* purple_plugin_get_version (const(PurplePlugin)* plugin);
const(gchar)* purple_plugin_get_summary (const(PurplePlugin)* plugin);
const(gchar)* purple_plugin_get_description (const(PurplePlugin)* plugin);
const(gchar)* purple_plugin_get_author (const(PurplePlugin)* plugin);
const(gchar)* purple_plugin_get_homepage (const(PurplePlugin)* plugin);
gboolean purple_plugin_ipc_register (PurplePlugin* plugin, const(char)* command, PurpleCallback func, PurpleSignalMarshalFunc marshal, PurpleValue* ret_value, int num_params, ...);
void purple_plugin_ipc_unregister (PurplePlugin* plugin, const(char)* command);
void purple_plugin_ipc_unregister_all (PurplePlugin* plugin);
gboolean purple_plugin_ipc_get_params (PurplePlugin* plugin, const(char)* command, PurpleValue** ret_value, int* num_params, PurpleValue*** params);
void* purple_plugin_ipc_call (PurplePlugin* plugin, const(char)* command, gboolean* ok, ...);
void purple_plugins_add_search_path (const(char)* path);
GList* purple_plugins_get_search_paths ();
void purple_plugins_unload_all ();
void purple_plugins_unload (PurplePluginType type);
void purple_plugins_destroy_all ();
void purple_plugins_save_loaded (const(char)* key);
void purple_plugins_load_saved (const(char)* key);
void purple_plugins_probe (const(char)* ext);
gboolean purple_plugins_enabled ();
void purple_plugins_register_probe_notify_cb (void function (void*) func, void* data);
void purple_plugins_unregister_probe_notify_cb (void function (void*) func);
void purple_plugins_register_load_notify_cb (void function (PurplePlugin*, void*) func, void* data);
void purple_plugins_unregister_load_notify_cb (void function (PurplePlugin*, void*) func);
void purple_plugins_register_unload_notify_cb (void function (PurplePlugin*, void*) func, void* data);
void purple_plugins_unregister_unload_notify_cb (void function (PurplePlugin*, void*) func);
PurplePlugin* purple_plugins_find_with_name (const(char)* name);
PurplePlugin* purple_plugins_find_with_filename (const(char)* filename);
PurplePlugin* purple_plugins_find_with_basename (const(char)* basename);
PurplePlugin* purple_plugins_find_with_id (const(char)* id);
GList* purple_plugins_get_loaded ();
GList* purple_plugins_get_protocols ();
GList* purple_plugins_get_all ();
void* purple_plugins_get_handle ();
void purple_plugins_init ();
void purple_plugins_uninit ();
PurplePluginAction* purple_plugin_action_new (const(char)* label, void function (PurplePluginAction*) callback);
void purple_plugin_action_free (PurplePluginAction* action);