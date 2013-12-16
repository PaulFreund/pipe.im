module derelict.purple.util;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.glib.gdataset;
import derelict.purple.account;
import derelict.purple.signals;
import derelict.purple.notify;
import derelict.purple.xmlnode;
import core.stdc.config;
import core.stdc.time;
import core.stdc.stdio;

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


alias da_purple_menu_action_new = PurpleMenuAction* function(const(char)* label, PurpleCallback callback, gpointer data, GList* children);																																																						/* da_purple_menu_action_new purple_menu_action_new; */
alias da_purple_menu_action_free = void function(PurpleMenuAction* act);																																																						/* da_purple_menu_action_free purple_menu_action_free; */
alias da_purple_util_set_current_song = void function(const(char)* title, const(char)* artist, const(char)* album);																																																						/* da_purple_util_set_current_song purple_util_set_current_song; */
alias da_purple_util_format_song_info = char* function(const(char)* title, const(char)* artist, const(char)* album, gpointer unused);																																																						/* da_purple_util_format_song_info purple_util_format_song_info; */
alias da_purple_util_init = void function();																																																						/* da_purple_util_init purple_util_init; */
alias da_purple_util_uninit = void function();																																																						/* da_purple_util_uninit purple_util_uninit; */
alias da_purple_base16_encode = gchar* function(const(guchar)* data, gsize len);																																																						/* da_purple_base16_encode purple_base16_encode; */
alias da_purple_base16_decode = guchar* function(const(char)* str, gsize* ret_len);																																																						/* da_purple_base16_decode purple_base16_decode; */
alias da_purple_base16_encode_chunked = gchar* function(const(guchar)* data, gsize len);																																																						/* da_purple_base16_encode_chunked purple_base16_encode_chunked; */
alias da_purple_base64_encode = gchar* function(const(guchar)* data, gsize len);																																																						/* da_purple_base64_encode purple_base64_encode; */
alias da_purple_base64_decode = guchar* function(const(char)* str, gsize* ret_len);																																																						/* da_purple_base64_decode purple_base64_decode; */
alias da_purple_quotedp_decode = guchar* function(const(char)* str, gsize* ret_len);																																																						/* da_purple_quotedp_decode purple_quotedp_decode; */
alias da_purple_mime_decode_field = char* function(const(char)* str);																																																						/* da_purple_mime_decode_field purple_mime_decode_field; */
alias da_purple_utf8_strftime = const(char)* function(const(char)* format, const(tm)* tm);																																																						/* da_purple_utf8_strftime purple_utf8_strftime; */
alias da_purple_get_tzoff_str = const(char)* function(const(tm)* tm, gboolean iso);																																																						/* da_purple_get_tzoff_str purple_get_tzoff_str; */
alias da_purple_date_format_short = const(char)* function(const(tm)* tm);																																																						/* da_purple_date_format_short purple_date_format_short; */
alias da_purple_date_format_long = const(char)* function(const(tm)* tm);																																																						/* da_purple_date_format_long purple_date_format_long; */
alias da_purple_date_format_full = const(char)* function(const(tm)* tm);																																																						/* da_purple_date_format_full purple_date_format_full; */
alias da_purple_time_format = const(char)* function(const(tm)* tm);																																																						/* da_purple_time_format purple_time_format; */
alias da_purple_time_build = time_t function(int year, int month, int day, int hour, int min, int sec);																																																						/* da_purple_time_build purple_time_build; */
alias da_purple_str_to_time = time_t function(const(char)* timestamp, gboolean utc, tm* tm, c_long* tz_off, const(char*)* rest);																																																						/* da_purple_str_to_time purple_str_to_time; */
alias da_purple_markup_escape_text = gchar* function(const(gchar)* text, gssize length);																																																						/* da_purple_markup_escape_text purple_markup_escape_text; */
alias da_purple_markup_find_tag = gboolean function(const(char)* needle, const(char)* haystack, const(char*)* start, const(char*)* end, GData** attributes);																																																						/* da_purple_markup_find_tag purple_markup_find_tag; */
alias da_purple_markup_extract_info_field = gboolean function(const(char)* str, int len, PurpleNotifyUserInfo* user_info, const(char)* start_token, int skip, const(char)* end_token, char check_value, const(char)* no_value_token, const(char)* display_name, gboolean is_link, const(char)* link_prefix, PurpleInfoFieldFormatCallback format_cb);																																																						/* da_purple_markup_extract_info_field purple_markup_extract_info_field; */
alias da_purple_markup_html_to_xhtml = void function(const(char)* html, char** dest_xhtml, char** dest_plain);																																																						/* da_purple_markup_html_to_xhtml purple_markup_html_to_xhtml; */
alias da_purple_markup_strip_html = char* function(const(char)* str);																																																						/* da_purple_markup_strip_html purple_markup_strip_html; */
alias da_purple_markup_linkify = char* function(const(char)* str);																																																						/* da_purple_markup_linkify purple_markup_linkify; */
alias da_purple_unescape_text = char* function(const(char)* text);																																																						/* da_purple_unescape_text purple_unescape_text; */
alias da_purple_unescape_html = char* function(const(char)* html);																																																						/* da_purple_unescape_html purple_unescape_html; */
alias da_purple_markup_slice = char* function(const(char)* str, guint x, guint y);																																																						/* da_purple_markup_slice purple_markup_slice; */
alias da_purple_markup_get_tag_name = char* function(const(char)* tag);																																																						/* da_purple_markup_get_tag_name purple_markup_get_tag_name; */
alias da_purple_markup_unescape_entity = const(char)* function(const(char)* text, int* length);																																																						/* da_purple_markup_unescape_entity purple_markup_unescape_entity; */
alias da_purple_markup_get_css_property = char* function(const(gchar)* style, const(gchar)* opt);																																																						/* da_purple_markup_get_css_property purple_markup_get_css_property; */
alias da_purple_markup_is_rtl = gboolean function(const(char)* html);																																																						/* da_purple_markup_is_rtl purple_markup_is_rtl; */
alias da_purple_home_dir = const(gchar)* function();																																																						/* da_purple_home_dir purple_home_dir; */
alias da_purple_user_dir = const(char)* function();																																																						/* da_purple_user_dir purple_user_dir; */
alias da_purple_util_set_user_dir = void function(const(char)* dir);																																																						/* da_purple_util_set_user_dir purple_util_set_user_dir; */
alias da_purple_build_dir = int function(const(char)* path, int mode);																																																						/* da_purple_build_dir purple_build_dir; */
alias da_purple_util_write_data_to_file = gboolean function(const(char)* filename, const(char)* data, gssize size);																																																						/* da_purple_util_write_data_to_file purple_util_write_data_to_file; */
alias da_purple_util_write_data_to_file_absolute = gboolean function(const(char)* filename_full, const(char)* data, gssize size);																																																						/* da_purple_util_write_data_to_file_absolute purple_util_write_data_to_file_absolute; */
alias da_purple_util_read_xml_from_file = xmlnode* function(const(char)* filename, const(char)* description);																																																						/* da_purple_util_read_xml_from_file purple_util_read_xml_from_file; */
alias da_purple_mkstemp = FILE* function(char** path, gboolean binary);																																																						/* da_purple_mkstemp purple_mkstemp; */
alias da_purple_util_get_image_extension = const(char)* function(gconstpointer data, size_t len);																																																						/* da_purple_util_get_image_extension purple_util_get_image_extension; */
alias da_purple_util_get_image_checksum = char* function(gconstpointer image_data, size_t image_len);																																																						/* da_purple_util_get_image_checksum purple_util_get_image_checksum; */
alias da_purple_util_get_image_filename = char* function(gconstpointer image_data, size_t image_len);																																																						/* da_purple_util_get_image_filename purple_util_get_image_filename; */
alias da_purple_program_is_valid = gboolean function(const(char)* program);																																																						/* da_purple_program_is_valid purple_program_is_valid; */
alias da_purple_running_gnome = gboolean function();																																																						/* da_purple_running_gnome purple_running_gnome; */
alias da_purple_running_kde = gboolean function();																																																						/* da_purple_running_kde purple_running_kde; */
alias da_purple_running_osx = gboolean function();																																																						/* da_purple_running_osx purple_running_osx; */
alias da_purple_fd_get_ip = char* function(int fd);																																																						/* da_purple_fd_get_ip purple_fd_get_ip; */
alias da_purple_socket_get_family = int function(int fd);																																																						/* da_purple_socket_get_family purple_socket_get_family; */
alias da_purple_socket_speaks_ipv4 = gboolean function(int fd);																																																						/* da_purple_socket_speaks_ipv4 purple_socket_speaks_ipv4; */
alias da_purple_strequal = gboolean function(const(gchar)* left, const(gchar)* right);																																																						/* da_purple_strequal purple_strequal; */
alias da_purple_normalize = const(char)* function(const(PurpleAccount)* account, const(char)* str);																																																						/* da_purple_normalize purple_normalize; */
alias da_purple_normalize_nocase = const(char)* function(const(PurpleAccount)* account, const(char)* str);																																																						/* da_purple_normalize_nocase purple_normalize_nocase; */
alias da_purple_str_has_prefix = gboolean function(const(char)* s, const(char)* p);																																																						/* da_purple_str_has_prefix purple_str_has_prefix; */
alias da_purple_str_has_suffix = gboolean function(const(char)* s, const(char)* x);																																																						/* da_purple_str_has_suffix purple_str_has_suffix; */
alias da_purple_strdup_withhtml = gchar* function(const(gchar)* src);																																																						/* da_purple_strdup_withhtml purple_strdup_withhtml; */
alias da_purple_str_add_cr = char* function(const(char)* str);																																																						/* da_purple_str_add_cr purple_str_add_cr; */
alias da_purple_str_strip_char = void function(char* str, char thechar);																																																						/* da_purple_str_strip_char purple_str_strip_char; */
alias da_purple_util_chrreplace = void function(char* string, char delimiter, char replacement);																																																						/* da_purple_util_chrreplace purple_util_chrreplace; */
alias da_purple_strreplace = gchar* function(const(char)* string, const(char)* delimiter, const(char)* replacement);																																																						/* da_purple_strreplace purple_strreplace; */
alias da_purple_utf8_ncr_encode = char* function(const(char)* in_);																																																						/* da_purple_utf8_ncr_encode purple_utf8_ncr_encode; */
alias da_purple_utf8_ncr_decode = char* function(const(char)* in_);																																																						/* da_purple_utf8_ncr_decode purple_utf8_ncr_decode; */
alias da_purple_strcasereplace = gchar* function(const(char)* string, const(char)* delimiter, const(char)* replacement);																																																						/* da_purple_strcasereplace purple_strcasereplace; */
alias da_purple_strcasestr = const(char)* function(const(char)* haystack, const(char)* needle);																																																						/* da_purple_strcasestr purple_strcasestr; */
alias da_purple_str_size_to_units = char* function(size_t size);																																																						/* da_purple_str_size_to_units purple_str_size_to_units; */
alias da_purple_str_seconds_to_string = char* function(guint sec);																																																						/* da_purple_str_seconds_to_string purple_str_seconds_to_string; */
alias da_purple_str_binary_to_ascii = char* function(const(ubyte)* binary, guint len);																																																						/* da_purple_str_binary_to_ascii purple_str_binary_to_ascii; */
alias da_purple_got_protocol_handler_uri = void function(const(char)* uri);																																																						/* da_purple_got_protocol_handler_uri purple_got_protocol_handler_uri; */
alias da_purple_url_parse = gboolean function(const(char)* url, char** ret_host, int* ret_port, char** ret_path, char** ret_user, char** ret_passwd);																																																						/* da_purple_url_parse purple_url_parse; */
alias da_purple_util_fetch_url_request = PurpleUtilFetchUrlData* function(const(gchar)* url, gboolean full, const(gchar)* user_agent, gboolean http11, const(gchar)* request, gboolean include_headers, PurpleUtilFetchUrlCallback callback, gpointer data);																																																						/* da_purple_util_fetch_url_request purple_util_fetch_url_request; */
alias da_purple_util_fetch_url_request_len = PurpleUtilFetchUrlData* function(const(gchar)* url, gboolean full, const(gchar)* user_agent, gboolean http11, const(gchar)* request, gboolean include_headers, gssize max_len, PurpleUtilFetchUrlCallback callback, gpointer data);																																																						/* da_purple_util_fetch_url_request_len purple_util_fetch_url_request_len; */
alias da_purple_util_fetch_url_request_len_with_account = PurpleUtilFetchUrlData* function(PurpleAccount* account, const(gchar)* url, gboolean full, const(gchar)* user_agent, gboolean http11, const(gchar)* request, gboolean include_headers, gssize max_len, PurpleUtilFetchUrlCallback callback, gpointer data);																																																						/* da_purple_util_fetch_url_request_len_with_account purple_util_fetch_url_request_len_with_account; */
alias da_purple_util_fetch_url_cancel = void function(PurpleUtilFetchUrlData* url_data);																																																						/* da_purple_util_fetch_url_cancel purple_util_fetch_url_cancel; */
alias da_purple_url_decode = const(char)* function(const(char)* str);																																																						/* da_purple_url_decode purple_url_decode; */
alias da_purple_url_encode = const(char)* function(const(char)* str);																																																						/* da_purple_url_encode purple_url_encode; */
alias da_purple_email_is_valid = gboolean function(const(char)* address);																																																						/* da_purple_email_is_valid purple_email_is_valid; */
alias da_purple_ip_address_is_valid = gboolean function(const(char)* ip);																																																						/* da_purple_ip_address_is_valid purple_ip_address_is_valid; */
alias da_purple_ipv4_address_is_valid = gboolean function(const(char)* ip);																																																						/* da_purple_ipv4_address_is_valid purple_ipv4_address_is_valid; */
alias da_purple_ipv6_address_is_valid = gboolean function(const(char)* ip);																																																						/* da_purple_ipv6_address_is_valid purple_ipv6_address_is_valid; */
alias da_purple_uri_list_extract_uris = GList* function(const(gchar)* uri_list);																																																						/* da_purple_uri_list_extract_uris purple_uri_list_extract_uris; */
alias da_purple_uri_list_extract_filenames = GList* function(const(gchar)* uri_list);																																																						/* da_purple_uri_list_extract_filenames purple_uri_list_extract_filenames; */
alias da_purple_utf8_try_convert = gchar* function(const(char)* str);																																																						/* da_purple_utf8_try_convert purple_utf8_try_convert; */
alias da_purple_utf8_salvage = gchar* function(const(char)* str);																																																						/* da_purple_utf8_salvage purple_utf8_salvage; */
alias da_purple_utf8_strip_unprintables = gchar* function(const(gchar)* str);																																																						/* da_purple_utf8_strip_unprintables purple_utf8_strip_unprintables; */
alias da_purple_gai_strerror = const(gchar)* function(gint errnum);																																																						/* da_purple_gai_strerror purple_gai_strerror; */
alias da_purple_utf8_strcasecmp = int function(const(char)* a, const(char)* b);																																																						/* da_purple_utf8_strcasecmp purple_utf8_strcasecmp; */
alias da_purple_utf8_has_word = gboolean function(const(char)* haystack, const(char)* needle);																																																						/* da_purple_utf8_has_word purple_utf8_has_word; */
alias da_purple_print_utf8_to_console = void function(FILE* filestream, char* message);																																																						/* da_purple_print_utf8_to_console purple_print_utf8_to_console; */
alias da_purple_message_meify = gboolean function(char* message, gssize len);																																																						/* da_purple_message_meify purple_message_meify; */
alias da_purple_text_strip_mnemonic = char* function(const(char)* in_);																																																						/* da_purple_text_strip_mnemonic purple_text_strip_mnemonic; */
alias da_purple_unescape_filename = const(char)* function(const(char)* str);																																																						/* da_purple_unescape_filename purple_unescape_filename; */
alias da_purple_escape_filename = const(char)* function(const(char)* str);																																																						/* da_purple_escape_filename purple_escape_filename; */
alias da__purple_oscar_convert = const(char)* function(const(char)* act, const(char)* protocol);																																																						/* da__purple_oscar_convert _purple_oscar_convert; */
alias da_purple_restore_default_signal_handlers = void function();																																																						/* da_purple_restore_default_signal_handlers purple_restore_default_signal_handlers; */
alias da_purple_get_host_name = const(gchar)* function();																																																						/* da_purple_get_host_name purple_get_host_name; */
alias da_purple_uuid_random = gchar* function();																																																						/* da_purple_uuid_random purple_uuid_random; */
