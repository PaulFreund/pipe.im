module derelict.purple._version;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

extern __gshared const guint purple_major_version;
extern __gshared const guint purple_minor_version;
extern __gshared const guint purple_micro_version;

const(char)* purple_version_check (guint required_major, guint required_minor, guint required_micro);