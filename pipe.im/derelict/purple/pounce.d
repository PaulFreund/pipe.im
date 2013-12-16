module derelict.purple.pounce;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.ghash;
import derelict.glib.glist;
import derelict.purple.account;
import derelict.purple.blist;

extern (C):

alias _PurplePounce PurplePounce;
alias _Anonymous_0 PurplePounceEvent;
alias _Anonymous_1 PurplePounceOption;
alias void function (_PurplePounce*, _Anonymous_0, void*) PurplePounceCb;

enum _Anonymous_0
{
	PURPLE_POUNCE_NONE = 0,
	PURPLE_POUNCE_SIGNON = 1,
	PURPLE_POUNCE_SIGNOFF = 2,
	PURPLE_POUNCE_AWAY = 4,
	PURPLE_POUNCE_AWAY_RETURN = 8,
	PURPLE_POUNCE_IDLE = 16,
	PURPLE_POUNCE_IDLE_RETURN = 32,
	PURPLE_POUNCE_TYPING = 64,
	PURPLE_POUNCE_TYPED = 128,
	PURPLE_POUNCE_TYPING_STOPPED = 256,
	PURPLE_POUNCE_MESSAGE_RECEIVED = 512
}

enum _Anonymous_1
{
	PURPLE_POUNCE_OPTION_NONE = 0,
	PURPLE_POUNCE_OPTION_AWAY = 1
}

struct _PurplePounce
{
	char* ui_type;
	PurplePounceEvent events;
	PurplePounceOption options;
	PurpleAccount* pouncer;
	char* pouncee;
	GHashTable* actions;
	gboolean save;
	void* data;
}

alias da_purple_pounce_new = PurplePounce* function(const(char)* ui_type, PurpleAccount* pouncer, const(char)* pouncee, PurplePounceEvent event, PurplePounceOption option);																																																						/* da_purple_pounce_new purple_pounce_new; */
alias da_purple_pounce_destroy = void function(PurplePounce* pounce);																																																						/* da_purple_pounce_destroy purple_pounce_destroy; */
alias da_purple_pounce_destroy_all_by_account = void function(PurpleAccount* account);																																																						/* da_purple_pounce_destroy_all_by_account purple_pounce_destroy_all_by_account; */
alias da_purple_pounce_destroy_all_by_buddy = void function(PurpleBuddy* buddy);																																																						/* da_purple_pounce_destroy_all_by_buddy purple_pounce_destroy_all_by_buddy; */
alias da_purple_pounce_set_events = void function(PurplePounce* pounce, PurplePounceEvent events);																																																						/* da_purple_pounce_set_events purple_pounce_set_events; */
alias da_purple_pounce_set_options = void function(PurplePounce* pounce, PurplePounceOption options);																																																						/* da_purple_pounce_set_options purple_pounce_set_options; */
alias da_purple_pounce_set_pouncer = void function(PurplePounce* pounce, PurpleAccount* pouncer);																																																						/* da_purple_pounce_set_pouncer purple_pounce_set_pouncer; */
alias da_purple_pounce_set_pouncee = void function(PurplePounce* pounce, const(char)* pouncee);																																																						/* da_purple_pounce_set_pouncee purple_pounce_set_pouncee; */
alias da_purple_pounce_set_save = void function(PurplePounce* pounce, gboolean save);																																																						/* da_purple_pounce_set_save purple_pounce_set_save; */
alias da_purple_pounce_action_register = void function(PurplePounce* pounce, const(char)* name);																																																						/* da_purple_pounce_action_register purple_pounce_action_register; */
alias da_purple_pounce_action_set_enabled = void function(PurplePounce* pounce, const(char)* action, gboolean enabled);																																																						/* da_purple_pounce_action_set_enabled purple_pounce_action_set_enabled; */
alias da_purple_pounce_action_set_attribute = void function(PurplePounce* pounce, const(char)* action, const(char)* attr, const(char)* value);																																																						/* da_purple_pounce_action_set_attribute purple_pounce_action_set_attribute; */
alias da_purple_pounce_set_data = void function(PurplePounce* pounce, void* data);																																																						/* da_purple_pounce_set_data purple_pounce_set_data; */
alias da_purple_pounce_get_events = PurplePounceEvent function(const(PurplePounce)* pounce);																																																						/* da_purple_pounce_get_events purple_pounce_get_events; */
alias da_purple_pounce_get_options = PurplePounceOption function(const(PurplePounce)* pounce);																																																						/* da_purple_pounce_get_options purple_pounce_get_options; */
alias da_purple_pounce_get_pouncer = PurpleAccount* function(const(PurplePounce)* pounce);																																																						/* da_purple_pounce_get_pouncer purple_pounce_get_pouncer; */
alias da_purple_pounce_get_pouncee = const(char)* function(const(PurplePounce)* pounce);																																																						/* da_purple_pounce_get_pouncee purple_pounce_get_pouncee; */
alias da_purple_pounce_get_save = gboolean function(const(PurplePounce)* pounce);																																																						/* da_purple_pounce_get_save purple_pounce_get_save; */
alias da_purple_pounce_action_is_enabled = gboolean function(const(PurplePounce)* pounce, const(char)* action);																																																						/* da_purple_pounce_action_is_enabled purple_pounce_action_is_enabled; */
alias da_purple_pounce_action_get_attribute = const(char)* function(const(PurplePounce)* pounce, const(char)* action, const(char)* attr);																																																						/* da_purple_pounce_action_get_attribute purple_pounce_action_get_attribute; */
alias da_purple_pounce_get_data = void* function(const(PurplePounce)* pounce);																																																						/* da_purple_pounce_get_data purple_pounce_get_data; */
alias da_purple_pounce_execute = void function(const(PurpleAccount)* pouncer, const(char)* pouncee, PurplePounceEvent events);																																																						/* da_purple_pounce_execute purple_pounce_execute; */
alias da_purple_find_pounce = PurplePounce* function(const(PurpleAccount)* pouncer, const(char)* pouncee, PurplePounceEvent events);																																																						/* da_purple_find_pounce purple_find_pounce; */
alias da_purple_pounces_load = gboolean function();																																																						/* da_purple_pounces_load purple_pounces_load; */
alias da_purple_pounces_register_handler = void function(const(char)* ui, PurplePounceCb cb, void function (PurplePounce*) new_pounce, void function (PurplePounce*) free_pounce);																																																						/* da_purple_pounces_register_handler purple_pounces_register_handler; */
alias da_purple_pounces_unregister_handler = void function(const(char)* ui);																																																						/* da_purple_pounces_unregister_handler purple_pounces_unregister_handler; */
alias da_purple_pounces_get_all = GList* function();																																																						/* da_purple_pounces_get_all purple_pounces_get_all; */
alias da_purple_pounces_get_all_for_ui = GList* function(const(char)* ui);																																																						/* da_purple_pounces_get_all_for_ui purple_pounces_get_all_for_ui; */
alias da_purple_pounces_get_handle = void* function();																																																						/* da_purple_pounces_get_handle purple_pounces_get_handle; */
alias da_purple_pounces_init = void function();																																																						/* da_purple_pounces_init purple_pounces_init; */
alias da_purple_pounces_uninit = void function();																																																						/* da_purple_pounces_uninit purple_pounces_uninit; */
