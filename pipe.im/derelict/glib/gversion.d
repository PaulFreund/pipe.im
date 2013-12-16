module derelict.glib.gversion;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

extern __gshared const guint glib_major_version;
extern __gshared const guint glib_minor_version;
extern __gshared const guint glib_micro_version;
extern __gshared const guint glib_interface_age;
extern __gshared const guint glib_binary_age;

alias da_glib_check_version = const(gchar)* function(guint required_major, guint required_minor, guint required_micro);																																																						/* da_glib_check_version glib_check_version; */
