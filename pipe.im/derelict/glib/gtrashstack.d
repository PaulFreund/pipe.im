module derelict.glib.gtrashstack;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _GTrashStack GTrashStack;

struct _GTrashStack
{
	GTrashStack* next;
}

alias da_g_trash_stack_push = void function(GTrashStack** stack_p, gpointer data_p);																																																						/* da_g_trash_stack_push g_trash_stack_push; */
alias da_g_trash_stack_pop = gpointer function(GTrashStack** stack_p);																																																						/* da_g_trash_stack_pop g_trash_stack_pop; */
alias da_g_trash_stack_peek = gpointer function(GTrashStack** stack_p);																																																						/* da_g_trash_stack_peek g_trash_stack_peek; */
alias da_g_trash_stack_height = guint function(GTrashStack** stack_p);																																																						/* da_g_trash_stack_height g_trash_stack_height; */
