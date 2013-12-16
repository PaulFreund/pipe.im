module derelict.purple.imgstore;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _PurpleStoredImage PurpleStoredImage;

struct _PurpleStoredImage;


PurpleStoredImage* purple_imgstore_add (gpointer data, size_t size, const(char)* filename);
PurpleStoredImage* purple_imgstore_new_from_file (const(char)* path);
int purple_imgstore_add_with_id (gpointer data, size_t size, const(char)* filename);
PurpleStoredImage* purple_imgstore_find_by_id (int id);
gconstpointer purple_imgstore_get_data (PurpleStoredImage* img);
size_t purple_imgstore_get_size (PurpleStoredImage* img);
const(char)* purple_imgstore_get_filename (const(PurpleStoredImage)* img);
const(char)* purple_imgstore_get_extension (PurpleStoredImage* img);
PurpleStoredImage* purple_imgstore_ref (PurpleStoredImage* img);
PurpleStoredImage* purple_imgstore_unref (PurpleStoredImage* img);
void purple_imgstore_ref_by_id (int id);
void purple_imgstore_unref_by_id (int id);
void* purple_imgstore_get_handle ();
void purple_imgstore_init ();
void purple_imgstore_uninit ();