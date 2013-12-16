module derelict.glib.gscanner;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.ghash;
import derelict.glib.gdataset;
import core.stdc.config;

extern (C):

alias _GScanner GScanner;
alias _GScannerConfig GScannerConfig;
alias _GTokenValue GTokenValue;
alias void function (_GScanner*, char*, int) GScannerMsgFunc;
alias _Anonymous_0 GErrorType;
alias _Anonymous_1 GTokenType;

enum _Anonymous_0
{
	G_ERR_UNKNOWN = 0,
	G_ERR_UNEXP_EOF = 1,
	G_ERR_UNEXP_EOF_IN_STRING = 2,
	G_ERR_UNEXP_EOF_IN_COMMENT = 3,
	G_ERR_NON_DIGIT_IN_CONST = 4,
	G_ERR_DIGIT_RADIX = 5,
	G_ERR_FLOAT_RADIX = 6,
	G_ERR_FLOAT_MALFORMED = 7
}

enum _Anonymous_1
{
	G_TOKEN_EOF = 0,
	G_TOKEN_LEFT_PAREN = 40,
	G_TOKEN_RIGHT_PAREN = 41,
	G_TOKEN_LEFT_CURLY = 123,
	G_TOKEN_RIGHT_CURLY = 125,
	G_TOKEN_LEFT_BRACE = 91,
	G_TOKEN_RIGHT_BRACE = 93,
	G_TOKEN_EQUAL_SIGN = 61,
	G_TOKEN_COMMA = 44,
	G_TOKEN_NONE = 256,
	G_TOKEN_ERROR = 257,
	G_TOKEN_CHAR = 258,
	G_TOKEN_BINARY = 259,
	G_TOKEN_OCTAL = 260,
	G_TOKEN_INT = 261,
	G_TOKEN_HEX = 262,
	G_TOKEN_FLOAT = 263,
	G_TOKEN_STRING = 264,
	G_TOKEN_SYMBOL = 265,
	G_TOKEN_IDENTIFIER = 266,
	G_TOKEN_IDENTIFIER_NULL = 267,
	G_TOKEN_COMMENT_SINGLE = 268,
	G_TOKEN_COMMENT_MULTI = 269,
	G_TOKEN_LAST = 270
}

struct _GScannerConfig
{
	gchar* cset_skip_characters;
	gchar* cset_identifier_first;
	gchar* cset_identifier_nth;
	gchar* cpair_comment_single;
	guint case_sensitive;
	guint skip_comment_multi;
	guint skip_comment_single;
	guint scan_comment_multi;
	guint scan_identifier;
	guint scan_identifier_1char;
	guint scan_identifier_NULL;
	guint scan_symbols;
	guint scan_binary;
	guint scan_octal;
	guint scan_float;
	guint scan_hex;
	guint scan_hex_dollar;
	guint scan_string_sq;
	guint scan_string_dq;
	guint numbers_2_int;
	guint int_2_float;
	guint identifier_2_string;
	guint char_2_token;
	guint symbol_2_token;
	guint scope_0_fallback;
	guint store_int64;
	guint padding_dummy;
}

struct _GScanner
{
	gpointer user_data;
	guint max_parse_errors;
	guint parse_errors;
	const(gchar)* input_name;
	GData* qdata;
	GScannerConfig* config;
	GTokenType token;
	GTokenValue value;
	guint line;
	guint position;
	GTokenType next_token;
	GTokenValue next_value;
	guint next_line;
	guint next_position;
	GHashTable* symbol_table;
	gint input_fd;
	const(gchar)* text;
	const(gchar)* text_end;
	gchar* buffer;
	guint scope_id;
	GScannerMsgFunc msg_handler;
}

//union _GTokenValue;


union _GTokenValue
{
	gpointer v_symbol;
	gchar* v_identifier;
	gulong v_binary;
	gulong v_octal;
	gulong v_int;
	guint64 v_int64;
	gdouble v_float;
	gulong v_hex;
	gchar* v_string;
	gchar* v_comment;
	guchar v_char;
	guint v_error;
}

