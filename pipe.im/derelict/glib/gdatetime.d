module derelict.glib.gdatetime;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.gdate;
import derelict.glib.gtimezone;
import core.stdc.time;
import core.stdc.config;

extern (C):

alias c_long GTimeSpan;
alias _GDateTime GDateTime;

struct _GDateTime;


alias da_g_date_time_unref = void function(GDateTime* datetime);																																																						/* da_g_date_time_unref g_date_time_unref; */
alias da_g_date_time_ref = GDateTime* function(GDateTime* datetime);																																																						/* da_g_date_time_ref g_date_time_ref; */
alias da_g_date_time_new_now = GDateTime* function(GTimeZone* tz);																																																						/* da_g_date_time_new_now g_date_time_new_now; */
alias da_g_date_time_new_now_local = GDateTime* function();																																																						/* da_g_date_time_new_now_local g_date_time_new_now_local; */
alias da_g_date_time_new_now_utc = GDateTime* function();																																																						/* da_g_date_time_new_now_utc g_date_time_new_now_utc; */
alias da_g_date_time_new_from_unix_local = GDateTime* function(gint64 t);																																																						/* da_g_date_time_new_from_unix_local g_date_time_new_from_unix_local; */
alias da_g_date_time_new_from_unix_utc = GDateTime* function(gint64 t);																																																						/* da_g_date_time_new_from_unix_utc g_date_time_new_from_unix_utc; */
alias da_g_date_time_new_from_timeval_local = GDateTime* function(const(GTimeVal)* tv);																																																						/* da_g_date_time_new_from_timeval_local g_date_time_new_from_timeval_local; */
alias da_g_date_time_new_from_timeval_utc = GDateTime* function(const(GTimeVal)* tv);																																																						/* da_g_date_time_new_from_timeval_utc g_date_time_new_from_timeval_utc; */
alias da_g_date_time_new = GDateTime* function(GTimeZone* tz, gint year, gint month, gint day, gint hour, gint minute, gdouble seconds);																																																						/* da_g_date_time_new g_date_time_new; */
alias da_g_date_time_new_local = GDateTime* function(gint year, gint month, gint day, gint hour, gint minute, gdouble seconds);																																																						/* da_g_date_time_new_local g_date_time_new_local; */
alias da_g_date_time_new_utc = GDateTime* function(gint year, gint month, gint day, gint hour, gint minute, gdouble seconds);																																																						/* da_g_date_time_new_utc g_date_time_new_utc; */
alias da_g_date_time_add = GDateTime* function(GDateTime* datetime, GTimeSpan timespan);																																																						/* da_g_date_time_add g_date_time_add; */
alias da_g_date_time_add_years = GDateTime* function(GDateTime* datetime, gint years);																																																						/* da_g_date_time_add_years g_date_time_add_years; */
alias da_g_date_time_add_months = GDateTime* function(GDateTime* datetime, gint months);																																																						/* da_g_date_time_add_months g_date_time_add_months; */
alias da_g_date_time_add_weeks = GDateTime* function(GDateTime* datetime, gint weeks);																																																						/* da_g_date_time_add_weeks g_date_time_add_weeks; */
alias da_g_date_time_add_days = GDateTime* function(GDateTime* datetime, gint days);																																																						/* da_g_date_time_add_days g_date_time_add_days; */
alias da_g_date_time_add_hours = GDateTime* function(GDateTime* datetime, gint hours);																																																						/* da_g_date_time_add_hours g_date_time_add_hours; */
alias da_g_date_time_add_minutes = GDateTime* function(GDateTime* datetime, gint minutes);																																																						/* da_g_date_time_add_minutes g_date_time_add_minutes; */
alias da_g_date_time_add_seconds = GDateTime* function(GDateTime* datetime, gdouble seconds);																																																						/* da_g_date_time_add_seconds g_date_time_add_seconds; */
alias da_g_date_time_add_full = GDateTime* function(GDateTime* datetime, gint years, gint months, gint days, gint hours, gint minutes, gdouble seconds);																																																						/* da_g_date_time_add_full g_date_time_add_full; */
alias da_g_date_time_compare = gint function(gconstpointer dt1, gconstpointer dt2);																																																						/* da_g_date_time_compare g_date_time_compare; */
alias da_g_date_time_difference = GTimeSpan function(GDateTime* end, GDateTime* begin);																																																						/* da_g_date_time_difference g_date_time_difference; */
alias da_g_date_time_hash = guint function(gconstpointer datetime);																																																						/* da_g_date_time_hash g_date_time_hash; */
alias da_g_date_time_equal = gboolean function(gconstpointer dt1, gconstpointer dt2);																																																						/* da_g_date_time_equal g_date_time_equal; */
alias da_g_date_time_get_ymd = void function(GDateTime* datetime, gint* year, gint* month, gint* day);																																																						/* da_g_date_time_get_ymd g_date_time_get_ymd; */
alias da_g_date_time_get_year = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_year g_date_time_get_year; */
alias da_g_date_time_get_month = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_month g_date_time_get_month; */
alias da_g_date_time_get_day_of_month = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_day_of_month g_date_time_get_day_of_month; */
alias da_g_date_time_get_week_numbering_year = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_week_numbering_year g_date_time_get_week_numbering_year; */
alias da_g_date_time_get_week_of_year = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_week_of_year g_date_time_get_week_of_year; */
alias da_g_date_time_get_day_of_week = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_day_of_week g_date_time_get_day_of_week; */
alias da_g_date_time_get_day_of_year = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_day_of_year g_date_time_get_day_of_year; */
alias da_g_date_time_get_hour = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_hour g_date_time_get_hour; */
alias da_g_date_time_get_minute = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_minute g_date_time_get_minute; */
alias da_g_date_time_get_second = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_second g_date_time_get_second; */
alias da_g_date_time_get_microsecond = gint function(GDateTime* datetime);																																																						/* da_g_date_time_get_microsecond g_date_time_get_microsecond; */
alias da_g_date_time_get_seconds = gdouble function(GDateTime* datetime);																																																						/* da_g_date_time_get_seconds g_date_time_get_seconds; */
alias da_g_date_time_to_unix = gint64 function(GDateTime* datetime);																																																						/* da_g_date_time_to_unix g_date_time_to_unix; */
alias da_g_date_time_to_timeval = gboolean function(GDateTime* datetime, GTimeVal* tv);																																																						/* da_g_date_time_to_timeval g_date_time_to_timeval; */
alias da_g_date_time_get_utc_offset = GTimeSpan function(GDateTime* datetime);																																																						/* da_g_date_time_get_utc_offset g_date_time_get_utc_offset; */
alias da_g_date_time_get_timezone_abbreviation = const(gchar)* function(GDateTime* datetime);																																																						/* da_g_date_time_get_timezone_abbreviation g_date_time_get_timezone_abbreviation; */
alias da_g_date_time_is_daylight_savings = gboolean function(GDateTime* datetime);																																																						/* da_g_date_time_is_daylight_savings g_date_time_is_daylight_savings; */
alias da_g_date_time_to_timezone = GDateTime* function(GDateTime* datetime, GTimeZone* tz);																																																						/* da_g_date_time_to_timezone g_date_time_to_timezone; */
alias da_g_date_time_to_local = GDateTime* function(GDateTime* datetime);																																																						/* da_g_date_time_to_local g_date_time_to_local; */
alias da_g_date_time_to_utc = GDateTime* function(GDateTime* datetime);																																																						/* da_g_date_time_to_utc g_date_time_to_utc; */
alias da_g_date_time_format = gchar* function(GDateTime* datetime, const(gchar)* format);																																																						/* da_g_date_time_format g_date_time_format; */
