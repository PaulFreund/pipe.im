module derelict.purple.blist;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.ghash;
import derelict.glib.gslist;
import derelict.glib.glist;
import derelict.purple.buddyicon;
import derelict.purple.account;
import derelict.purple.status;
import derelict.purple.enum_types;

extern (C):

alias _PurpleBuddyList PurpleBuddyList;
alias _PurpleBlistUiOps PurpleBlistUiOps;
alias _PurpleBlistNode PurpleBlistNode;
alias _PurpleChat PurpleChat;
alias _PurpleGroup PurpleGroup;
alias _PurpleContact PurpleContact;
alias _PurpleBuddy PurpleBuddy;
alias _Anonymous_0 PurpleBlistNodeType;
alias _Anonymous_1 PurpleBlistNodeFlags;

enum _Anonymous_0
{
	PURPLE_BLIST_GROUP_NODE = 0,
	PURPLE_BLIST_CONTACT_NODE = 1,
	PURPLE_BLIST_BUDDY_NODE = 2,
	PURPLE_BLIST_CHAT_NODE = 3,
	PURPLE_BLIST_OTHER_NODE = 4
}

enum _Anonymous_1
{
	PURPLE_BLIST_NODE_FLAG_NO_SAVE = 1
}

struct _PurpleBlistNode
{
	PurpleBlistNodeType type;
	PurpleBlistNode* prev;
	PurpleBlistNode* next;
	PurpleBlistNode* parent;
	PurpleBlistNode* child;
	GHashTable* settings;
	void* ui_data;
	PurpleBlistNodeFlags flags;
}

struct _PurpleBuddy
{
	PurpleBlistNode node;
	char* name;
	char* alias_;
	char* server_alias;
	void* proto_data;
	PurpleBuddyIcon* icon;
	PurpleAccount* account;
	PurplePresence* presence;
	PurpleMediaCaps media_caps;
}

struct _PurpleContact
{
	PurpleBlistNode node;
	char* alias_;
	int totalsize;
	int currentsize;
	int online;
	PurpleBuddy* priority;
	gboolean priority_valid;
}

struct _PurpleGroup
{
	PurpleBlistNode node;
	char* name;
	int totalsize;
	int currentsize;
	int online;
}

struct _PurpleChat
{
	PurpleBlistNode node;
	char* alias_;
	GHashTable* components;
	PurpleAccount* account;
}

struct _PurpleBuddyList
{
	PurpleBlistNode* root;
	GHashTable* buddies;
	void* ui_data;
}

struct _PurpleBlistUiOps
{
	void function (PurpleBuddyList*) new_list;
	void function (PurpleBlistNode*) new_node;
	void function (PurpleBuddyList*) show;
	void function (PurpleBuddyList*, PurpleBlistNode*) update;
	void function (PurpleBuddyList*, PurpleBlistNode*) remove;
	void function (PurpleBuddyList*) destroy;
	void function (PurpleBuddyList*, gboolean) set_visible;
	void function (PurpleAccount*, const(char)*, const(char)*, const(char)*) request_add_buddy;
	void function (PurpleAccount*, PurpleGroup*, const(char)*, const(char)*) request_add_chat;
	void function () request_add_group;
	void function (PurpleBlistNode*) save_node;
	void function (PurpleBlistNode*) remove_node;
	void function (PurpleAccount*) save_account;
	void function () _purple_reserved1;
}

