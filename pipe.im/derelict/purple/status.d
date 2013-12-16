module derelict.purple.status;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.value;
import derelict.purple.account;
import derelict.purple.conversation;
import derelict.purple.blist;
import core.stdc.time;
import std.c.stdarg;

extern (C):

alias _PurpleStatusType PurpleStatusType;
alias _PurpleStatusAttr PurpleStatusAttr;
alias _PurplePresence PurplePresence;
alias _PurpleStatus PurpleStatus;
alias _PurpleMood PurpleMood;
alias _Anonymous_0 PurplePresenceContext;
alias _Anonymous_1 PurpleStatusPrimitive;

enum _Anonymous_0
{
	PURPLE_PRESENCE_CONTEXT_UNSET = 0,
	PURPLE_PRESENCE_CONTEXT_ACCOUNT = 1,
	PURPLE_PRESENCE_CONTEXT_CONV = 2,
	PURPLE_PRESENCE_CONTEXT_BUDDY = 3
}

enum _Anonymous_1
{
	PURPLE_STATUS_UNSET = 0,
	PURPLE_STATUS_OFFLINE = 1,
	PURPLE_STATUS_AVAILABLE = 2,
	PURPLE_STATUS_UNAVAILABLE = 3,
	PURPLE_STATUS_INVISIBLE = 4,
	PURPLE_STATUS_AWAY = 5,
	PURPLE_STATUS_EXTENDED_AWAY = 6,
	PURPLE_STATUS_MOBILE = 7,
	PURPLE_STATUS_TUNE = 8,
	PURPLE_STATUS_MOOD = 9,
	PURPLE_STATUS_NUM_PRIMITIVES = 10
}

struct _PurpleMood
{
	const(char)* mood;
	const(char)* description;
	gpointer* padding;
}

struct _PurpleStatus;


struct _PurpleStatusAttr;


struct _PurplePresence;


struct _PurpleStatusType;


