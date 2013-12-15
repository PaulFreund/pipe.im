module derelict.purple.mediamanager;

extern (C):

alias _PurpleMediaManager PurpleMediaManager;
alias _PurpleMediaManagerClass PurpleMediaManagerClass;

struct _PurpleMediaManager;


struct _PurpleMediaManagerClass;


GType purple_media_manager_get_type ();
PurpleMediaManager* purple_media_manager_get ();
PurpleMedia* purple_media_manager_create_media (PurpleMediaManager* manager, PurpleAccount* account, const(char)* conference_type, const(char)* remote_user, gboolean initiator);
GList* purple_media_manager_get_media (PurpleMediaManager* manager);
GList* purple_media_manager_get_media_by_account (PurpleMediaManager* manager, PurpleAccount* account);
void purple_media_manager_remove_media (PurpleMediaManager* manager, PurpleMedia* media);
gboolean purple_media_manager_create_output_window (PurpleMediaManager* manager, PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant);
gulong purple_media_manager_set_output_window (PurpleMediaManager* manager, PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant, gulong window_id);
gboolean purple_media_manager_remove_output_window (PurpleMediaManager* manager, gulong output_window_id);
void purple_media_manager_remove_output_windows (PurpleMediaManager* manager, PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant);
void purple_media_manager_set_ui_caps (PurpleMediaManager* manager, PurpleMediaCaps caps);
PurpleMediaCaps purple_media_manager_get_ui_caps (PurpleMediaManager* manager);
void purple_media_manager_set_backend_type (PurpleMediaManager* manager, GType backend_type);
GType purple_media_manager_get_backend_type (PurpleMediaManager* manager);