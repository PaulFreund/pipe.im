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


void* purple_notify_searchresults (PurpleConnection* gc, const(char)* title, const(char)* primary, const(char)* secondary, PurpleNotifySearchResults* results, PurpleNotifyCloseCallback cb, gpointer user_data);
void purple_notify_searchresults_free (PurpleNotifySearchResults* results);
void purple_notify_searchresults_new_rows (PurpleConnection* gc, PurpleNotifySearchResults* results, void* data);
void purple_notify_searchresults_button_add (PurpleNotifySearchResults* results, PurpleNotifySearchButtonType type, PurpleNotifySearchResultsCallback cb);
void purple_notify_searchresults_button_add_labeled (PurpleNotifySearchResults* results, const(char)* label, PurpleNotifySearchResultsCallback cb);
PurpleNotifySearchResults* purple_notify_searchresults_new ();
PurpleNotifySearchColumn* purple_notify_searchresults_column_new (const(char)* title);
void purple_notify_searchresults_column_add (PurpleNotifySearchResults* results, PurpleNotifySearchColumn* column);
void purple_notify_searchresults_row_add (PurpleNotifySearchResults* results, GList* row);
guint purple_notify_searchresults_get_rows_count (PurpleNotifySearchResults* results);
guint purple_notify_searchresults_get_columns_count (PurpleNotifySearchResults* results);
GList* purple_notify_searchresults_row_get (PurpleNotifySearchResults* results, uint row_id);
char* purple_notify_searchresults_column_get_title (PurpleNotifySearchResults* results, uint column_id);
void* purple_notify_message (void* handle, PurpleNotifyMsgType type, const(char)* title, const(char)* primary, const(char)* secondary, PurpleNotifyCloseCallback cb, gpointer user_data);
void* purple_notify_email (void* handle, const(char)* subject, const(char)* from, const(char)* to, const(char)* url, PurpleNotifyCloseCallback cb, gpointer user_data);
void* purple_notify_emails (void* handle, size_t count, gboolean detailed, const(char*)* subjects, const(char*)* froms, const(char*)* tos, const(char*)* urls, PurpleNotifyCloseCallback cb, gpointer user_data);
void* purple_notify_formatted (void* handle, const(char)* title, const(char)* primary, const(char)* secondary, const(char)* text, PurpleNotifyCloseCallback cb, gpointer user_data);
void* purple_notify_userinfo (PurpleConnection* gc, const(char)* who, PurpleNotifyUserInfo* user_info, PurpleNotifyCloseCallback cb, gpointer user_data);
PurpleNotifyUserInfo* purple_notify_user_info_new ();
void purple_notify_user_info_destroy (PurpleNotifyUserInfo* user_info);
GList* purple_notify_user_info_get_entries (PurpleNotifyUserInfo* user_info);
char* purple_notify_user_info_get_text_with_newline (PurpleNotifyUserInfo* user_info, const(char)* newline);
void purple_notify_user_info_add_pair (PurpleNotifyUserInfo* user_info, const(char)* label, const(char)* value);
void purple_notify_user_info_add_pair_plaintext (PurpleNotifyUserInfo* user_info, const(char)* label, const(char)* value);
void purple_notify_user_info_prepend_pair (PurpleNotifyUserInfo* user_info, const(char)* label, const(char)* value);
void purple_notify_user_info_remove_entry (PurpleNotifyUserInfo* user_info, PurpleNotifyUserInfoEntry* user_info_entry);
PurpleNotifyUserInfoEntry* purple_notify_user_info_entry_new (const(char)* label, const(char)* value);
void purple_notify_user_info_add_section_break (PurpleNotifyUserInfo* user_info);
void purple_notify_user_info_prepend_section_break (PurpleNotifyUserInfo* user_info);
void purple_notify_user_info_add_section_header (PurpleNotifyUserInfo* user_info, const(char)* label);
void purple_notify_user_info_prepend_section_header (PurpleNotifyUserInfo* user_info, const(char)* label);
void purple_notify_user_info_remove_last_item (PurpleNotifyUserInfo* user_info);
const(gchar)* purple_notify_user_info_entry_get_label (PurpleNotifyUserInfoEntry* user_info_entry);
void purple_notify_user_info_entry_set_label (PurpleNotifyUserInfoEntry* user_info_entry, const(char)* label);
const(gchar)* purple_notify_user_info_entry_get_value (PurpleNotifyUserInfoEntry* user_info_entry);
void purple_notify_user_info_entry_set_value (PurpleNotifyUserInfoEntry* user_info_entry, const(char)* value);
PurpleNotifyUserInfoEntryType purple_notify_user_info_entry_get_type (PurpleNotifyUserInfoEntry* user_info_entry);
void purple_notify_user_info_entry_set_type (PurpleNotifyUserInfoEntry* user_info_entry, PurpleNotifyUserInfoEntryType type);
void* purple_notify_uri (void* handle, const(char)* uri);
void purple_notify_close (PurpleNotifyType type, void* ui_handle);
void purple_notify_close_with_handle (void* handle);
void purple_notify_set_ui_ops (PurpleNotifyUiOps* ops);
PurpleNotifyUiOps* purple_notify_get_ui_ops ();
void* purple_notify_get_handle ();
void purple_notify_init ();
void purple_notify_uninit ();