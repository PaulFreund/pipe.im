module derelict.purple.whiteboard;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.account;
extern (C):

alias _PurpleWhiteboardPrplOps PurpleWhiteboardPrplOps;
alias _PurpleWhiteboard PurpleWhiteboard;
alias _PurpleWhiteboardUiOps PurpleWhiteboardUiOps;

struct _PurpleWhiteboard
{
	int state;
	PurpleAccount* account;
	char* who;
	void* ui_data;
	void* proto_data;
	PurpleWhiteboardPrplOps* prpl_ops;
	GList* draw_list;
}

struct _PurpleWhiteboardUiOps
{
	void function (PurpleWhiteboard*) create;
	void function (PurpleWhiteboard*) destroy;
	void function (PurpleWhiteboard*, int, int) set_dimensions;
	void function (PurpleWhiteboard*, int, int) set_brush;
	void function (PurpleWhiteboard*, int, int, int, int) draw_point;
	void function (PurpleWhiteboard*, int, int, int, int, int, int) draw_line;
	void function (PurpleWhiteboard*) clear;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

struct _PurpleWhiteboardPrplOps
{
	void function (PurpleWhiteboard*) start;
	void function (PurpleWhiteboard*) end;
	void function (const(PurpleWhiteboard)*, int*, int*) get_dimensions;
	void function (PurpleWhiteboard*, int, int) set_dimensions;
	void function (const(PurpleWhiteboard)*, int*, int*) get_brush;
	void function (PurpleWhiteboard*, int, int) set_brush;
	void function (PurpleWhiteboard*, GList*) send_draw_list;
	void function (PurpleWhiteboard*) clear;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

alias da_purple_whiteboard_set_ui_ops = void function(PurpleWhiteboardUiOps* ops);																																																						/* da_purple_whiteboard_set_ui_ops purple_whiteboard_set_ui_ops; */
alias da_purple_whiteboard_set_prpl_ops = void function(PurpleWhiteboard* wb, PurpleWhiteboardPrplOps* ops);																																																						/* da_purple_whiteboard_set_prpl_ops purple_whiteboard_set_prpl_ops; */
alias da_purple_whiteboard_create = PurpleWhiteboard* function(PurpleAccount* account, const(char)* who, int state);																																																						/* da_purple_whiteboard_create purple_whiteboard_create; */
alias da_purple_whiteboard_destroy = void function(PurpleWhiteboard* wb);																																																						/* da_purple_whiteboard_destroy purple_whiteboard_destroy; */
alias da_purple_whiteboard_start = void function(PurpleWhiteboard* wb);																																																						/* da_purple_whiteboard_start purple_whiteboard_start; */
alias da_purple_whiteboard_get_session = PurpleWhiteboard* function(const(PurpleAccount)* account, const(char)* who);																																																						/* da_purple_whiteboard_get_session purple_whiteboard_get_session; */
alias da_purple_whiteboard_draw_list_destroy = void function(GList* draw_list);																																																						/* da_purple_whiteboard_draw_list_destroy purple_whiteboard_draw_list_destroy; */
alias da_purple_whiteboard_get_dimensions = gboolean function(const(PurpleWhiteboard)* wb, int* width, int* height);																																																						/* da_purple_whiteboard_get_dimensions purple_whiteboard_get_dimensions; */
alias da_purple_whiteboard_set_dimensions = void function(PurpleWhiteboard* wb, int width, int height);																																																						/* da_purple_whiteboard_set_dimensions purple_whiteboard_set_dimensions; */
alias da_purple_whiteboard_draw_point = void function(PurpleWhiteboard* wb, int x, int y, int color, int size);																																																						/* da_purple_whiteboard_draw_point purple_whiteboard_draw_point; */
alias da_purple_whiteboard_send_draw_list = void function(PurpleWhiteboard* wb, GList* list);																																																						/* da_purple_whiteboard_send_draw_list purple_whiteboard_send_draw_list; */
alias da_purple_whiteboard_draw_line = void function(PurpleWhiteboard* wb, int x1, int y1, int x2, int y2, int color, int size);																																																						/* da_purple_whiteboard_draw_line purple_whiteboard_draw_line; */
alias da_purple_whiteboard_clear = void function(PurpleWhiteboard* wb);																																																						/* da_purple_whiteboard_clear purple_whiteboard_clear; */
alias da_purple_whiteboard_send_clear = void function(PurpleWhiteboard* wb);																																																						/* da_purple_whiteboard_send_clear purple_whiteboard_send_clear; */
alias da_purple_whiteboard_send_brush = void function(PurpleWhiteboard* wb, int size, int color);																																																						/* da_purple_whiteboard_send_brush purple_whiteboard_send_brush; */
alias da_purple_whiteboard_get_brush = gboolean function(const(PurpleWhiteboard)* wb, int* size, int* color);																																																						/* da_purple_whiteboard_get_brush purple_whiteboard_get_brush; */
alias da_purple_whiteboard_set_brush = void function(PurpleWhiteboard* wb, int size, int color);																																																						/* da_purple_whiteboard_set_brush purple_whiteboard_set_brush; */
