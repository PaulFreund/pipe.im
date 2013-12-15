module derelict.glib.gdate;

import core.stdc.config;
import core.stdc.time;

extern (C):

alias int GTime;
alias ushort GDateYear;
alias ubyte GDateDay;
alias _GDate GDate;
alias _Anonymous_0 GDateDMY;
alias _Anonymous_1 GDateWeekday;
alias _Anonymous_2 GDateMonth;

enum _Anonymous_0
{
	G_DATE_DAY = 0,
	G_DATE_MONTH = 1,
	G_DATE_YEAR = 2
}

enum _Anonymous_1
{
	G_DATE_BAD_WEEKDAY = 0,
	G_DATE_MONDAY = 1,
	G_DATE_TUESDAY = 2,
	G_DATE_WEDNESDAY = 3,
	G_DATE_THURSDAY = 4,
	G_DATE_FRIDAY = 5,
	G_DATE_SATURDAY = 6,
	G_DATE_SUNDAY = 7
}

enum _Anonymous_2
{
	G_DATE_BAD_MONTH = 0,
	G_DATE_JANUARY = 1,
	G_DATE_FEBRUARY = 2,
	G_DATE_MARCH = 3,
	G_DATE_APRIL = 4,
	G_DATE_MAY = 5,
	G_DATE_JUNE = 6,
	G_DATE_JULY = 7,
	G_DATE_AUGUST = 8,
	G_DATE_SEPTEMBER = 9,
	G_DATE_OCTOBER = 10,
	G_DATE_NOVEMBER = 11,
	G_DATE_DECEMBER = 12
}

struct _GDate
{
	guint julian_days;
	guint julian;
	guint dmy;
	guint day;
	guint month;
	guint year;
}

GDate* g_date_new ();
GDate* g_date_new_dmy (GDateDay day, GDateMonth month, GDateYear year);
GDate* g_date_new_julian (guint32 julian_day);
void g_date_free (GDate* date);
gboolean g_date_valid (const(GDate)* date);
gboolean g_date_valid_day (GDateDay day);
gboolean g_date_valid_month (GDateMonth month);
gboolean g_date_valid_year (GDateYear year);
gboolean g_date_valid_weekday (GDateWeekday weekday);
gboolean g_date_valid_julian (guint32 julian_date);
gboolean g_date_valid_dmy (GDateDay day, GDateMonth month, GDateYear year);
GDateWeekday g_date_get_weekday (const(GDate)* date);
GDateMonth g_date_get_month (const(GDate)* date);
GDateYear g_date_get_year (const(GDate)* date);
GDateDay g_date_get_day (const(GDate)* date);
guint32 g_date_get_julian (const(GDate)* date);
guint g_date_get_day_of_year (const(GDate)* date);
guint g_date_get_monday_week_of_year (const(GDate)* date);
guint g_date_get_sunday_week_of_year (const(GDate)* date);
guint g_date_get_iso8601_week_of_year (const(GDate)* date);
void g_date_clear (GDate* date, guint n_dates);
void g_date_set_parse (GDate* date, const(gchar)* str);
void g_date_set_time_t (GDate* date, time_t timet);
void g_date_set_time_val (GDate* date, GTimeVal* timeval);
void g_date_set_time (GDate* date, GTime time_);
void g_date_set_month (GDate* date, GDateMonth month);
void g_date_set_day (GDate* date, GDateDay day);
void g_date_set_year (GDate* date, GDateYear year);
void g_date_set_dmy (GDate* date, GDateDay day, GDateMonth month, GDateYear y);
void g_date_set_julian (GDate* date, guint32 julian_date);
gboolean g_date_is_first_of_month (const(GDate)* date);
gboolean g_date_is_last_of_month (const(GDate)* date);
void g_date_add_days (GDate* date, guint n_days);
void g_date_subtract_days (GDate* date, guint n_days);
void g_date_add_months (GDate* date, guint n_months);
void g_date_subtract_months (GDate* date, guint n_months);
void g_date_add_years (GDate* date, guint n_years);
void g_date_subtract_years (GDate* date, guint n_years);
gboolean g_date_is_leap_year (GDateYear year);
guint8 g_date_get_days_in_month (GDateMonth month, GDateYear year);
guint8 g_date_get_monday_weeks_in_year (GDateYear year);
guint8 g_date_get_sunday_weeks_in_year (GDateYear year);
gint g_date_days_between (const(GDate)* date1, const(GDate)* date2);
gint g_date_compare (const(GDate)* lhs, const(GDate)* rhs);
void g_date_to_struct_tm (const(GDate)* date, tm* tm);
void g_date_clamp (GDate* date, const(GDate)* min_date, const(GDate)* max_date);
void g_date_order (GDate* date1, GDate* date2);
gsize g_date_strftime (gchar* s, gsize slen, const(gchar)* format, const(GDate)* date);