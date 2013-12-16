module derelict.purple.prpl;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.glib.ghash;
import derelict.purple.account;
import derelict.purple.blist;
import derelict.purple.connection;
import derelict.purple.conversation;
import derelict.purple.notify;
import derelict.purple.status;
import derelict.purple.imgstore;
import derelict.purple.roomlist;
import derelict.purple.whiteboard;
import derelict.purple.enum_types;
import derelict.purple.plugin;
import derelict.purple.ft;
import core.stdc.time;
import core.stdc.config;

extern (C):

alias _PurplePluginProtocolInfo PurplePluginProtocolInfo;
alias _PurpleAttentionType PurpleAttentionType;
alias _Anonymous_0 PurpleIconScaleRules;
alias _PurpleBuddyIconSpec PurpleBuddyIconSpec;
alias _PurpleThumbnailSpec PurpleThumbnailSpec;
alias _Anonymous_1 PurpleProtocolOptions;

enum _Anonymous_0
{
	PURPLE_ICON_SCALE_DISPLAY = 1,
	PURPLE_ICON_SCALE_SEND = 2
}

enum _Anonymous_1
{
	OPT_PROTO_UNIQUE_CHATNAME = 4,
	OPT_PROTO_CHAT_TOPIC = 8,
	OPT_PROTO_NO_PASSWORD = 16,
	OPT_PROTO_MAIL_CHECK = 32,
	OPT_PROTO_IM_IMAGE = 64,
	OPT_PROTO_PASSWORD_OPTIONAL = 128,
	OPT_PROTO_USE_POINTSIZE = 256,
	OPT_PROTO_REGISTER_NOSCREENNAME = 512,
	OPT_PROTO_SLASH_COMMANDS_NATIVE = 1024,
	OPT_PROTO_INVITE_MESSAGE = 2048
}

struct _PurpleBuddyIconSpec
{
	char* format;
	int min_width;
	int min_height;
	int max_width;
	int max_height;
	size_t max_filesize;
	PurpleIconScaleRules scale_rules;
}

struct proto_chat_entry
{
	const(char)* label;
	const(char)* identifier;
	gboolean required;
	gboolean is_int;
	int min;
	int max;
	gboolean secret;
}

struct _PurpleAttentionType
{
	const(char)* name;
	const(char)* incoming_description;
	const(char)* outgoing_description;
	const(char)* icon_name;
	const(char)* unlocalized_name;
	gpointer _reserved2;
	gpointer _reserved3;
	gpointer _reserved4;
}

struct _PurplePluginProtocolInfo
{
	PurpleProtocolOptions options;
	GList* user_splits;
	GList* protocol_options;
	PurpleBuddyIconSpec icon_spec;
	const(char)* function (PurpleAccount*, PurpleBuddy*) list_icon;
	const(char)* function (PurpleBuddy*) list_emblem;
	char* function (PurpleBuddy*) status_text;
	void function (PurpleBuddy*, PurpleNotifyUserInfo*, gboolean) tooltip_text;
	GList* function (PurpleAccount*) status_types;
	GList* function (PurpleBlistNode*) blist_node_menu;
	GList* function (PurpleConnection*) chat_info;
	GHashTable* function (PurpleConnection*, const(char)*) chat_info_defaults;
	void function (PurpleAccount*) login;
	void function (PurpleConnection*) close;
	int function (PurpleConnection*, const(char)*, const(char)*, PurpleMessageFlags) send_im;
	void function (PurpleConnection*, const(char)*) set_info;
	uint function (PurpleConnection*, const(char)*, PurpleTypingState) send_typing;
	void function (PurpleConnection*, const(char)*) get_info;
	void function (PurpleAccount*, PurpleStatus*) set_status;
	void function (PurpleConnection*, int) set_idle;
	void function (PurpleConnection*, const(char)*, const(char)*) change_passwd;
	void function (PurpleConnection*, PurpleBuddy*, PurpleGroup*) add_buddy;
	void function (PurpleConnection*, GList*, GList*) add_buddies;
	void function (PurpleConnection*, PurpleBuddy*, PurpleGroup*) remove_buddy;
	void function (PurpleConnection*, GList*, GList*) remove_buddies;
	void function (PurpleConnection*, const(char)*) add_permit;
	void function (PurpleConnection*, const(char)*) add_deny;
	void function (PurpleConnection*, const(char)*) rem_permit;
	void function (PurpleConnection*, const(char)*) rem_deny;
	void function (PurpleConnection*) set_permit_deny;
	void function (PurpleConnection*, GHashTable*) join_chat;
	void function (PurpleConnection*, GHashTable*) reject_chat;
	char* function (GHashTable*) get_chat_name;
	void function (PurpleConnection*, int, const(char)*, const(char)*) chat_invite;
	void function (PurpleConnection*, int) chat_leave;
	void function (PurpleConnection*, int, const(char)*, const(char)*) chat_whisper;
	int function (PurpleConnection*, int, const(char)*, PurpleMessageFlags) chat_send;
	void function (PurpleConnection*) keepalive;
	void function (PurpleAccount*) register_user;
	void function (PurpleConnection*, int, const(char)*) get_cb_info;
	void function (PurpleConnection*, int, const(char)*) get_cb_away;
	void function (PurpleConnection*, const(char)*, const(char)*) alias_buddy;
	void function (PurpleConnection*, const(char)*, const(char)*, const(char)*) group_buddy;
	void function (PurpleConnection*, const(char)*, PurpleGroup*, GList*) rename_group;
	void function (PurpleBuddy*) buddy_free;
	void function (PurpleConnection*, const(char)*) convo_closed;
	const(char)* function (const(PurpleAccount)*, const(char)*) normalize;
	void function (PurpleConnection*, PurpleStoredImage*) set_buddy_icon;
	void function (PurpleConnection*, PurpleGroup*) remove_group;
	char* function (PurpleConnection*, int, const(char)*) get_cb_real_name;
	void function (PurpleConnection*, int, const(char)*) set_chat_topic;
	PurpleChat* function (PurpleAccount*, const(char)*) find_blist_chat;
	PurpleRoomlist* function (PurpleConnection*) roomlist_get_list;
	void function (PurpleRoomlist*) roomlist_cancel;
	void function (PurpleRoomlist*, PurpleRoomlistRoom*) roomlist_expand_category;
	gboolean function (PurpleConnection*, const(char)*) can_receive_file;
	void function (PurpleConnection*, const(char)*, const(char)*) send_file;
	PurpleXfer* function (PurpleConnection*, const(char)*) new_xfer;
	gboolean function (const(PurpleBuddy)*) offline_message;
	PurpleWhiteboardPrplOps* whiteboard_prpl_ops;
	int function (PurpleConnection*, const(char)*, int) send_raw;
	char* function (PurpleRoomlistRoom*) roomlist_room_serialize;
	void function (PurpleAccount*, PurpleAccountUnregistrationCb, void*) unregister_user;
	gboolean function (PurpleConnection*, const(char)*, guint) send_attention;
	GList* function (PurpleAccount*) get_attention_types;
	c_ulong struct_size;
	GHashTable* function (PurpleAccount*) get_account_text_table;
	gboolean function (PurpleAccount*, const(char)*, PurpleMediaSessionType) initiate_media;
	PurpleMediaCaps function (PurpleAccount*, const(char)*) get_media_caps;
	PurpleMood* function (PurpleAccount*) get_moods;
	void function (PurpleConnection*, const(char)*, PurpleSetPublicAliasSuccessCallback, PurpleSetPublicAliasFailureCallback) set_public_alias;
	void function (PurpleConnection*, PurpleGetPublicAliasSuccessCallback, PurpleGetPublicAliasFailureCallback) get_public_alias;
	void function (PurpleConnection*, PurpleBuddy*, PurpleGroup*, const(char)*) add_buddy_with_invite;
	void function (PurpleConnection*, GList*, GList*, const(char)*) add_buddies_with_invite;
}

