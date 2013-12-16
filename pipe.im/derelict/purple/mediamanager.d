module derelict.purple.mediamanager;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.media;
import derelict.purple.account;
import derelict.purple.enum_types;

extern (C):

alias _PurpleMediaManager PurpleMediaManager;
alias _PurpleMediaManagerClass PurpleMediaManagerClass;

struct _PurpleMediaManager;


struct _PurpleMediaManagerClass;


alias da_purple_media_manager_get_type = GType function();																																																						/* da_purple_media_manager_get_type purple_media_manager_get_type; */
alias da_purple_media_manager_get = PurpleMediaManager* function();																																																						/* da_purple_media_manager_get purple_media_manager_get; */
alias da_purple_media_manager_create_media = PurpleMedia* function(PurpleMediaManager* manager, PurpleAccount* account, const(char)* conference_type, const(char)* remote_user, gboolean initiator);																																																						/* da_purple_media_manager_create_media purple_media_manager_create_media; */
alias da_purple_media_manager_get_media = GList* function(PurpleMediaManager* manager);																																																						/* da_purple_media_manager_get_media purple_media_manager_get_media; */
alias da_purple_media_manager_get_media_by_account = GList* function(PurpleMediaManager* manager, PurpleAccount* account);																																																						/* da_purple_media_manager_get_media_by_account purple_media_manager_get_media_by_account; */
alias da_purple_media_manager_remove_media = void function(PurpleMediaManager* manager, PurpleMedia* media);																																																						/* da_purple_media_manager_remove_media purple_media_manager_remove_media; */
alias da_purple_media_manager_create_output_window = gboolean function(PurpleMediaManager* manager, PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant);																																																						/* da_purple_media_manager_create_output_window purple_media_manager_create_output_window; */
alias da_purple_media_manager_set_output_window = gulong function(PurpleMediaManager* manager, PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant, gulong window_id);																																																						/* da_purple_media_manager_set_output_window purple_media_manager_set_output_window; */
alias da_purple_media_manager_remove_output_window = gboolean function(PurpleMediaManager* manager, gulong output_window_id);																																																						/* da_purple_media_manager_remove_output_window purple_media_manager_remove_output_window; */
alias da_purple_media_manager_remove_output_windows = void function(PurpleMediaManager* manager, PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant);																																																						/* da_purple_media_manager_remove_output_windows purple_media_manager_remove_output_windows; */
alias da_purple_media_manager_set_ui_caps = void function(PurpleMediaManager* manager, PurpleMediaCaps caps);																																																						/* da_purple_media_manager_set_ui_caps purple_media_manager_set_ui_caps; */
alias da_purple_media_manager_get_ui_caps = PurpleMediaCaps function(PurpleMediaManager* manager);																																																						/* da_purple_media_manager_get_ui_caps purple_media_manager_get_ui_caps; */
alias da_purple_media_manager_set_backend_type = void function(PurpleMediaManager* manager, GType backend_type);																																																						/* da_purple_media_manager_set_backend_type purple_media_manager_set_backend_type; */
alias da_purple_media_manager_get_backend_type = GType function(PurpleMediaManager* manager);																																																						/* da_purple_media_manager_get_backend_type purple_media_manager_get_backend_type; */
