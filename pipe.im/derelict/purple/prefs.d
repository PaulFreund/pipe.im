module derelict.purple.prefs;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
extern (C):

alias _PurplePrefType PurplePrefType;
alias void function (const(char)*, _PurplePrefType, const(void)*, void*) PurplePrefCallback;

enum _PurplePrefType
{
	PURPLE_PREF_NONE = 0,
	PURPLE_PREF_BOOLEAN = 1,
	PURPLE_PREF_INT = 2,
	PURPLE_PREF_STRING = 3,
	PURPLE_PREF_STRING_LIST = 4,
	PURPLE_PREF_PATH = 5,
	PURPLE_PREF_PATH_LIST = 6
}

alias da_purple_prefs_get_handle = void* function();																																																						/* da_purple_prefs_get_handle purple_prefs_get_handle; */
alias da_purple_prefs_init = void function();																																																						/* da_purple_prefs_init purple_prefs_init; */
alias da_purple_prefs_uninit = void function();																																																						/* da_purple_prefs_uninit purple_prefs_uninit; */
alias da_purple_prefs_add_none = void function(const(char)* name);																																																						/* da_purple_prefs_add_none purple_prefs_add_none; */
alias da_purple_prefs_add_bool = void function(const(char)* name, gboolean value);																																																						/* da_purple_prefs_add_bool purple_prefs_add_bool; */
alias da_purple_prefs_add_int = void function(const(char)* name, int value);																																																						/* da_purple_prefs_add_int purple_prefs_add_int; */
alias da_purple_prefs_add_string = void function(const(char)* name, const(char)* value);																																																						/* da_purple_prefs_add_string purple_prefs_add_string; */
alias da_purple_prefs_add_string_list = void function(const(char)* name, GList* value);																																																						/* da_purple_prefs_add_string_list purple_prefs_add_string_list; */
alias da_purple_prefs_add_path = void function(const(char)* name, const(char)* value);																																																						/* da_purple_prefs_add_path purple_prefs_add_path; */
alias da_purple_prefs_add_path_list = void function(const(char)* name, GList* value);																																																						/* da_purple_prefs_add_path_list purple_prefs_add_path_list; */
alias da_purple_prefs_remove = void function(const(char)* name);																																																						/* da_purple_prefs_remove purple_prefs_remove; */
alias da_purple_prefs_rename = void function(const(char)* oldname, const(char)* newname);																																																						/* da_purple_prefs_rename purple_prefs_rename; */
alias da_purple_prefs_rename_boolean_toggle = void function(const(char)* oldname, const(char)* newname);																																																						/* da_purple_prefs_rename_boolean_toggle purple_prefs_rename_boolean_toggle; */
alias da_purple_prefs_destroy = void function();																																																						/* da_purple_prefs_destroy purple_prefs_destroy; */
alias da_purple_prefs_set_generic = void function(const(char)* name, gpointer value);																																																						/* da_purple_prefs_set_generic purple_prefs_set_generic; */
alias da_purple_prefs_set_bool = void function(const(char)* name, gboolean value);																																																						/* da_purple_prefs_set_bool purple_prefs_set_bool; */
alias da_purple_prefs_set_int = void function(const(char)* name, int value);																																																						/* da_purple_prefs_set_int purple_prefs_set_int; */
alias da_purple_prefs_set_string = void function(const(char)* name, const(char)* value);																																																						/* da_purple_prefs_set_string purple_prefs_set_string; */
alias da_purple_prefs_set_string_list = void function(const(char)* name, GList* value);																																																						/* da_purple_prefs_set_string_list purple_prefs_set_string_list; */
alias da_purple_prefs_set_path = void function(const(char)* name, const(char)* value);																																																						/* da_purple_prefs_set_path purple_prefs_set_path; */
alias da_purple_prefs_set_path_list = void function(const(char)* name, GList* value);																																																						/* da_purple_prefs_set_path_list purple_prefs_set_path_list; */
alias da_purple_prefs_exists = gboolean function(const(char)* name);																																																						/* da_purple_prefs_exists purple_prefs_exists; */
alias da_purple_prefs_get_type = PurplePrefType function(const(char)* name);																																																						/* da_purple_prefs_get_type purple_prefs_get_type; */
alias da_purple_prefs_get_bool = gboolean function(const(char)* name);																																																						/* da_purple_prefs_get_bool purple_prefs_get_bool; */
alias da_purple_prefs_get_int = int function(const(char)* name);																																																						/* da_purple_prefs_get_int purple_prefs_get_int; */
alias da_purple_prefs_get_string = const(char)* function(const(char)* name);																																																						/* da_purple_prefs_get_string purple_prefs_get_string; */
alias da_purple_prefs_get_string_list = GList* function(const(char)* name);																																																						/* da_purple_prefs_get_string_list purple_prefs_get_string_list; */
alias da_purple_prefs_get_path = const(char)* function(const(char)* name);																																																						/* da_purple_prefs_get_path purple_prefs_get_path; */
alias da_purple_prefs_get_path_list = GList* function(const(char)* name);																																																						/* da_purple_prefs_get_path_list purple_prefs_get_path_list; */
alias da_purple_prefs_get_children_names = GList* function(const(char)* name);																																																						/* da_purple_prefs_get_children_names purple_prefs_get_children_names; */
alias da_purple_prefs_connect_callback = guint function(void* handle, const(char)* name, PurplePrefCallback cb, gpointer data);																																																						/* da_purple_prefs_connect_callback purple_prefs_connect_callback; */
alias da_purple_prefs_disconnect_callback = void function(guint callback_id);																																																						/* da_purple_prefs_disconnect_callback purple_prefs_disconnect_callback; */
alias da_purple_prefs_disconnect_by_handle = void function(void* handle);																																																						/* da_purple_prefs_disconnect_by_handle purple_prefs_disconnect_by_handle; */
alias da_purple_prefs_trigger_callback = void function(const(char)* name);																																																						/* da_purple_prefs_trigger_callback purple_prefs_trigger_callback; */
alias da_purple_prefs_load = gboolean function();																																																						/* da_purple_prefs_load purple_prefs_load; */
alias da_purple_prefs_update_old = void function();																																																						/* da_purple_prefs_update_old purple_prefs_update_old; */
