module derelict.purple.eventloop;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gmain;

extern (C):

alias _Anonymous_0 PurpleInputCondition;
alias void function (void*, int, _Anonymous_0) PurpleInputFunction;
alias _PurpleEventLoopUiOps PurpleEventLoopUiOps;

enum _Anonymous_0
{
	PURPLE_INPUT_READ = 1,
	PURPLE_INPUT_WRITE = 2
}

struct _PurpleEventLoopUiOps
{
	guint function (guint, GSourceFunc, gpointer) timeout_add;
	gboolean function (guint) timeout_remove;
	guint function (int, PurpleInputCondition, PurpleInputFunction, gpointer) input_add;
	gboolean function (guint) input_remove;
	int function (int, int*) input_get_error;
	guint function (guint, GSourceFunc, gpointer) timeout_add_seconds;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

alias da_purple_timeout_add = guint function(guint interval, GSourceFunc function_, gpointer data);																																																						/* da_purple_timeout_add purple_timeout_add; */
alias da_purple_timeout_add_seconds = guint function(guint interval, GSourceFunc function_, gpointer data);																																																						/* da_purple_timeout_add_seconds purple_timeout_add_seconds; */
alias da_purple_timeout_remove = gboolean function(guint handle);																																																						/* da_purple_timeout_remove purple_timeout_remove; */
alias da_purple_input_add = guint function(int fd, PurpleInputCondition cond, PurpleInputFunction func, gpointer user_data);																																																						/* da_purple_input_add purple_input_add; */
alias da_purple_input_remove = gboolean function(guint handle);																																																						/* da_purple_input_remove purple_input_remove; */
alias da_purple_input_get_error = int function(int fd, int* error);																																																						/* da_purple_input_get_error purple_input_get_error; */
alias da_purple_eventloop_set_ui_ops = void function(PurpleEventLoopUiOps* ops);																																																						/* da_purple_eventloop_set_ui_ops purple_eventloop_set_ui_ops; */
alias da_purple_eventloop_get_ui_ops = PurpleEventLoopUiOps* function();																																																						/* da_purple_eventloop_get_ui_ops purple_eventloop_get_ui_ops; */
