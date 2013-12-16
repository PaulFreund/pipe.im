module derelict.purple.conversation;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.glib.ghash;
import derelict.purple.connection;
import derelict.purple.account;
import derelict.purple.buddyicon;
import core.stdc.time;
import core.stdc.config;

extern (C):

alias _PurpleConversationUiOps PurpleConversationUiOps;
alias _PurpleConversation PurpleConversation;
alias _PurpleConvIm PurpleConvIm;
alias _PurpleConvChat PurpleConvChat;
alias _PurpleConvChatBuddy PurpleConvChatBuddy;
alias _PurpleConvMessage PurpleConvMessage;
alias _Anonymous_0 PurpleConversationType;
alias _Anonymous_1 PurpleConvUpdateType;
alias _Anonymous_2 PurpleTypingState;
alias _Anonymous_3 PurpleMessageFlags;
alias _Anonymous_4 PurpleConvChatBuddyFlags;

enum _Anonymous_0
{
	PURPLE_CONV_TYPE_UNKNOWN = 0,
	PURPLE_CONV_TYPE_IM = 1,
	PURPLE_CONV_TYPE_CHAT = 2,
	PURPLE_CONV_TYPE_MISC = 3,
	PURPLE_CONV_TYPE_ANY = 4
}

enum _Anonymous_1
{
	PURPLE_CONV_UPDATE_ADD = 0,
	PURPLE_CONV_UPDATE_REMOVE = 1,
	PURPLE_CONV_UPDATE_ACCOUNT = 2,
	PURPLE_CONV_UPDATE_TYPING = 3,
	PURPLE_CONV_UPDATE_UNSEEN = 4,
	PURPLE_CONV_UPDATE_LOGGING = 5,
	PURPLE_CONV_UPDATE_TOPIC = 6,
	PURPLE_CONV_ACCOUNT_ONLINE = 7,
	PURPLE_CONV_ACCOUNT_OFFLINE = 8,
	PURPLE_CONV_UPDATE_AWAY = 9,
	PURPLE_CONV_UPDATE_ICON = 10,
	PURPLE_CONV_UPDATE_TITLE = 11,
	PURPLE_CONV_UPDATE_CHATLEFT = 12,
	PURPLE_CONV_UPDATE_FEATURES = 13
}

enum _Anonymous_2
{
	PURPLE_NOT_TYPING = 0,
	PURPLE_TYPING = 1,
	PURPLE_TYPED = 2
}

enum _Anonymous_3
{
	PURPLE_MESSAGE_SEND = 1,
	PURPLE_MESSAGE_RECV = 2,
	PURPLE_MESSAGE_SYSTEM = 4,
	PURPLE_MESSAGE_AUTO_RESP = 8,
	PURPLE_MESSAGE_ACTIVE_ONLY = 16,
	PURPLE_MESSAGE_NICK = 32,
	PURPLE_MESSAGE_NO_LOG = 64,
	PURPLE_MESSAGE_WHISPER = 128,
	PURPLE_MESSAGE_ERROR = 512,
	PURPLE_MESSAGE_DELAYED = 1024,
	PURPLE_MESSAGE_RAW = 2048,
	PURPLE_MESSAGE_IMAGES = 4096,
	PURPLE_MESSAGE_NOTIFY = 8192,
	PURPLE_MESSAGE_NO_LINKIFY = 16384,
	PURPLE_MESSAGE_INVISIBLE = 32768
}

enum _Anonymous_4
{
	PURPLE_CBFLAGS_NONE = 0,
	PURPLE_CBFLAGS_VOICE = 1,
	PURPLE_CBFLAGS_HALFOP = 2,
	PURPLE_CBFLAGS_OP = 4,
	PURPLE_CBFLAGS_FOUNDER = 8,
	PURPLE_CBFLAGS_TYPING = 16,
	PURPLE_CBFLAGS_AWAY = 32
}

