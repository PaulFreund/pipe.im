module derelict.glib.gtimer;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _GTimer GTimer;

struct _GTimer;


alias da_g_timer_new = GTimer* function();																																																						/* da_g_timer_new g_timer_new; */
alias da_g_timer_destroy = void function(GTimer* timer);																																																						/* da_g_timer_destroy g_timer_destroy; */
alias da_g_timer_start = void function(GTimer* timer);																																																						/* da_g_timer_start g_timer_start; */
alias da_g_timer_stop = void function(GTimer* timer);																																																						/* da_g_timer_stop g_timer_stop; */
alias da_g_timer_reset = void function(GTimer* timer);																																																						/* da_g_timer_reset g_timer_reset; */
alias da_g_timer_continue = void function(GTimer* timer);																																																						/* da_g_timer_continue g_timer_continue; */
alias da_g_timer_elapsed = gdouble function(GTimer* timer, gulong* microseconds);																																																						/* da_g_timer_elapsed g_timer_elapsed; */
alias da_g_usleep = void function(gulong microseconds);																																																						/* da_g_usleep g_usleep; */
alias da_g_time_val_add = void function(GTimeVal* time_, glong microseconds);																																																						/* da_g_time_val_add g_time_val_add; */
alias da_g_time_val_from_iso8601 = gboolean function(const(gchar)* iso_date, GTimeVal* time_);																																																						/* da_g_time_val_from_iso8601 g_time_val_from_iso8601; */
alias da_g_time_val_to_iso8601 = gchar* function(GTimeVal* time_);																																																						/* da_g_time_val_to_iso8601 g_time_val_to_iso8601; */
