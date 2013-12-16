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

alias da_purple_value_new = PurpleValue* function(PurpleType type, ...);																																																						/* da_purple_value_new purple_value_new; */
alias da_purple_value_new_outgoing = PurpleValue* function(PurpleType type, ...);																																																						/* da_purple_value_new_outgoing purple_value_new_outgoing; */
alias da_purple_value_destroy = void function(PurpleValue* value);																																																						/* da_purple_value_destroy purple_value_destroy; */
alias da_purple_value_dup = PurpleValue* function(const(PurpleValue)* value);																																																						/* da_purple_value_dup purple_value_dup; */
alias da_purple_value_get_type = PurpleType function(const(PurpleValue)* value);																																																						/* da_purple_value_get_type purple_value_get_type; */
alias da_purple_value_get_subtype = uint function(const(PurpleValue)* value);																																																						/* da_purple_value_get_subtype purple_value_get_subtype; */
alias da_purple_value_get_specific_type = const(char)* function(const(PurpleValue)* value);																																																						/* da_purple_value_get_specific_type purple_value_get_specific_type; */
alias da_purple_value_is_outgoing = gboolean function(const(PurpleValue)* value);																																																						/* da_purple_value_is_outgoing purple_value_is_outgoing; */
alias da_purple_value_set_char = void function(PurpleValue* value, char data);																																																						/* da_purple_value_set_char purple_value_set_char; */
alias da_purple_value_set_uchar = void function(PurpleValue* value, ubyte data);																																																						/* da_purple_value_set_uchar purple_value_set_uchar; */
alias da_purple_value_set_boolean = void function(PurpleValue* value, gboolean data);																																																						/* da_purple_value_set_boolean purple_value_set_boolean; */
alias da_purple_value_set_short = void function(PurpleValue* value, short data);																																																						/* da_purple_value_set_short purple_value_set_short; */
alias da_purple_value_set_ushort = void function(PurpleValue* value, ushort data);																																																						/* da_purple_value_set_ushort purple_value_set_ushort; */
alias da_purple_value_set_int = void function(PurpleValue* value, int data);																																																						/* da_purple_value_set_int purple_value_set_int; */
alias da_purple_value_set_uint = void function(PurpleValue* value, uint data);																																																						/* da_purple_value_set_uint purple_value_set_uint; */
alias da_purple_value_set_long = void function(PurpleValue* value, c_long data);																																																						/* da_purple_value_set_long purple_value_set_long; */
alias da_purple_value_set_ulong = void function(PurpleValue* value, c_ulong data);																																																						/* da_purple_value_set_ulong purple_value_set_ulong; */
alias da_purple_value_set_int64 = void function(PurpleValue* value, gint64 data);																																																						/* da_purple_value_set_int64 purple_value_set_int64; */
alias da_purple_value_set_uint64 = void function(PurpleValue* value, guint64 data);																																																						/* da_purple_value_set_uint64 purple_value_set_uint64; */
alias da_purple_value_set_string = void function(PurpleValue* value, const(char)* data);																																																						/* da_purple_value_set_string purple_value_set_string; */
alias da_purple_value_set_object = void function(PurpleValue* value, void* data);																																																						/* da_purple_value_set_object purple_value_set_object; */
alias da_purple_value_set_pointer = void function(PurpleValue* value, void* data);																																																						/* da_purple_value_set_pointer purple_value_set_pointer; */
alias da_purple_value_set_enum = void function(PurpleValue* value, int data);																																																						/* da_purple_value_set_enum purple_value_set_enum; */
alias da_purple_value_set_boxed = void function(PurpleValue* value, void* data);																																																						/* da_purple_value_set_boxed purple_value_set_boxed; */
alias da_purple_value_get_char = char function(const(PurpleValue)* value);																																																						/* da_purple_value_get_char purple_value_get_char; */
alias da_purple_value_get_uchar = ubyte function(const(PurpleValue)* value);																																																						/* da_purple_value_get_uchar purple_value_get_uchar; */
alias da_purple_value_get_boolean = gboolean function(const(PurpleValue)* value);																																																						/* da_purple_value_get_boolean purple_value_get_boolean; */
alias da_purple_value_get_short = short function(const(PurpleValue)* value);																																																						/* da_purple_value_get_short purple_value_get_short; */
alias da_purple_value_get_ushort = ushort function(const(PurpleValue)* value);																																																						/* da_purple_value_get_ushort purple_value_get_ushort; */
alias da_purple_value_get_int = int function(const(PurpleValue)* value);																																																						/* da_purple_value_get_int purple_value_get_int; */
alias da_purple_value_get_uint = uint function(const(PurpleValue)* value);																																																						/* da_purple_value_get_uint purple_value_get_uint; */
alias da_purple_value_get_long = c_long function(const(PurpleValue)* value);																																																						/* da_purple_value_get_long purple_value_get_long; */
alias da_purple_value_get_ulong = c_ulong function(const(PurpleValue)* value);																																																						/* da_purple_value_get_ulong purple_value_get_ulong; */
alias da_purple_value_get_int64 = gint64 function(const(PurpleValue)* value);																																																						/* da_purple_value_get_int64 purple_value_get_int64; */
alias da_purple_value_get_uint64 = guint64 function(const(PurpleValue)* value);																																																						/* da_purple_value_get_uint64 purple_value_get_uint64; */
alias da_purple_value_get_string = const(char)* function(const(PurpleValue)* value);																																																						/* da_purple_value_get_string purple_value_get_string; */
alias da_purple_value_get_object = void* function(const(PurpleValue)* value);																																																						/* da_purple_value_get_object purple_value_get_object; */
alias da_purple_value_get_pointer = void* function(const(PurpleValue)* value);																																																						/* da_purple_value_get_pointer purple_value_get_pointer; */
alias da_purple_value_get_enum = int function(const(PurpleValue)* value);																																																						/* da_purple_value_get_enum purple_value_get_enum; */
alias da_purple_value_get_boxed = void* function(const(PurpleValue)* value);																																																						/* da_purple_value_get_boxed purple_value_get_boxed; */
