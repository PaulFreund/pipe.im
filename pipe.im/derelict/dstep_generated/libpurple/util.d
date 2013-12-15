import core.stdc.config;
import core.stdc.time;
import core.stdc.config;
import core.stdc.stdio;
import core.stdc.config;
import core.stdc.stdio;
import core.stdc.config;

extern (C):

alias _PurpleUtilFetchUrlData PurpleUtilFetchUrlData;
alias _PurpleMenuAction PurpleMenuAction;
alias _PurpleKeyValuePair PurpleKeyValuePair;
alias char* function (const(char)*, c_ulong) PurpleInfoFieldFormatCallback;
alias void function (_PurpleUtilFetchUrlData*, void*, const(char)*, c_ulong, const(char)*) PurpleUtilFetchUrlCallback;

struct _PurpleMenuAction
{
	char* label;
	PurpleCallback callback;
	gpointer data;
	GList* children;
}

struct _PurpleKeyValuePair
{
	gchar* key;
	void* value;
}

struct _PurpleUtilFetchUrlData;


PurpleMenuAction* purple_menu_action_new (const(char)* label, PurpleCallback callback, gpointer data, GList* children);
void purple_menu_action_free (PurpleMenuAction* act);
void purple_util_set_current_song (const(char)* title, const(char)* artist, const(char)* album);
char* purple_util_format_song_info (const(char)* title, const(char)* artist, const(char)* album, gpointer unused);
void purple_util_init ();
void purple_util_uninit ();
gchar* purple_base16_encode (const(guchar)* data, gsize len);
guchar* purple_base16_decode (const(char)* str, gsize* ret_len);
gchar* purple_base16_encode_chunked (const(guchar)* data, gsize len);
gchar* purple_base64_encode (const(guchar)* data, gsize len);
guchar* purple_base64_decode (const(char)* str, gsize* ret_len);
guchar* purple_quotedp_decode (const(char)* str, gsize* ret_len);
char* purple_mime_decode_field (const(char)* str);
const(char)* purple_utf8_strftime (const(char)* format, const(tm)* tm);
const(char)* purple_get_tzoff_str (const(tm)* tm, gboolean iso);
const(char)* purple_date_format_short (const(tm)* tm);
const(char)* purple_date_format_long (const(tm)* tm);
const(char)* purple_date_format_full (const(tm)* tm);
const(char)* purple_time_format (const(tm)* tm);
time_t purple_time_build (int year, int month, int day, int hour, int min, int sec);
time_t purple_str_to_time (const(char)* timestamp, gboolean utc, tm* tm, c_long* tz_off, const(char*)* rest);
gchar* purple_markup_escape_text (const(gchar)* text, gssize length);
gboolean purple_markup_find_tag (const(char)* needle, const(char)* haystack, const(char*)* start, const(char*)* end, GData** attributes);
gboolean purple_markup_extract_info_field (const(char)* str, int len, PurpleNotifyUserInfo* user_info, const(char)* start_token, int skip, const(char)* end_token, char check_value, const(char)* no_value_token, const(char)* display_name, gboolean is_link, const(char)* link_prefix, PurpleInfoFieldFormatCallback format_cb);
void purple_markup_html_to_xhtml (const(char)* html, char** dest_xhtml, char** dest_plain);
char* purple_markup_strip_html (const(char)* str);
char* purple_markup_linkify (const(char)* str);
char* purple_unescape_text (const(char)* text);
char* purple_unescape_html (const(char)* html);
char* purple_markup_slice (const(char)* str, guint x, guint y);
char* purple_markup_get_tag_name (const(char)* tag);
const(char)* purple_markup_unescape_entity (const(char)* text, int* length);
char* purple_markup_get_css_property (const(gchar)* style, const(gchar)* opt);
gboolean purple_markup_is_rtl (const(char)* html);
const(gchar)* purple_home_dir ();
const(char)* purple_user_dir ();
void purple_util_set_user_dir (const(char)* dir);
int purple_build_dir (const(char)* path, int mode);
gboolean purple_util_write_data_to_file (const(char)* filename, const(char)* data, gssize size);
gboolean purple_util_write_data_to_file_absolute (const(char)* filename_full, const(char)* data, gssize size);
xmlnode* purple_util_read_xml_from_file (const(char)* filename, const(char)* description);
FILE* purple_mkstemp (char** path, gboolean binary);
const(char)* purple_util_get_image_extension (gconstpointer data, size_t len);
char* purple_util_get_image_checksum (gconstpointer image_data, size_t image_len);
char* purple_util_get_image_filename (gconstpointer image_data, size_t image_len);
gboolean purple_program_is_valid (const(char)* program);
gboolean purple_running_gnome ();
gboolean purple_running_kde ();
gboolean purple_running_osx ();
char* purple_fd_get_ip (int fd);
int purple_socket_get_family (int fd);
gboolean purple_socket_speaks_ipv4 (int fd);
gboolean purple_strequal (const(gchar)* left, const(gchar)* right);
const(char)* purple_normalize (const(PurpleAccount)* account, const(char)* str);
const(char)* purple_normalize_nocase (const(PurpleAccount)* account, const(char)* str);
gboolean purple_str_has_prefix (const(char)* s, const(char)* p);
gboolean purple_str_has_suffix (const(char)* s, const(char)* x);
gchar* purple_strdup_withhtml (const(gchar)* src);
char* purple_str_add_cr (const(char)* str);
void purple_str_strip_char (char* str, char thechar);
void purple_util_chrreplace (char* string, char delimiter, char replacement);
gchar* purple_strreplace (const(char)* string, const(char)* delimiter, const(char)* replacement);
char* purple_utf8_ncr_encode (const(char)* in_);
char* purple_utf8_ncr_decode (const(char)* in_);
gchar* purple_strcasereplace (const(char)* string, const(char)* delimiter, const(char)* replacement);
const(char)* purple_strcasestr (const(char)* haystack, const(char)* needle);
char* purple_str_size_to_units (size_t size);
char* purple_str_seconds_to_string (guint sec);
char* purple_str_binary_to_ascii (const(ubyte)* binary, guint len);
void purple_got_protocol_handler_uri (const(char)* uri);
gboolean purple_url_parse (const(char)* url, char** ret_host, int* ret_port, char** ret_path, char** ret_user, char** ret_passwd);
PurpleUtilFetchUrlData* purple_util_fetch_url_request (const(gchar)* url, gboolean full, const(gchar)* user_agent, gboolean http11, const(gchar)* request, gboolean include_headers, PurpleUtilFetchUrlCallback callback, gpointer data);
PurpleUtilFetchUrlData* purple_util_fetch_url_request_len (const(gchar)* url, gboolean full, const(gchar)* user_agent, gboolean http11, const(gchar)* request, gboolean include_headers, gssize max_len, PurpleUtilFetchUrlCallback callback, gpointer data);
PurpleUtilFetchUrlData* purple_util_fetch_url_request_len_with_account (PurpleAccount* account, const(gchar)* url, gboolean full, const(gchar)* user_agent, gboolean http11, const(gchar)* request, gboolean include_headers, gssize max_len, PurpleUtilFetchUrlCallback callback, gpointer data);
void purple_util_fetch_url_cancel (PurpleUtilFetchUrlData* url_data);
const(char)* purple_url_decode (const(char)* str);
const(char)* purple_url_encode (const(char)* str);
gboolean purple_email_is_valid (const(char)* address);
gboolean purple_ip_address_is_valid (const(char)* ip);
gboolean purple_ipv4_address_is_valid (const(char)* ip);
gboolean purple_ipv6_address_is_valid (const(char)* ip);
GList* purple_uri_list_extract_uris (const(gchar)* uri_list);
GList* purple_uri_list_extract_filenames (const(gchar)* uri_list);
gchar* purple_utf8_try_convert (const(char)* str);
gchar* purple_utf8_salvage (const(char)* str);
gchar* purple_utf8_strip_unprintables (const(gchar)* str);
const(gchar)* purple_gai_strerror (gint errnum);
int purple_utf8_strcasecmp (const(char)* a, const(char)* b);
gboolean purple_utf8_has_word (const(char)* haystack, const(char)* needle);
void purple_print_utf8_to_console (FILE* filestream, char* message);
gboolean purple_message_meify (char* message, gssize len);
char* purple_text_strip_mnemonic (const(char)* in_);
const(char)* purple_unescape_filename (const(char)* str);
const(char)* purple_escape_filename (const(char)* str);
const(char)* _purple_oscar_convert (const(char)* act, const(char)* protocol);
void purple_restore_default_signal_handlers ();
const(gchar)* purple_get_host_name ();
gchar* purple_uuid_random ();