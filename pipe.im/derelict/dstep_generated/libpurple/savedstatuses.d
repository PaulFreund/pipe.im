import core.stdc.time;

extern (C):

alias _PurpleSavedStatus PurpleSavedStatus;
alias _PurpleSavedStatusSub PurpleSavedStatusSub;

struct _PurpleSavedStatus;


struct _PurpleSavedStatusSub;


PurpleSavedStatus* purple_savedstatus_new (const(char)* title, PurpleStatusPrimitive type);
void purple_savedstatus_set_title (PurpleSavedStatus* status, const(char)* title);
void purple_savedstatus_set_type (PurpleSavedStatus* status, PurpleStatusPrimitive type);
void purple_savedstatus_set_message (PurpleSavedStatus* status, const(char)* message);
void purple_savedstatus_set_substatus (PurpleSavedStatus* status, const(PurpleAccount)* account, const(PurpleStatusType)* type, const(char)* message);
void purple_savedstatus_unset_substatus (PurpleSavedStatus* saved_status, const(PurpleAccount)* account);
gboolean purple_savedstatus_delete (const(char)* title);
void purple_savedstatus_delete_by_status (PurpleSavedStatus* saved_status);
GList* purple_savedstatuses_get_all ();
GList* purple_savedstatuses_get_popular (uint how_many);
PurpleSavedStatus* purple_savedstatus_get_current ();
PurpleSavedStatus* purple_savedstatus_get_default ();
PurpleSavedStatus* purple_savedstatus_get_idleaway ();
gboolean purple_savedstatus_is_idleaway ();
void purple_savedstatus_set_idleaway (gboolean idleaway);
PurpleSavedStatus* purple_savedstatus_get_startup ();
PurpleSavedStatus* purple_savedstatus_find (const(char)* title);
PurpleSavedStatus* purple_savedstatus_find_by_creation_time (time_t creation_time);
PurpleSavedStatus* purple_savedstatus_find_transient_by_type_and_message (PurpleStatusPrimitive type, const(char)* message);
gboolean purple_savedstatus_is_transient (const(PurpleSavedStatus)* saved_status);
const(char)* purple_savedstatus_get_title (const(PurpleSavedStatus)* saved_status);
PurpleStatusPrimitive purple_savedstatus_get_type (const(PurpleSavedStatus)* saved_status);
const(char)* purple_savedstatus_get_message (const(PurpleSavedStatus)* saved_status);
time_t purple_savedstatus_get_creation_time (const(PurpleSavedStatus)* saved_status);
gboolean purple_savedstatus_has_substatuses (const(PurpleSavedStatus)* saved_status);
PurpleSavedStatusSub* purple_savedstatus_get_substatus (const(PurpleSavedStatus)* saved_status, const(PurpleAccount)* account);
const(PurpleStatusType)* purple_savedstatus_substatus_get_type (const(PurpleSavedStatusSub)* substatus);
const(char)* purple_savedstatus_substatus_get_message (const(PurpleSavedStatusSub)* substatus);
void purple_savedstatus_activate (PurpleSavedStatus* saved_status);
void purple_savedstatus_activate_for_account (const(PurpleSavedStatus)* saved_status, PurpleAccount* account);
void* purple_savedstatuses_get_handle ();
void purple_savedstatuses_init ();
void purple_savedstatuses_uninit ();