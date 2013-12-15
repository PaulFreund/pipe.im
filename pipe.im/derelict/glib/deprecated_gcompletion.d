module derelict.glib.deprecated_gcompletion;

import core.stdc.config;

extern (C):

alias _GCompletion GCompletion;
alias char* function (void*) GCompletionFunc;
alias int function (const(char)*, const(char)*, c_ulong) GCompletionStrncmpFunc;

struct _GCompletion
{
	GList* items;
	GCompletionFunc func;
	gchar* prefix;
	GList* cache;
	GCompletionStrncmpFunc strncmp_func;
}

GCompletion* g_completion_new (GCompletionFunc func);
void g_completion_add_items (GCompletion* cmp, GList* items);
void g_completion_remove_items (GCompletion* cmp, GList* items);
void g_completion_clear_items (GCompletion* cmp);
GList* g_completion_complete (GCompletion* cmp, const(gchar)* prefix, gchar** new_prefix);
GList* g_completion_complete_utf8 (GCompletion* cmp, const(gchar)* prefix, gchar** new_prefix);
void g_completion_set_compare (GCompletion* cmp, GCompletionStrncmpFunc strncmp_func);
void g_completion_free (GCompletion* cmp);