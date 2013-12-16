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

alias da_purple_sound_theme_get_type = GType function();																																																						/* da_purple_sound_theme_get_type purple_sound_theme_get_type; */
alias da_purple_sound_theme_get_file = const(gchar)* function(PurpleSoundTheme* theme, const(gchar)* event);																																																						/* da_purple_sound_theme_get_file purple_sound_theme_get_file; */
alias da_purple_sound_theme_get_file_full = gchar* function(PurpleSoundTheme* theme, const(gchar)* event);																																																						/* da_purple_sound_theme_get_file_full purple_sound_theme_get_file_full; */
alias da_purple_sound_theme_set_file = void function(PurpleSoundTheme* theme, const(gchar)* event, const(gchar)* filename);																																																						/* da_purple_sound_theme_set_file purple_sound_theme_set_file; */
