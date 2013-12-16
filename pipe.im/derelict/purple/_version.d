module derelict.purple._version;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

extern __gshared const guint purple_major_version;
extern __gshared const guint purple_minor_version;
extern __gshared const guint purple_micro_version;

alias da_purple_version_check = const(char)* function(guint required_major, guint required_minor, guint required_micro);																																																						/* da_purple_version_check purple_version_check; */
