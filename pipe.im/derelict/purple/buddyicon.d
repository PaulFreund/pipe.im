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


alias da_purple_buddy_icon_new = PurpleBuddyIcon* function(PurpleAccount* account, const(char)* username, void* icon_data, size_t icon_len, const(char)* checksum);																																																						/* da_purple_buddy_icon_new purple_buddy_icon_new; */
alias da_purple_buddy_icon_ref = PurpleBuddyIcon* function(PurpleBuddyIcon* icon);																																																						/* da_purple_buddy_icon_ref purple_buddy_icon_ref; */
alias da_purple_buddy_icon_unref = PurpleBuddyIcon* function(PurpleBuddyIcon* icon);																																																						/* da_purple_buddy_icon_unref purple_buddy_icon_unref; */
alias da_purple_buddy_icon_update = void function(PurpleBuddyIcon* icon);																																																						/* da_purple_buddy_icon_update purple_buddy_icon_update; */
alias da_purple_buddy_icon_set_data = void function(PurpleBuddyIcon* icon, guchar* data, size_t len, const(char)* checksum);																																																						/* da_purple_buddy_icon_set_data purple_buddy_icon_set_data; */
alias da_purple_buddy_icon_get_account = PurpleAccount* function(const(PurpleBuddyIcon)* icon);																																																						/* da_purple_buddy_icon_get_account purple_buddy_icon_get_account; */
alias da_purple_buddy_icon_get_username = const(char)* function(const(PurpleBuddyIcon)* icon);																																																						/* da_purple_buddy_icon_get_username purple_buddy_icon_get_username; */
alias da_purple_buddy_icon_get_checksum = const(char)* function(const(PurpleBuddyIcon)* icon);																																																						/* da_purple_buddy_icon_get_checksum purple_buddy_icon_get_checksum; */
alias da_purple_buddy_icon_get_data = gconstpointer function(const(PurpleBuddyIcon)* icon, size_t* len);																																																						/* da_purple_buddy_icon_get_data purple_buddy_icon_get_data; */
alias da_purple_buddy_icon_get_extension = const(char)* function(const(PurpleBuddyIcon)* icon);																																																						/* da_purple_buddy_icon_get_extension purple_buddy_icon_get_extension; */
alias da_purple_buddy_icon_get_full_path = char* function(PurpleBuddyIcon* icon);																																																						/* da_purple_buddy_icon_get_full_path purple_buddy_icon_get_full_path; */
alias da_purple_buddy_icons_set_for_user = void function(PurpleAccount* account, const(char)* username, void* icon_data, size_t icon_len, const(char)* checksum);																																																						/* da_purple_buddy_icons_set_for_user purple_buddy_icons_set_for_user; */
alias da_purple_buddy_icons_get_checksum_for_user = const(char)* function(PurpleBuddy* buddy);																																																						/* da_purple_buddy_icons_get_checksum_for_user purple_buddy_icons_get_checksum_for_user; */
alias da_purple_buddy_icons_find = PurpleBuddyIcon* function(PurpleAccount* account, const(char)* username);																																																						/* da_purple_buddy_icons_find purple_buddy_icons_find; */
alias da_purple_buddy_icons_find_account_icon = PurpleStoredImage* function(PurpleAccount* account);																																																						/* da_purple_buddy_icons_find_account_icon purple_buddy_icons_find_account_icon; */
alias da_purple_buddy_icons_set_account_icon = PurpleStoredImage* function(PurpleAccount* account, guchar* icon_data, size_t icon_len);																																																						/* da_purple_buddy_icons_set_account_icon purple_buddy_icons_set_account_icon; */
alias da_purple_buddy_icons_get_account_icon_timestamp = time_t function(PurpleAccount* account);																																																						/* da_purple_buddy_icons_get_account_icon_timestamp purple_buddy_icons_get_account_icon_timestamp; */
alias da_purple_buddy_icons_node_has_custom_icon = gboolean function(PurpleBlistNode* node);																																																						/* da_purple_buddy_icons_node_has_custom_icon purple_buddy_icons_node_has_custom_icon; */
alias da_purple_buddy_icons_node_find_custom_icon = PurpleStoredImage* function(PurpleBlistNode* node);																																																						/* da_purple_buddy_icons_node_find_custom_icon purple_buddy_icons_node_find_custom_icon; */
alias da_purple_buddy_icons_node_set_custom_icon = PurpleStoredImage* function(PurpleBlistNode* node, guchar* icon_data, size_t icon_len);																																																						/* da_purple_buddy_icons_node_set_custom_icon purple_buddy_icons_node_set_custom_icon; */
alias da_purple_buddy_icons_node_set_custom_icon_from_file = PurpleStoredImage* function(PurpleBlistNode* node, const(gchar)* filename);																																																						/* da_purple_buddy_icons_node_set_custom_icon_from_file purple_buddy_icons_node_set_custom_icon_from_file; */
alias da_purple_buddy_icons_has_custom_icon = gboolean function(PurpleContact* contact);																																																						/* da_purple_buddy_icons_has_custom_icon purple_buddy_icons_has_custom_icon; */
alias da_purple_buddy_icons_find_custom_icon = PurpleStoredImage* function(PurpleContact* contact);																																																						/* da_purple_buddy_icons_find_custom_icon purple_buddy_icons_find_custom_icon; */
alias da_purple_buddy_icons_set_custom_icon = PurpleStoredImage* function(PurpleContact* contact, guchar* icon_data, size_t icon_len);																																																						/* da_purple_buddy_icons_set_custom_icon purple_buddy_icons_set_custom_icon; */
alias da_purple_buddy_icons_set_caching = void function(gboolean caching);																																																						/* da_purple_buddy_icons_set_caching purple_buddy_icons_set_caching; */
alias da_purple_buddy_icons_is_caching = gboolean function();																																																						/* da_purple_buddy_icons_is_caching purple_buddy_icons_is_caching; */
alias da_purple_buddy_icons_set_cache_dir = void function(const(char)* cache_dir);																																																						/* da_purple_buddy_icons_set_cache_dir purple_buddy_icons_set_cache_dir; */
alias da_purple_buddy_icons_get_cache_dir = const(char)* function();																																																						/* da_purple_buddy_icons_get_cache_dir purple_buddy_icons_get_cache_dir; */
alias da_purple_buddy_icons_get_handle = void* function();																																																						/* da_purple_buddy_icons_get_handle purple_buddy_icons_get_handle; */
alias da_purple_buddy_icons_init = void function();																																																						/* da_purple_buddy_icons_init purple_buddy_icons_init; */
alias da_purple_buddy_icons_uninit = void function();																																																						/* da_purple_buddy_icons_uninit purple_buddy_icons_uninit; */
alias da_purple_buddy_icon_get_scale_size = void function(PurpleBuddyIconSpec* spec, int* width, int* height);																																																						/* da_purple_buddy_icon_get_scale_size purple_buddy_icon_get_scale_size; */
