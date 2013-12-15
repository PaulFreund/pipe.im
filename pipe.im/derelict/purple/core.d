module derelict.purple.core;

extern (C):

alias PurpleCore PurpleCore;
alias _Anonymous_0 PurpleCoreUiOps;

struct _Anonymous_0
{
	void function () ui_prefs_init;
	void function () debug_ui_init;
	void function () ui_init;
	void function () quit;
	GHashTable* function () get_ui_info;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
}

struct PurpleCore;


gboolean purple_core_init (const(char)* ui);
void purple_core_quit ();
gboolean purple_core_quit_cb (gpointer unused);
const(char)* purple_core_get_version ();
const(char)* purple_core_get_ui ();
PurpleCore* purple_get_core ();
void purple_core_set_ui_ops (PurpleCoreUiOps* ops);
PurpleCoreUiOps* purple_core_get_ui_ops ();
gboolean purple_core_migrate ();
gboolean purple_core_ensure_single_instance ();
GHashTable* purple_core_get_ui_info ();