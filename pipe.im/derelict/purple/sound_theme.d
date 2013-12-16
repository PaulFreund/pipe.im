module derelict.purple.sound_theme;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.purple.theme;

extern (C):

alias _PurpleSoundTheme PurpleSoundTheme;
alias _PurpleSoundThemeClass PurpleSoundThemeClass;

struct _PurpleSoundTheme
{
	PurpleTheme parent;
	gpointer priv;
}

struct _PurpleSoundThemeClass
{
	PurpleThemeClass parent_class;
}

GType purple_sound_theme_get_type ();
const(gchar)* purple_sound_theme_get_file (PurpleSoundTheme* theme, const(gchar)* event);
gchar* purple_sound_theme_get_file_full (PurpleSoundTheme* theme, const(gchar)* event);
void purple_sound_theme_set_file (PurpleSoundTheme* theme, const(gchar)* event, const(gchar)* filename);