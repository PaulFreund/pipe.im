module derelict.purple.notify;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.connection;

extern (C):

alias _PurpleNotifyUserInfoEntry PurpleNotifyUserInfoEntry;
alias _PurpleNotifyUserInfo PurpleNotifyUserInfo;
alias void function (void*) PurpleNotifyCloseCallback;
alias _Anonymous_0 PurpleNotifyType;
alias _Anonymous_1 PurpleNotifyMsgType;
alias _Anonymous_2 PurpleNotifySearchButtonType;
alias _Anonymous_3 PurpleNotifySearchResults;
alias _Anonymous_4 PurpleNotifyUserInfoEntryType;
alias _Anonymous_5 PurpleNotifySearchColumn;
alias void function (_PurpleConnection*, _GList*, void*) PurpleNotifySearchResultsCallback;
alias _Anonymous_6 PurpleNotifySearchButton;
alias _Anonymous_7 PurpleNotifyUiOps;

enum _Anonymous_0
{
	PURPLE_NOTIFY_MESSAGE = 0,
	PURPLE_NOTIFY_EMAIL = 1,
	PURPLE_NOTIFY_EMAILS = 2,
	PURPLE_NOTIFY_FORMATTED = 3,
	PURPLE_NOTIFY_SEARCHRESULTS = 4,
	PURPLE_NOTIFY_USERINFO = 5,
	PURPLE_NOTIFY_URI = 6
}

enum _Anonymous_1
{
	PURPLE_NOTIFY_MSG_ERROR = 0,
	PURPLE_NOTIFY_MSG_WARNING = 1,
	PURPLE_NOTIFY_MSG_INFO = 2
}

enum _Anonymous_2
{
	PURPLE_NOTIFY_BUTTON_LABELED = 0,
	PURPLE_NOTIFY_BUTTON_CONTINUE = 1,
	PURPLE_NOTIFY_BUTTON_ADD = 2,
	PURPLE_NOTIFY_BUTTON_INFO = 3,
	PURPLE_NOTIFY_BUTTON_IM = 4,
	PURPLE_NOTIFY_BUTTON_JOIN = 5,
	PURPLE_NOTIFY_BUTTON_INVITE = 6
}

enum _Anonymous_4
{
	PURPLE_NOTIFY_USER_INFO_ENTRY_PAIR = 0,
	PURPLE_NOTIFY_USER_INFO_ENTRY_SECTION_BREAK = 1,
	PURPLE_NOTIFY_USER_INFO_ENTRY_SECTION_HEADER = 2
}

struct _Anonymous_3
{
	GList* columns;
	GList* rows;
	GList* buttons;
}

struct _Anonymous_5
{
	char* title;
}

struct _Anonymous_6
{
	PurpleNotifySearchButtonType type;
	PurpleNotifySearchResultsCallback callback;
	char* label;
}

