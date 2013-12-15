extern (C):

char* g_uri_unescape_string (const(char)* escaped_string, const(char)* illegal_characters);
char* g_uri_unescape_segment (const(char)* escaped_string, const(char)* escaped_string_end, const(char)* illegal_characters);
char* g_uri_parse_scheme (const(char)* uri);
char* g_uri_escape_string (const(char)* unescaped, const(char)* reserved_chars_allowed, gboolean allow_utf8);