alias da_g_scanner_new = GScanner* function(const(GScannerConfig)* config_templ);																																																						/* da_g_scanner_new g_scanner_new; */
alias da_g_scanner_destroy = void function(GScanner* scanner);																																																						/* da_g_scanner_destroy g_scanner_destroy; */
alias da_g_scanner_input_file = void function(GScanner* scanner, gint input_fd);																																																						/* da_g_scanner_input_file g_scanner_input_file; */
alias da_g_scanner_sync_file_offset = void function(GScanner* scanner);																																																						/* da_g_scanner_sync_file_offset g_scanner_sync_file_offset; */
alias da_g_scanner_input_text = void function(GScanner* scanner, const(gchar)* text, guint text_len);																																																						/* da_g_scanner_input_text g_scanner_input_text; */
alias da_g_scanner_get_next_token = GTokenType function(GScanner* scanner);																																																						/* da_g_scanner_get_next_token g_scanner_get_next_token; */
alias da_g_scanner_peek_next_token = GTokenType function(GScanner* scanner);																																																						/* da_g_scanner_peek_next_token g_scanner_peek_next_token; */
alias da_g_scanner_cur_token = GTokenType function(GScanner* scanner);																																																						/* da_g_scanner_cur_token g_scanner_cur_token; */
alias da_g_scanner_cur_value = GTokenValue function(GScanner* scanner);																																																						/* da_g_scanner_cur_value g_scanner_cur_value; */
alias da_g_scanner_cur_line = guint function(GScanner* scanner);																																																						/* da_g_scanner_cur_line g_scanner_cur_line; */
alias da_g_scanner_cur_position = guint function(GScanner* scanner);																																																						/* da_g_scanner_cur_position g_scanner_cur_position; */
alias da_g_scanner_eof = gboolean function(GScanner* scanner);																																																						/* da_g_scanner_eof g_scanner_eof; */
alias da_g_scanner_set_scope = guint function(GScanner* scanner, guint scope_id);																																																						/* da_g_scanner_set_scope g_scanner_set_scope; */
alias da_g_scanner_scope_add_symbol = void function(GScanner* scanner, guint scope_id, const(gchar)* symbol, gpointer value);																																																						/* da_g_scanner_scope_add_symbol g_scanner_scope_add_symbol; */
alias da_g_scanner_scope_remove_symbol = void function(GScanner* scanner, guint scope_id, const(gchar)* symbol);																																																						/* da_g_scanner_scope_remove_symbol g_scanner_scope_remove_symbol; */
alias da_g_scanner_scope_lookup_symbol = gpointer function(GScanner* scanner, guint scope_id, const(gchar)* symbol);																																																						/* da_g_scanner_scope_lookup_symbol g_scanner_scope_lookup_symbol; */
alias da_g_scanner_scope_foreach_symbol = void function(GScanner* scanner, guint scope_id, GHFunc func, gpointer user_data);																																																						/* da_g_scanner_scope_foreach_symbol g_scanner_scope_foreach_symbol; */
alias da_g_scanner_lookup_symbol = gpointer function(GScanner* scanner, const(gchar)* symbol);																																																						/* da_g_scanner_lookup_symbol g_scanner_lookup_symbol; */
alias da_g_scanner_unexp_token = void function(GScanner* scanner, GTokenType expected_token, const(gchar)* identifier_spec, const(gchar)* symbol_spec, const(gchar)* symbol_name, const(gchar)* message, gint is_error);																																																						/* da_g_scanner_unexp_token g_scanner_unexp_token; */
alias da_g_scanner_error = void function(GScanner* scanner, const(gchar)* format, ...);																																																						/* da_g_scanner_error g_scanner_error; */
alias da_g_scanner_warn = void function(GScanner* scanner, const(gchar)* format, ...);																																																						/* da_g_scanner_warn g_scanner_warn; */
