module derelict.glib.gpattern;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _GPatternSpec GPatternSpec;

struct _GPatternSpec;


alias da_g_pattern_spec_new = GPatternSpec* function(const(gchar)* pattern);																																																						/* da_g_pattern_spec_new g_pattern_spec_new; */
alias da_g_pattern_spec_free = void function(GPatternSpec* pspec);																																																						/* da_g_pattern_spec_free g_pattern_spec_free; */
alias da_g_pattern_spec_equal = gboolean function(GPatternSpec* pspec1, GPatternSpec* pspec2);																																																						/* da_g_pattern_spec_equal g_pattern_spec_equal; */
alias da_g_pattern_match = gboolean function(GPatternSpec* pspec, guint string_length, const(gchar)* string, const(gchar)* string_reversed);																																																						/* da_g_pattern_match g_pattern_match; */
alias da_g_pattern_match_string = gboolean function(GPatternSpec* pspec, const(gchar)* string);																																																						/* da_g_pattern_match_string g_pattern_match_string; */
alias da_g_pattern_match_simple = gboolean function(const(gchar)* pattern, const(gchar)* string);																																																						/* da_g_pattern_match_simple g_pattern_match_simple; */
