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

import purple.events;
import purple.client;
import derelict.glib.glib;
import derelict.purple.purple;
import std.c.stdarg;
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
// Connect
//===================================================================================================

static PurpleClient g_purpleClient = null;
static PurpleEventLoopUiOps g_eventloopUiOps; 
static PurpleRequestUiOps g_requestUiOps; 

void ConnectUiOpsCallbacks(PurpleClient client) {
    assert(g_purpleClient is null);
    g_purpleClient = client;

    // Eventloop UI ops
    version(Derelict_Link_Static) {
        g_eventloopUiOps = PurpleEventLoopUiOps(&g_timeout_add, &g_source_remove, 
                                               &purple_cb_ops_input_add, &g_source_remove, 
                                               null, &g_timeout_add_seconds, 
                                               null, null, null);
    }
    else {
        g_eventloopUiOps = PurpleEventLoopUiOps(g_timeout_add, g_source_remove, 
                                               &purple_cb_ops_input_add, g_source_remove, 
                                               null, g_timeout_add_seconds, 
                                               null, null, null);
    }

    purple_eventloop_set_ui_ops(&g_eventloopUiOps);

    // Request UI ops
    g_requestUiOps = PurpleRequestUiOps(&purple_cb_ops_request_input, &purple_cb_ops_request_choice, 
                                        &purple_cb_ops_request_action, &purple_cb_ops_request_fields,
                                        &purple_cb_ops_request_file, &purple_cb_ops_close_request,
                                        &purple_cb_ops_request_folder, &purple_cb_ops_request_action_with_icon,
                                        null, null, null);

    purple_request_set_ui_ops(&g_requestUiOps);
}

