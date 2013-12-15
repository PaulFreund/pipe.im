extern (C):

extern __gshared const guint glib_major_version;
extern __gshared const guint glib_minor_version;
extern __gshared const guint glib_micro_version;
extern __gshared const guint glib_interface_age;
extern __gshared const guint glib_binary_age;

const(gchar)* glib_check_version (guint required_major, guint required_minor, guint required_micro);