struct _Anonymous_7
{
	void* function (PurpleNotifyMsgType, const(char)*, const(char)*, const(char)*) notify_message;
	void* function (PurpleConnection*, const(char)*, const(char)*, const(char)*, const(char)*) notify_email;
	void* function (PurpleConnection*, size_t, gboolean, const(char*)*, const(char*)*, const(char*)*, const(char*)*) notify_emails;
	void* function (const(char)*, const(char)*, const(char)*, const(char)*) notify_formatted;
	void* function (PurpleConnection*, const(char)*, const(char)*, const(char)*, PurpleNotifySearchResults*, gpointer) notify_searchresults;
	void function (PurpleConnection*, PurpleNotifySearchResults*, void*) notify_searchresults_new_rows;
	void* function (PurpleConnection*, const(char)*, PurpleNotifyUserInfo*) notify_userinfo;
	void* function (const(char)*) notify_uri;
	void function (PurpleNotifyType, void*) close_notify;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurpleNotifyUserInfoEntry;


struct _PurpleNotifyUserInfo;


alias da_purple_notify_searchresults = void* function(PurpleConnection* gc, const(char)* title, const(char)* primary, const(char)* secondary, PurpleNotifySearchResults* results, PurpleNotifyCloseCallback cb, gpointer user_data);																																																						/* da_purple_notify_searchresults purple_notify_searchresults; */
alias da_purple_notify_searchresults_free = void function(PurpleNotifySearchResults* results);																																																						/* da_purple_notify_searchresults_free purple_notify_searchresults_free; */
alias da_purple_notify_searchresults_new_rows = void function(PurpleConnection* gc, PurpleNotifySearchResults* results, void* data);																																																						/* da_purple_notify_searchresults_new_rows purple_notify_searchresults_new_rows; */
alias da_purple_notify_searchresults_button_add = void function(PurpleNotifySearchResults* results, PurpleNotifySearchButtonType type, PurpleNotifySearchResultsCallback cb);																																																						/* da_purple_notify_searchresults_button_add purple_notify_searchresults_button_add; */
alias da_purple_notify_searchresults_button_add_labeled = void function(PurpleNotifySearchResults* results, const(char)* label, PurpleNotifySearchResultsCallback cb);																																																						/* da_purple_notify_searchresults_button_add_labeled purple_notify_searchresults_button_add_labeled; */
alias da_purple_notify_searchresults_new = PurpleNotifySearchResults* function();																																																						/* da_purple_notify_searchresults_new purple_notify_searchresults_new; */
alias da_purple_notify_searchresults_column_new = PurpleNotifySearchColumn* function(const(char)* title);																																																						/* da_purple_notify_searchresults_column_new purple_notify_searchresults_column_new; */
alias da_purple_notify_searchresults_column_add = void function(PurpleNotifySearchResults* results, PurpleNotifySearchColumn* column);																																																						/* da_purple_notify_searchresults_column_add purple_notify_searchresults_column_add; */
alias da_purple_notify_searchresults_row_add = void function(PurpleNotifySearchResults* results, GList* row);																																																						/* da_purple_notify_searchresults_row_add purple_notify_searchresults_row_add; */
alias da_purple_notify_searchresults_get_rows_count = guint function(PurpleNotifySearchResults* results);																																																						/* da_purple_notify_searchresults_get_rows_count purple_notify_searchresults_get_rows_count; */
alias da_purple_notify_searchresults_get_columns_count = guint function(PurpleNotifySearchResults* results);																																																						/* da_purple_notify_searchresults_get_columns_count purple_notify_searchresults_get_columns_count; */
alias da_purple_notify_searchresults_row_get = GList* function(PurpleNotifySearchResults* results, uint row_id);																																																						/* da_purple_notify_searchresults_row_get purple_notify_searchresults_row_get; */
alias da_purple_notify_searchresults_column_get_title = char* function(PurpleNotifySearchResults* results, uint column_id);																																																						/* da_purple_notify_searchresults_column_get_title purple_notify_searchresults_column_get_title; */
alias da_purple_notify_message = void* function(void* handle, PurpleNotifyMsgType type, const(char)* title, const(char)* primary, const(char)* secondary, PurpleNotifyCloseCallback cb, gpointer user_data);																																																						/* da_purple_notify_message purple_notify_message; */
alias da_purple_notify_email = void* function(void* handle, const(char)* subject, const(char)* from, const(char)* to, const(char)* url, PurpleNotifyCloseCallback cb, gpointer user_data);																																																						/* da_purple_notify_email purple_notify_email; */
alias da_purple_notify_emails = void* function(void* handle, size_t count, gboolean detailed, const(char*)* subjects, const(char*)* froms, const(char*)* tos, const(char*)* urls, PurpleNotifyCloseCallback cb, gpointer user_data);																																																						/* da_purple_notify_emails purple_notify_emails; */
alias da_purple_notify_formatted = void* function(void* handle, const(char)* title, const(char)* primary, const(char)* secondary, const(char)* text, PurpleNotifyCloseCallback cb, gpointer user_data);																																																						/* da_purple_notify_formatted purple_notify_formatted; */
alias da_purple_notify_userinfo = void* function(PurpleConnection* gc, const(char)* who, PurpleNotifyUserInfo* user_info, PurpleNotifyCloseCallback cb, gpointer user_data);																																																						/* da_purple_notify_userinfo purple_notify_userinfo; */
alias da_purple_notify_user_info_new = PurpleNotifyUserInfo* function();																																																						/* da_purple_notify_user_info_new purple_notify_user_info_new; */
alias da_purple_notify_user_info_destroy = void function(PurpleNotifyUserInfo* user_info);																																																						/* da_purple_notify_user_info_destroy purple_notify_user_info_destroy; */
alias da_purple_notify_user_info_get_entries = GList* function(PurpleNotifyUserInfo* user_info);																																																						/* da_purple_notify_user_info_get_entries purple_notify_user_info_get_entries; */
alias da_purple_notify_user_info_get_text_with_newline = char* function(PurpleNotifyUserInfo* user_info, const(char)* newline);																																																						/* da_purple_notify_user_info_get_text_with_newline purple_notify_user_info_get_text_with_newline; */
alias da_purple_notify_user_info_add_pair = void function(PurpleNotifyUserInfo* user_info, const(char)* label, const(char)* value);																																																						/* da_purple_notify_user_info_add_pair purple_notify_user_info_add_pair; */
alias da_purple_notify_user_info_add_pair_plaintext = void function(PurpleNotifyUserInfo* user_info, const(char)* label, const(char)* value);																																																						/* da_purple_notify_user_info_add_pair_plaintext purple_notify_user_info_add_pair_plaintext; */
alias da_purple_notify_user_info_prepend_pair = void function(PurpleNotifyUserInfo* user_info, const(char)* label, const(char)* value);																																																						/* da_purple_notify_user_info_prepend_pair purple_notify_user_info_prepend_pair; */
alias da_purple_notify_user_info_remove_entry = void function(PurpleNotifyUserInfo* user_info, PurpleNotifyUserInfoEntry* user_info_entry);																																																						/* da_purple_notify_user_info_remove_entry purple_notify_user_info_remove_entry; */
alias da_purple_notify_user_info_entry_new = PurpleNotifyUserInfoEntry* function(const(char)* label, const(char)* value);																																																						/* da_purple_notify_user_info_entry_new purple_notify_user_info_entry_new; */
alias da_purple_notify_user_info_add_section_break = void function(PurpleNotifyUserInfo* user_info);																																																						/* da_purple_notify_user_info_add_section_break purple_notify_user_info_add_section_break; */
alias da_purple_notify_user_info_prepend_section_break = void function(PurpleNotifyUserInfo* user_info);																																																						/* da_purple_notify_user_info_prepend_section_break purple_notify_user_info_prepend_section_break; */
alias da_purple_notify_user_info_add_section_header = void function(PurpleNotifyUserInfo* user_info, const(char)* label);																																																						/* da_purple_notify_user_info_add_section_header purple_notify_user_info_add_section_header; */
alias da_purple_notify_user_info_prepend_section_header = void function(PurpleNotifyUserInfo* user_info, const(char)* label);																																																						/* da_purple_notify_user_info_prepend_section_header purple_notify_user_info_prepend_section_header; */
alias da_purple_notify_user_info_remove_last_item = void function(PurpleNotifyUserInfo* user_info);																																																						/* da_purple_notify_user_info_remove_last_item purple_notify_user_info_remove_last_item; */
alias da_purple_notify_user_info_entry_get_label = const(gchar)* function(PurpleNotifyUserInfoEntry* user_info_entry);																																																						/* da_purple_notify_user_info_entry_get_label purple_notify_user_info_entry_get_label; */
alias da_purple_notify_user_info_entry_set_label = void function(PurpleNotifyUserInfoEntry* user_info_entry, const(char)* label);																																																						/* da_purple_notify_user_info_entry_set_label purple_notify_user_info_entry_set_label; */
alias da_purple_notify_user_info_entry_get_value = const(gchar)* function(PurpleNotifyUserInfoEntry* user_info_entry);																																																						/* da_purple_notify_user_info_entry_get_value purple_notify_user_info_entry_get_value; */
alias da_purple_notify_user_info_entry_set_value = void function(PurpleNotifyUserInfoEntry* user_info_entry, const(char)* value);																																																						/* da_purple_notify_user_info_entry_set_value purple_notify_user_info_entry_set_value; */
alias da_purple_notify_user_info_entry_get_type = PurpleNotifyUserInfoEntryType function(PurpleNotifyUserInfoEntry* user_info_entry);																																																						/* da_purple_notify_user_info_entry_get_type purple_notify_user_info_entry_get_type; */
alias da_purple_notify_user_info_entry_set_type = void function(PurpleNotifyUserInfoEntry* user_info_entry, PurpleNotifyUserInfoEntryType type);																																																						/* da_purple_notify_user_info_entry_set_type purple_notify_user_info_entry_set_type; */
alias da_purple_notify_uri = void* function(void* handle, const(char)* uri);																																																						/* da_purple_notify_uri purple_notify_uri; */
alias da_purple_notify_close = void function(PurpleNotifyType type, void* ui_handle);																																																						/* da_purple_notify_close purple_notify_close; */
alias da_purple_notify_close_with_handle = void function(void* handle);																																																						/* da_purple_notify_close_with_handle purple_notify_close_with_handle; */
alias da_purple_notify_set_ui_ops = void function(PurpleNotifyUiOps* ops);																																																						/* da_purple_notify_set_ui_ops purple_notify_set_ui_ops; */
alias da_purple_notify_get_ui_ops = PurpleNotifyUiOps* function();																																																						/* da_purple_notify_get_ui_ops purple_notify_get_ui_ops; */
alias da_purple_notify_get_handle = void* function();																																																						/* da_purple_notify_get_handle purple_notify_get_handle; */
alias da_purple_notify_init = void function();																																																						/* da_purple_notify_init purple_notify_init; */
alias da_purple_notify_uninit = void function();																																																						/* da_purple_notify_uninit purple_notify_uninit; */
