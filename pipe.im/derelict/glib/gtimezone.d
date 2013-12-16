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


GTimeZone* g_time_zone_new (const(gchar)* identifier);
GTimeZone* g_time_zone_new_utc ();
GTimeZone* g_time_zone_new_local ();
GTimeZone* g_time_zone_ref (GTimeZone* tz);
void g_time_zone_unref (GTimeZone* tz);
gint g_time_zone_find_interval (GTimeZone* tz, GTimeType type, gint64 time_);
gint g_time_zone_adjust_time (GTimeZone* tz, GTimeType type, gint64* time_);
const(gchar)* g_time_zone_get_abbreviation (GTimeZone* tz, gint interval);
gint32 g_time_zone_get_offset (GTimeZone* tz, gint interval);
gboolean g_time_zone_is_dst (GTimeZone* tz, gint interval);