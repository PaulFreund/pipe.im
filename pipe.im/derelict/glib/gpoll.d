module derelict.glib.gpoll;

import core.sys.posix.poll;

extern (C):

alias _GPollFD GPollFD;
alias int function (_GPollFD*, uint, int) GPollFunc;

struct _GPollFD
{
	gint fd;
	gushort events;
	gushort revents;
}

gint g_poll (GPollFD* fds, guint nfds, gint timeout);