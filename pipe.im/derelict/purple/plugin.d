module derelict.purple.plugin;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.pluginpref;
import derelict.purple.signals;
import derelict.purple.value;
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

alias da_purple_plugin_new = PurplePlugin* function(gboolean native, const(char)* path);																																																						/* da_purple_plugin_new purple_plugin_new; */
alias da_purple_plugin_probe = PurplePlugin* function(const(char)* filename);																																																						/* da_purple_plugin_probe purple_plugin_probe; */
alias da_purple_plugin_register = gboolean function(PurplePlugin* plugin);																																																						/* da_purple_plugin_register purple_plugin_register; */
alias da_purple_plugin_load = gboolean function(PurplePlugin* plugin);																																																						/* da_purple_plugin_load purple_plugin_load; */
alias da_purple_plugin_unload = gboolean function(PurplePlugin* plugin);																																																						/* da_purple_plugin_unload purple_plugin_unload; */
alias da_purple_plugin_disable = void function(PurplePlugin* plugin);																																																						/* da_purple_plugin_disable purple_plugin_disable; */
alias da_purple_plugin_reload = gboolean function(PurplePlugin* plugin);																																																						/* da_purple_plugin_reload purple_plugin_reload; */
alias da_purple_plugin_destroy = void function(PurplePlugin* plugin);																																																						/* da_purple_plugin_destroy purple_plugin_destroy; */
alias da_purple_plugin_is_loaded = gboolean function(const(PurplePlugin)* plugin);																																																						/* da_purple_plugin_is_loaded purple_plugin_is_loaded; */
alias da_purple_plugin_is_unloadable = gboolean function(const(PurplePlugin)* plugin);																																																						/* da_purple_plugin_is_unloadable purple_plugin_is_unloadable; */
alias da_purple_plugin_get_id = const(gchar)* function(const(PurplePlugin)* plugin);																																																						/* da_purple_plugin_get_id purple_plugin_get_id; */
alias da_purple_plugin_get_name = const(gchar)* function(const(PurplePlugin)* plugin);																																																						/* da_purple_plugin_get_name purple_plugin_get_name; */
alias da_purple_plugin_get_version = const(gchar)* function(const(PurplePlugin)* plugin);																																																						/* da_purple_plugin_get_version purple_plugin_get_version; */
alias da_purple_plugin_get_summary = const(gchar)* function(const(PurplePlugin)* plugin);																																																						/* da_purple_plugin_get_summary purple_plugin_get_summary; */
alias da_purple_plugin_get_description = const(gchar)* function(const(PurplePlugin)* plugin);																																																						/* da_purple_plugin_get_description purple_plugin_get_description; */
alias da_purple_plugin_get_author = const(gchar)* function(const(PurplePlugin)* plugin);																																																						/* da_purple_plugin_get_author purple_plugin_get_author; */
alias da_purple_plugin_get_homepage = const(gchar)* function(const(PurplePlugin)* plugin);																																																						/* da_purple_plugin_get_homepage purple_plugin_get_homepage; */
alias da_purple_plugin_ipc_register = gboolean function(PurplePlugin* plugin, const(char)* command, PurpleCallback func, PurpleSignalMarshalFunc marshal, PurpleValue* ret_value, int num_params, ...);																																																						/* da_purple_plugin_ipc_register purple_plugin_ipc_register; */
alias da_purple_plugin_ipc_unregister = void function(PurplePlugin* plugin, const(char)* command);																																																						/* da_purple_plugin_ipc_unregister purple_plugin_ipc_unregister; */
alias da_purple_plugin_ipc_unregister_all = void function(PurplePlugin* plugin);																																																						/* da_purple_plugin_ipc_unregister_all purple_plugin_ipc_unregister_all; */
alias da_purple_plugin_ipc_get_params = gboolean function(PurplePlugin* plugin, const(char)* command, PurpleValue** ret_value, int* num_params, PurpleValue*** params);																																																						/* da_purple_plugin_ipc_get_params purple_plugin_ipc_get_params; */
alias da_purple_plugin_ipc_call = void* function(PurplePlugin* plugin, const(char)* command, gboolean* ok, ...);																																																						/* da_purple_plugin_ipc_call purple_plugin_ipc_call; */
alias da_purple_plugins_add_search_path = void function(const(char)* path);																																																						/* da_purple_plugins_add_search_path purple_plugins_add_search_path; */
alias da_purple_plugins_get_search_paths = GList* function();																																																						/* da_purple_plugins_get_search_paths purple_plugins_get_search_paths; */
alias da_purple_plugins_unload_all = void function();																																																						/* da_purple_plugins_unload_all purple_plugins_unload_all; */
alias da_purple_plugins_unload = void function(PurplePluginType type);																																																						/* da_purple_plugins_unload purple_plugins_unload; */
alias da_purple_plugins_destroy_all = void function();																																																						/* da_purple_plugins_destroy_all purple_plugins_destroy_all; */
alias da_purple_plugins_save_loaded = void function(const(char)* key);																																																						/* da_purple_plugins_save_loaded purple_plugins_save_loaded; */
alias da_purple_plugins_load_saved = void function(const(char)* key);																																																						/* da_purple_plugins_load_saved purple_plugins_load_saved; */
alias da_purple_plugins_probe = void function(const(char)* ext);																																																						/* da_purple_plugins_probe purple_plugins_probe; */
alias da_purple_plugins_enabled = gboolean function();																																																						/* da_purple_plugins_enabled purple_plugins_enabled; */
alias da_purple_plugins_register_probe_notify_cb = void function(void function (void*) func, void* data);																																																						/* da_purple_plugins_register_probe_notify_cb purple_plugins_register_probe_notify_cb; */
alias da_purple_plugins_unregister_probe_notify_cb = void function(void function (void*) func);																																																						/* da_purple_plugins_unregister_probe_notify_cb purple_plugins_unregister_probe_notify_cb; */
alias da_purple_plugins_register_load_notify_cb = void function(void function (PurplePlugin*, void*) func, void* data);																																																						/* da_purple_plugins_register_load_notify_cb purple_plugins_register_load_notify_cb; */
alias da_purple_plugins_unregister_load_notify_cb = void function(void function (PurplePlugin*, void*) func);																																																						/* da_purple_plugins_unregister_load_notify_cb purple_plugins_unregister_load_notify_cb; */
alias da_purple_plugins_register_unload_notify_cb = void function(void function (PurplePlugin*, void*) func, void* data);																																																						/* da_purple_plugins_register_unload_notify_cb purple_plugins_register_unload_notify_cb; */
alias da_purple_plugins_unregister_unload_notify_cb = void function(void function (PurplePlugin*, void*) func);																																																						/* da_purple_plugins_unregister_unload_notify_cb purple_plugins_unregister_unload_notify_cb; */
alias da_purple_plugins_find_with_name = PurplePlugin* function(const(char)* name);																																																						/* da_purple_plugins_find_with_name purple_plugins_find_with_name; */
alias da_purple_plugins_find_with_filename = PurplePlugin* function(const(char)* filename);																																																						/* da_purple_plugins_find_with_filename purple_plugins_find_with_filename; */
alias da_purple_plugins_find_with_basename = PurplePlugin* function(const(char)* basename);																																																						/* da_purple_plugins_find_with_basename purple_plugins_find_with_basename; */
alias da_purple_plugins_find_with_id = PurplePlugin* function(const(char)* id);																																																						/* da_purple_plugins_find_with_id purple_plugins_find_with_id; */
alias da_purple_plugins_get_loaded = GList* function();																																																						/* da_purple_plugins_get_loaded purple_plugins_get_loaded; */
alias da_purple_plugins_get_protocols = GList* function();																																																						/* da_purple_plugins_get_protocols purple_plugins_get_protocols; */
alias da_purple_plugins_get_all = GList* function();																																																						/* da_purple_plugins_get_all purple_plugins_get_all; */
alias da_purple_plugins_get_handle = void* function();																																																						/* da_purple_plugins_get_handle purple_plugins_get_handle; */
alias da_purple_plugins_init = void function();																																																						/* da_purple_plugins_init purple_plugins_init; */
alias da_purple_plugins_uninit = void function();																																																						/* da_purple_plugins_uninit purple_plugins_uninit; */
alias da_purple_plugin_action_new = PurplePluginAction* function(const(char)* label, void function (PurplePluginAction*) callback);																																																						/* da_purple_plugin_action_new purple_plugin_action_new; */
alias da_purple_plugin_action_free = void function(PurplePluginAction* action);																																																						/* da_purple_plugin_action_free purple_plugin_action_free; */
