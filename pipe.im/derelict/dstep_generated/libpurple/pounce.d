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

PurplePounce* purple_pounce_new (const(char)* ui_type, PurpleAccount* pouncer, const(char)* pouncee, PurplePounceEvent event, PurplePounceOption option);
void purple_pounce_destroy (PurplePounce* pounce);
void purple_pounce_destroy_all_by_account (PurpleAccount* account);
void purple_pounce_destroy_all_by_buddy (PurpleBuddy* buddy);
void purple_pounce_set_events (PurplePounce* pounce, PurplePounceEvent events);
void purple_pounce_set_options (PurplePounce* pounce, PurplePounceOption options);
void purple_pounce_set_pouncer (PurplePounce* pounce, PurpleAccount* pouncer);
void purple_pounce_set_pouncee (PurplePounce* pounce, const(char)* pouncee);
void purple_pounce_set_save (PurplePounce* pounce, gboolean save);
void purple_pounce_action_register (PurplePounce* pounce, const(char)* name);
void purple_pounce_action_set_enabled (PurplePounce* pounce, const(char)* action, gboolean enabled);
void purple_pounce_action_set_attribute (PurplePounce* pounce, const(char)* action, const(char)* attr, const(char)* value);
void purple_pounce_set_data (PurplePounce* pounce, void* data);
PurplePounceEvent purple_pounce_get_events (const(PurplePounce)* pounce);
PurplePounceOption purple_pounce_get_options (const(PurplePounce)* pounce);
PurpleAccount* purple_pounce_get_pouncer (const(PurplePounce)* pounce);
const(char)* purple_pounce_get_pouncee (const(PurplePounce)* pounce);
gboolean purple_pounce_get_save (const(PurplePounce)* pounce);
gboolean purple_pounce_action_is_enabled (const(PurplePounce)* pounce, const(char)* action);
const(char)* purple_pounce_action_get_attribute (const(PurplePounce)* pounce, const(char)* action, const(char)* attr);
void* purple_pounce_get_data (const(PurplePounce)* pounce);
void purple_pounce_execute (const(PurpleAccount)* pouncer, const(char)* pouncee, PurplePounceEvent events);
PurplePounce* purple_find_pounce (const(PurpleAccount)* pouncer, const(char)* pouncee, PurplePounceEvent events);
gboolean purple_pounces_load ();
void purple_pounces_register_handler (const(char)* ui, PurplePounceCb cb, void function (PurplePounce*) new_pounce, void function (PurplePounce*) free_pounce);
void purple_pounces_unregister_handler (const(char)* ui);
GList* purple_pounces_get_all ();
GList* purple_pounces_get_all_for_ui (const(char)* ui);
void* purple_pounces_get_handle ();
void purple_pounces_init ();
void purple_pounces_uninit ();