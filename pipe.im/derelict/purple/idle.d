module derelict.purple.idle;

import core.stdc.time;

extern (C):

alias _Anonymous_0 PurpleIdleUiOps;

struct _Anonymous_0
{
	time_t function () get_time_idle;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

void purple_idle_touch ();
void purple_idle_set (time_t time);
void purple_idle_set_ui_ops (PurpleIdleUiOps* ops);
PurpleIdleUiOps* purple_idle_get_ui_ops ();
void purple_idle_init ();
void purple_idle_uninit ();