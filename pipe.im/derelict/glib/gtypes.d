module derelict.glib.gtypes;

import core.stdc.config;

extern (C):

alias char gchar;
alias short gshort;
alias c_long glong;
alias int gint;
alias int gboolean;
alias ubyte guchar;
alias ushort gushort;
alias c_ulong gulong;
alias uint guint;
alias float gfloat;
alias double gdouble;
alias void* gpointer;
alias const(void)* gconstpointer;
alias int function (const(void)*, const(void)*) GCompareFunc;
alias int function (const(void)*, const(void)*, void*) GCompareDataFunc;
alias int function (const(void)*, const(void)*) GEqualFunc;
alias void function (void*) GDestroyNotify;
alias void function (void*, void*) GFunc;
alias uint function (const(void)*) GHashFunc;
alias void function (void*, void*, void*) GHFunc;
alias void function (void*) GFreeFunc;
alias const(char)* function (const(char)*, void*) GTranslateFunc;
alias _GDoubleIEEE754 GDoubleIEEE754;
alias _GFloatIEEE754 GFloatIEEE754;
alias _GTimeVal GTimeVal;

struct _GTimeVal
{
	glong tv_sec;
	glong tv_usec;
}

//union _GDoubleIEEE754;


//union _GFloatIEEE754;


union _GFloatIEEE754
{
	gfloat v_float;
	struct
	{
		guint mantissa;
		guint biased_exponent;
		guint sign;
	}
}

union _GDoubleIEEE754
{
	gdouble v_double;
	struct
	{
		guint mantissa_low;
		guint mantissa_high;
		guint biased_exponent;
		guint sign;
	}
}
