module derelict.glib.gpoll;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
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

alias da_g_poll = gint function(GPollFD* fds, guint nfds, gint timeout);																																																						/* da_g_poll g_poll; */
