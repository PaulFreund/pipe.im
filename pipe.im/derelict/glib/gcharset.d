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

module derelict.glib.gcharset;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

extern( C ) nothrow 
{
    alias da_g_get_charset = gboolean function(const(char*)* charset);				
    alias da_g_get_codeset = gchar* function();										
    alias da_g_get_language_names = const(gchar*)* function();						
    alias da_g_get_locale_variants = gchar** function(const(gchar)* locale);		
}

__gshared
{
    da_g_get_charset g_get_charset; 
    da_g_get_codeset g_get_codeset; 
    da_g_get_language_names g_get_language_names; 
    da_g_get_locale_variants g_get_locale_variants; 
}