module derelict.glib.gtrashstack;

extern (C):

alias _GTrashStack GTrashStack;

struct _GTrashStack
{
	GTrashStack* next;
}

void g_trash_stack_push (GTrashStack** stack_p, gpointer data_p);
gpointer g_trash_stack_pop (GTrashStack** stack_p);
gpointer g_trash_stack_peek (GTrashStack** stack_p);
guint g_trash_stack_height (GTrashStack** stack_p);
void g_trash_stack_push (GTrashStack** stack_p, gpointer data_p);
gpointer g_trash_stack_pop (GTrashStack** stack_p);
gpointer g_trash_stack_peek (GTrashStack** stack_p);
guint g_trash_stack_height (GTrashStack** stack_p);