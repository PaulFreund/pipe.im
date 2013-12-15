module derelict.glib.gpattern;

extern (C):

alias _GPatternSpec GPatternSpec;

struct _GPatternSpec;


GPatternSpec* g_pattern_spec_new (const(gchar)* pattern);
void g_pattern_spec_free (GPatternSpec* pspec);
gboolean g_pattern_spec_equal (GPatternSpec* pspec1, GPatternSpec* pspec2);
gboolean g_pattern_match (GPatternSpec* pspec, guint string_length, const(gchar)* string, const(gchar)* string_reversed);
gboolean g_pattern_match_string (GPatternSpec* pspec, const(gchar)* string);
gboolean g_pattern_match_simple (const(gchar)* pattern, const(gchar)* string);