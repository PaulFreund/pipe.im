module derelict.purple.roomlist;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.account;
import derelict.purple.connection;

extern (C):

alias _PurpleRoomlist PurpleRoomlist;
alias _PurpleRoomlistRoom PurpleRoomlistRoom;
alias _PurpleRoomlistField PurpleRoomlistField;
alias _PurpleRoomlistUiOps PurpleRoomlistUiOps;
alias _Anonymous_0 PurpleRoomlistRoomType;
alias _Anonymous_1 PurpleRoomlistFieldType;

enum _Anonymous_0
{
	PURPLE_ROOMLIST_ROOMTYPE_CATEGORY = 1,
	PURPLE_ROOMLIST_ROOMTYPE_ROOM = 2
}

enum _Anonymous_1
{
	PURPLE_ROOMLIST_FIELD_BOOL = 0,
	PURPLE_ROOMLIST_FIELD_INT = 1,
	PURPLE_ROOMLIST_FIELD_STRING = 2
}

struct _PurpleRoomlist
{
	PurpleAccount* account;
	GList* fields;
	GList* rooms;
	gboolean in_progress;
	gpointer ui_data;
	gpointer proto_data;
	guint ref_;
}

struct _PurpleRoomlistRoom
{
	PurpleRoomlistRoomType type;
	gchar* name;
	GList* fields;
	PurpleRoomlistRoom* parent;
	gboolean expanded_once;
}

struct _PurpleRoomlistField
{
	PurpleRoomlistFieldType type;
	gchar* label;
	gchar* name;
	gboolean hidden;
}

struct _PurpleRoomlistUiOps
{
	void function (PurpleAccount*) show_with_account;
	void function (PurpleRoomlist*) create;
	void function (PurpleRoomlist*, GList*) set_fields;
	void function (PurpleRoomlist*, PurpleRoomlistRoom*) add_room;
	void function (PurpleRoomlist*, gboolean) in_progress;
	void function (PurpleRoomlist*) destroy;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

alias da_purple_roomlist_show_with_account = void function(PurpleAccount* account);																																																						/* da_purple_roomlist_show_with_account purple_roomlist_show_with_account; */
alias da_purple_roomlist_new = PurpleRoomlist* function(PurpleAccount* account);																																																						/* da_purple_roomlist_new purple_roomlist_new; */
alias da_purple_roomlist_ref = void function(PurpleRoomlist* list);																																																						/* da_purple_roomlist_ref purple_roomlist_ref; */
alias da_purple_roomlist_unref = void function(PurpleRoomlist* list);																																																						/* da_purple_roomlist_unref purple_roomlist_unref; */
alias da_purple_roomlist_set_fields = void function(PurpleRoomlist* list, GList* fields);																																																						/* da_purple_roomlist_set_fields purple_roomlist_set_fields; */
alias da_purple_roomlist_set_in_progress = void function(PurpleRoomlist* list, gboolean in_progress);																																																						/* da_purple_roomlist_set_in_progress purple_roomlist_set_in_progress; */
alias da_purple_roomlist_get_in_progress = gboolean function(PurpleRoomlist* list);																																																						/* da_purple_roomlist_get_in_progress purple_roomlist_get_in_progress; */
alias da_purple_roomlist_room_add = void function(PurpleRoomlist* list, PurpleRoomlistRoom* room);																																																						/* da_purple_roomlist_room_add purple_roomlist_room_add; */
alias da_purple_roomlist_get_list = PurpleRoomlist* function(PurpleConnection* gc);																																																						/* da_purple_roomlist_get_list purple_roomlist_get_list; */
alias da_purple_roomlist_cancel_get_list = void function(PurpleRoomlist* list);																																																						/* da_purple_roomlist_cancel_get_list purple_roomlist_cancel_get_list; */
alias da_purple_roomlist_expand_category = void function(PurpleRoomlist* list, PurpleRoomlistRoom* category);																																																						/* da_purple_roomlist_expand_category purple_roomlist_expand_category; */
alias da_purple_roomlist_get_fields = GList* function(PurpleRoomlist* roomlist);																																																						/* da_purple_roomlist_get_fields purple_roomlist_get_fields; */
alias da_purple_roomlist_room_new = PurpleRoomlistRoom* function(PurpleRoomlistRoomType type, const(gchar)* name, PurpleRoomlistRoom* parent);																																																						/* da_purple_roomlist_room_new purple_roomlist_room_new; */
alias da_purple_roomlist_room_add_field = void function(PurpleRoomlist* list, PurpleRoomlistRoom* room, gconstpointer field);																																																						/* da_purple_roomlist_room_add_field purple_roomlist_room_add_field; */
alias da_purple_roomlist_room_join = void function(PurpleRoomlist* list, PurpleRoomlistRoom* room);																																																						/* da_purple_roomlist_room_join purple_roomlist_room_join; */
alias da_purple_roomlist_room_get_type = PurpleRoomlistRoomType function(PurpleRoomlistRoom* room);																																																						/* da_purple_roomlist_room_get_type purple_roomlist_room_get_type; */
alias da_purple_roomlist_room_get_name = const(char)* function(PurpleRoomlistRoom* room);																																																						/* da_purple_roomlist_room_get_name purple_roomlist_room_get_name; */
alias da_purple_roomlist_room_get_parent = PurpleRoomlistRoom* function(PurpleRoomlistRoom* room);																																																						/* da_purple_roomlist_room_get_parent purple_roomlist_room_get_parent; */
alias da_purple_roomlist_room_get_fields = GList* function(PurpleRoomlistRoom* room);																																																						/* da_purple_roomlist_room_get_fields purple_roomlist_room_get_fields; */
alias da_purple_roomlist_field_new = PurpleRoomlistField* function(PurpleRoomlistFieldType type, const(gchar)* label, const(gchar)* name, gboolean hidden);																																																						/* da_purple_roomlist_field_new purple_roomlist_field_new; */
alias da_purple_roomlist_field_get_type = PurpleRoomlistFieldType function(PurpleRoomlistField* field);																																																						/* da_purple_roomlist_field_get_type purple_roomlist_field_get_type; */
alias da_purple_roomlist_field_get_label = const(char)* function(PurpleRoomlistField* field);																																																						/* da_purple_roomlist_field_get_label purple_roomlist_field_get_label; */
alias da_purple_roomlist_field_get_hidden = gboolean function(PurpleRoomlistField* field);																																																						/* da_purple_roomlist_field_get_hidden purple_roomlist_field_get_hidden; */
alias da_purple_roomlist_set_ui_ops = void function(PurpleRoomlistUiOps* ops);																																																						/* da_purple_roomlist_set_ui_ops purple_roomlist_set_ui_ops; */
alias da_purple_roomlist_get_ui_ops = PurpleRoomlistUiOps* function();																																																						/* da_purple_roomlist_get_ui_ops purple_roomlist_get_ui_ops; */
