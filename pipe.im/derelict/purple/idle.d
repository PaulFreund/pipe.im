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

alias da_purple_idle_touch = void function();																																																						/* da_purple_idle_touch purple_idle_touch; */
alias da_purple_idle_set = void function(time_t time);																																																						/* da_purple_idle_set purple_idle_set; */
alias da_purple_idle_set_ui_ops = void function(PurpleIdleUiOps* ops);																																																						/* da_purple_idle_set_ui_ops purple_idle_set_ui_ops; */
alias da_purple_idle_get_ui_ops = PurpleIdleUiOps* function();																																																						/* da_purple_idle_get_ui_ops purple_idle_get_ui_ops; */
alias da_purple_idle_init = void function();																																																						/* da_purple_idle_init purple_idle_init; */
alias da_purple_idle_uninit = void function();																																																						/* da_purple_idle_uninit purple_idle_uninit; */
