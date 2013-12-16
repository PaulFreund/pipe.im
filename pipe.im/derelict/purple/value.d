module derelict.purple.value;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias _Anonymous_0 PurpleType;
alias _Anonymous_1 PurpleSubType;
alias _Anonymous_2 PurpleValue;

enum _Anonymous_0
{
	PURPLE_TYPE_UNKNOWN = 0,
	PURPLE_TYPE_SUBTYPE = 1,
	PURPLE_TYPE_CHAR = 2,
	PURPLE_TYPE_UCHAR = 3,
	PURPLE_TYPE_BOOLEAN = 4,
	PURPLE_TYPE_SHORT = 5,
	PURPLE_TYPE_USHORT = 6,
	PURPLE_TYPE_INT = 7,
	PURPLE_TYPE_UINT = 8,
	PURPLE_TYPE_LONG = 9,
	PURPLE_TYPE_ULONG = 10,
	PURPLE_TYPE_INT64 = 11,
	PURPLE_TYPE_UINT64 = 12,
	PURPLE_TYPE_STRING = 13,
	PURPLE_TYPE_OBJECT = 14,
	PURPLE_TYPE_POINTER = 15,
	PURPLE_TYPE_ENUM = 16,
	PURPLE_TYPE_BOXED = 17
}

enum _Anonymous_1
{
	PURPLE_SUBTYPE_UNKNOWN = 0,
	PURPLE_SUBTYPE_ACCOUNT = 1,
	PURPLE_SUBTYPE_BLIST = 2,
	PURPLE_SUBTYPE_BLIST_BUDDY = 3,
	PURPLE_SUBTYPE_BLIST_GROUP = 4,
	PURPLE_SUBTYPE_BLIST_CHAT = 5,
	PURPLE_SUBTYPE_BUDDY_ICON = 6,
	PURPLE_SUBTYPE_CONNECTION = 7,
	PURPLE_SUBTYPE_CONVERSATION = 8,
	PURPLE_SUBTYPE_PLUGIN = 9,
	PURPLE_SUBTYPE_BLIST_NODE = 10,
	PURPLE_SUBTYPE_CIPHER = 11,
	PURPLE_SUBTYPE_STATUS = 12,
	PURPLE_SUBTYPE_LOG = 13,
	PURPLE_SUBTYPE_XFER = 14,
	PURPLE_SUBTYPE_SAVEDSTATUS = 15,
	PURPLE_SUBTYPE_XMLNODE = 16,
	PURPLE_SUBTYPE_USERINFO = 17,
	PURPLE_SUBTYPE_STORED_IMAGE = 18,
	PURPLE_SUBTYPE_CERTIFICATEPOOL = 19,
	PURPLE_SUBTYPE_CHATBUDDY = 20
}

struct _Anonymous_2
{
	PurpleType type;
	ushort flags;
	union
	{
		char char_data;
		ubyte uchar_data;
		gboolean boolean_data;
		short short_data;
		ushort ushort_data;
		int int_data;
		uint uint_data;
		c_long long_data;
		c_ulong ulong_data;
		gint64 int64_data;
		guint64 uint64_data;
		char* string_data;
		void* object_data;
		void* pointer_data;
		int enum_data;
		void* boxed_data;
	}
	union
	{
		uint subtype;
		char* specific_type;
	}
}

PurpleValue* purple_value_new (PurpleType type, ...);
PurpleValue* purple_value_new_outgoing (PurpleType type, ...);
void purple_value_destroy (PurpleValue* value);
PurpleValue* purple_value_dup (const(PurpleValue)* value);
PurpleType purple_value_get_type (const(PurpleValue)* value);
uint purple_value_get_subtype (const(PurpleValue)* value);
const(char)* purple_value_get_specific_type (const(PurpleValue)* value);
gboolean purple_value_is_outgoing (const(PurpleValue)* value);
void purple_value_set_char (PurpleValue* value, char data);
void purple_value_set_uchar (PurpleValue* value, ubyte data);
void purple_value_set_boolean (PurpleValue* value, gboolean data);
void purple_value_set_short (PurpleValue* value, short data);
void purple_value_set_ushort (PurpleValue* value, ushort data);
void purple_value_set_int (PurpleValue* value, int data);
void purple_value_set_uint (PurpleValue* value, uint data);
void purple_value_set_long (PurpleValue* value, c_long data);
void purple_value_set_ulong (PurpleValue* value, c_ulong data);
void purple_value_set_int64 (PurpleValue* value, gint64 data);
void purple_value_set_uint64 (PurpleValue* value, guint64 data);
void purple_value_set_string (PurpleValue* value, const(char)* data);
void purple_value_set_object (PurpleValue* value, void* data);
void purple_value_set_pointer (PurpleValue* value, void* data);
void purple_value_set_enum (PurpleValue* value, int data);
void purple_value_set_boxed (PurpleValue* value, void* data);
char purple_value_get_char (const(PurpleValue)* value);
ubyte purple_value_get_uchar (const(PurpleValue)* value);
gboolean purple_value_get_boolean (const(PurpleValue)* value);
short purple_value_get_short (const(PurpleValue)* value);
ushort purple_value_get_ushort (const(PurpleValue)* value);
int purple_value_get_int (const(PurpleValue)* value);
uint purple_value_get_uint (const(PurpleValue)* value);
c_long purple_value_get_long (const(PurpleValue)* value);
c_ulong purple_value_get_ulong (const(PurpleValue)* value);
gint64 purple_value_get_int64 (const(PurpleValue)* value);
guint64 purple_value_get_uint64 (const(PurpleValue)* value);
const(char)* purple_value_get_string (const(PurpleValue)* value);
void* purple_value_get_object (const(PurpleValue)* value);
void* purple_value_get_pointer (const(PurpleValue)* value);
int purple_value_get_enum (const(PurpleValue)* value);
void* purple_value_get_boxed (const(PurpleValue)* value);