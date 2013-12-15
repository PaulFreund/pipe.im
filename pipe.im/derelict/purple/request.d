module derelict.purple.request;

import core.stdc.config;

extern (C):

alias _PurpleRequestField PurpleRequestField;
alias _Anonymous_0 PurpleRequestType;
alias _Anonymous_1 PurpleRequestFieldType;
alias _Anonymous_2 PurpleRequestFields;
alias _Anonymous_3 PurpleRequestFieldGroup;
alias _Anonymous_4 PurpleRequestUiOps;
alias void function (void*, const(char)*) PurpleRequestInputCb;
alias void function (void*, int) PurpleRequestActionCb;
alias void function (void*, int) PurpleRequestChoiceCb;
alias void function (void*, _Anonymous_2*) PurpleRequestFieldsCb;
alias void function (void*, const(char)*) PurpleRequestFileCb;

enum _Anonymous_0
{
	PURPLE_REQUEST_INPUT = 0,
	PURPLE_REQUEST_CHOICE = 1,
	PURPLE_REQUEST_ACTION = 2,
	PURPLE_REQUEST_FIELDS = 3,
	PURPLE_REQUEST_FILE = 4,
	PURPLE_REQUEST_FOLDER = 5
}

enum _Anonymous_1
{
	PURPLE_REQUEST_FIELD_NONE = 0,
	PURPLE_REQUEST_FIELD_STRING = 1,
	PURPLE_REQUEST_FIELD_INTEGER = 2,
	PURPLE_REQUEST_FIELD_BOOLEAN = 3,
	PURPLE_REQUEST_FIELD_CHOICE = 4,
	PURPLE_REQUEST_FIELD_LIST = 5,
	PURPLE_REQUEST_FIELD_LABEL = 6,
	PURPLE_REQUEST_FIELD_IMAGE = 7,
	PURPLE_REQUEST_FIELD_ACCOUNT = 8
}

struct _Anonymous_2
{
	GList* groups;
	GHashTable* fields;
	GList* required_fields;
	void* ui_data;
}

struct _Anonymous_3
{
	PurpleRequestFields* fields_list;
	char* title;
	GList* fields;
}

struct _PurpleRequestField
{
	PurpleRequestFieldType type;
	PurpleRequestFieldGroup* group;
	char* id;
	char* label;
	char* type_hint;
	gboolean visible;
	gboolean required;
	union
	{
		struct
		{
			gboolean multiline;
			gboolean masked;
			gboolean editable;
			char* default_value;
			char* value;
		}
		struct
		{
			int default_value;
			int value;
		}
		struct
		{
			gboolean default_value;
			gboolean value;
		}
		struct
		{
			int default_value;
			int value;
			GList* labels;
		}
		struct
		{
			GList* items;
			GList* icons;
			GHashTable* item_data;
			GList* selected;
			GHashTable* selected_table;
			gboolean multiple_selection;
		}
		struct
		{
			PurpleAccount* default_account;
			PurpleAccount* account;
			gboolean show_all;
			PurpleFilterAccountFunc filter_func;
		}
		struct
		{
			uint scale_x;
			uint scale_y;
			const(char)* buffer;
			gsize size;
		}
	}
	void* ui_data;
}

struct _Anonymous_4
{
	void* function (const(char)*, const(char)*, const(char)*, const(char)*, gboolean, gboolean, gchar*, const(char)*, GCallback, const(char)*, GCallback, PurpleAccount*, const(char)*, PurpleConversation*, void*) request_input;
	void* function (const(char)*, const(char)*, const(char)*, int, const(char)*, GCallback, const(char)*, GCallback, PurpleAccount*, const(char)*, PurpleConversation*, void*, __va_list_tag*) request_choice;
	void* function (const(char)*, const(char)*, const(char)*, int, PurpleAccount*, const(char)*, PurpleConversation*, void*, size_t, __va_list_tag*) request_action;
	void* function (const(char)*, const(char)*, const(char)*, PurpleRequestFields*, const(char)*, GCallback, const(char)*, GCallback, PurpleAccount*, const(char)*, PurpleConversation*, void*) request_fields;
	void* function (const(char)*, const(char)*, gboolean, GCallback, GCallback, PurpleAccount*, const(char)*, PurpleConversation*, void*) request_file;
	void function (PurpleRequestType, void*) close_request;
	void* function (const(char)*, const(char)*, GCallback, GCallback, PurpleAccount*, const(char)*, PurpleConversation*, void*) request_folder;
	void* function (const(char)*, const(char)*, const(char)*, int, PurpleAccount*, const(char)*, PurpleConversation*, gconstpointer, gsize, void*, size_t, __va_list_tag*) request_action_with_icon;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
}

