module derelict.purple.core;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.ghash;

extern (C):

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


alias da_purple_core_init = gboolean function(const(char)* ui);																																																						/* da_purple_core_init purple_core_init; */
alias da_purple_core_quit = void function();																																																						/* da_purple_core_quit purple_core_quit; */
alias da_purple_core_quit_cb = gboolean function(gpointer unused);																																																						/* da_purple_core_quit_cb purple_core_quit_cb; */
alias da_purple_core_get_version = const(char)* function();																																																						/* da_purple_core_get_version purple_core_get_version; */
alias da_purple_core_get_ui = const(char)* function();																																																						/* da_purple_core_get_ui purple_core_get_ui; */
alias da_purple_get_core = PurpleCore* function();																																																						/* da_purple_get_core purple_get_core; */
alias da_purple_core_set_ui_ops = void function(PurpleCoreUiOps* ops);																																																						/* da_purple_core_set_ui_ops purple_core_set_ui_ops; */
alias da_purple_core_get_ui_ops = PurpleCoreUiOps* function();																																																						/* da_purple_core_get_ui_ops purple_core_get_ui_ops; */
alias da_purple_core_migrate = gboolean function();																																																						/* da_purple_core_migrate purple_core_migrate; */
alias da_purple_core_ensure_single_instance = gboolean function();																																																						/* da_purple_core_ensure_single_instance purple_core_ensure_single_instance; */
alias da_purple_core_get_ui_info = GHashTable* function();																																																						/* da_purple_core_get_ui_info purple_core_get_ui_info; */
