module derelict.purple.theme;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _PurpleTheme PurpleTheme;
alias _PurpleThemeClass PurpleThemeClass;

struct _PurpleTheme
{
	GObject parent;
	gpointer priv;
}

struct _PurpleThemeClass
{
	GObjectClass parent_class;
}

alias da_purple_theme_get_type = GType function();																																																						/* da_purple_theme_get_type purple_theme_get_type; */
alias da_purple_theme_get_name = const(gchar)* function(PurpleTheme* theme);																																																						/* da_purple_theme_get_name purple_theme_get_name; */
alias da_purple_theme_set_name = void function(PurpleTheme* theme, const(gchar)* name);																																																						/* da_purple_theme_set_name purple_theme_set_name; */
alias da_purple_theme_get_description = const(gchar)* function(PurpleTheme* theme);																																																						/* da_purple_theme_get_description purple_theme_get_description; */
alias da_purple_theme_set_description = void function(PurpleTheme* theme, const(gchar)* description);																																																						/* da_purple_theme_set_description purple_theme_set_description; */
alias da_purple_theme_get_author = const(gchar)* function(PurpleTheme* theme);																																																						/* da_purple_theme_get_author purple_theme_get_author; */
alias da_purple_theme_set_author = void function(PurpleTheme* theme, const(gchar)* author);																																																						/* da_purple_theme_set_author purple_theme_set_author; */
alias da_purple_theme_get_type_string = const(gchar)* function(PurpleTheme* theme);																																																						/* da_purple_theme_get_type_string purple_theme_get_type_string; */
alias da_purple_theme_get_dir = const(gchar)* function(PurpleTheme* theme);																																																						/* da_purple_theme_get_dir purple_theme_get_dir; */
alias da_purple_theme_set_dir = void function(PurpleTheme* theme, const(gchar)* dir);																																																						/* da_purple_theme_set_dir purple_theme_set_dir; */
alias da_purple_theme_get_image = const(gchar)* function(PurpleTheme* theme);																																																						/* da_purple_theme_get_image purple_theme_get_image; */
alias da_purple_theme_get_image_full = gchar* function(PurpleTheme* theme);																																																						/* da_purple_theme_get_image_full purple_theme_get_image_full; */
alias da_purple_theme_set_image = void function(PurpleTheme* theme, const(gchar)* img);																																																						/* da_purple_theme_set_image purple_theme_set_image; */
