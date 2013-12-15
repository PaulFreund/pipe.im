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
	<unimplemented> function (const(gchar)*) purple_theme_loader_build;
}

GType purple_theme_loader_get_type ();
const(gchar)* purple_theme_loader_get_type_string (PurpleThemeLoader* self);
PurpleTheme* purple_theme_loader_build (PurpleThemeLoader* loader, const(gchar)* dir);