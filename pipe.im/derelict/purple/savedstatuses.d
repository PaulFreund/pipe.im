module derelict.purple.savedstatuses;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.status;
import derelict.purple.account;
import core.stdc.time;

extern (C):

alias _PurpleSavedStatus PurpleSavedStatus;
alias _PurpleSavedStatusSub PurpleSavedStatusSub;

struct _PurpleSavedStatus;


struct _PurpleSavedStatusSub;


alias da_purple_savedstatus_new = PurpleSavedStatus* function(const(char)* title, PurpleStatusPrimitive type);																																																						/* da_purple_savedstatus_new purple_savedstatus_new; */
alias da_purple_savedstatus_set_title = void function(PurpleSavedStatus* status, const(char)* title);																																																						/* da_purple_savedstatus_set_title purple_savedstatus_set_title; */
alias da_purple_savedstatus_set_type = void function(PurpleSavedStatus* status, PurpleStatusPrimitive type);																																																						/* da_purple_savedstatus_set_type purple_savedstatus_set_type; */
alias da_purple_savedstatus_set_message = void function(PurpleSavedStatus* status, const(char)* message);																																																						/* da_purple_savedstatus_set_message purple_savedstatus_set_message; */
alias da_purple_savedstatus_set_substatus = void function(PurpleSavedStatus* status, const(PurpleAccount)* account, const(PurpleStatusType)* type, const(char)* message);																																																						/* da_purple_savedstatus_set_substatus purple_savedstatus_set_substatus; */
alias da_purple_savedstatus_unset_substatus = void function(PurpleSavedStatus* saved_status, const(PurpleAccount)* account);																																																						/* da_purple_savedstatus_unset_substatus purple_savedstatus_unset_substatus; */
alias da_purple_savedstatus_delete = gboolean function(const(char)* title);																																																						/* da_purple_savedstatus_delete purple_savedstatus_delete; */
alias da_purple_savedstatus_delete_by_status = void function(PurpleSavedStatus* saved_status);																																																						/* da_purple_savedstatus_delete_by_status purple_savedstatus_delete_by_status; */
alias da_purple_savedstatuses_get_all = GList* function();																																																						/* da_purple_savedstatuses_get_all purple_savedstatuses_get_all; */
alias da_purple_savedstatuses_get_popular = GList* function(uint how_many);																																																						/* da_purple_savedstatuses_get_popular purple_savedstatuses_get_popular; */
alias da_purple_savedstatus_get_current = PurpleSavedStatus* function();																																																						/* da_purple_savedstatus_get_current purple_savedstatus_get_current; */
alias da_purple_savedstatus_get_default = PurpleSavedStatus* function();																																																						/* da_purple_savedstatus_get_default purple_savedstatus_get_default; */
alias da_purple_savedstatus_get_idleaway = PurpleSavedStatus* function();																																																						/* da_purple_savedstatus_get_idleaway purple_savedstatus_get_idleaway; */
alias da_purple_savedstatus_is_idleaway = gboolean function();																																																						/* da_purple_savedstatus_is_idleaway purple_savedstatus_is_idleaway; */
alias da_purple_savedstatus_set_idleaway = void function(gboolean idleaway);																																																						/* da_purple_savedstatus_set_idleaway purple_savedstatus_set_idleaway; */
alias da_purple_savedstatus_get_startup = PurpleSavedStatus* function();																																																						/* da_purple_savedstatus_get_startup purple_savedstatus_get_startup; */
alias da_purple_savedstatus_find = PurpleSavedStatus* function(const(char)* title);																																																						/* da_purple_savedstatus_find purple_savedstatus_find; */
alias da_purple_savedstatus_find_by_creation_time = PurpleSavedStatus* function(time_t creation_time);																																																						/* da_purple_savedstatus_find_by_creation_time purple_savedstatus_find_by_creation_time; */
alias da_purple_savedstatus_find_transient_by_type_and_message = PurpleSavedStatus* function(PurpleStatusPrimitive type, const(char)* message);																																																						/* da_purple_savedstatus_find_transient_by_type_and_message purple_savedstatus_find_transient_by_type_and_message; */
alias da_purple_savedstatus_is_transient = gboolean function(const(PurpleSavedStatus)* saved_status);																																																						/* da_purple_savedstatus_is_transient purple_savedstatus_is_transient; */
alias da_purple_savedstatus_get_title = const(char)* function(const(PurpleSavedStatus)* saved_status);																																																						/* da_purple_savedstatus_get_title purple_savedstatus_get_title; */
alias da_purple_savedstatus_get_type = PurpleStatusPrimitive function(const(PurpleSavedStatus)* saved_status);																																																						/* da_purple_savedstatus_get_type purple_savedstatus_get_type; */
alias da_purple_savedstatus_get_message = const(char)* function(const(PurpleSavedStatus)* saved_status);																																																						/* da_purple_savedstatus_get_message purple_savedstatus_get_message; */
alias da_purple_savedstatus_get_creation_time = time_t function(const(PurpleSavedStatus)* saved_status);																																																						/* da_purple_savedstatus_get_creation_time purple_savedstatus_get_creation_time; */
alias da_purple_savedstatus_has_substatuses = gboolean function(const(PurpleSavedStatus)* saved_status);																																																						/* da_purple_savedstatus_has_substatuses purple_savedstatus_has_substatuses; */
alias da_purple_savedstatus_get_substatus = PurpleSavedStatusSub* function(const(PurpleSavedStatus)* saved_status, const(PurpleAccount)* account);																																																						/* da_purple_savedstatus_get_substatus purple_savedstatus_get_substatus; */
alias da_purple_savedstatus_substatus_get_type = const(PurpleStatusType)* function(const(PurpleSavedStatusSub)* substatus);																																																						/* da_purple_savedstatus_substatus_get_type purple_savedstatus_substatus_get_type; */
alias da_purple_savedstatus_substatus_get_message = const(char)* function(const(PurpleSavedStatusSub)* substatus);																																																						/* da_purple_savedstatus_substatus_get_message purple_savedstatus_substatus_get_message; */
alias da_purple_savedstatus_activate = void function(PurpleSavedStatus* saved_status);																																																						/* da_purple_savedstatus_activate purple_savedstatus_activate; */
alias da_purple_savedstatus_activate_for_account = void function(const(PurpleSavedStatus)* saved_status, PurpleAccount* account);																																																						/* da_purple_savedstatus_activate_for_account purple_savedstatus_activate_for_account; */
alias da_purple_savedstatuses_get_handle = void* function();																																																						/* da_purple_savedstatuses_get_handle purple_savedstatuses_get_handle; */
alias da_purple_savedstatuses_init = void function();																																																						/* da_purple_savedstatuses_init purple_savedstatuses_init; */
alias da_purple_savedstatuses_uninit = void function();																																																						/* da_purple_savedstatuses_uninit purple_savedstatuses_uninit; */
