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

guint purple_timeout_add (guint interval, GSourceFunc function_, gpointer data);
guint purple_timeout_add_seconds (guint interval, GSourceFunc function_, gpointer data);
gboolean purple_timeout_remove (guint handle);
guint purple_input_add (int fd, PurpleInputCondition cond, PurpleInputFunction func, gpointer user_data);
gboolean purple_input_remove (guint handle);
int purple_input_get_error (int fd, int* error);
void purple_eventloop_set_ui_ops (PurpleEventLoopUiOps* ops);
PurpleEventLoopUiOps* purple_eventloop_get_ui_ops ();