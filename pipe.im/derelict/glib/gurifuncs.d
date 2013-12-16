module derelict.glib.gurifuncs;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias da_g_uri_unescape_string = char* function(const(char)* escaped_string, const(char)* illegal_characters);																																																						/* da_g_uri_unescape_string g_uri_unescape_string; */
alias da_g_uri_unescape_segment = char* function(const(char)* escaped_string, const(char)* escaped_string_end, const(char)* illegal_characters);																																																						/* da_g_uri_unescape_segment g_uri_unescape_segment; */
alias da_g_uri_parse_scheme = char* function(const(char)* uri);																																																						/* da_g_uri_parse_scheme g_uri_parse_scheme; */
alias da_g_uri_escape_string = char* function(const(char)* unescaped, const(char)* reserved_chars_allowed, gboolean allow_utf8);																																																						/* da_g_uri_escape_string g_uri_escape_string; */
