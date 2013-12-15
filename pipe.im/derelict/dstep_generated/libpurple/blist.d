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

PurpleBuddyList* purple_blist_new ();
void purple_set_blist (PurpleBuddyList* blist);
PurpleBuddyList* purple_get_blist ();
PurpleBlistNode* purple_blist_get_root ();
GSList* purple_blist_get_buddies ();
gpointer purple_blist_get_ui_data ();
void purple_blist_set_ui_data (gpointer ui_data);
PurpleBlistNode* purple_blist_node_next (PurpleBlistNode* node, gboolean offline);
PurpleBlistNode* purple_blist_node_get_parent (PurpleBlistNode* node);
PurpleBlistNode* purple_blist_node_get_first_child (PurpleBlistNode* node);
PurpleBlistNode* purple_blist_node_get_sibling_next (PurpleBlistNode* node);
PurpleBlistNode* purple_blist_node_get_sibling_prev (PurpleBlistNode* node);
gpointer purple_blist_node_get_ui_data (const(PurpleBlistNode)* node);
void purple_blist_node_set_ui_data (PurpleBlistNode* node, gpointer ui_data);
void purple_blist_show ();
void purple_blist_destroy ();
void purple_blist_set_visible (gboolean show);
void purple_blist_update_buddy_status (PurpleBuddy* buddy, PurpleStatus* old_status);
void purple_blist_update_node_icon (PurpleBlistNode* node);
void purple_blist_update_buddy_icon (PurpleBuddy* buddy);
void purple_blist_rename_buddy (PurpleBuddy* buddy, const(char)* name);
void purple_blist_alias_contact (PurpleContact* contact, const(char)* alias_);
void purple_blist_alias_buddy (PurpleBuddy* buddy, const(char)* alias_);
void purple_blist_server_alias_buddy (PurpleBuddy* buddy, const(char)* alias_);
void purple_blist_alias_chat (PurpleChat* chat, const(char)* alias_);
void purple_blist_rename_group (PurpleGroup* group, const(char)* name);
PurpleChat* purple_chat_new (PurpleAccount* account, const(char)* alias_, GHashTable* components);
void purple_chat_destroy (PurpleChat* chat);
void purple_blist_add_chat (PurpleChat* chat, PurpleGroup* group, PurpleBlistNode* node);
PurpleBuddy* purple_buddy_new (PurpleAccount* account, const(char)* name, const(char)* alias_);
void purple_buddy_destroy (PurpleBuddy* buddy);
void purple_buddy_set_icon (PurpleBuddy* buddy, PurpleBuddyIcon* icon);
PurpleAccount* purple_buddy_get_account (const(PurpleBuddy)* buddy);
const(char)* purple_buddy_get_name (const(PurpleBuddy)* buddy);
PurpleBuddyIcon* purple_buddy_get_icon (const(PurpleBuddy)* buddy);
gpointer purple_buddy_get_protocol_data (const(PurpleBuddy)* buddy);
void purple_buddy_set_protocol_data (PurpleBuddy* buddy, gpointer data);
PurpleContact* purple_buddy_get_contact (PurpleBuddy* buddy);
PurplePresence* purple_buddy_get_presence (const(PurpleBuddy)* buddy);
PurpleMediaCaps purple_buddy_get_media_caps (const(PurpleBuddy)* buddy);
void purple_buddy_set_media_caps (PurpleBuddy* buddy, PurpleMediaCaps media_caps);
void purple_blist_add_buddy (PurpleBuddy* buddy, PurpleContact* contact, PurpleGroup* group, PurpleBlistNode* node);
PurpleGroup* purple_group_new (const(char)* name);
void purple_group_destroy (PurpleGroup* group);
void purple_blist_add_group (PurpleGroup* group, PurpleBlistNode* node);
PurpleContact* purple_contact_new ();
void purple_contact_destroy (PurpleContact* contact);
PurpleGroup* purple_contact_get_group (const(PurpleContact)* contact);
void purple_blist_add_contact (PurpleContact* contact, PurpleGroup* group, PurpleBlistNode* node);
void purple_blist_merge_contact (PurpleContact* source, PurpleBlistNode* node);
PurpleBuddy* purple_contact_get_priority_buddy (PurpleContact* contact);
void purple_contact_set_alias (PurpleContact* contact, const(char)* alias_);
const(char)* purple_contact_get_alias (PurpleContact* contact);
gboolean purple_contact_on_account (PurpleContact* contact, PurpleAccount* account);
void purple_contact_invalidate_priority_buddy (PurpleContact* contact);
void purple_blist_remove_buddy (PurpleBuddy* buddy);
void purple_blist_remove_contact (PurpleContact* contact);
void purple_blist_remove_chat (PurpleChat* chat);
void purple_blist_remove_group (PurpleGroup* group);
const(char)* purple_buddy_get_alias_only (PurpleBuddy* buddy);
const(char)* purple_buddy_get_server_alias (PurpleBuddy* buddy);
const(char)* purple_buddy_get_contact_alias (PurpleBuddy* buddy);
const(char)* purple_buddy_get_local_alias (PurpleBuddy* buddy);
const(char)* purple_buddy_get_alias (PurpleBuddy* buddy);
const(char)* purple_buddy_get_local_buddy_alias (PurpleBuddy* buddy);
const(char)* purple_chat_get_name (PurpleChat* chat);
PurpleBuddy* purple_find_buddy (PurpleAccount* account, const(char)* name);
PurpleBuddy* purple_find_buddy_in_group (PurpleAccount* account, const(char)* name, PurpleGroup* group);
GSList* purple_find_buddies (PurpleAccount* account, const(char)* name);
PurpleGroup* purple_find_group (const(char)* name);
PurpleChat* purple_blist_find_chat (PurpleAccount* account, const(char)* name);
PurpleGroup* purple_chat_get_group (PurpleChat* chat);
PurpleAccount* purple_chat_get_account (PurpleChat* chat);
GHashTable* purple_chat_get_components (PurpleChat* chat);
PurpleGroup* purple_buddy_get_group (PurpleBuddy* buddy);
GSList* purple_group_get_accounts (PurpleGroup* g);
gboolean purple_group_on_account (PurpleGroup* g, PurpleAccount* account);
const(char)* purple_group_get_name (PurpleGroup* group);
void purple_blist_add_account (PurpleAccount* account);
void purple_blist_remove_account (PurpleAccount* account);
int purple_blist_get_group_size (PurpleGroup* group, gboolean offline);
int purple_blist_get_group_online_count (PurpleGroup* group);
void purple_blist_load ();
void purple_blist_schedule_save ();
void purple_blist_request_add_buddy (PurpleAccount* account, const(char)* username, const(char)* group, const(char)* alias_);
void purple_blist_request_add_chat (PurpleAccount* account, PurpleGroup* group, const(char)* alias_, const(char)* name);
void purple_blist_request_add_group ();
void purple_blist_node_set_bool (PurpleBlistNode* node, const(char)* key, gboolean value);
gboolean purple_blist_node_get_bool (PurpleBlistNode* node, const(char)* key);
void purple_blist_node_set_int (PurpleBlistNode* node, const(char)* key, int value);
int purple_blist_node_get_int (PurpleBlistNode* node, const(char)* key);
void purple_blist_node_set_string (PurpleBlistNode* node, const(char)* key, const(char)* value);
const(char)* purple_blist_node_get_string (PurpleBlistNode* node, const(char)* key);
void purple_blist_node_remove_setting (PurpleBlistNode* node, const(char)* key);
void purple_blist_node_set_flags (PurpleBlistNode* node, PurpleBlistNodeFlags flags);
PurpleBlistNodeFlags purple_blist_node_get_flags (PurpleBlistNode* node);
PurpleBlistNodeType purple_blist_node_get_type (PurpleBlistNode* node);
GList* purple_blist_node_get_extended_menu (PurpleBlistNode* n);
void purple_blist_set_ui_ops (PurpleBlistUiOps* ops);
PurpleBlistUiOps* purple_blist_get_ui_ops ();
void* purple_blist_get_handle ();
void purple_blist_init ();
void purple_blist_uninit ();