void ConnectSignalsCallbacks() {
    assert(!(g_purpleClient is null));

    void* cbData = cast(void*)g_purpleClient;
    void* cbHandle = cast(void*)g_purpleClient;

    // Connection
    auto hConnections = purple_connections_get_handle();
    purple_signal_connect(hConnections, "signing-on", cbHandle, cast(PurpleCallback)&purple_cb_signing_on, cbData);
    purple_signal_connect(hConnections, "signed-on", cbHandle, cast(PurpleCallback)&purple_cb_signed_on, cbData);
    purple_signal_connect(hConnections, "signing-off", cbHandle, cast(PurpleCallback)&purple_cb_signing_off, cbData);
    purple_signal_connect(hConnections, "signed-off", cbHandle, cast(PurpleCallback)&purple_cb_signed_off, cbData);
    purple_signal_connect(hConnections, "connection-error", cbHandle, cast(PurpleCallback)&purple_cb_connection_error, cbData);
    purple_signal_connect(hConnections, "autojoin", cbHandle, cast(PurpleCallback)&purple_cb_autojoin, cbData);

    // Accounts
    auto hAccounts = purple_accounts_get_handle();
    purple_signal_connect(hAccounts, "account-connecting", cbHandle, cast(PurpleCallback)&purple_cb_account_connecting, cbData);
    purple_signal_connect(hAccounts, "account-disabled", cbHandle, cast(PurpleCallback)&purple_cb_account_disabled, cbData);
    purple_signal_connect(hAccounts, "account-enabled", cbHandle, cast(PurpleCallback)&purple_cb_account_enabled, cbData);
    purple_signal_connect(hAccounts, "account-created", cbHandle, cast(PurpleCallback)&purple_cb_account_created, cbData);
    purple_signal_connect(hAccounts, "account-destroying", cbHandle, cast(PurpleCallback)&purple_cb_account_destroying, cbData);
    purple_signal_connect(hAccounts, "account-added", cbHandle, cast(PurpleCallback)&purple_cb_account_added, cbData);
    purple_signal_connect(hAccounts, "account-removed", cbHandle, cast(PurpleCallback)&purple_cb_account_removed, cbData);
    purple_signal_connect(hAccounts, "account-status-changed", cbHandle, cast(PurpleCallback)&purple_cb_account_status_changed, cbData);
    purple_signal_connect(hAccounts, "account-actions-changed", cbHandle, cast(PurpleCallback)&purple_cb_account_actions_changed, cbData);
    purple_signal_connect(hAccounts, "account-alias-changed", cbHandle, cast(PurpleCallback)&purple_cb_account_alias_changed, cbData);
    purple_signal_connect(hAccounts, "account-authorization-requested", cbHandle, cast(PurpleCallback)&purple_cb_account_authorization_requested, cbData);
    purple_signal_connect(hAccounts, "account-authorization-requested-with-message", cbHandle, cast(PurpleCallback)&purple_cb_account_authorization_requested_with_message, cbData);
    purple_signal_connect(hAccounts, "account-authorization-denied", cbHandle, cast(PurpleCallback)&purple_cb_account_authorization_denied, cbData);
    purple_signal_connect(hAccounts, "account-authorization-granted", cbHandle, cast(PurpleCallback)&purple_cb_account_authorization_granted, cbData);
    purple_signal_connect(hAccounts, "account-error-changed", cbHandle, cast(PurpleCallback)&purple_cb_account_error_changed, cbData);
    purple_signal_connect(hAccounts, "account-signed-on", cbHandle, cast(PurpleCallback)&purple_cb_account_signed_on, cbData);
    purple_signal_connect(hAccounts, "account-signed-off", cbHandle, cast(PurpleCallback)&purple_cb_account_signed_off, cbData);
    purple_signal_connect(hAccounts, "account-connection-error", cbHandle, cast(PurpleCallback)&purple_cb_account_connection_error, cbData);

    // BuddyList
    auto hBuddyList = purple_blist_get_handle();
    purple_signal_connect(hBuddyList, "buddy-status-changed", cbHandle, cast(PurpleCallback)&purple_cb_buddy_status_changed, cbData);
    purple_signal_connect(hBuddyList, "buddy-privacy-changed", cbHandle, cast(PurpleCallback)&purple_cb_buddy_privacy_changed, cbData);
    purple_signal_connect(hBuddyList, "buddy-idle-changed", cbHandle, cast(PurpleCallback)&purple_cb_buddy_idle_changed, cbData);
    purple_signal_connect(hBuddyList, "buddy-signed-on", cbHandle, cast(PurpleCallback)&purple_cb_buddy_signed_on, cbData);
    purple_signal_connect(hBuddyList, "buddy-signed-off", cbHandle, cast(PurpleCallback)&purple_cb_buddy_signed_off, cbData);
    purple_signal_connect(hBuddyList, "buddy-got-login-time", cbHandle, cast(PurpleCallback)&purple_cb_buddy_got_login_time, cbData);
    purple_signal_connect(hBuddyList, "blist-node-added", cbHandle, cast(PurpleCallback)&purple_cb_blist_node_added, cbData);
    purple_signal_connect(hBuddyList, "blist-node-removed", cbHandle, cast(PurpleCallback)&purple_cb_blist_node_removed, cbData);
    purple_signal_connect(hBuddyList, "buddy-added", cbHandle, cast(PurpleCallback)&purple_cb_buddy_added, cbData);
    purple_signal_connect(hBuddyList, "buddy-removed", cbHandle, cast(PurpleCallback)&purple_cb_buddy_removed, cbData);
    purple_signal_connect(hBuddyList, "buddy-icon-changed", cbHandle, cast(PurpleCallback)&purple_cb_buddy_icon_changed, cbData);
    purple_signal_connect(hBuddyList, "blist-node-extended-menu", cbHandle, cast(PurpleCallback)&purple_cb_blist_node_extended_menu, cbData);
    purple_signal_connect(hBuddyList, "blist-node-aliased", cbHandle, cast(PurpleCallback)&purple_cb_blist_node_aliased, cbData);
    purple_signal_connect(hBuddyList, "buddy-caps-changed", cbHandle, cast(PurpleCallback)&purple_cb_buddy_caps_changed, cbData);

    // Conversation
    auto hConversations = purple_conversations_get_handle();
    purple_signal_connect(hConversations, "writing-im-msg", cbHandle, cast(PurpleCallback)&purple_cb_writing_im_msg, cbData);
    purple_signal_connect(hConversations, "wrote-im-msg", cbHandle, cast(PurpleCallback)&purple_cb_wrote_im_msg, cbData);
    purple_signal_connect(hConversations, "sent-attention", cbHandle, cast(PurpleCallback)&purple_cb_sent_attention, cbData);
    purple_signal_connect(hConversations, "got-attention", cbHandle, cast(PurpleCallback)&purple_cb_got_attention, cbData);
    purple_signal_connect(hConversations, "sending-im-msg", cbHandle, cast(PurpleCallback)&purple_cb_sending_im_msg, cbData);
    purple_signal_connect(hConversations, "sent-im-msg", cbHandle, cast(PurpleCallback)&purple_cb_sent_im_msg, cbData);
    purple_signal_connect(hConversations, "receiving-im-msg", cbHandle, cast(PurpleCallback)&purple_cb_receiving_im_msg, cbData);
    purple_signal_connect(hConversations, "received-im-msg", cbHandle, cast(PurpleCallback)&purple_cb_received_im_msg, cbData);
    purple_signal_connect(hConversations, "blocked-im-msg", cbHandle, cast(PurpleCallback)&purple_cb_blocked_im_msg, cbData);
    purple_signal_connect(hConversations, "writing-chat-msg", cbHandle, cast(PurpleCallback)&purple_cb_writing_chat_msg, cbData);
    purple_signal_connect(hConversations, "wrote-chat-msg", cbHandle, cast(PurpleCallback)&purple_cb_wrote_chat_msg, cbData);
    purple_signal_connect(hConversations, "sending-chat-msg", cbHandle, cast(PurpleCallback)&purple_cb_sending_chat_msg, cbData);
    purple_signal_connect(hConversations, "sent-chat-msg", cbHandle, cast(PurpleCallback)&purple_cb_sent_chat_msg, cbData);
    purple_signal_connect(hConversations, "receiving-chat-msg", cbHandle, cast(PurpleCallback)&purple_cb_receiving_chat_msg, cbData);
    purple_signal_connect(hConversations, "received-chat-msg", cbHandle, cast(PurpleCallback)&purple_cb_received_chat_msg, cbData);
    purple_signal_connect(hConversations, "conversation-created", cbHandle, cast(PurpleCallback)&purple_cb_conversation_created, cbData);
    purple_signal_connect(hConversations, "conversation-updated", cbHandle, cast(PurpleCallback)&purple_cb_conversation_updated, cbData);
    purple_signal_connect(hConversations, "deleting-conversation", cbHandle, cast(PurpleCallback)&purple_cb_deleting_conversation, cbData);
    purple_signal_connect(hConversations, "buddy-typing", cbHandle, cast(PurpleCallback)&purple_cb_buddy_typing, cbData);
    purple_signal_connect(hConversations, "buddy-typed", cbHandle, cast(PurpleCallback)&purple_cb_buddy_typed, cbData);
    purple_signal_connect(hConversations, "buddy-typing-stopped", cbHandle, cast(PurpleCallback)&purple_cb_buddy_typing_stopped, cbData);
    purple_signal_connect(hConversations, "chat-buddy-joining", cbHandle, cast(PurpleCallback)&purple_cb_chat_buddy_joining, cbData);
    purple_signal_connect(hConversations, "chat-buddy-joined", cbHandle, cast(PurpleCallback)&purple_cb_chat_buddy_joined, cbData);
    purple_signal_connect(hConversations, "chat-buddy-flags", cbHandle, cast(PurpleCallback)&purple_cb_chat_buddy_flags, cbData);
    purple_signal_connect(hConversations, "chat-buddy-leaving", cbHandle, cast(PurpleCallback)&purple_cb_chat_buddy_leaving, cbData);
    purple_signal_connect(hConversations, "chat-buddy-left", cbHandle, cast(PurpleCallback)&purple_cb_chat_buddy_left, cbData);
    purple_signal_connect(hConversations, "deleting-chat-buddy", cbHandle, cast(PurpleCallback)&purple_cb_deleting_chat_buddy, cbData);
    purple_signal_connect(hConversations, "chat-inviting-user", cbHandle, cast(PurpleCallback)&purple_cb_chat_inviting_user, cbData);
    purple_signal_connect(hConversations, "chat-invited-user", cbHandle, cast(PurpleCallback)&purple_cb_chat_invited_user, cbData);
    purple_signal_connect(hConversations, "chat-invited", cbHandle, cast(PurpleCallback)&purple_cb_chat_invited, cbData);
    purple_signal_connect(hConversations, "chat-invite-blocked", cbHandle, cast(PurpleCallback)&purple_cb_chat_invite_blocked, cbData);
    purple_signal_connect(hConversations, "chat-joined", cbHandle, cast(PurpleCallback)&purple_cb_chat_joined, cbData);
    purple_signal_connect(hConversations, "chat-join-failed", cbHandle, cast(PurpleCallback)&purple_cb_chat_join_failed, cbData);
    purple_signal_connect(hConversations, "chat-left", cbHandle, cast(PurpleCallback)&purple_cb_chat_left, cbData);
    purple_signal_connect(hConversations, "chat-topic-changed", cbHandle, cast(PurpleCallback)&purple_cb_chat_topic_changed, cbData);
    purple_signal_connect(hConversations, "cleared-message-history", cbHandle, cast(PurpleCallback)&purple_cb_cleared_message_history, cbData);
    purple_signal_connect(hConversations, "conversation-extended-menu", cbHandle, cast(PurpleCallback)&purple_cb_conversation_extended_menu, cbData);

    // Notify
    auto hNotify = purple_notify_get_handle();
    purple_signal_connect(hNotify, "displaying-userinfo", cbHandle, cast(PurpleCallback)&purple_cb_displaying_userinfo, cbData);
}

