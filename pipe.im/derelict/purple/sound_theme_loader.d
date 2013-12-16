module derelict.purple.sound_theme_loader;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.purple.theme_loader;

extern (C):

alias _PurpleSoundThemeLoader PurpleSoundThemeLoader;
alias _PurpleSoundThemeLoaderClass PurpleSoundThemeLoaderClass;

struct _PurpleSoundThemeLoader
{
	PurpleThemeLoader parent;
}

struct _PurpleSoundThemeLoaderClass
{
	PurpleThemeLoaderClass parent_class;
}

alias da_purple_sound_theme_loader_get_type = GType function();																																																						/* da_purple_sound_theme_loader_get_type purple_sound_theme_loader_get_type; */
