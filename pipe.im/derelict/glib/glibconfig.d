module derelict.glib.glibconfig;

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