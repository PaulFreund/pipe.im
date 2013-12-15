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

void purple_whiteboard_set_ui_ops (PurpleWhiteboardUiOps* ops);
void purple_whiteboard_set_prpl_ops (PurpleWhiteboard* wb, PurpleWhiteboardPrplOps* ops);
PurpleWhiteboard* purple_whiteboard_create (PurpleAccount* account, const(char)* who, int state);
void purple_whiteboard_destroy (PurpleWhiteboard* wb);
void purple_whiteboard_start (PurpleWhiteboard* wb);
PurpleWhiteboard* purple_whiteboard_get_session (const(PurpleAccount)* account, const(char)* who);
void purple_whiteboard_draw_list_destroy (GList* draw_list);
gboolean purple_whiteboard_get_dimensions (const(PurpleWhiteboard)* wb, int* width, int* height);
void purple_whiteboard_set_dimensions (PurpleWhiteboard* wb, int width, int height);
void purple_whiteboard_draw_point (PurpleWhiteboard* wb, int x, int y, int color, int size);
void purple_whiteboard_send_draw_list (PurpleWhiteboard* wb, GList* list);
void purple_whiteboard_draw_line (PurpleWhiteboard* wb, int x1, int y1, int x2, int y2, int color, int size);
void purple_whiteboard_clear (PurpleWhiteboard* wb);
void purple_whiteboard_send_clear (PurpleWhiteboard* wb);
void purple_whiteboard_send_brush (PurpleWhiteboard* wb, int size, int color);
gboolean purple_whiteboard_get_brush (const(PurpleWhiteboard)* wb, int* size, int* color);
void purple_whiteboard_set_brush (PurpleWhiteboard* wb, int size, int color);