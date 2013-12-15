module derelict.purple.theme_manager;

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

GType purple_theme_manager_get_type ();
void purple_theme_manager_init ();
void purple_theme_manager_uninit ();
void purple_theme_manager_refresh ();
PurpleTheme* purple_theme_manager_find_theme (const(gchar)* name, const(gchar)* type);
void purple_theme_manager_add_theme (PurpleTheme* theme);
void purple_theme_manager_remove_theme (PurpleTheme* theme);
void purple_theme_manager_register_type (PurpleThemeLoader* loader);
void purple_theme_manager_unregister_type (PurpleThemeLoader* loader);
void purple_theme_manager_for_each_theme (PTFunc func);
PurpleTheme* purple_theme_manager_load_theme (const(gchar)* theme_dir, const(gchar)* type);