struct _PurpleConversationUiOps
{
	void function (PurpleConversation*) create_conversation;
	void function (PurpleConversation*) destroy_conversation;
	void function (PurpleConversation*, const(char)*, const(char)*, PurpleMessageFlags, time_t) write_chat;
	void function (PurpleConversation*, const(char)*, const(char)*, PurpleMessageFlags, time_t) write_im;
	void function (PurpleConversation*, const(char)*, const(char)*, const(char)*, PurpleMessageFlags, time_t) write_conv;
	void function (PurpleConversation*, GList*, gboolean) chat_add_users;
	void function (PurpleConversation*, const(char)*, const(char)*, const(char)*) chat_rename_user;
	void function (PurpleConversation*, GList*) chat_remove_users;
	void function (PurpleConversation*, const(char)*) chat_update_user;
	void function (PurpleConversation*) present;
	gboolean function (PurpleConversation*) has_focus;
	gboolean function (PurpleConversation*, const(char)*, gboolean) custom_smiley_add;
	void function (PurpleConversation*, const(char)*, const(guchar)*, gsize) custom_smiley_write;
	void function (PurpleConversation*, const(char)*) custom_smiley_close;
	void function (PurpleConversation*, const(char)*) send_confirm;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurpleConvIm
{
	PurpleConversation* conv;
	PurpleTypingState typing_state;
	guint typing_timeout;
	time_t type_again;
	guint send_typed_timeout;
	PurpleBuddyIcon* icon;
}

struct _PurpleConvChat
{
	PurpleConversation* conv;
	GList* in_room;
	GList* ignored;
	char* who;
	char* topic;
	int id;
	char* nick;
	gboolean left;
	GHashTable* users;
}

struct _PurpleConvChatBuddy
{
	char* name;
	char* alias_;
	char* alias_key;
	gboolean buddy;
	PurpleConvChatBuddyFlags flags;
	GHashTable* attributes;
	gpointer ui_data;
}

struct _PurpleConvMessage
{
	char* who;
	char* what;
	PurpleMessageFlags flags;
	time_t when;
	PurpleConversation* conv;
	char* alias_;
}

struct _PurpleConversation
{
	PurpleConversationType type;
	PurpleAccount* account;
	char* name;
	char* title;
	gboolean logging;
	GList* logs;
	union
	{
		PurpleConvIm* im;
		PurpleConvChat* chat;
		void* misc;
	}
	PurpleConversationUiOps* ui_ops;
	void* ui_data;
	GHashTable* data;
	PurpleConnectionFlags features;
	GList* message_history;
}

PurpleConversation* purple_conversation_new (PurpleConversationType type, PurpleAccount* account, const(char)* name);
void purple_conversation_destroy (PurpleConversation* conv);
void purple_conversation_present (PurpleConversation* conv);
PurpleConversationType purple_conversation_get_type (const(PurpleConversation)* conv);
void purple_conversation_set_ui_ops (PurpleConversation* conv, PurpleConversationUiOps* ops);
void purple_conversations_set_ui_ops (PurpleConversationUiOps* ops);
PurpleConversationUiOps* purple_conversation_get_ui_ops (const(PurpleConversation)* conv);
void purple_conversation_set_account (PurpleConversation* conv, PurpleAccount* account);
PurpleAccount* purple_conversation_get_account (const(PurpleConversation)* conv);
PurpleConnection* purple_conversation_get_gc (const(PurpleConversation)* conv);
void purple_conversation_set_title (PurpleConversation* conv, const(char)* title);
const(char)* purple_conversation_get_title (const(PurpleConversation)* conv);
void purple_conversation_autoset_title (PurpleConversation* conv);
void purple_conversation_set_name (PurpleConversation* conv, const(char)* name);
const(char)* purple_conversation_get_name (const(PurpleConversation)* conv);
const(char)* purple_conv_chat_cb_get_attribute (PurpleConvChatBuddy* cb, const(char)* key);
GList* purple_conv_chat_cb_get_attribute_keys (PurpleConvChatBuddy* cb);
void purple_conv_chat_cb_set_attribute (PurpleConvChat* chat, PurpleConvChatBuddy* cb, const(char)* key, const(char)* value);
void purple_conv_chat_cb_set_attributes (PurpleConvChat* chat, PurpleConvChatBuddy* cb, GList* keys, GList* values);
void purple_conversation_set_logging (PurpleConversation* conv, gboolean log);
gboolean purple_conversation_is_logging (const(PurpleConversation)* conv);
void purple_conversation_close_logs (PurpleConversation* conv);
PurpleConvIm* purple_conversation_get_im_data (const(PurpleConversation)* conv);
PurpleConvChat* purple_conversation_get_chat_data (const(PurpleConversation)* conv);
void purple_conversation_set_data (PurpleConversation* conv, const(char)* key, gpointer data);
gpointer purple_conversation_get_data (PurpleConversation* conv, const(char)* key);
GList* purple_get_conversations ();
GList* purple_get_ims ();
GList* purple_get_chats ();
PurpleConversation* purple_find_conversation_with_account (PurpleConversationType type, const(char)* name, const(PurpleAccount)* account);
void purple_conversation_write (PurpleConversation* conv, const(char)* who, const(char)* message, PurpleMessageFlags flags, time_t mtime);
void purple_conversation_set_features (PurpleConversation* conv, PurpleConnectionFlags features);
PurpleConnectionFlags purple_conversation_get_features (PurpleConversation* conv);
gboolean purple_conversation_has_focus (PurpleConversation* conv);
void purple_conversation_update (PurpleConversation* conv, PurpleConvUpdateType type);
void purple_conversation_foreach (void function (PurpleConversation*) func);
GList* purple_conversation_get_message_history (PurpleConversation* conv);
void purple_conversation_clear_message_history (PurpleConversation* conv);
const(char)* purple_conversation_message_get_sender (PurpleConvMessage* msg);
const(char)* purple_conversation_message_get_message (PurpleConvMessage* msg);
PurpleMessageFlags purple_conversation_message_get_flags (PurpleConvMessage* msg);
time_t purple_conversation_message_get_timestamp (PurpleConvMessage* msg);
PurpleConversation* purple_conv_im_get_conversation (const(PurpleConvIm)* im);
void purple_conv_im_set_icon (PurpleConvIm* im, PurpleBuddyIcon* icon);
PurpleBuddyIcon* purple_conv_im_get_icon (const(PurpleConvIm)* im);
void purple_conv_im_set_typing_state (PurpleConvIm* im, PurpleTypingState state);
PurpleTypingState purple_conv_im_get_typing_state (const(PurpleConvIm)* im);
void purple_conv_im_start_typing_timeout (PurpleConvIm* im, int timeout);
void purple_conv_im_stop_typing_timeout (PurpleConvIm* im);
guint purple_conv_im_get_typing_timeout (const(PurpleConvIm)* im);
void purple_conv_im_set_type_again (PurpleConvIm* im, uint val);
time_t purple_conv_im_get_type_again (const(PurpleConvIm)* im);
void purple_conv_im_start_send_typed_timeout (PurpleConvIm* im);
void purple_conv_im_stop_send_typed_timeout (PurpleConvIm* im);
guint purple_conv_im_get_send_typed_timeout (const(PurpleConvIm)* im);
void purple_conv_im_update_typing (PurpleConvIm* im);
void purple_conv_im_write (PurpleConvIm* im, const(char)* who, const(char)* message, PurpleMessageFlags flags, time_t mtime);
gboolean purple_conv_present_error (const(char)* who, PurpleAccount* account, const(char)* what);
void purple_conv_im_send (PurpleConvIm* im, const(char)* message);
void purple_conv_send_confirm (PurpleConversation* conv, const(char)* message);
void purple_conv_im_send_with_flags (PurpleConvIm* im, const(char)* message, PurpleMessageFlags flags);
gboolean purple_conv_custom_smiley_add (PurpleConversation* conv, const(char)* smile, const(char)* cksum_type, const(char)* chksum, gboolean remote);
void purple_conv_custom_smiley_write (PurpleConversation* conv, const(char)* smile, const(guchar)* data, gsize size);
void purple_conv_custom_smiley_close (PurpleConversation* conv, const(char)* smile);
PurpleConversation* purple_conv_chat_get_conversation (const(PurpleConvChat)* chat);
GList* purple_conv_chat_set_users (PurpleConvChat* chat, GList* users);
GList* purple_conv_chat_get_users (const(PurpleConvChat)* chat);
void purple_conv_chat_ignore (PurpleConvChat* chat, const(char)* name);
void purple_conv_chat_unignore (PurpleConvChat* chat, const(char)* name);
GList* purple_conv_chat_set_ignored (PurpleConvChat* chat, GList* ignored);
GList* purple_conv_chat_get_ignored (const(PurpleConvChat)* chat);
const(char)* purple_conv_chat_get_ignored_user (const(PurpleConvChat)* chat, const(char)* user);
gboolean purple_conv_chat_is_user_ignored (const(PurpleConvChat)* chat, const(char)* user);
void purple_conv_chat_set_topic (PurpleConvChat* chat, const(char)* who, const(char)* topic);
const(char)* purple_conv_chat_get_topic (const(PurpleConvChat)* chat);
void purple_conv_chat_set_id (PurpleConvChat* chat, int id);
int purple_conv_chat_get_id (const(PurpleConvChat)* chat);
void purple_conv_chat_write (PurpleConvChat* chat, const(char)* who, const(char)* message, PurpleMessageFlags flags, time_t mtime);
void purple_conv_chat_send (PurpleConvChat* chat, const(char)* message);
void purple_conv_chat_send_with_flags (PurpleConvChat* chat, const(char)* message, PurpleMessageFlags flags);
void purple_conv_chat_add_user (PurpleConvChat* chat, const(char)* user, const(char)* extra_msg, PurpleConvChatBuddyFlags flags, gboolean new_arrival);
void purple_conv_chat_add_users (PurpleConvChat* chat, GList* users, GList* extra_msgs, GList* flags, gboolean new_arrivals);
void purple_conv_chat_rename_user (PurpleConvChat* chat, const(char)* old_user, const(char)* new_user);
void purple_conv_chat_remove_user (PurpleConvChat* chat, const(char)* user, const(char)* reason);
void purple_conv_chat_remove_users (PurpleConvChat* chat, GList* users, const(char)* reason);
gboolean purple_conv_chat_find_user (PurpleConvChat* chat, const(char)* user);
void purple_conv_chat_user_set_flags (PurpleConvChat* chat, const(char)* user, PurpleConvChatBuddyFlags flags);
PurpleConvChatBuddyFlags purple_conv_chat_user_get_flags (PurpleConvChat* chat, const(char)* user);
void purple_conv_chat_clear_users (PurpleConvChat* chat);
void purple_conv_chat_set_nick (PurpleConvChat* chat, const(char)* nick);
const(char)* purple_conv_chat_get_nick (PurpleConvChat* chat);
PurpleConversation* purple_find_chat (const(PurpleConnection)* gc, int id);
void purple_conv_chat_left (PurpleConvChat* chat);
void purple_conv_chat_invite_user (PurpleConvChat* chat, const(char)* user, const(char)* message, gboolean confirm);
gboolean purple_conv_chat_has_left (PurpleConvChat* chat);
PurpleConvChatBuddy* purple_conv_chat_cb_new (const(char)* name, const(char)* alias_, PurpleConvChatBuddyFlags flags);
PurpleConvChatBuddy* purple_conv_chat_cb_find (PurpleConvChat* chat, const(char)* name);
const(char)* purple_conv_chat_cb_get_name (PurpleConvChatBuddy* cb);
void purple_conv_chat_cb_destroy (PurpleConvChatBuddy* cb);
GList* purple_conversation_get_extended_menu (PurpleConversation* conv);
gboolean purple_conversation_do_command (PurpleConversation* conv, const(gchar)* cmdline, const(gchar)* markup, gchar** error);
void* purple_conversations_get_handle ();
void purple_conversations_init ();
void purple_conversations_uninit ();