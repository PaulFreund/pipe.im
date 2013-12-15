module derelict.purple.desktopitem;

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


GType purple_desktop_item_get_type ();
PurpleDesktopItem* purple_desktop_item_new_from_file (const(char)* filename);
PurpleDesktopItemType purple_desktop_item_get_entry_type (const(PurpleDesktopItem)* item);
const(char)* purple_desktop_item_get_string (const(PurpleDesktopItem)* item, const(char)* attr);
PurpleDesktopItem* purple_desktop_item_copy (const(PurpleDesktopItem)* item);
void purple_desktop_item_unref (PurpleDesktopItem* item);