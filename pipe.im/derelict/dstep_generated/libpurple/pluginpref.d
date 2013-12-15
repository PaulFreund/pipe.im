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


PurplePluginPrefFrame* purple_plugin_pref_frame_new ();
void purple_plugin_pref_frame_destroy (PurplePluginPrefFrame* frame);
void purple_plugin_pref_frame_add (PurplePluginPrefFrame* frame, PurplePluginPref* pref);
GList* purple_plugin_pref_frame_get_prefs (PurplePluginPrefFrame* frame);
PurplePluginPref* purple_plugin_pref_new ();
PurplePluginPref* purple_plugin_pref_new_with_name (const(char)* name);
PurplePluginPref* purple_plugin_pref_new_with_label (const(char)* label);
PurplePluginPref* purple_plugin_pref_new_with_name_and_label (const(char)* name, const(char)* label);
void purple_plugin_pref_destroy (PurplePluginPref* pref);
void purple_plugin_pref_set_name (PurplePluginPref* pref, const(char)* name);
const(char)* purple_plugin_pref_get_name (PurplePluginPref* pref);
void purple_plugin_pref_set_label (PurplePluginPref* pref, const(char)* label);
const(char)* purple_plugin_pref_get_label (PurplePluginPref* pref);
void purple_plugin_pref_set_bounds (PurplePluginPref* pref, int min, int max);
void purple_plugin_pref_get_bounds (PurplePluginPref* pref, int* min, int* max);
void purple_plugin_pref_set_type (PurplePluginPref* pref, PurplePluginPrefType type);
PurplePluginPrefType purple_plugin_pref_get_type (PurplePluginPref* pref);
void purple_plugin_pref_add_choice (PurplePluginPref* pref, const(char)* label, gpointer choice);
GList* purple_plugin_pref_get_choices (PurplePluginPref* pref);
void purple_plugin_pref_set_max_length (PurplePluginPref* pref, uint max_length);
uint purple_plugin_pref_get_max_length (PurplePluginPref* pref);
void purple_plugin_pref_set_masked (PurplePluginPref* pref, gboolean mask);
gboolean purple_plugin_pref_get_masked (PurplePluginPref* pref);
void purple_plugin_pref_set_format_type (PurplePluginPref* pref, PurpleStringFormatType format);
PurpleStringFormatType purple_plugin_pref_get_format_type (PurplePluginPref* pref);