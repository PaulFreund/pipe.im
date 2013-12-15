module derelict.purple._debug;

extern (C):

alias _Anonymous_0 PurpleDebugLevel;
alias _Anonymous_1 PurpleDebugUiOps;

enum _Anonymous_0
{
	PURPLE_DEBUG_ALL = 0,
	PURPLE_DEBUG_MISC = 1,
	PURPLE_DEBUG_INFO = 2,
	PURPLE_DEBUG_WARNING = 3,
	PURPLE_DEBUG_ERROR = 4,
	PURPLE_DEBUG_FATAL = 5
}

struct _Anonymous_1
{
	void function (PurpleDebugLevel, const(char)*, const(char)*) print;
	gboolean function (PurpleDebugLevel, const(char)*) is_enabled;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

void purple_debug (PurpleDebugLevel level, const(char)* category, const(char)* format, ...);
void purple_debug_misc (const(char)* category, const(char)* format, ...);
void purple_debug_info (const(char)* category, const(char)* format, ...);
void purple_debug_warning (const(char)* category, const(char)* format, ...);
void purple_debug_error (const(char)* category, const(char)* format, ...);
void purple_debug_fatal (const(char)* category, const(char)* format, ...);
void purple_debug_set_enabled (gboolean enabled);
gboolean purple_debug_is_enabled ();
void purple_debug_set_verbose (gboolean verbose);
gboolean purple_debug_is_verbose ();
void purple_debug_set_unsafe (gboolean unsafe);
gboolean purple_debug_is_unsafe ();
void purple_debug_set_ui_ops (PurpleDebugUiOps* ops);
PurpleDebugUiOps* purple_debug_get_ui_ops ();
void purple_debug_init ();