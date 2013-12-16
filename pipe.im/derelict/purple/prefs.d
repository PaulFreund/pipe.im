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

void* purple_prefs_get_handle ();
void purple_prefs_init ();
void purple_prefs_uninit ();
void purple_prefs_add_none (const(char)* name);
void purple_prefs_add_bool (const(char)* name, gboolean value);
void purple_prefs_add_int (const(char)* name, int value);
void purple_prefs_add_string (const(char)* name, const(char)* value);
void purple_prefs_add_string_list (const(char)* name, GList* value);
void purple_prefs_add_path (const(char)* name, const(char)* value);
void purple_prefs_add_path_list (const(char)* name, GList* value);
void purple_prefs_remove (const(char)* name);
void purple_prefs_rename (const(char)* oldname, const(char)* newname);
void purple_prefs_rename_boolean_toggle (const(char)* oldname, const(char)* newname);
void purple_prefs_destroy ();
void purple_prefs_set_generic (const(char)* name, gpointer value);
void purple_prefs_set_bool (const(char)* name, gboolean value);
void purple_prefs_set_int (const(char)* name, int value);
void purple_prefs_set_string (const(char)* name, const(char)* value);
void purple_prefs_set_string_list (const(char)* name, GList* value);
void purple_prefs_set_path (const(char)* name, const(char)* value);
void purple_prefs_set_path_list (const(char)* name, GList* value);
gboolean purple_prefs_exists (const(char)* name);
PurplePrefType purple_prefs_get_type (const(char)* name);
gboolean purple_prefs_get_bool (const(char)* name);
int purple_prefs_get_int (const(char)* name);
const(char)* purple_prefs_get_string (const(char)* name);
GList* purple_prefs_get_string_list (const(char)* name);
const(char)* purple_prefs_get_path (const(char)* name);
GList* purple_prefs_get_path_list (const(char)* name);
GList* purple_prefs_get_children_names (const(char)* name);
guint purple_prefs_connect_callback (void* handle, const(char)* name, PurplePrefCallback cb, gpointer data);
void purple_prefs_disconnect_callback (guint callback_id);
void purple_prefs_disconnect_by_handle (void* handle);
void purple_prefs_trigger_callback (const(char)* name);
gboolean purple_prefs_load ();
void purple_prefs_update_old ();