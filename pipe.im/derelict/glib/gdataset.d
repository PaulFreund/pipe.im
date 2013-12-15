module derelict.glib.gdataset;

extern (C):

alias _GData GData;
alias void function (uint, void*, void*) GDataForeachFunc;

struct _GData;


void g_datalist_init (GData** datalist);
void g_datalist_clear (GData** datalist);
gpointer g_datalist_id_get_data (GData** datalist, GQuark key_id);
void g_datalist_id_set_data_full (GData** datalist, GQuark key_id, gpointer data, GDestroyNotify destroy_func);
gpointer g_datalist_id_remove_no_notify (GData** datalist, GQuark key_id);
void g_datalist_foreach (GData** datalist, GDataForeachFunc func, gpointer user_data);
void g_datalist_set_flags (GData** datalist, guint flags);
void g_datalist_unset_flags (GData** datalist, guint flags);
guint g_datalist_get_flags (GData** datalist);
void g_dataset_destroy (gconstpointer dataset_location);
gpointer g_dataset_id_get_data (gconstpointer dataset_location, GQuark key_id);
gpointer g_datalist_get_data (GData** datalist, const(gchar)* key);
void g_dataset_id_set_data_full (gconstpointer dataset_location, GQuark key_id, gpointer data, GDestroyNotify destroy_func);
gpointer g_dataset_id_remove_no_notify (gconstpointer dataset_location, GQuark key_id);
void g_dataset_foreach (gconstpointer dataset_location, GDataForeachFunc func, gpointer user_data);