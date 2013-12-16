module derelict.purple.server;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.ghash;
import derelict.purple.blist;
import derelict.purple.connection;
import derelict.purple.conversation;
import derelict.purple.prpl;
import derelict.purple.account;
import core.stdc.time;

extern (C):

alias da_serv_send_typing = uint function(PurpleConnection* gc, const(char)* name, PurpleTypingState state);																																																						/* da_serv_send_typing serv_send_typing; */
alias da_serv_move_buddy = void function(PurpleBuddy*, PurpleGroup*, PurpleGroup*);																																																						/* da_serv_move_buddy serv_move_buddy; */
alias da_serv_send_im = int function(PurpleConnection*, const(char)*, const(char)*, PurpleMessageFlags flags);																																																						/* da_serv_send_im serv_send_im; */
alias da_purple_get_attention_type_from_code = PurpleAttentionType* function(PurpleAccount* account, guint type_code);																																																						/* da_purple_get_attention_type_from_code purple_get_attention_type_from_code; */
alias da_serv_send_attention = void function(PurpleConnection* gc, const(char)* who, guint type_code);																																																						/* da_serv_send_attention serv_send_attention; */
alias da_serv_got_attention = void function(PurpleConnection* gc, const(char)* who, guint type_code);																																																						/* da_serv_got_attention serv_got_attention; */
alias da_serv_get_info = void function(PurpleConnection*, const(char)*);																																																						/* da_serv_get_info serv_get_info; */
alias da_serv_set_info = void function(PurpleConnection*, const(char)*);																																																						/* da_serv_set_info serv_set_info; */
alias da_serv_add_permit = void function(PurpleConnection*, const(char)*);																																																						/* da_serv_add_permit serv_add_permit; */
alias da_serv_add_deny = void function(PurpleConnection*, const(char)*);																																																						/* da_serv_add_deny serv_add_deny; */
alias da_serv_rem_permit = void function(PurpleConnection*, const(char)*);																																																						/* da_serv_rem_permit serv_rem_permit; */
alias da_serv_rem_deny = void function(PurpleConnection*, const(char)*);																																																						/* da_serv_rem_deny serv_rem_deny; */
alias da_serv_set_permit_deny = void function(PurpleConnection*);																																																						/* da_serv_set_permit_deny serv_set_permit_deny; */
alias da_serv_chat_invite = void function(PurpleConnection*, int, const(char)*, const(char)*);																																																						/* da_serv_chat_invite serv_chat_invite; */
alias da_serv_chat_leave = void function(PurpleConnection*, int);																																																						/* da_serv_chat_leave serv_chat_leave; */
alias da_serv_chat_whisper = void function(PurpleConnection*, int, const(char)*, const(char)*);																																																						/* da_serv_chat_whisper serv_chat_whisper; */
alias da_serv_chat_send = int function(PurpleConnection*, int, const(char)*, PurpleMessageFlags flags);																																																						/* da_serv_chat_send serv_chat_send; */
alias da_serv_alias_buddy = void function(PurpleBuddy*);																																																						/* da_serv_alias_buddy serv_alias_buddy; */
alias da_serv_got_alias = void function(PurpleConnection* gc, const(char)* who, const(char)* alias_);																																																						/* da_serv_got_alias serv_got_alias; */
alias da_purple_serv_got_private_alias = void function(PurpleConnection* gc, const(char)* who, const(char)* alias_);																																																						/* da_purple_serv_got_private_alias purple_serv_got_private_alias; */
alias da_serv_got_typing = void function(PurpleConnection* gc, const(char)* name, int timeout, PurpleTypingState state);																																																						/* da_serv_got_typing serv_got_typing; */
alias da_serv_got_typing_stopped = void function(PurpleConnection* gc, const(char)* name);																																																						/* da_serv_got_typing_stopped serv_got_typing_stopped; */
alias da_serv_got_im = void function(PurpleConnection* gc, const(char)* who, const(char)* msg, PurpleMessageFlags flags, time_t mtime);																																																						/* da_serv_got_im serv_got_im; */
alias da_serv_join_chat = void function(PurpleConnection*, GHashTable* data);																																																						/* da_serv_join_chat serv_join_chat; */
alias da_serv_reject_chat = void function(PurpleConnection*, GHashTable* data);																																																						/* da_serv_reject_chat serv_reject_chat; */
alias da_serv_got_chat_invite = void function(PurpleConnection* gc, const(char)* name, const(char)* who, const(char)* message, GHashTable* data);																																																						/* da_serv_got_chat_invite serv_got_chat_invite; */
alias da_serv_got_joined_chat = PurpleConversation* function(PurpleConnection* gc, int id, const(char)* name);																																																						/* da_serv_got_joined_chat serv_got_joined_chat; */
alias da_purple_serv_got_join_chat_failed = void function(PurpleConnection* gc, GHashTable* data);																																																						/* da_purple_serv_got_join_chat_failed purple_serv_got_join_chat_failed; */
alias da_serv_got_chat_left = void function(PurpleConnection* g, int id);																																																						/* da_serv_got_chat_left serv_got_chat_left; */
alias da_serv_got_chat_in = void function(PurpleConnection* g, int id, const(char)* who, PurpleMessageFlags flags, const(char)* message, time_t mtime);																																																						/* da_serv_got_chat_in serv_got_chat_in; */
alias da_serv_send_file = void function(PurpleConnection* gc, const(char)* who, const(char)* file);																																																						/* da_serv_send_file serv_send_file; */
