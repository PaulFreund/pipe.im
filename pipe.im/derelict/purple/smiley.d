module derelict.purple.smiley;

extern (C):

alias _PurpleSmiley PurpleSmiley;
alias _PurpleSmileyClass PurpleSmileyClass;

struct _PurpleSmiley;


struct _PurpleSmileyClass;


GType purple_smiley_get_type ();
PurpleSmiley* purple_smiley_new (PurpleStoredImage* img, const(char)* shortcut);
PurpleSmiley* purple_smiley_new_from_file (const(char)* shortcut, const(char)* filepath);
void purple_smiley_delete (PurpleSmiley* smiley);
gboolean purple_smiley_set_shortcut (PurpleSmiley* smiley, const(char)* shortcut);
void purple_smiley_set_data (PurpleSmiley* smiley, guchar* smiley_data, size_t smiley_data_len);
const(char)* purple_smiley_get_shortcut (const(PurpleSmiley)* smiley);
const(char)* purple_smiley_get_checksum (const(PurpleSmiley)* smiley);
PurpleStoredImage* purple_smiley_get_stored_image (const(PurpleSmiley)* smiley);
gconstpointer purple_smiley_get_data (const(PurpleSmiley)* smiley, size_t* len);
const(char)* purple_smiley_get_extension (const(PurpleSmiley)* smiley);
char* purple_smiley_get_full_path (PurpleSmiley* smiley);
GList* purple_smileys_get_all ();
PurpleSmiley* purple_smileys_find_by_shortcut (const(char)* shortcut);
PurpleSmiley* purple_smileys_find_by_checksum (const(char)* checksum);
const(char)* purple_smileys_get_storing_dir ();
void purple_smileys_init ();
void purple_smileys_uninit ();