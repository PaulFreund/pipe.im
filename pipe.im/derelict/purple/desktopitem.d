module derelict.purple.desktopitem;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _Anonymous_0 PurpleDesktopItemType;
alias _PurpleDesktopItem PurpleDesktopItem;

enum _Anonymous_0
{
	PURPLE_DESKTOP_ITEM_TYPE_NULL = 0,
	PURPLE_DESKTOP_ITEM_TYPE_OTHER = 1,
	PURPLE_DESKTOP_ITEM_TYPE_APPLICATION = 2,
	PURPLE_DESKTOP_ITEM_TYPE_LINK = 3,
	PURPLE_DESKTOP_ITEM_TYPE_FSDEVICE = 4,
	PURPLE_DESKTOP_ITEM_TYPE_MIME_TYPE = 5,
	PURPLE_DESKTOP_ITEM_TYPE_DIRECTORY = 6,
	PURPLE_DESKTOP_ITEM_TYPE_SERVICE = 7,
	PURPLE_DESKTOP_ITEM_TYPE_SERVICE_TYPE = 8
}

struct _PurpleDesktopItem;


alias da_purple_desktop_item_get_type = GType function();																																																						/* da_purple_desktop_item_get_type purple_desktop_item_get_type; */
alias da_purple_desktop_item_new_from_file = PurpleDesktopItem* function(const(char)* filename);																																																						/* da_purple_desktop_item_new_from_file purple_desktop_item_new_from_file; */
alias da_purple_desktop_item_get_entry_type = PurpleDesktopItemType function(const(PurpleDesktopItem)* item);																																																						/* da_purple_desktop_item_get_entry_type purple_desktop_item_get_entry_type; */
alias da_purple_desktop_item_get_string = const(char)* function(const(PurpleDesktopItem)* item, const(char)* attr);																																																						/* da_purple_desktop_item_get_string purple_desktop_item_get_string; */
alias da_purple_desktop_item_copy = PurpleDesktopItem* function(const(PurpleDesktopItem)* item);																																																						/* da_purple_desktop_item_copy purple_desktop_item_copy; */
alias da_purple_desktop_item_unref = void function(PurpleDesktopItem* item);																																																						/* da_purple_desktop_item_unref purple_desktop_item_unref; */
