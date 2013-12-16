module derelict.purple.buddyicon;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.purple.account;
import derelict.purple.blist;
import derelict.purple.imgstore;
import derelict.purple.prpl;
import core.stdc.time;

extern (C):

alias _PurpleBuddyIcon PurpleBuddyIcon;

struct _PurpleBuddyIcon;


PurpleBuddyIcon* purple_buddy_icon_new (PurpleAccount* account, const(char)* username, void* icon_data, size_t icon_len, const(char)* checksum);
PurpleBuddyIcon* purple_buddy_icon_ref (PurpleBuddyIcon* icon);
PurpleBuddyIcon* purple_buddy_icon_unref (PurpleBuddyIcon* icon);
void purple_buddy_icon_update (PurpleBuddyIcon* icon);
void purple_buddy_icon_set_data (PurpleBuddyIcon* icon, guchar* data, size_t len, const(char)* checksum);
PurpleAccount* purple_buddy_icon_get_account (const(PurpleBuddyIcon)* icon);
const(char)* purple_buddy_icon_get_username (const(PurpleBuddyIcon)* icon);
const(char)* purple_buddy_icon_get_checksum (const(PurpleBuddyIcon)* icon);
gconstpointer purple_buddy_icon_get_data (const(PurpleBuddyIcon)* icon, size_t* len);
const(char)* purple_buddy_icon_get_extension (const(PurpleBuddyIcon)* icon);
char* purple_buddy_icon_get_full_path (PurpleBuddyIcon* icon);
void purple_buddy_icons_set_for_user (PurpleAccount* account, const(char)* username, void* icon_data, size_t icon_len, const(char)* checksum);
const(char)* purple_buddy_icons_get_checksum_for_user (PurpleBuddy* buddy);
PurpleBuddyIcon* purple_buddy_icons_find (PurpleAccount* account, const(char)* username);
PurpleStoredImage* purple_buddy_icons_find_account_icon (PurpleAccount* account);
PurpleStoredImage* purple_buddy_icons_set_account_icon (PurpleAccount* account, guchar* icon_data, size_t icon_len);
time_t purple_buddy_icons_get_account_icon_timestamp (PurpleAccount* account);
gboolean purple_buddy_icons_node_has_custom_icon (PurpleBlistNode* node);
PurpleStoredImage* purple_buddy_icons_node_find_custom_icon (PurpleBlistNode* node);
PurpleStoredImage* purple_buddy_icons_node_set_custom_icon (PurpleBlistNode* node, guchar* icon_data, size_t icon_len);
PurpleStoredImage* purple_buddy_icons_node_set_custom_icon_from_file (PurpleBlistNode* node, const(gchar)* filename);
gboolean purple_buddy_icons_has_custom_icon (PurpleContact* contact);
PurpleStoredImage* purple_buddy_icons_find_custom_icon (PurpleContact* contact);
PurpleStoredImage* purple_buddy_icons_set_custom_icon (PurpleContact* contact, guchar* icon_data, size_t icon_len);
void purple_buddy_icons_set_caching (gboolean caching);
gboolean purple_buddy_icons_is_caching ();
void purple_buddy_icons_set_cache_dir (const(char)* cache_dir);
const(char)* purple_buddy_icons_get_cache_dir ();
void* purple_buddy_icons_get_handle ();
void purple_buddy_icons_init ();
void purple_buddy_icons_uninit ();
void purple_buddy_icon_get_scale_size (PurpleBuddyIconSpec* spec, int* width, int* height);