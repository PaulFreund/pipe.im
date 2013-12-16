module derelict.purple.smiley;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.imgstore;

extern (C):

alias _PurpleSmiley PurpleSmiley;
alias _PurpleSmileyClass PurpleSmileyClass;

struct _PurpleSmiley;


struct _PurpleSmileyClass;


alias da_purple_smiley_get_type = GType function();																																																						/* da_purple_smiley_get_type purple_smiley_get_type; */
alias da_purple_smiley_new = PurpleSmiley* function(PurpleStoredImage* img, const(char)* shortcut);																																																						/* da_purple_smiley_new purple_smiley_new; */
alias da_purple_smiley_new_from_file = PurpleSmiley* function(const(char)* shortcut, const(char)* filepath);																																																						/* da_purple_smiley_new_from_file purple_smiley_new_from_file; */
alias da_purple_smiley_delete = void function(PurpleSmiley* smiley);																																																						/* da_purple_smiley_delete purple_smiley_delete; */
alias da_purple_smiley_set_shortcut = gboolean function(PurpleSmiley* smiley, const(char)* shortcut);																																																						/* da_purple_smiley_set_shortcut purple_smiley_set_shortcut; */
alias da_purple_smiley_set_data = void function(PurpleSmiley* smiley, guchar* smiley_data, size_t smiley_data_len);																																																						/* da_purple_smiley_set_data purple_smiley_set_data; */
alias da_purple_smiley_get_shortcut = const(char)* function(const(PurpleSmiley)* smiley);																																																						/* da_purple_smiley_get_shortcut purple_smiley_get_shortcut; */
alias da_purple_smiley_get_checksum = const(char)* function(const(PurpleSmiley)* smiley);																																																						/* da_purple_smiley_get_checksum purple_smiley_get_checksum; */
alias da_purple_smiley_get_stored_image = PurpleStoredImage* function(const(PurpleSmiley)* smiley);																																																						/* da_purple_smiley_get_stored_image purple_smiley_get_stored_image; */
alias da_purple_smiley_get_data = gconstpointer function(const(PurpleSmiley)* smiley, size_t* len);																																																						/* da_purple_smiley_get_data purple_smiley_get_data; */
alias da_purple_smiley_get_extension = const(char)* function(const(PurpleSmiley)* smiley);																																																						/* da_purple_smiley_get_extension purple_smiley_get_extension; */
alias da_purple_smiley_get_full_path = char* function(PurpleSmiley* smiley);																																																						/* da_purple_smiley_get_full_path purple_smiley_get_full_path; */
alias da_purple_smileys_get_all = GList* function();																																																						/* da_purple_smileys_get_all purple_smileys_get_all; */
alias da_purple_smileys_find_by_shortcut = PurpleSmiley* function(const(char)* shortcut);																																																						/* da_purple_smileys_find_by_shortcut purple_smileys_find_by_shortcut; */
alias da_purple_smileys_find_by_checksum = PurpleSmiley* function(const(char)* checksum);																																																						/* da_purple_smileys_find_by_checksum purple_smileys_find_by_checksum; */
alias da_purple_smileys_get_storing_dir = const(char)* function();																																																						/* da_purple_smileys_get_storing_dir purple_smileys_get_storing_dir; */
alias da_purple_smileys_init = void function();																																																						/* da_purple_smileys_init purple_smileys_init; */
alias da_purple_smileys_uninit = void function();																																																						/* da_purple_smileys_uninit purple_smileys_uninit; */