PurpleRequestFields* purple_request_fields_new ();
void purple_request_fields_destroy (PurpleRequestFields* fields);
void purple_request_fields_add_group (PurpleRequestFields* fields, PurpleRequestFieldGroup* group);
GList* purple_request_fields_get_groups (const(PurpleRequestFields)* fields);
gboolean purple_request_fields_exists (const(PurpleRequestFields)* fields, const(char)* id);
GList* purple_request_fields_get_required (const(PurpleRequestFields)* fields);
gboolean purple_request_fields_is_field_required (const(PurpleRequestFields)* fields, const(char)* id);
gboolean purple_request_fields_all_required_filled (const(PurpleRequestFields)* fields);
PurpleRequestField* purple_request_fields_get_field (const(PurpleRequestFields)* fields, const(char)* id);
const(char)* purple_request_fields_get_string (const(PurpleRequestFields)* fields, const(char)* id);
int purple_request_fields_get_integer (const(PurpleRequestFields)* fields, const(char)* id);
gboolean purple_request_fields_get_bool (const(PurpleRequestFields)* fields, const(char)* id);
int purple_request_fields_get_choice (const(PurpleRequestFields)* fields, const(char)* id);
PurpleAccount* purple_request_fields_get_account (const(PurpleRequestFields)* fields, const(char)* id);
PurpleRequestFieldGroup* purple_request_field_group_new (const(char)* title);
void purple_request_field_group_destroy (PurpleRequestFieldGroup* group);
void purple_request_field_group_add_field (PurpleRequestFieldGroup* group, PurpleRequestField* field);
const(char)* purple_request_field_group_get_title (const(PurpleRequestFieldGroup)* group);
GList* purple_request_field_group_get_fields (const(PurpleRequestFieldGroup)* group);
PurpleRequestField* purple_request_field_new (const(char)* id, const(char)* text, PurpleRequestFieldType type);
void purple_request_field_destroy (PurpleRequestField* field);
void purple_request_field_set_label (PurpleRequestField* field, const(char)* label);
void purple_request_field_set_visible (PurpleRequestField* field, gboolean visible);
void purple_request_field_set_type_hint (PurpleRequestField* field, const(char)* type_hint);
void purple_request_field_set_required (PurpleRequestField* field, gboolean required);
PurpleRequestFieldType purple_request_field_get_type (const(PurpleRequestField)* field);
PurpleRequestFieldGroup* purple_request_field_get_group (const(PurpleRequestField)* field);
const(char)* purple_request_field_get_id (const(PurpleRequestField)* field);
const(char)* purple_request_field_get_label (const(PurpleRequestField)* field);
gboolean purple_request_field_is_visible (const(PurpleRequestField)* field);
const(char)* purple_request_field_get_type_hint (const(PurpleRequestField)* field);
gboolean purple_request_field_is_required (const(PurpleRequestField)* field);
gpointer purple_request_field_get_ui_data (const(PurpleRequestField)* field);
void purple_request_field_set_ui_data (PurpleRequestField* field, gpointer ui_data);
PurpleRequestField* purple_request_field_string_new (const(char)* id, const(char)* text, const(char)* default_value, gboolean multiline);
void purple_request_field_string_set_default_value (PurpleRequestField* field, const(char)* default_value);
void purple_request_field_string_set_value (PurpleRequestField* field, const(char)* value);
void purple_request_field_string_set_masked (PurpleRequestField* field, gboolean masked);
void purple_request_field_string_set_editable (PurpleRequestField* field, gboolean editable);
const(char)* purple_request_field_string_get_default_value (const(PurpleRequestField)* field);
const(char)* purple_request_field_string_get_value (const(PurpleRequestField)* field);
gboolean purple_request_field_string_is_multiline (const(PurpleRequestField)* field);
gboolean purple_request_field_string_is_masked (const(PurpleRequestField)* field);
gboolean purple_request_field_string_is_editable (const(PurpleRequestField)* field);
PurpleRequestField* purple_request_field_int_new (const(char)* id, const(char)* text, int default_value);
void purple_request_field_int_set_default_value (PurpleRequestField* field, int default_value);
void purple_request_field_int_set_value (PurpleRequestField* field, int value);
int purple_request_field_int_get_default_value (const(PurpleRequestField)* field);
int purple_request_field_int_get_value (const(PurpleRequestField)* field);
PurpleRequestField* purple_request_field_bool_new (const(char)* id, const(char)* text, gboolean default_value);
void purple_request_field_bool_set_default_value (PurpleRequestField* field, gboolean default_value);
void purple_request_field_bool_set_value (PurpleRequestField* field, gboolean value);
gboolean purple_request_field_bool_get_default_value (const(PurpleRequestField)* field);
gboolean purple_request_field_bool_get_value (const(PurpleRequestField)* field);
PurpleRequestField* purple_request_field_choice_new (const(char)* id, const(char)* text, int default_value);
void purple_request_field_choice_add (PurpleRequestField* field, const(char)* label);
void purple_request_field_choice_set_default_value (PurpleRequestField* field, int default_value);
void purple_request_field_choice_set_value (PurpleRequestField* field, int value);
int purple_request_field_choice_get_default_value (const(PurpleRequestField)* field);
int purple_request_field_choice_get_value (const(PurpleRequestField)* field);
GList* purple_request_field_choice_get_labels (const(PurpleRequestField)* field);
PurpleRequestField* purple_request_field_list_new (const(char)* id, const(char)* text);
void purple_request_field_list_set_multi_select (PurpleRequestField* field, gboolean multi_select);
gboolean purple_request_field_list_get_multi_select (const(PurpleRequestField)* field);
void* purple_request_field_list_get_data (const(PurpleRequestField)* field, const(char)* text);
void purple_request_field_list_add (PurpleRequestField* field, const(char)* item, void* data);
void purple_request_field_list_add_icon (PurpleRequestField* field, const(char)* item, const(char)* icon_path, void* data);
void purple_request_field_list_add_selected (PurpleRequestField* field, const(char)* item);
void purple_request_field_list_clear_selected (PurpleRequestField* field);
void purple_request_field_list_set_selected (PurpleRequestField* field, GList* items);
gboolean purple_request_field_list_is_selected (const(PurpleRequestField)* field, const(char)* item);
GList* purple_request_field_list_get_selected (const(PurpleRequestField)* field);
GList* purple_request_field_list_get_items (const(PurpleRequestField)* field);
GList* purple_request_field_list_get_icons (const(PurpleRequestField)* field);
PurpleRequestField* purple_request_field_label_new (const(char)* id, const(char)* text);
PurpleRequestField* purple_request_field_image_new (const(char)* id, const(char)* text, const(char)* buf, gsize size);
void purple_request_field_image_set_scale (PurpleRequestField* field, uint x, uint y);
const(char)* purple_request_field_image_get_buffer (PurpleRequestField* field);
gsize purple_request_field_image_get_size (PurpleRequestField* field);
uint purple_request_field_image_get_scale_x (PurpleRequestField* field);
uint purple_request_field_image_get_scale_y (PurpleRequestField* field);
PurpleRequestField* purple_request_field_account_new (const(char)* id, const(char)* text, PurpleAccount* account);
void purple_request_field_account_set_default_value (PurpleRequestField* field, PurpleAccount* default_value);
void purple_request_field_account_set_value (PurpleRequestField* field, PurpleAccount* value);
void purple_request_field_account_set_show_all (PurpleRequestField* field, gboolean show_all);
void purple_request_field_account_set_filter (PurpleRequestField* field, PurpleFilterAccountFunc filter_func);
PurpleAccount* purple_request_field_account_get_default_value (const(PurpleRequestField)* field);
PurpleAccount* purple_request_field_account_get_value (const(PurpleRequestField)* field);
gboolean purple_request_field_account_get_show_all (const(PurpleRequestField)* field);
PurpleFilterAccountFunc purple_request_field_account_get_filter (const(PurpleRequestField)* field);
void* purple_request_input (void* handle, const(char)* title, const(char)* primary, const(char)* secondary, const(char)* default_value, gboolean multiline, gboolean masked, gchar* hint, const(char)* ok_text, GCallback ok_cb, const(char)* cancel_text, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data);
void* purple_request_choice (void* handle, const(char)* title, const(char)* primary, const(char)* secondary, int default_value, const(char)* ok_text, GCallback ok_cb, const(char)* cancel_text, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data, ...);
void* purple_request_choice_varg (void* handle, const(char)* title, const(char)* primary, const(char)* secondary, int default_value, const(char)* ok_text, GCallback ok_cb, const(char)* cancel_text, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data, __va_list_tag* choices);
void* purple_request_action (void* handle, const(char)* title, const(char)* primary, const(char)* secondary, int default_action, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data, size_t action_count, ...);
void* purple_request_action_varg (void* handle, const(char)* title, const(char)* primary, const(char)* secondary, int default_action, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data, size_t action_count, __va_list_tag* actions);
void* purple_request_action_with_icon (void* handle, const(char)* title, const(char)* primary, const(char)* secondary, int default_action, PurpleAccount* account, const(char)* who, PurpleConversation* conv, gconstpointer icon_data, gsize icon_size, void* user_data, size_t action_count, ...);
void* purple_request_action_with_icon_varg (void* handle, const(char)* title, const(char)* primary, const(char)* secondary, int default_action, PurpleAccount* account, const(char)* who, PurpleConversation* conv, gconstpointer icon_data, gsize icon_size, void* user_data, size_t action_count, __va_list_tag* actions);
void* purple_request_fields (void* handle, const(char)* title, const(char)* primary, const(char)* secondary, PurpleRequestFields* fields, const(char)* ok_text, GCallback ok_cb, const(char)* cancel_text, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data);
void purple_request_close (PurpleRequestType type, void* uihandle);
void purple_request_close_with_handle (void* handle);
void* purple_request_file (void* handle, const(char)* title, const(char)* filename, gboolean savedialog, GCallback ok_cb, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data);
void* purple_request_folder (void* handle, const(char)* title, const(char)* dirname, GCallback ok_cb, GCallback cancel_cb, PurpleAccount* account, const(char)* who, PurpleConversation* conv, void* user_data);
void purple_request_set_ui_ops (PurpleRequestUiOps* ops);
PurpleRequestUiOps* purple_request_get_ui_ops ();