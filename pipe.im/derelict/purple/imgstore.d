module derelict.purple.imgstore;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _PurpleStoredImage PurpleStoredImage;

struct _PurpleStoredImage;


alias da_purple_imgstore_add = PurpleStoredImage* function(gpointer data, size_t size, const(char)* filename);																																																						/* da_purple_imgstore_add purple_imgstore_add; */
alias da_purple_imgstore_new_from_file = PurpleStoredImage* function(const(char)* path);																																																						/* da_purple_imgstore_new_from_file purple_imgstore_new_from_file; */
alias da_purple_imgstore_add_with_id = int function(gpointer data, size_t size, const(char)* filename);																																																						/* da_purple_imgstore_add_with_id purple_imgstore_add_with_id; */
alias da_purple_imgstore_find_by_id = PurpleStoredImage* function(int id);																																																						/* da_purple_imgstore_find_by_id purple_imgstore_find_by_id; */
alias da_purple_imgstore_get_data = gconstpointer function(PurpleStoredImage* img);																																																						/* da_purple_imgstore_get_data purple_imgstore_get_data; */
alias da_purple_imgstore_get_size = size_t function(PurpleStoredImage* img);																																																						/* da_purple_imgstore_get_size purple_imgstore_get_size; */
alias da_purple_imgstore_get_filename = const(char)* function(const(PurpleStoredImage)* img);																																																						/* da_purple_imgstore_get_filename purple_imgstore_get_filename; */
alias da_purple_imgstore_get_extension = const(char)* function(PurpleStoredImage* img);																																																						/* da_purple_imgstore_get_extension purple_imgstore_get_extension; */
alias da_purple_imgstore_ref = PurpleStoredImage* function(PurpleStoredImage* img);																																																						/* da_purple_imgstore_ref purple_imgstore_ref; */
alias da_purple_imgstore_unref = PurpleStoredImage* function(PurpleStoredImage* img);																																																						/* da_purple_imgstore_unref purple_imgstore_unref; */
alias da_purple_imgstore_ref_by_id = void function(int id);																																																						/* da_purple_imgstore_ref_by_id purple_imgstore_ref_by_id; */
alias da_purple_imgstore_unref_by_id = void function(int id);																																																						/* da_purple_imgstore_unref_by_id purple_imgstore_unref_by_id; */
alias da_purple_imgstore_get_handle = void* function();																																																						/* da_purple_imgstore_get_handle purple_imgstore_get_handle; */
alias da_purple_imgstore_init = void function();																																																						/* da_purple_imgstore_init purple_imgstore_init; */
alias da_purple_imgstore_uninit = void function();																																																						/* da_purple_imgstore_uninit purple_imgstore_uninit; */
