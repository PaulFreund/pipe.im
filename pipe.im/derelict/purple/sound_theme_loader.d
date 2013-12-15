module derelict.purple.sound_theme_loader;

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

GType purple_sound_theme_loader_get_type ();