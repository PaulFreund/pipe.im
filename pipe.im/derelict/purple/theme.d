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

GType purple_theme_get_type ();
const(gchar)* purple_theme_get_name (PurpleTheme* theme);
void purple_theme_set_name (PurpleTheme* theme, const(gchar)* name);
const(gchar)* purple_theme_get_description (PurpleTheme* theme);
void purple_theme_set_description (PurpleTheme* theme, const(gchar)* description);
const(gchar)* purple_theme_get_author (PurpleTheme* theme);
void purple_theme_set_author (PurpleTheme* theme, const(gchar)* author);
const(gchar)* purple_theme_get_type_string (PurpleTheme* theme);
const(gchar)* purple_theme_get_dir (PurpleTheme* theme);
void purple_theme_set_dir (PurpleTheme* theme, const(gchar)* dir);
const(gchar)* purple_theme_get_image (PurpleTheme* theme);
gchar* purple_theme_get_image_full (PurpleTheme* theme);
void purple_theme_set_image (PurpleTheme* theme, const(gchar)* img);