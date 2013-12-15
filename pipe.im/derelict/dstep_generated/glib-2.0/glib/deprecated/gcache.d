extern (C):

alias _GCache GCache;
alias void* function (void*) GCacheNewFunc;
alias void* function (void*) GCacheDupFunc;
alias void function (void*) GCacheDestroyFunc;

struct _GCache;


GCache* g_cache_new (GCacheNewFunc value_new_func, GCacheDestroyFunc value_destroy_func, GCacheDupFunc key_dup_func, GCacheDestroyFunc key_destroy_func, GHashFunc hash_key_func, GHashFunc hash_value_func, GEqualFunc key_equal_func);
void g_cache_destroy (GCache* cache);
gpointer g_cache_insert (GCache* cache, gpointer key);
void g_cache_remove (GCache* cache, gconstpointer value);
void g_cache_key_foreach (GCache* cache, GHFunc func, gpointer user_data);
void g_cache_value_foreach (GCache* cache, GHFunc func, gpointer user_data);