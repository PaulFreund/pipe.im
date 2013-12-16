module derelict.glib.gtimezone;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import core.stdc.config;

extern (C):

alias _GTimeZone GTimeZone;
alias _Anonymous_0 GTimeType;

enum _Anonymous_0
{
	G_TIME_TYPE_STANDARD = 0,
	G_TIME_TYPE_DAYLIGHT = 1,
	G_TIME_TYPE_UNIVERSAL = 2
}

struct _GTimeZone;


alias da_g_time_zone_new = GTimeZone* function(const(gchar)* identifier);																																																						/* da_g_time_zone_new g_time_zone_new; */
alias da_g_time_zone_new_utc = GTimeZone* function();																																																						/* da_g_time_zone_new_utc g_time_zone_new_utc; */
alias da_g_time_zone_new_local = GTimeZone* function();																																																						/* da_g_time_zone_new_local g_time_zone_new_local; */
alias da_g_time_zone_ref = GTimeZone* function(GTimeZone* tz);																																																						/* da_g_time_zone_ref g_time_zone_ref; */
alias da_g_time_zone_unref = void function(GTimeZone* tz);																																																						/* da_g_time_zone_unref g_time_zone_unref; */
alias da_g_time_zone_find_interval = gint function(GTimeZone* tz, GTimeType type, gint64 time_);																																																						/* da_g_time_zone_find_interval g_time_zone_find_interval; */
alias da_g_time_zone_adjust_time = gint function(GTimeZone* tz, GTimeType type, gint64* time_);																																																						/* da_g_time_zone_adjust_time g_time_zone_adjust_time; */
alias da_g_time_zone_get_abbreviation = const(gchar)* function(GTimeZone* tz, gint interval);																																																						/* da_g_time_zone_get_abbreviation g_time_zone_get_abbreviation; */
alias da_g_time_zone_get_offset = gint32 function(GTimeZone* tz, gint interval);																																																						/* da_g_time_zone_get_offset g_time_zone_get_offset; */
alias da_g_time_zone_is_dst = gboolean function(GTimeZone* tz, gint interval);																																																						/* da_g_time_zone_is_dst g_time_zone_is_dst; */