const(char)* purple_primitive_get_id_from_type (PurpleStatusPrimitive type);
const(char)* purple_primitive_get_name_from_type (PurpleStatusPrimitive type);
PurpleStatusPrimitive purple_primitive_get_type_from_id (const(char)* id);
PurpleStatusType* purple_status_type_new_full (PurpleStatusPrimitive primitive, const(char)* id, const(char)* name, gboolean saveable, gboolean user_settable, gboolean independent);
PurpleStatusType* purple_status_type_new (PurpleStatusPrimitive primitive, const(char)* id, const(char)* name, gboolean user_settable);
PurpleStatusType* purple_status_type_new_with_attrs (PurpleStatusPrimitive primitive, const(char)* id, const(char)* name, gboolean saveable, gboolean user_settable, gboolean independent, const(char)* attr_id, const(char)* attr_name, PurpleValue* attr_value, ...);
void purple_status_type_destroy (PurpleStatusType* status_type);
void purple_status_type_set_primary_attr (PurpleStatusType* status_type, const(char)* attr_id);
void purple_status_type_add_attr (PurpleStatusType* status_type, const(char)* id, const(char)* name, PurpleValue* value);
void purple_status_type_add_attrs (PurpleStatusType* status_type, const(char)* id, const(char)* name, PurpleValue* value, ...);
void purple_status_type_add_attrs_vargs (PurpleStatusType* status_type, va_list args);
PurpleStatusPrimitive purple_status_type_get_primitive (const(PurpleStatusType)* status_type);
const(char)* purple_status_type_get_id (const(PurpleStatusType)* status_type);
const(char)* purple_status_type_get_name (const(PurpleStatusType)* status_type);
gboolean purple_status_type_is_saveable (const(PurpleStatusType)* status_type);
gboolean purple_status_type_is_user_settable (const(PurpleStatusType)* status_type);
gboolean purple_status_type_is_independent (const(PurpleStatusType)* status_type);
gboolean purple_status_type_is_exclusive (const(PurpleStatusType)* status_type);
gboolean purple_status_type_is_available (const(PurpleStatusType)* status_type);
const(char)* purple_status_type_get_primary_attr (const(PurpleStatusType)* type);
PurpleStatusAttr* purple_status_type_get_attr (const(PurpleStatusType)* status_type, const(char)* id);
GList* purple_status_type_get_attrs (const(PurpleStatusType)* status_type);
const(PurpleStatusType)* purple_status_type_find_with_id (GList* status_types, const(char)* id);
PurpleStatusAttr* purple_status_attr_new (const(char)* id, const(char)* name, PurpleValue* value_type);
void purple_status_attr_destroy (PurpleStatusAttr* attr);
const(char)* purple_status_attr_get_id (const(PurpleStatusAttr)* attr);
const(char)* purple_status_attr_get_name (const(PurpleStatusAttr)* attr);
PurpleValue* purple_status_attr_get_value (const(PurpleStatusAttr)* attr);
PurpleStatus* purple_status_new (PurpleStatusType* status_type, PurplePresence* presence);
void purple_status_destroy (PurpleStatus* status);
void purple_status_set_active (PurpleStatus* status, gboolean active);
void purple_status_set_active_with_attrs (PurpleStatus* status, gboolean active, va_list args);
void purple_status_set_active_with_attrs_list (PurpleStatus* status, gboolean active, GList* attrs);
void purple_status_set_attr_boolean (PurpleStatus* status, const(char)* id, gboolean value);
void purple_status_set_attr_int (PurpleStatus* status, const(char)* id, int value);
void purple_status_set_attr_string (PurpleStatus* status, const(char)* id, const(char)* value);
PurpleStatusType* purple_status_get_type (const(PurpleStatus)* status);
PurplePresence* purple_status_get_presence (const(PurpleStatus)* status);
const(char)* purple_status_get_id (const(PurpleStatus)* status);
const(char)* purple_status_get_name (const(PurpleStatus)* status);
gboolean purple_status_is_independent (const(PurpleStatus)* status);
gboolean purple_status_is_exclusive (const(PurpleStatus)* status);
gboolean purple_status_is_available (const(PurpleStatus)* status);
gboolean purple_status_is_active (const(PurpleStatus)* status);
gboolean purple_status_is_online (const(PurpleStatus)* status);
PurpleValue* purple_status_get_attr_value (const(PurpleStatus)* status, const(char)* id);
gboolean purple_status_get_attr_boolean (const(PurpleStatus)* status, const(char)* id);
int purple_status_get_attr_int (const(PurpleStatus)* status, const(char)* id);
const(char)* purple_status_get_attr_string (const(PurpleStatus)* status, const(char)* id);
gint purple_status_compare (const(PurpleStatus)* status1, const(PurpleStatus)* status2);
PurplePresence* purple_presence_new (PurplePresenceContext context);
PurplePresence* purple_presence_new_for_account (PurpleAccount* account);
PurplePresence* purple_presence_new_for_conv (PurpleConversation* conv);
PurplePresence* purple_presence_new_for_buddy (PurpleBuddy* buddy);
void purple_presence_destroy (PurplePresence* presence);
void purple_presence_add_status (PurplePresence* presence, PurpleStatus* status);
void purple_presence_add_list (PurplePresence* presence, GList* source_list);
void purple_presence_set_status_active (PurplePresence* presence, const(char)* status_id, gboolean active);
void purple_presence_switch_status (PurplePresence* presence, const(char)* status_id);
void purple_presence_set_idle (PurplePresence* presence, gboolean idle, time_t idle_time);
void purple_presence_set_login_time (PurplePresence* presence, time_t login_time);
PurplePresenceContext purple_presence_get_context (const(PurplePresence)* presence);
PurpleAccount* purple_presence_get_account (const(PurplePresence)* presence);
PurpleConversation* purple_presence_get_conversation (const(PurplePresence)* presence);
const(char)* purple_presence_get_chat_user (const(PurplePresence)* presence);
PurpleBuddy* purple_presence_get_buddy (const(PurplePresence)* presence);
GList* purple_presence_get_statuses (const(PurplePresence)* presence);
PurpleStatus* purple_presence_get_status (const(PurplePresence)* presence, const(char)* status_id);
PurpleStatus* purple_presence_get_active_status (const(PurplePresence)* presence);
gboolean purple_presence_is_available (const(PurplePresence)* presence);
gboolean purple_presence_is_online (const(PurplePresence)* presence);
gboolean purple_presence_is_status_active (const(PurplePresence)* presence, const(char)* status_id);
gboolean purple_presence_is_status_primitive_active (const(PurplePresence)* presence, PurpleStatusPrimitive primitive);
gboolean purple_presence_is_idle (const(PurplePresence)* presence);
time_t purple_presence_get_idle_time (const(PurplePresence)* presence);
time_t purple_presence_get_login_time (const(PurplePresence)* presence);
gint purple_presence_compare (const(PurplePresence)* presence1, const(PurplePresence)* presence2);
void* purple_status_get_handle ();
void purple_status_init ();
void purple_status_uninit ();