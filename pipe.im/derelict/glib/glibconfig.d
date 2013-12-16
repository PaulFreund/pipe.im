module derelict.glib.glibconfig;

import derelict.glib.gtypes;
import derelict.glib.gdataset;
import derelict.glib.gslist;
import core.stdc.config;

extern (C):

alias wchar gint8;
alias ubyte guint8;
alias short gint16;
alias ushort guint16;
alias int gint32;
alias uint guint32;
alias c_long gint64;
alias c_ulong guint64;
alias c_long gssize;
alias c_ulong gsize;
alias c_long goffset;
alias c_long gintptr;
alias c_ulong guintptr;
alias int GPid;

// Normally in gobject

alias int GType;

alias _GObject GObject;
struct _GObject
{
	GTypeInstance g_type_instance;
	guint ref_count;
	GData* qdata;
}

alias _GTypeInstance GTypeInstance;
struct _GTypeInstance
{
	GTypeClass* g_class;
}

alias _GParamSpec GParamSpec;
struct _GParamSpec
{
	GTypeInstance g_type_instance;
	const(gchar)* name;
	GParamFlags flags;
	GType value_type;
	GType owner_type;
	gchar* _nick;
	gchar* _blurb;
	GData* qdata;
	guint ref_count;
	guint param_id;
}

alias _GParamFlags GParamFlags;
enum _GParamFlags
{
	G_PARAM_READABLE = 1,
	G_PARAM_WRITABLE = 2,
	G_PARAM_CONSTRUCT = 4,
	G_PARAM_CONSTRUCT_ONLY = 8,
	G_PARAM_LAX_VALIDATION = 16,
	G_PARAM_STATIC_NAME = 32,
	G_PARAM_PRIVATE = 32,
	G_PARAM_STATIC_NICK = 64,
	G_PARAM_STATIC_BLURB = 128,
	G_PARAM_DEPRECATED = -2147483648
}

alias _GTypeClass GTypeClass;
struct _GTypeClass
{
	GType g_type;
}

alias _GObjectClass GObjectClass;
struct _GObjectClass
{
	GTypeClass g_type_class;
	GSList* construct_properties;
	GObject* function (GType, guint, GObjectConstructParam*) constructor;
	void function (GObject*, guint, const(GValue)*, GParamSpec*) set_property;
	void function (GObject*, guint, GValue*, GParamSpec*) get_property;
	void function (GObject*) dispose;
	void function (GObject*) finalize;
	void function (GObject*, guint, GParamSpec**) dispatch_properties_changed;
	void function (GObject*, GParamSpec*) notify;
	void function (GObject*) constructed;
	gsize flags;
	gpointer[6] pdummy;
}

alias _GObjectConstructParam GObjectConstructParam;
struct _GObjectConstructParam
{
	GParamSpec* pspec;
	GValue* value;
}

alias _GValue GValue;
struct _GValue {
};

alias _GClosure GClosure;
struct _GClosure {
    guint	 in_marshal;
    guint	 is_invalid;
};

alias _GParameter GParameter;
struct _GParameter {
    const gchar *name;
    GValue       value;
};

alias void function() GCallback;