//===================================================================================================
// UI ops callbacks
//===================================================================================================

static extern(C) guint purple_cb_ops_input_add(gint fd, PurpleInputCondition condition, PurpleInputFunction fkt, gpointer data) {
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
    closure.result = g_io_add_watch_full(channel, 0, cond, &purple_cb_ops_io_invoke, cast(void*)closure, null);

    g_io_channel_unref(channel);
    return closure.result;
}

static extern(C) gboolean purple_cb_ops_io_invoke(GIOChannel *source, GIOCondition condition, gpointer data) {
    PurpleGLibIOClosure* closure = cast(PurpleGLibIOClosure *)data;
    PurpleInputCondition purple_cond = cast(PurpleInputCondition)0;

    if(condition & PURPLE_GLIB_READ_COND)
        purple_cond = cast(PurpleInputCondition)(purple_cond | PurpleInputCondition.PURPLE_INPUT_READ);
    if(condition & PURPLE_GLIB_WRITE_COND)
        purple_cond = cast(PurpleInputCondition)(purple_cond | PurpleInputCondition.PURPLE_INPUT_WRITE);

    closure.fkt(closure.data, g_io_channel_unix_get_fd(source), purple_cond);

    return true;
}


static extern(C) void* purple_cb_ops_request_input(const(char)* title, const(char)* primary, const(char)* secondary, const(char)* default_value, gboolean multiline, gboolean masked, gchar* hint, const(char)* ok_text, GCallback ok_cb, const(char)* cancel_text, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data) {
    PurpleClient client = g_purpleClient;

    return null;
}