alias da_purple_blist_new = PurpleBuddyList* function();																																																						/* da_purple_blist_new purple_blist_new; */
alias da_purple_set_blist = void function(PurpleBuddyList* blist);																																																						/* da_purple_set_blist purple_set_blist; */
alias da_purple_get_blist = PurpleBuddyList* function();																																																						/* da_purple_get_blist purple_get_blist; */
alias da_purple_blist_get_root = PurpleBlistNode* function();																																																						/* da_purple_blist_get_root purple_blist_get_root; */
alias da_purple_blist_get_buddies = GSList* function();																																																						/* da_purple_blist_get_buddies purple_blist_get_buddies; */
alias da_purple_blist_get_ui_data = gpointer function();																																																						/* da_purple_blist_get_ui_data purple_blist_get_ui_data; */
alias da_purple_blist_set_ui_data = void function(gpointer ui_data);																																																						/* da_purple_blist_set_ui_data purple_blist_set_ui_data; */
alias da_purple_blist_node_next = PurpleBlistNode* function(PurpleBlistNode* node, gboolean offline);																																																						/* da_purple_blist_node_next purple_blist_node_next; */
alias da_purple_blist_node_get_parent = PurpleBlistNode* function(PurpleBlistNode* node);																																																						/* da_purple_blist_node_get_parent purple_blist_node_get_parent; */
alias da_purple_blist_node_get_first_child = PurpleBlistNode* function(PurpleBlistNode* node);																																																						/* da_purple_blist_node_get_first_child purple_blist_node_get_first_child; */
alias da_purple_blist_node_get_sibling_next = PurpleBlistNode* function(PurpleBlistNode* node);																																																						/* da_purple_blist_node_get_sibling_next purple_blist_node_get_sibling_next; */
alias da_purple_blist_node_get_sibling_prev = PurpleBlistNode* function(PurpleBlistNode* node);																																																						/* da_purple_blist_node_get_sibling_prev purple_blist_node_get_sibling_prev; */
alias da_purple_blist_node_get_ui_data = gpointer function(const(PurpleBlistNode)* node);																																																						/* da_purple_blist_node_get_ui_data purple_blist_node_get_ui_data; */
alias da_purple_blist_node_set_ui_data = void function(PurpleBlistNode* node, gpointer ui_data);																																																						/* da_purple_blist_node_set_ui_data purple_blist_node_set_ui_data; */
alias da_purple_blist_show = void function();																																																						/* da_purple_blist_show purple_blist_show; */
alias da_purple_blist_destroy = void function();																																																						/* da_purple_blist_destroy purple_blist_destroy; */
alias da_purple_blist_set_visible = void function(gboolean show);																																																						/* da_purple_blist_set_visible purple_blist_set_visible; */
alias da_purple_blist_update_buddy_status = void function(PurpleBuddy* buddy, PurpleStatus* old_status);																																																						/* da_purple_blist_update_buddy_status purple_blist_update_buddy_status; */
alias da_purple_blist_update_node_icon = void function(PurpleBlistNode* node);																																																						/* da_purple_blist_update_node_icon purple_blist_update_node_icon; */
alias da_purple_blist_update_buddy_icon = void function(PurpleBuddy* buddy);																																																						/* da_purple_blist_update_buddy_icon purple_blist_update_buddy_icon; */
alias da_purple_blist_rename_buddy = void function(PurpleBuddy* buddy, const(char)* name);																																																						/* da_purple_blist_rename_buddy purple_blist_rename_buddy; */
alias da_purple_blist_alias_contact = void function(PurpleContact* contact, const(char)* alias_);																																																						/* da_purple_blist_alias_contact purple_blist_alias_contact; */
alias da_purple_blist_alias_buddy = void function(PurpleBuddy* buddy, const(char)* alias_);																																																						/* da_purple_blist_alias_buddy purple_blist_alias_buddy; */
alias da_purple_blist_server_alias_buddy = void function(PurpleBuddy* buddy, const(char)* alias_);																																																						/* da_purple_blist_server_alias_buddy purple_blist_server_alias_buddy; */
alias da_purple_blist_alias_chat = void function(PurpleChat* chat, const(char)* alias_);																																																						/* da_purple_blist_alias_chat purple_blist_alias_chat; */
alias da_purple_blist_rename_group = void function(PurpleGroup* group, const(char)* name);																																																						/* da_purple_blist_rename_group purple_blist_rename_group; */
alias da_purple_chat_new = PurpleChat* function(PurpleAccount* account, const(char)* alias_, GHashTable* components);																																																						/* da_purple_chat_new purple_chat_new; */
alias da_purple_chat_destroy = void function(PurpleChat* chat);																																																						/* da_purple_chat_destroy purple_chat_destroy; */
alias da_purple_blist_add_chat = void function(PurpleChat* chat, PurpleGroup* group, PurpleBlistNode* node);																																																						/* da_purple_blist_add_chat purple_blist_add_chat; */
alias da_purple_buddy_new = PurpleBuddy* function(PurpleAccount* account, const(char)* name, const(char)* alias_);																																																						/* da_purple_buddy_new purple_buddy_new; */
alias da_purple_buddy_destroy = void function(PurpleBuddy* buddy);																																																						/* da_purple_buddy_destroy purple_buddy_destroy; */
alias da_purple_buddy_set_icon = void function(PurpleBuddy* buddy, PurpleBuddyIcon* icon);																																																						/* da_purple_buddy_set_icon purple_buddy_set_icon; */
alias da_purple_buddy_get_account = PurpleAccount* function(const(PurpleBuddy)* buddy);																																																						/* da_purple_buddy_get_account purple_buddy_get_account; */
alias da_purple_buddy_get_name = const(char)* function(const(PurpleBuddy)* buddy);																																																						/* da_purple_buddy_get_name purple_buddy_get_name; */
alias da_purple_buddy_get_icon = PurpleBuddyIcon* function(const(PurpleBuddy)* buddy);																																																						/* da_purple_buddy_get_icon purple_buddy_get_icon; */
alias da_purple_buddy_get_protocol_data = gpointer function(const(PurpleBuddy)* buddy);																																																						/* da_purple_buddy_get_protocol_data purple_buddy_get_protocol_data; */
alias da_purple_buddy_set_protocol_data = void function(PurpleBuddy* buddy, gpointer data);																																																						/* da_purple_buddy_set_protocol_data purple_buddy_set_protocol_data; */
alias da_purple_buddy_get_contact = PurpleContact* function(PurpleBuddy* buddy);																																																						/* da_purple_buddy_get_contact purple_buddy_get_contact; */
alias da_purple_buddy_get_presence = PurplePresence* function(const(PurpleBuddy)* buddy);																																																						/* da_purple_buddy_get_presence purple_buddy_get_presence; */
alias da_purple_buddy_get_media_caps = PurpleMediaCaps function(const(PurpleBuddy)* buddy);																																																						/* da_purple_buddy_get_media_caps purple_buddy_get_media_caps; */
alias da_purple_buddy_set_media_caps = void function(PurpleBuddy* buddy, PurpleMediaCaps media_caps);																																																						/* da_purple_buddy_set_media_caps purple_buddy_set_media_caps; */
alias da_purple_blist_add_buddy = void function(PurpleBuddy* buddy, PurpleContact* contact, PurpleGroup* group, PurpleBlistNode* node);																																																						/* da_purple_blist_add_buddy purple_blist_add_buddy; */
alias da_purple_group_new = PurpleGroup* function(const(char)* name);																																																						/* da_purple_group_new purple_group_new; */
alias da_purple_group_destroy = void function(PurpleGroup* group);																																																						/* da_purple_group_destroy purple_group_destroy; */
alias da_purple_blist_add_group = void function(PurpleGroup* group, PurpleBlistNode* node);																																																						/* da_purple_blist_add_group purple_blist_add_group; */
alias da_purple_contact_new = PurpleContact* function();																																																						/* da_purple_contact_new purple_contact_new; */
alias da_purple_contact_destroy = void function(PurpleContact* contact);																																																						/* da_purple_contact_destroy purple_contact_destroy; */
alias da_purple_contact_get_group = PurpleGroup* function(const(PurpleContact)* contact);																																																						/* da_purple_contact_get_group purple_contact_get_group; */
alias da_purple_blist_add_contact = void function(PurpleContact* contact, PurpleGroup* group, PurpleBlistNode* node);																																																						/* da_purple_blist_add_contact purple_blist_add_contact; */
alias da_purple_blist_merge_contact = void function(PurpleContact* source, PurpleBlistNode* node);																																																						/* da_purple_blist_merge_contact purple_blist_merge_contact; */
alias da_purple_contact_get_priority_buddy = PurpleBuddy* function(PurpleContact* contact);																																																						/* da_purple_contact_get_priority_buddy purple_contact_get_priority_buddy; */
alias da_purple_contact_set_alias = void function(PurpleContact* contact, const(char)* alias_);																																																						/* da_purple_contact_set_alias purple_contact_set_alias; */
alias da_purple_contact_get_alias = const(char)* function(PurpleContact* contact);																																																						/* da_purple_contact_get_alias purple_contact_get_alias; */
alias da_purple_contact_on_account = gboolean function(PurpleContact* contact, PurpleAccount* account);																																																						/* da_purple_contact_on_account purple_contact_on_account; */
alias da_purple_contact_invalidate_priority_buddy = void function(PurpleContact* contact);																																																						/* da_purple_contact_invalidate_priority_buddy purple_contact_invalidate_priority_buddy; */
alias da_purple_blist_remove_buddy = void function(PurpleBuddy* buddy);																																																						/* da_purple_blist_remove_buddy purple_blist_remove_buddy; */
alias da_purple_blist_remove_contact = void function(PurpleContact* contact);																																																						/* da_purple_blist_remove_contact purple_blist_remove_contact; */
alias da_purple_blist_remove_chat = void function(PurpleChat* chat);																																																						/* da_purple_blist_remove_chat purple_blist_remove_chat; */
alias da_purple_blist_remove_group = void function(PurpleGroup* group);																																																						/* da_purple_blist_remove_group purple_blist_remove_group; */
alias da_purple_buddy_get_alias_only = const(char)* function(PurpleBuddy* buddy);																																																						/* da_purple_buddy_get_alias_only purple_buddy_get_alias_only; */
alias da_purple_buddy_get_server_alias = const(char)* function(PurpleBuddy* buddy);																																																						/* da_purple_buddy_get_server_alias purple_buddy_get_server_alias; */
alias da_purple_buddy_get_contact_alias = const(char)* function(PurpleBuddy* buddy);																																																						/* da_purple_buddy_get_contact_alias purple_buddy_get_contact_alias; */
alias da_purple_buddy_get_local_alias = const(char)* function(PurpleBuddy* buddy);																																																						/* da_purple_buddy_get_local_alias purple_buddy_get_local_alias; */
alias da_purple_buddy_get_alias = const(char)* function(PurpleBuddy* buddy);																																																						/* da_purple_buddy_get_alias purple_buddy_get_alias; */
alias da_purple_buddy_get_local_buddy_alias = const(char)* function(PurpleBuddy* buddy);																																																						/* da_purple_buddy_get_local_buddy_alias purple_buddy_get_local_buddy_alias; */
alias da_purple_chat_get_name = const(char)* function(PurpleChat* chat);																																																						/* da_purple_chat_get_name purple_chat_get_name; */
alias da_purple_find_buddy = PurpleBuddy* function(PurpleAccount* account, const(char)* name);																																																						/* da_purple_find_buddy purple_find_buddy; */
alias da_purple_find_buddy_in_group = PurpleBuddy* function(PurpleAccount* account, const(char)* name, PurpleGroup* group);																																																						/* da_purple_find_buddy_in_group purple_find_buddy_in_group; */
alias da_purple_find_buddies = GSList* function(PurpleAccount* account, const(char)* name);																																																						/* da_purple_find_buddies purple_find_buddies; */
alias da_purple_find_group = PurpleGroup* function(const(char)* name);																																																						/* da_purple_find_group purple_find_group; */
alias da_purple_blist_find_chat = PurpleChat* function(PurpleAccount* account, const(char)* name);																																																						/* da_purple_blist_find_chat purple_blist_find_chat; */
alias da_purple_chat_get_group = PurpleGroup* function(PurpleChat* chat);																																																						/* da_purple_chat_get_group purple_chat_get_group; */
alias da_purple_chat_get_account = PurpleAccount* function(PurpleChat* chat);																																																						/* da_purple_chat_get_account purple_chat_get_account; */
alias da_purple_chat_get_components = GHashTable* function(PurpleChat* chat);																																																						/* da_purple_chat_get_components purple_chat_get_components; */
alias da_purple_buddy_get_group = PurpleGroup* function(PurpleBuddy* buddy);																																																						/* da_purple_buddy_get_group purple_buddy_get_group; */
alias da_purple_group_get_accounts = GSList* function(PurpleGroup* g);																																																						/* da_purple_group_get_accounts purple_group_get_accounts; */
alias da_purple_group_on_account = gboolean function(PurpleGroup* g, PurpleAccount* account);																																																						/* da_purple_group_on_account purple_group_on_account; */
alias da_purple_group_get_name = const(char)* function(PurpleGroup* group);																																																						/* da_purple_group_get_name purple_group_get_name; */
alias da_purple_blist_add_account = void function(PurpleAccount* account);																																																						/* da_purple_blist_add_account purple_blist_add_account; */
alias da_purple_blist_remove_account = void function(PurpleAccount* account);																																																						/* da_purple_blist_remove_account purple_blist_remove_account; */
alias da_purple_blist_get_group_size = int function(PurpleGroup* group, gboolean offline);																																																						/* da_purple_blist_get_group_size purple_blist_get_group_size; */
alias da_purple_blist_get_group_online_count = int function(PurpleGroup* group);																																																						/* da_purple_blist_get_group_online_count purple_blist_get_group_online_count; */
alias da_purple_blist_load = void function();																																																						/* da_purple_blist_load purple_blist_load; */
alias da_purple_blist_schedule_save = void function();																																																						/* da_purple_blist_schedule_save purple_blist_schedule_save; */
alias da_purple_blist_request_add_buddy = void function(PurpleAccount* account, const(char)* username, const(char)* group, const(char)* alias_);																																																						/* da_purple_blist_request_add_buddy purple_blist_request_add_buddy; */
alias da_purple_blist_request_add_chat = void function(PurpleAccount* account, PurpleGroup* group, const(char)* alias_, const(char)* name);																																																						/* da_purple_blist_request_add_chat purple_blist_request_add_chat; */
alias da_purple_blist_request_add_group = void function();																																																						/* da_purple_blist_request_add_group purple_blist_request_add_group; */
alias da_purple_blist_node_set_bool = void function(PurpleBlistNode* node, const(char)* key, gboolean value);																																																						/* da_purple_blist_node_set_bool purple_blist_node_set_bool; */
alias da_purple_blist_node_get_bool = gboolean function(PurpleBlistNode* node, const(char)* key);																																																						/* da_purple_blist_node_get_bool purple_blist_node_get_bool; */
alias da_purple_blist_node_set_int = void function(PurpleBlistNode* node, const(char)* key, int value);																																																						/* da_purple_blist_node_set_int purple_blist_node_set_int; */
alias da_purple_blist_node_get_int = int function(PurpleBlistNode* node, const(char)* key);																																																						/* da_purple_blist_node_get_int purple_blist_node_get_int; */
alias da_purple_blist_node_set_string = void function(PurpleBlistNode* node, const(char)* key, const(char)* value);																																																						/* da_purple_blist_node_set_string purple_blist_node_set_string; */
alias da_purple_blist_node_get_string = const(char)* function(PurpleBlistNode* node, const(char)* key);																																																						/* da_purple_blist_node_get_string purple_blist_node_get_string; */
alias da_purple_blist_node_remove_setting = void function(PurpleBlistNode* node, const(char)* key);																																																						/* da_purple_blist_node_remove_setting purple_blist_node_remove_setting; */
alias da_purple_blist_node_set_flags = void function(PurpleBlistNode* node, PurpleBlistNodeFlags flags);																																																						/* da_purple_blist_node_set_flags purple_blist_node_set_flags; */
alias da_purple_blist_node_get_flags = PurpleBlistNodeFlags function(PurpleBlistNode* node);																																																						/* da_purple_blist_node_get_flags purple_blist_node_get_flags; */
alias da_purple_blist_node_get_type = PurpleBlistNodeType function(PurpleBlistNode* node);																																																						/* da_purple_blist_node_get_type purple_blist_node_get_type; */
alias da_purple_blist_node_get_extended_menu = GList* function(PurpleBlistNode* n);																																																						/* da_purple_blist_node_get_extended_menu purple_blist_node_get_extended_menu; */
alias da_purple_blist_set_ui_ops = void function(PurpleBlistUiOps* ops);																																																						/* da_purple_blist_set_ui_ops purple_blist_set_ui_ops; */
alias da_purple_blist_get_ui_ops = PurpleBlistUiOps* function();																																																						/* da_purple_blist_get_ui_ops purple_blist_get_ui_ops; */
alias da_purple_blist_get_handle = void* function();																																																						/* da_purple_blist_get_handle purple_blist_get_handle; */
alias da_purple_blist_init = void function();																																																						/* da_purple_blist_init purple_blist_init; */
alias da_purple_blist_uninit = void function();																																																						/* da_purple_blist_uninit purple_blist_uninit; */