struct _PurpleThumbnailSpec;


PurpleAttentionType* purple_attention_type_new (const(char)* ulname, const(char)* name, const(char)* inc_desc, const(char)* out_desc);
void purple_attention_type_set_name (PurpleAttentionType* type, const(char)* name);
void purple_attention_type_set_incoming_desc (PurpleAttentionType* type, const(char)* desc);
void purple_attention_type_set_outgoing_desc (PurpleAttentionType* type, const(char)* desc);
void purple_attention_type_set_icon_name (PurpleAttentionType* type, const(char)* name);
void purple_attention_type_set_unlocalized_name (PurpleAttentionType* type, const(char)* ulname);
const(char)* purple_attention_type_get_name (const(PurpleAttentionType)* type);
const(char)* purple_attention_type_get_incoming_desc (const(PurpleAttentionType)* type);
const(char)* purple_attention_type_get_outgoing_desc (const(PurpleAttentionType)* type);
const(char)* purple_attention_type_get_icon_name (const(PurpleAttentionType)* type);
const(char)* purple_attention_type_get_unlocalized_name (const(PurpleAttentionType)* type);
void purple_prpl_got_account_idle (PurpleAccount* account, gboolean idle, time_t idle_time);
void purple_prpl_got_account_login_time (PurpleAccount* account, time_t login_time);
void purple_prpl_got_account_status (PurpleAccount* account, const(char)* status_id, ...);
void purple_prpl_got_account_actions (PurpleAccount* account);
void purple_prpl_got_user_idle (PurpleAccount* account, const(char)* name, gboolean idle, time_t idle_time);
void purple_prpl_got_user_login_time (PurpleAccount* account, const(char)* name, time_t login_time);
void purple_prpl_got_user_status (PurpleAccount* account, const(char)* name, const(char)* status_id, ...);
void purple_prpl_got_user_status_deactive (PurpleAccount* account, const(char)* name, const(char)* status_id);
void purple_prpl_change_account_status (PurpleAccount* account, PurpleStatus* old_status, PurpleStatus* new_status);
GList* purple_prpl_get_statuses (PurpleAccount* account, PurplePresence* presence);
void purple_prpl_send_attention (PurpleConnection* gc, const(char)* who, guint type_code);
void purple_prpl_got_attention (PurpleConnection* gc, const(char)* who, guint type_code);
void purple_prpl_got_attention_in_chat (PurpleConnection* gc, int id, const(char)* who, guint type_code);
PurpleMediaCaps purple_prpl_get_media_caps (PurpleAccount* account, const(char)* who);
gboolean purple_prpl_initiate_media (PurpleAccount* account, const(char)* who, PurpleMediaSessionType type);
void purple_prpl_got_media_caps (PurpleAccount* account, const(char)* who);
PurplePlugin* purple_find_prpl (const(char)* id);