static extern(C) void* purple_cb_ops_request_choice(const(char)* title, const(char)* primary, const(char)* secondary, int default_value, const(char)* ok_text, GCallback ok_cb, const(char)* cancel_text, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data, va_list choices) {
    PurpleClient client = g_purpleClient;

    return null;
}

static extern(C) void* purple_cb_ops_request_action(const(char)* title, const(char)* primary, const(char)* secondary, int default_action, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data, size_t action_count, va_list actions) {
    PurpleClient client = g_purpleClient;

    return null;
}

static extern(C) void* purple_cb_ops_request_fields(const(char)* title, const(char)* primary, const(char)* secondary, PurpleRequestFields* fields, const(char)* ok_text, GCallback ok_cb, const(char)* cancel_text, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data) {
    PurpleClient client = g_purpleClient;

    return null;
}

static extern(C) void* purple_cb_ops_request_file(const(char)* title, const(char)* filename, gboolean savedialog, GCallback ok_cb, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data) {
    PurpleClient client = g_purpleClient;

    return null;
}

static extern(C) void purple_cb_ops_close_request(PurpleRequestType type, void* ui_handle) {
    PurpleClient client = g_purpleClient;

}

static extern(C) void* purple_cb_ops_request_folder(const(char)* title, const(char)* dirname, GCallback ok_cb, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data) {
    PurpleClient client = g_purpleClient;

    return null;
}

static extern(C) void* purple_cb_ops_request_action_with_icon(const(char)* title, const(char)* primary, const(char)* secondary, int default_action, PurpleAccount* account, const(char)* who, PurpleConversation* conv, gconstpointer icon_data, gsize icon_size, void* user_data, size_t action_count, va_list actions) {
    PurpleClient client = g_purpleClient;

    return null;
}

//===================================================================================================
// Signals callbacks
//===================================================================================================

