import core.stdc.time;

extern (C):

uint serv_send_typing (PurpleConnection* gc, const(char)* name, PurpleTypingState state);
void serv_move_buddy (PurpleBuddy*, PurpleGroup*, PurpleGroup*);
int serv_send_im (PurpleConnection*, const(char)*, const(char)*, PurpleMessageFlags flags);
PurpleAttentionType* purple_get_attention_type_from_code (PurpleAccount* account, guint type_code);
void serv_send_attention (PurpleConnection* gc, const(char)* who, guint type_code);
void serv_got_attention (PurpleConnection* gc, const(char)* who, guint type_code);
void serv_get_info (PurpleConnection*, const(char)*);
void serv_set_info (PurpleConnection*, const(char)*);
void serv_add_permit (PurpleConnection*, const(char)*);
void serv_add_deny (PurpleConnection*, const(char)*);
void serv_rem_permit (PurpleConnection*, const(char)*);
void serv_rem_deny (PurpleConnection*, const(char)*);
void serv_set_permit_deny (PurpleConnection*);
void serv_chat_invite (PurpleConnection*, int, const(char)*, const(char)*);
void serv_chat_leave (PurpleConnection*, int);
void serv_chat_whisper (PurpleConnection*, int, const(char)*, const(char)*);
int serv_chat_send (PurpleConnection*, int, const(char)*, PurpleMessageFlags flags);
void serv_alias_buddy (PurpleBuddy*);
void serv_got_alias (PurpleConnection* gc, const(char)* who, const(char)* alias_);
void purple_serv_got_private_alias (PurpleConnection* gc, const(char)* who, const(char)* alias_);
void serv_got_typing (PurpleConnection* gc, const(char)* name, int timeout, PurpleTypingState state);
void serv_got_typing_stopped (PurpleConnection* gc, const(char)* name);
void serv_got_im (PurpleConnection* gc, const(char)* who, const(char)* msg, PurpleMessageFlags flags, time_t mtime);
void serv_join_chat (PurpleConnection*, GHashTable* data);
void serv_reject_chat (PurpleConnection*, GHashTable* data);
void serv_got_chat_invite (PurpleConnection* gc, const(char)* name, const(char)* who, const(char)* message, GHashTable* data);
PurpleConversation* serv_got_joined_chat (PurpleConnection* gc, int id, const(char)* name);
void purple_serv_got_join_chat_failed (PurpleConnection* gc, GHashTable* data);
void serv_got_chat_left (PurpleConnection* g, int id);
void serv_got_chat_in (PurpleConnection* g, int id, const(char)* who, PurpleMessageFlags flags, const(char)* message, time_t mtime);
void serv_send_file (PurpleConnection* gc, const(char)* who, const(char)* file);