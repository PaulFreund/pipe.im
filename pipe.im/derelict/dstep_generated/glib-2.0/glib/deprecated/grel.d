extern (C):

alias _GRelation GRelation;
alias _GTuples GTuples;

struct _GTuples
{
	guint len;
}

struct _GRelation;


GRelation* g_relation_new (gint fields);
void g_relation_destroy (GRelation* relation);
void g_relation_index (GRelation* relation, gint field, GHashFunc hash_func, GEqualFunc key_equal_func);
void g_relation_insert (GRelation* relation, ...);
gint g_relation_delete (GRelation* relation, gconstpointer key, gint field);
GTuples* g_relation_select (GRelation* relation, gconstpointer key, gint field);
gint g_relation_count (GRelation* relation, gconstpointer key, gint field);
gboolean g_relation_exists (GRelation* relation, ...);
void g_relation_print (GRelation* relation);
void g_tuples_destroy (GTuples* tuples);
gpointer g_tuples_index (GTuples* tuples, gint index_, gint field);