static extern(C) void purple_cb_signing_on(PurpleConnection* connection, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_signed_on(PurpleConnection* connection, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    //client.outputString = "Connected";
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

    return false;
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

static extern(C) void purple_cb_sending_im_msg(PurpleAccount* account, const char* sender, char** message , gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_sent_im_msg(PurpleAccount* account, const char* sender, const char* message , gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) gboolean purple_cb_receiving_im_msg(PurpleAccount* account, char** sender, char** message, PurpleConversation *conv, PurpleMessageFlags flags, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return false;
}

static extern(C) void purple_cb_received_im_msg(PurpleAccount* account, const char* sender, const char* message, PurpleConversation *conv, PurpleMessageFlags flags, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    if (conv==null) {
        conv = purple_conversation_new(PurpleConversationType.PURPLE_CONV_TYPE_IM, account, sender);
    }

    //client.outputString ~= "(" ~ to!string(purple_utf8_strftime("%H:%M:%S", null)) ~ ") ";
    //client.outputString ~= to!string(sender);
    //client.outputString ~= "(" ~ to!string(purple_conversation_get_name(conv)) ~ "): ";
    //client.outputString ~= to!string(message);
}


static extern(C) void purple_cb_blocked_im_msg(PurpleAccount* account, const char* sender, const char* message, PurpleMessageFlags flags, uint mtime, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) gboolean purple_cb_writing_chat_msg(PurpleAccount* account, const char* sender, char** message, PurpleConversation* conversation, PurpleMessageFlags flags, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return false;
}

static extern(C) void purple_cb_wrote_chat_msg(PurpleAccount* account, const char* sender, const char* message, PurpleConversation* conversation, PurpleMessageFlags flags, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_sending_chat_msg(PurpleAccount* account, char** message, uint convID, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_sent_chat_msg(PurpleAccount* account, const char* message, uint convID, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) gboolean purple_cb_receiving_chat_msg(PurpleAccount* account, char** sender, char** message, PurpleConversation *conv, PurpleMessageFlags* flags, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return false;
}

static extern(C) void purple_cb_received_chat_msg(PurpleAccount* account, const char* sender, const char* message, PurpleConversation *conv, PurpleMessageFlags flags, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_conversation_created(PurpleConversation *conv, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_conversation_updated(PurpleConversation *conv, PurpleConvUpdateType type, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_deleting_conversation(PurpleConversation *conv, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_typing(PurpleAccount* account, const char* name, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_typed(PurpleAccount* account, const char* name, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_buddy_typing_stopped(PurpleAccount* account, const char* name, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) gboolean purple_cb_chat_buddy_joining(PurpleConversation *conv, const char* name, PurpleConvChatBuddyFlags flags, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return false;
}

static extern(C) void purple_cb_chat_buddy_joined(PurpleConversation *conv, const char* name, PurpleConvChatBuddyFlags flags, gboolean newArrivals, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_chat_buddy_flags(PurpleConversation *conv, const char* name, PurpleConvChatBuddyFlags oldFlags, PurpleConvChatBuddyFlags newFlags, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) gboolean purple_cb_chat_buddy_leaving(PurpleConversation *conv, const char* name, const char* reason, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return false;
}

static extern(C) void purple_cb_chat_buddy_left(PurpleConversation *conv, const char* name, const char* reason, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_deleting_chat_buddy(PurpleConvChatBuddy* buddy, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_chat_inviting_user(PurpleConversation *conv, const char* name, char** message, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_chat_invited_user(PurpleConversation *conv, const char* name, const char* message, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) int purple_cb_chat_invited(PurpleAccount* account, const char* sender, const char* name, const char* message, GHashTable* inviteData, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

    return 0;
}

static extern(C) void purple_cb_chat_invite_blocked(PurpleAccount* account, const char* sender, const char* name, const char* message, GHashTable* inviteData, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_chat_joined(PurpleConversation *conv, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_chat_join_failed(PurpleConnection *connection, GHashTable* joinData, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_chat_left(PurpleConversation *conv, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_chat_topic_changed(PurpleConversation *conv, const char* user, const char* newTopic, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_cleared_message_history(PurpleConversation *conv, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

static extern(C) void purple_cb_conversation_extended_menu(PurpleConversation *conv, GList** menuData, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}

//===================================================================================================
// Notify callbacks
//===================================================================================================

static extern(C) void purple_cb_displaying_userinfo(PurpleAccount* account, const char* who, PurpleNotifyUserInfo* user_info, gpointer data) {
    PurpleClient client = cast(PurpleClient)data;

}