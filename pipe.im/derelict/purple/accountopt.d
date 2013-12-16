module derelict.purple.accountopt;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.prefs;
extern (C):

alias _Anonymous_0 PurpleAccountOption;
alias _Anonymous_1 PurpleAccountUserSplit;

struct _Anonymous_0
{
	PurplePrefType type;
	char* text;
	char* pref_name;
	union
	{
		gboolean boolean;
		int integer;
		char* string;
		GList* list;
	}
	gboolean masked;
}

struct _Anonymous_1
{
	char* text;
	char* default_value;
	char field_sep;
	gboolean reverse;
}

alias da_purple_account_option_new = PurpleAccountOption* function(PurplePrefType type, const(char)* text, const(char)* pref_name);																																																						/* da_purple_account_option_new purple_account_option_new; */
alias da_purple_account_option_bool_new = PurpleAccountOption* function(const(char)* text, const(char)* pref_name, gboolean default_value);																																																						/* da_purple_account_option_bool_new purple_account_option_bool_new; */
alias da_purple_account_option_int_new = PurpleAccountOption* function(const(char)* text, const(char)* pref_name, int default_value);																																																						/* da_purple_account_option_int_new purple_account_option_int_new; */
alias da_purple_account_option_string_new = PurpleAccountOption* function(const(char)* text, const(char)* pref_name, const(char)* default_value);																																																						/* da_purple_account_option_string_new purple_account_option_string_new; */
alias da_purple_account_option_list_new = PurpleAccountOption* function(const(char)* text, const(char)* pref_name, GList* list);																																																						/* da_purple_account_option_list_new purple_account_option_list_new; */
alias da_purple_account_option_destroy = void function(PurpleAccountOption* option);																																																						/* da_purple_account_option_destroy purple_account_option_destroy; */
alias da_purple_account_option_set_default_bool = void function(PurpleAccountOption* option, gboolean value);																																																						/* da_purple_account_option_set_default_bool purple_account_option_set_default_bool; */
alias da_purple_account_option_set_default_int = void function(PurpleAccountOption* option, int value);																																																						/* da_purple_account_option_set_default_int purple_account_option_set_default_int; */
alias da_purple_account_option_set_default_string = void function(PurpleAccountOption* option, const(char)* value);																																																						/* da_purple_account_option_set_default_string purple_account_option_set_default_string; */
alias da_purple_account_option_set_masked = void function(PurpleAccountOption* option, gboolean masked);																																																						/* da_purple_account_option_set_masked purple_account_option_set_masked; */
alias da_purple_account_option_set_list = void function(PurpleAccountOption* option, GList* values);																																																						/* da_purple_account_option_set_list purple_account_option_set_list; */
alias da_purple_account_option_add_list_item = void function(PurpleAccountOption* option, const(char)* key, const(char)* value);																																																						/* da_purple_account_option_add_list_item purple_account_option_add_list_item; */
alias da_purple_account_option_get_type = PurplePrefType function(const(PurpleAccountOption)* option);																																																						/* da_purple_account_option_get_type purple_account_option_get_type; */
alias da_purple_account_option_get_text = const(char)* function(const(PurpleAccountOption)* option);																																																						/* da_purple_account_option_get_text purple_account_option_get_text; */
alias da_purple_account_option_get_setting = const(char)* function(const(PurpleAccountOption)* option);																																																						/* da_purple_account_option_get_setting purple_account_option_get_setting; */
alias da_purple_account_option_get_default_bool = gboolean function(const(PurpleAccountOption)* option);																																																						/* da_purple_account_option_get_default_bool purple_account_option_get_default_bool; */
alias da_purple_account_option_get_default_int = int function(const(PurpleAccountOption)* option);																																																						/* da_purple_account_option_get_default_int purple_account_option_get_default_int; */
alias da_purple_account_option_get_default_string = const(char)* function(const(PurpleAccountOption)* option);																																																						/* da_purple_account_option_get_default_string purple_account_option_get_default_string; */
alias da_purple_account_option_get_default_list_value = const(char)* function(const(PurpleAccountOption)* option);																																																						/* da_purple_account_option_get_default_list_value purple_account_option_get_default_list_value; */
alias da_purple_account_option_get_masked = gboolean function(const(PurpleAccountOption)* option);																																																						/* da_purple_account_option_get_masked purple_account_option_get_masked; */
alias da_purple_account_option_get_list = GList* function(const(PurpleAccountOption)* option);																																																						/* da_purple_account_option_get_list purple_account_option_get_list; */
alias da_purple_account_user_split_new = PurpleAccountUserSplit* function(const(char)* text, const(char)* default_value, char sep);																																																						/* da_purple_account_user_split_new purple_account_user_split_new; */
alias da_purple_account_user_split_destroy = void function(PurpleAccountUserSplit* split);																																																						/* da_purple_account_user_split_destroy purple_account_user_split_destroy; */
alias da_purple_account_user_split_get_text = const(char)* function(const(PurpleAccountUserSplit)* split);																																																						/* da_purple_account_user_split_get_text purple_account_user_split_get_text; */
alias da_purple_account_user_split_get_default_value = const(char)* function(const(PurpleAccountUserSplit)* split);																																																						/* da_purple_account_user_split_get_default_value purple_account_user_split_get_default_value; */
alias da_purple_account_user_split_get_separator = char function(const(PurpleAccountUserSplit)* split);																																																						/* da_purple_account_user_split_get_separator purple_account_user_split_get_separator; */
alias da_purple_account_user_split_get_reverse = gboolean function(const(PurpleAccountUserSplit)* split);																																																						/* da_purple_account_user_split_get_reverse purple_account_user_split_get_reverse; */
alias da_purple_account_user_split_set_reverse = void function(PurpleAccountUserSplit* split, gboolean reverse);																																																						/* da_purple_account_user_split_set_reverse purple_account_user_split_set_reverse; */
