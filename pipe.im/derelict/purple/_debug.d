module derelict.purple._debug;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

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

alias da_purple_debug = void function(PurpleDebugLevel level, const(char)* category, const(char)* format, ...);																																																						/* da_purple_debug purple_debug; */
alias da_purple_debug_misc = void function(const(char)* category, const(char)* format, ...);																																																						/* da_purple_debug_misc purple_debug_misc; */
alias da_purple_debug_info = void function(const(char)* category, const(char)* format, ...);																																																						/* da_purple_debug_info purple_debug_info; */
alias da_purple_debug_warning = void function(const(char)* category, const(char)* format, ...);																																																						/* da_purple_debug_warning purple_debug_warning; */
alias da_purple_debug_error = void function(const(char)* category, const(char)* format, ...);																																																						/* da_purple_debug_error purple_debug_error; */
alias da_purple_debug_fatal = void function(const(char)* category, const(char)* format, ...);																																																						/* da_purple_debug_fatal purple_debug_fatal; */
alias da_purple_debug_set_enabled = void function(gboolean enabled);																																																						/* da_purple_debug_set_enabled purple_debug_set_enabled; */
alias da_purple_debug_is_enabled = gboolean function();																																																						/* da_purple_debug_is_enabled purple_debug_is_enabled; */
alias da_purple_debug_set_verbose = void function(gboolean verbose);																																																						/* da_purple_debug_set_verbose purple_debug_set_verbose; */
alias da_purple_debug_is_verbose = gboolean function();																																																						/* da_purple_debug_is_verbose purple_debug_is_verbose; */
alias da_purple_debug_set_unsafe = void function(gboolean unsafe);																																																						/* da_purple_debug_set_unsafe purple_debug_set_unsafe; */
alias da_purple_debug_is_unsafe = gboolean function();																																																						/* da_purple_debug_is_unsafe purple_debug_is_unsafe; */
alias da_purple_debug_set_ui_ops = void function(PurpleDebugUiOps* ops);																																																						/* da_purple_debug_set_ui_ops purple_debug_set_ui_ops; */
alias da_purple_debug_get_ui_ops = PurpleDebugUiOps* function();																																																						/* da_purple_debug_get_ui_ops purple_debug_get_ui_ops; */
alias da_purple_debug_init = void function();																																																						/* da_purple_debug_init purple_debug_init; */
