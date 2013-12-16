module derelict.purple.theme_manager;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.purple.theme;
import derelict.purple.theme_loader;

extern (C):

alias void function (_PurpleTheme*) PTFunc;
alias _PurpleThemeManager PurpleThemeManager;
alias _PurpleThemeManagerClass PurpleThemeManagerClass;

struct _PurpleThemeManager
{
	GObject parent;
}

struct _PurpleThemeManagerClass
{
	GObjectClass parent_class;
}

alias da_purple_theme_manager_get_type = GType function();																																																						/* da_purple_theme_manager_get_type purple_theme_manager_get_type; */
alias da_purple_theme_manager_init = void function();																																																						/* da_purple_theme_manager_init purple_theme_manager_init; */
alias da_purple_theme_manager_uninit = void function();																																																						/* da_purple_theme_manager_uninit purple_theme_manager_uninit; */
alias da_purple_theme_manager_refresh = void function();																																																						/* da_purple_theme_manager_refresh purple_theme_manager_refresh; */
alias da_purple_theme_manager_find_theme = PurpleTheme* function(const(gchar)* name, const(gchar)* type);																																																						/* da_purple_theme_manager_find_theme purple_theme_manager_find_theme; */
alias da_purple_theme_manager_add_theme = void function(PurpleTheme* theme);																																																						/* da_purple_theme_manager_add_theme purple_theme_manager_add_theme; */
alias da_purple_theme_manager_remove_theme = void function(PurpleTheme* theme);																																																						/* da_purple_theme_manager_remove_theme purple_theme_manager_remove_theme; */
alias da_purple_theme_manager_register_type = void function(PurpleThemeLoader* loader);																																																						/* da_purple_theme_manager_register_type purple_theme_manager_register_type; */
alias da_purple_theme_manager_unregister_type = void function(PurpleThemeLoader* loader);																																																						/* da_purple_theme_manager_unregister_type purple_theme_manager_unregister_type; */
alias da_purple_theme_manager_for_each_theme = void function(PTFunc func);																																																						/* da_purple_theme_manager_for_each_theme purple_theme_manager_for_each_theme; */
alias da_purple_theme_manager_load_theme = PurpleTheme* function(const(gchar)* theme_dir, const(gchar)* type);																																																						/* da_purple_theme_manager_load_theme purple_theme_manager_load_theme; */
