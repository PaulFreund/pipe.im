module derelict.purple.pluginpref;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
extern (C):

alias _PurplePluginPrefFrame PurplePluginPrefFrame;
alias _PurplePluginPref PurplePluginPref;
alias _Anonymous_0 PurpleStringFormatType;
alias _Anonymous_1 PurplePluginPrefType;

enum _Anonymous_0
{
	PURPLE_STRING_FORMAT_TYPE_NONE = 0,
	PURPLE_STRING_FORMAT_TYPE_MULTILINE = 1,
	PURPLE_STRING_FORMAT_TYPE_HTML = 2
}

enum _Anonymous_1
{
	PURPLE_PLUGIN_PREF_NONE = 0,
	PURPLE_PLUGIN_PREF_CHOICE = 1,
	PURPLE_PLUGIN_PREF_INFO = 2,
	PURPLE_PLUGIN_PREF_STRING_FORMAT = 3
}

struct _PurplePluginPrefFrame;


struct _PurplePluginPref;


alias da_purple_plugin_pref_frame_new = PurplePluginPrefFrame* function();																																																						/* da_purple_plugin_pref_frame_new purple_plugin_pref_frame_new; */
alias da_purple_plugin_pref_frame_destroy = void function(PurplePluginPrefFrame* frame);																																																						/* da_purple_plugin_pref_frame_destroy purple_plugin_pref_frame_destroy; */
alias da_purple_plugin_pref_frame_add = void function(PurplePluginPrefFrame* frame, PurplePluginPref* pref);																																																						/* da_purple_plugin_pref_frame_add purple_plugin_pref_frame_add; */
alias da_purple_plugin_pref_frame_get_prefs = GList* function(PurplePluginPrefFrame* frame);																																																						/* da_purple_plugin_pref_frame_get_prefs purple_plugin_pref_frame_get_prefs; */
alias da_purple_plugin_pref_new = PurplePluginPref* function();																																																						/* da_purple_plugin_pref_new purple_plugin_pref_new; */
alias da_purple_plugin_pref_new_with_name = PurplePluginPref* function(const(char)* name);																																																						/* da_purple_plugin_pref_new_with_name purple_plugin_pref_new_with_name; */
alias da_purple_plugin_pref_new_with_label = PurplePluginPref* function(const(char)* label);																																																						/* da_purple_plugin_pref_new_with_label purple_plugin_pref_new_with_label; */
alias da_purple_plugin_pref_new_with_name_and_label = PurplePluginPref* function(const(char)* name, const(char)* label);																																																						/* da_purple_plugin_pref_new_with_name_and_label purple_plugin_pref_new_with_name_and_label; */
alias da_purple_plugin_pref_destroy = void function(PurplePluginPref* pref);																																																						/* da_purple_plugin_pref_destroy purple_plugin_pref_destroy; */
alias da_purple_plugin_pref_set_name = void function(PurplePluginPref* pref, const(char)* name);																																																						/* da_purple_plugin_pref_set_name purple_plugin_pref_set_name; */
alias da_purple_plugin_pref_get_name = const(char)* function(PurplePluginPref* pref);																																																						/* da_purple_plugin_pref_get_name purple_plugin_pref_get_name; */
alias da_purple_plugin_pref_set_label = void function(PurplePluginPref* pref, const(char)* label);																																																						/* da_purple_plugin_pref_set_label purple_plugin_pref_set_label; */
alias da_purple_plugin_pref_get_label = const(char)* function(PurplePluginPref* pref);																																																						/* da_purple_plugin_pref_get_label purple_plugin_pref_get_label; */
alias da_purple_plugin_pref_set_bounds = void function(PurplePluginPref* pref, int min, int max);																																																						/* da_purple_plugin_pref_set_bounds purple_plugin_pref_set_bounds; */
alias da_purple_plugin_pref_get_bounds = void function(PurplePluginPref* pref, int* min, int* max);																																																						/* da_purple_plugin_pref_get_bounds purple_plugin_pref_get_bounds; */
alias da_purple_plugin_pref_set_type = void function(PurplePluginPref* pref, PurplePluginPrefType type);																																																						/* da_purple_plugin_pref_set_type purple_plugin_pref_set_type; */
alias da_purple_plugin_pref_get_type = PurplePluginPrefType function(PurplePluginPref* pref);																																																						/* da_purple_plugin_pref_get_type purple_plugin_pref_get_type; */
alias da_purple_plugin_pref_add_choice = void function(PurplePluginPref* pref, const(char)* label, gpointer choice);																																																						/* da_purple_plugin_pref_add_choice purple_plugin_pref_add_choice; */
alias da_purple_plugin_pref_get_choices = GList* function(PurplePluginPref* pref);																																																						/* da_purple_plugin_pref_get_choices purple_plugin_pref_get_choices; */
alias da_purple_plugin_pref_set_max_length = void function(PurplePluginPref* pref, uint max_length);																																																						/* da_purple_plugin_pref_set_max_length purple_plugin_pref_set_max_length; */
alias da_purple_plugin_pref_get_max_length = uint function(PurplePluginPref* pref);																																																						/* da_purple_plugin_pref_get_max_length purple_plugin_pref_get_max_length; */
alias da_purple_plugin_pref_set_masked = void function(PurplePluginPref* pref, gboolean mask);																																																						/* da_purple_plugin_pref_set_masked purple_plugin_pref_set_masked; */
alias da_purple_plugin_pref_get_masked = gboolean function(PurplePluginPref* pref);																																																						/* da_purple_plugin_pref_get_masked purple_plugin_pref_get_masked; */
alias da_purple_plugin_pref_set_format_type = void function(PurplePluginPref* pref, PurpleStringFormatType format);																																																						/* da_purple_plugin_pref_set_format_type purple_plugin_pref_set_format_type; */
alias da_purple_plugin_pref_get_format_type = PurpleStringFormatType function(PurplePluginPref* pref);																																																						/* da_purple_plugin_pref_get_format_type purple_plugin_pref_get_format_type; */
