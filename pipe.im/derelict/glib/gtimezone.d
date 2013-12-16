/*

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/ 

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


extern( C ) nothrow 
{
	alias da_g_time_zone_new = GTimeZone* function(const(gchar)* identifier);							
    alias da_g_time_zone_new_utc = GTimeZone* function();												
    alias da_g_time_zone_new_local = GTimeZone* function();												
    alias da_g_time_zone_ref = GTimeZone* function(GTimeZone* tz);										
    alias da_g_time_zone_unref = void function(GTimeZone* tz);											
    alias da_g_time_zone_find_interval = gint function(GTimeZone* tz, GTimeType type, gint64 time_);	
    alias da_g_time_zone_adjust_time = gint function(GTimeZone* tz, GTimeType type, gint64* time_);		
    alias da_g_time_zone_get_abbreviation = const(gchar)* function(GTimeZone* tz, gint interval);		
    alias da_g_time_zone_get_offset = gint32 function(GTimeZone* tz, gint interval);					
    alias da_g_time_zone_is_dst = gboolean function(GTimeZone* tz, gint interval);				
}

__gshared
{
    da_g_time_zone_new g_time_zone_new; 
    da_g_time_zone_new_utc g_time_zone_new_utc; 
    da_g_time_zone_new_local g_time_zone_new_local; 
    da_g_time_zone_ref g_time_zone_ref; 
    da_g_time_zone_unref g_time_zone_unref; 
    da_g_time_zone_find_interval g_time_zone_find_interval; 
    da_g_time_zone_adjust_time g_time_zone_adjust_time; 
    da_g_time_zone_get_abbreviation g_time_zone_get_abbreviation; 
    da_g_time_zone_get_offset g_time_zone_get_offset; 
    da_g_time_zone_is_dst g_time_zone_is_dst; 
}