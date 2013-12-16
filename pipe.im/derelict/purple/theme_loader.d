module derelict.purple.theme_loader;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.purple.theme;

extern (C):

alias _PurpleThemeLoader PurpleThemeLoader;
alias _PurpleThemeLoaderClass PurpleThemeLoaderClass;

struct _PurpleThemeLoader
{
	GObject parent;
	gpointer priv;
}

struct _PurpleThemeLoaderClass
{
	GObjectClass parent_class;
	//<unimplemented> function (const(gchar)*) purple_theme_loader_build;
}

alias da_purple_theme_loader_get_type = GType function();																																																						/* da_purple_theme_loader_get_type purple_theme_loader_get_type; */
alias da_purple_theme_loader_get_type_string = const(gchar)* function(PurpleThemeLoader* self);																																																						/* da_purple_theme_loader_get_type_string purple_theme_loader_get_type_string; */
alias da_purple_theme_loader_build = PurpleTheme* function(PurpleThemeLoader* loader, const(gchar)* dir);																																																						/* da_purple_theme_loader_build purple_theme_loader_build; */
