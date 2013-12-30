//###################################################################################################
/*
Copyright (c) since 2013 - Paul Freund 

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/
//###################################################################################################

module purple.callbacks;

//###################################################################################################

import purple.client;
import derelict.glib.glib;
import derelict.purple.purple;
import std.stdio;
import std.conv;

//###################################################################################################

const int PURPLE_GLIB_READ_COND  = GIOCondition.G_IO_IN | GIOCondition.G_IO_HUP | GIOCondition.G_IO_ERR;
const int PURPLE_GLIB_WRITE_COND = GIOCondition.G_IO_OUT | GIOCondition.G_IO_HUP | GIOCondition.G_IO_ERR | GIOCondition.G_IO_NVAL;

struct PurpleGLibIOClosure {
    PurpleInputFunction fkt;
    guint result;
    gpointer data;
}

//===================================================================================================
// General callbacks
//===================================================================================================

static extern(C) guint purple_cb_input_add(gint fd, PurpleInputCondition condition, PurpleInputFunction fkt, gpointer data) {
    GIOChannel *channel;
    
    version(Win32)
        channel = wpurple_g_io_channel_win32_new_socket(fd);
    else 
        channel = g_io_channel_unix_new(fd);

    GIOCondition cond = cast(GIOCondition)0;
    if(condition & PurpleInputCondition.PURPLE_INPUT_READ)
        cond = cast(GIOCondition)(cond | cast(int)(PURPLE_GLIB_READ_COND));
    if(condition & PurpleInputCondition.PURPLE_INPUT_WRITE)
        cond = cast(GIOCondition)(cond | cast(int)(PURPLE_GLIB_WRITE_COND));

    PurpleGLibIOClosure *closure = new PurpleGLibIOClosure();
    closure.fkt = fkt;
    closure.data = data;
    closure.result = g_io_add_watch_full(channel, 0, cond, &purple_cb_io_invoke, cast(void*)closure, null);

    g_io_channel_unref(channel);
    return closure.result;
}

static extern(C) gboolean purple_cb_io_invoke(GIOChannel *source, GIOCondition condition, gpointer data) {
    PurpleGLibIOClosure* closure = cast(PurpleGLibIOClosure *)data;
    PurpleInputCondition purple_cond = cast(PurpleInputCondition)0;

    if(condition & PURPLE_GLIB_READ_COND)
        purple_cond = cast(PurpleInputCondition)(purple_cond | PurpleInputCondition.PURPLE_INPUT_READ);
    if(condition & PURPLE_GLIB_WRITE_COND)
        purple_cond = cast(PurpleInputCondition)(purple_cond | PurpleInputCondition.PURPLE_INPUT_WRITE);

    closure.fkt(closure.data, g_io_channel_unix_get_fd(source), purple_cond);

    return true;
}

//===================================================================================================
// Account callbacks
//===================================================================================================

static extern(C) void purple_cb_account_connecting(PurpleAccount* account, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;
    
}

static extern(C) void purple_cb_account_disabled(PurpleAccount* account, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_enabled(PurpleAccount* account, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_created(PurpleAccount* account, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_destroying(PurpleAccount* account, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_added(PurpleAccount* account, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_removed(PurpleAccount* account, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) gboolean purple_cb_account_status_changed(PurpleAccount* account, PurpleStatus* oldStatus, PurpleStatus* newStatus, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return true;
}

static extern(C) void purple_cb_account_actions_changed(PurpleAccount* account, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_alias_changed(PurpleAccount* account, const char* oldAlias, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) gint purple_cb_account_authorization_requested(PurpleAccount* account, const char* remoteUser, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return 0;
}

static extern(C) gint purple_cb_account_authorization_requested_with_message(PurpleAccount* account, const char* remoteUser, const char* message, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return 0;
}

static extern(C) void purple_cb_account_authorization_denied(PurpleAccount* account, const char* message, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_authorization_granted(PurpleAccount* account, const char* message, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_error_changed(PurpleAccount* account, const char* oldError, const char* newError, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_signed_on(PurpleAccount* account, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_signed_off(PurpleAccount* account, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_account_connection_error(PurpleAccount* account, PurpleConnectionError type, const char* description, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

//===================================================================================================
// Buddy list callbacks
//===================================================================================================


static extern(C) void purple_cb_buddy_status_changed(PurpleBuddy* buddy, PurpleStatus* oldStatus, PurpleStatus* newStatus, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_privacy_changed(PurpleBuddy* buddy, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_idle_changed(PurpleBuddy* buddy, gboolean oldIdle, gboolean newIdle, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_signed_on(PurpleBuddy* buddy, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_signed_off(PurpleBuddy* buddy, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_got_login_time(PurpleBuddy* buddy, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_blist_node_added(PurpleBlistNode* buddy, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_blist_node_removed(PurpleBlistNode* buddy, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_added(PurpleBuddy* buddy, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_removed(PurpleBuddy* buddy, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_icon_changed(PurpleBuddy* buddy, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_blist_node_extended_menu(PurpleBlistNode* buddy, GList** menu, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_blist_node_aliased(PurpleBlistNode* buddy, const char* oldAlias, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_caps_changed(PurpleBuddy* buddy, PurpleMediaCaps oldCaps, PurpleMediaCaps newCaps, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

//===================================================================================================
// Connection callbacks
//===================================================================================================

static extern(C) void purple_cb_signing_on(PurpleConnection* connection, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_signed_on(PurpleConnection* connection, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    client.outputString = "Connected";
}

static extern(C) void purple_cb_signing_off(PurpleConnection* connection, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_signed_off(PurpleConnection* connection, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_connection_error(PurpleConnection* connection, PurpleConnectionError reason, const char* description, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) gboolean purple_cb_autojoin(PurpleConnection* connection, PurpleConnectionError reason, const char* description, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return false;
}

//===================================================================================================
// Conversation callbacks
//===================================================================================================

static extern(C) gboolean purple_cb_writing_im_msg(PurpleAccount* account, const char* sender, char** message, PurpleConversation* conversation, PurpleMessageFlags flags, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return false;
}

static extern(C) void purple_cb_wrote_im_msg(PurpleAccount* account, const char* sender, const char* message, PurpleConversation* conversation, PurpleMessageFlags flags, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_sent_attention(PurpleAccount* account, const char* sender, PurpleConversation* conversation, guint type, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_got_attention(PurpleAccount* account, const char* sender, PurpleConversation* conversation, guint type, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}


/*
purple_signal_register(handle, "sending-im-msg",
                       purple_marshal_VOID__POINTER_POINTER_POINTER,
                       NULL, 3,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new_outgoing(PURPLE_TYPE_STRING));

purple_signal_register(handle, "sent-im-msg",
                       purple_marshal_VOID__POINTER_POINTER_POINTER,
                       NULL, 3,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING));

purple_signal_register(handle, "receiving-im-msg",
                       purple_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER_POINTER,
                       purple_value_new(PURPLE_TYPE_BOOLEAN), 5,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new_outgoing(PURPLE_TYPE_STRING),
                       purple_value_new_outgoing(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new_outgoing(PURPLE_TYPE_UINT));

purple_signal_register(handle, "received-im-msg",
                       purple_marshal_VOID__POINTER_POINTER_POINTER_POINTER_UINT,
                       NULL, 5,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_UINT));

purple_signal_register(handle, "blocked-im-msg",
                       purple_marshal_VOID__POINTER_POINTER_POINTER_UINT_UINT,
                       NULL, 5,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
                                        PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_UINT),
                       purple_value_new(PURPLE_TYPE_UINT));

purple_signal_register(handle, "writing-chat-msg",
                       purple_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER_UINT,
                       purple_value_new(PURPLE_TYPE_BOOLEAN), 5,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new_outgoing(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_UINT));

purple_signal_register(handle, "wrote-chat-msg",
                       purple_marshal_VOID__POINTER_POINTER_POINTER_POINTER_UINT,
                       NULL, 5,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_UINT));

purple_signal_register(handle, "sending-chat-msg",
                       purple_marshal_VOID__POINTER_POINTER_UINT, NULL, 3,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new_outgoing(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_UINT));

purple_signal_register(handle, "sent-chat-msg",
                       purple_marshal_VOID__POINTER_POINTER_UINT, NULL, 3,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_UINT));

purple_signal_register(handle, "receiving-chat-msg",
                       purple_marshal_BOOLEAN__POINTER_POINTER_POINTER_POINTER_POINTER,
                       purple_value_new(PURPLE_TYPE_BOOLEAN), 5,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new_outgoing(PURPLE_TYPE_STRING),
                       purple_value_new_outgoing(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new_outgoing(PURPLE_TYPE_UINT));

purple_signal_register(handle, "received-chat-msg",
                       purple_marshal_VOID__POINTER_POINTER_POINTER_POINTER_UINT,
                       NULL, 5,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_UINT));

purple_signal_register(handle, "conversation-created",
                       purple_marshal_VOID__POINTER, NULL, 1,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION));

purple_signal_register(handle, "conversation-updated",
                       purple_marshal_VOID__POINTER_UINT, NULL, 2,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_UINT));

purple_signal_register(handle, "deleting-conversation",
                       purple_marshal_VOID__POINTER, NULL, 1,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION));

purple_signal_register(handle, "buddy-typing",
                       purple_marshal_VOID__POINTER_POINTER, NULL, 2,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING));

purple_signal_register(handle, "buddy-typed",
                       purple_marshal_VOID__POINTER_POINTER, NULL, 2,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING));

purple_signal_register(handle, "buddy-typing-stopped",
                       purple_marshal_VOID__POINTER_POINTER, NULL, 2,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING));

purple_signal_register(handle, "chat-buddy-joining",
                       purple_marshal_BOOLEAN__POINTER_POINTER_UINT,
                       purple_value_new(PURPLE_TYPE_BOOLEAN), 3,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_UINT));

purple_signal_register(handle, "chat-buddy-joined",
                       purple_marshal_VOID__POINTER_POINTER_UINT_UINT, NULL, 4,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_UINT),
                       purple_value_new(PURPLE_TYPE_BOOLEAN));

purple_signal_register(handle, "chat-buddy-flags",
                       purple_marshal_VOID__POINTER_POINTER_UINT_UINT, NULL, 4,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_UINT),
                       purple_value_new(PURPLE_TYPE_UINT));

purple_signal_register(handle, "chat-buddy-leaving",
                       purple_marshal_BOOLEAN__POINTER_POINTER_POINTER,
                       purple_value_new(PURPLE_TYPE_BOOLEAN), 3,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING));

purple_signal_register(handle, "chat-buddy-left",
                       purple_marshal_VOID__POINTER_POINTER_POINTER, NULL, 3,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING));

purple_signal_register(handle, "deleting-chat-buddy",
                       purple_marshal_VOID__POINTER, NULL, 1,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CHATBUDDY));

purple_signal_register(handle, "chat-inviting-user",
                       purple_marshal_VOID__POINTER_POINTER_POINTER, NULL, 3,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new_outgoing(PURPLE_TYPE_STRING));

purple_signal_register(handle, "chat-invited-user",
                       purple_marshal_VOID__POINTER_POINTER_POINTER, NULL, 3,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING));

purple_signal_register(handle, "chat-invited",
                       purple_marshal_INT__POINTER_POINTER_POINTER_POINTER_POINTER,
                       purple_value_new(PURPLE_TYPE_INT), 5,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_POINTER));

purple_signal_register(handle, "chat-invite-blocked",
                       purple_marshal_VOID__POINTER_POINTER_POINTER_POINTER_POINTER,
                       NULL, 5,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
                                        PURPLE_SUBTYPE_ACCOUNT),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_BOXED, "GHashTable *"));

purple_signal_register(handle, "chat-joined",
                       purple_marshal_VOID__POINTER, NULL, 1,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION));

purple_signal_register(handle, "chat-join-failed",
                       purple_marshal_VOID__POINTER_POINTER, NULL, 2,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONNECTION),
                       purple_value_new(PURPLE_TYPE_POINTER));

purple_signal_register(handle, "chat-left",
                       purple_marshal_VOID__POINTER, NULL, 1,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION));

purple_signal_register(handle, "chat-topic-changed",
                       purple_marshal_VOID__POINTER_POINTER_POINTER, NULL, 3,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
										PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_STRING),
                       purple_value_new(PURPLE_TYPE_STRING));

purple_signal_register(handle, "cleared-message-history",
                       purple_marshal_VOID__POINTER, NULL, 1,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
                                        PURPLE_SUBTYPE_CONVERSATION));

purple_signal_register(handle, "conversation-extended-menu",
                       purple_marshal_VOID__POINTER_POINTER, NULL, 2,
                       purple_value_new(PURPLE_TYPE_SUBTYPE,
                                        PURPLE_SUBTYPE_CONVERSATION),
                       purple_value_new(PURPLE_TYPE_BOXED, "GList **"));


*/


static extern(C) void purple_cb_received_im_msg(PurpleAccount *account, char *sender, char *message, PurpleConversation *conv, PurpleMessageFlags flags, gpointer data) {
    
    PurpleClient client = cast(PurpleClient)data;

    if (conv==null) {
        conv = purple_conversation_new(PurpleConversationType.PURPLE_CONV_TYPE_IM, account, sender);
    }

    client.outputString ~= "(" ~ to!string(purple_utf8_strftime("%H:%M:%S", null)) ~ ") ";
    client.outputString ~= to!string(sender);
    client.outputString ~= "(" ~ to!string(purple_conversation_get_name(conv)) ~ "): ";
    client.outputString ~= to!string(message);
}
