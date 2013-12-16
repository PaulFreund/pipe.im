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

void purple_roomlist_show_with_account (PurpleAccount* account);
PurpleRoomlist* purple_roomlist_new (PurpleAccount* account);
void purple_roomlist_ref (PurpleRoomlist* list);
void purple_roomlist_unref (PurpleRoomlist* list);
void purple_roomlist_set_fields (PurpleRoomlist* list, GList* fields);
void purple_roomlist_set_in_progress (PurpleRoomlist* list, gboolean in_progress);
gboolean purple_roomlist_get_in_progress (PurpleRoomlist* list);
void purple_roomlist_room_add (PurpleRoomlist* list, PurpleRoomlistRoom* room);
PurpleRoomlist* purple_roomlist_get_list (PurpleConnection* gc);
void purple_roomlist_cancel_get_list (PurpleRoomlist* list);
void purple_roomlist_expand_category (PurpleRoomlist* list, PurpleRoomlistRoom* category);
GList* purple_roomlist_get_fields (PurpleRoomlist* roomlist);
PurpleRoomlistRoom* purple_roomlist_room_new (PurpleRoomlistRoomType type, const(gchar)* name, PurpleRoomlistRoom* parent);
void purple_roomlist_room_add_field (PurpleRoomlist* list, PurpleRoomlistRoom* room, gconstpointer field);
void purple_roomlist_room_join (PurpleRoomlist* list, PurpleRoomlistRoom* room);
PurpleRoomlistRoomType purple_roomlist_room_get_type (PurpleRoomlistRoom* room);
const(char)* purple_roomlist_room_get_name (PurpleRoomlistRoom* room);
PurpleRoomlistRoom* purple_roomlist_room_get_parent (PurpleRoomlistRoom* room);
GList* purple_roomlist_room_get_fields (PurpleRoomlistRoom* room);
PurpleRoomlistField* purple_roomlist_field_new (PurpleRoomlistFieldType type, const(gchar)* label, const(gchar)* name, gboolean hidden);
PurpleRoomlistFieldType purple_roomlist_field_get_type (PurpleRoomlistField* field);
const(char)* purple_roomlist_field_get_label (PurpleRoomlistField* field);
gboolean purple_roomlist_field_get_hidden (PurpleRoomlistField* field);
void purple_roomlist_set_ui_ops (PurpleRoomlistUiOps* ops);
PurpleRoomlistUiOps* purple_roomlist_get_ui_ops ();