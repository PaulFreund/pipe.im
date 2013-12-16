module derelict.purple.media;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.account;
import derelict.purple.enum_types;

extern (C):

alias _PurpleMediaCodec PurpleMediaCodec;

struct _PurpleMediaCodec;


alias _PurpleMedia PurpleMedia;

struct _PurpleMediaManager;


struct _PurpleMedia;


alias da_purple_media_get_type = GType function();																																																						/* da_purple_media_get_type purple_media_get_type; */
alias da_purple_media_get_session_ids = GList* function(PurpleMedia* media);																																																						/* da_purple_media_get_session_ids purple_media_get_session_ids; */
alias da_purple_media_get_account = PurpleAccount* function(PurpleMedia* media);																																																						/* da_purple_media_get_account purple_media_get_account; */
alias da_purple_media_get_prpl_data = gpointer function(PurpleMedia* media);																																																						/* da_purple_media_get_prpl_data purple_media_get_prpl_data; */
alias da_purple_media_set_prpl_data = void function(PurpleMedia* media, gpointer prpl_data);																																																						/* da_purple_media_set_prpl_data purple_media_set_prpl_data; */
alias da_purple_media_error = void function(PurpleMedia* media, const(gchar)* error, ...);																																																						/* da_purple_media_error purple_media_error; */
alias da_purple_media_end = void function(PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant);																																																						/* da_purple_media_end purple_media_end; */
alias da_purple_media_stream_info = void function(PurpleMedia* media, PurpleMediaInfoType type, const(gchar)* session_id, const(gchar)* participant, gboolean local);																																																						/* da_purple_media_stream_info purple_media_stream_info; */
alias da_purple_media_set_params = void function(PurpleMedia* media, guint num_params, GParameter* params);																																																						/* da_purple_media_set_params purple_media_set_params; */
alias da_purple_media_get_available_params = const(gchar*)* function(PurpleMedia* media);																																																						/* da_purple_media_get_available_params purple_media_get_available_params; */
alias da_purple_media_param_is_supported = gboolean function(PurpleMedia* media, const(gchar)* param);																																																						/* da_purple_media_param_is_supported purple_media_param_is_supported; */
alias da_purple_media_add_stream = gboolean function(PurpleMedia* media, const(gchar)* sess_id, const(gchar)* who, PurpleMediaSessionType type, gboolean initiator, const(gchar)* transmitter, guint num_params, GParameter* params);																																																						/* da_purple_media_add_stream purple_media_add_stream; */
alias da_purple_media_get_session_type = PurpleMediaSessionType function(PurpleMedia* media, const(gchar)* sess_id);																																																						/* da_purple_media_get_session_type purple_media_get_session_type; */
alias da_purple_media_get_manager = _PurpleMediaManager* function(PurpleMedia* media);																																																						/* da_purple_media_get_manager purple_media_get_manager; */
alias da_purple_media_get_codecs = GList* function(PurpleMedia* media, const(gchar)* sess_id);																																																						/* da_purple_media_get_codecs purple_media_get_codecs; */
alias da_purple_media_add_remote_candidates = void function(PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant, GList* remote_candidates);																																																						/* da_purple_media_add_remote_candidates purple_media_add_remote_candidates; */
alias da_purple_media_get_local_candidates = GList* function(PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant);																																																						/* da_purple_media_get_local_candidates purple_media_get_local_candidates; */
alias da_purple_media_get_active_local_candidates = GList* function(PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant);																																																						/* da_purple_media_get_active_local_candidates purple_media_get_active_local_candidates; */
alias da_purple_media_get_active_remote_candidates = GList* function(PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant);																																																						/* da_purple_media_get_active_remote_candidates purple_media_get_active_remote_candidates; */
alias da_purple_media_set_remote_codecs = gboolean function(PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant, GList* codecs);																																																						/* da_purple_media_set_remote_codecs purple_media_set_remote_codecs; */
alias da_purple_media_candidates_prepared = gboolean function(PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant);																																																						/* da_purple_media_candidates_prepared purple_media_candidates_prepared; */
alias da_purple_media_set_send_codec = gboolean function(PurpleMedia* media, const(gchar)* sess_id, PurpleMediaCodec* codec);																																																						/* da_purple_media_set_send_codec purple_media_set_send_codec; */
alias da_purple_media_codecs_ready = gboolean function(PurpleMedia* media, const(gchar)* sess_id);																																																						/* da_purple_media_codecs_ready purple_media_codecs_ready; */
alias da_purple_media_is_initiator = gboolean function(PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant);																																																						/* da_purple_media_is_initiator purple_media_is_initiator; */
alias da_purple_media_accepted = gboolean function(PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant);																																																						/* da_purple_media_accepted purple_media_accepted; */
alias da_purple_media_set_input_volume = void function(PurpleMedia* media, const(gchar)* session_id, double level);																																																						/* da_purple_media_set_input_volume purple_media_set_input_volume; */
alias da_purple_media_set_output_volume = void function(PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant, double level);																																																						/* da_purple_media_set_output_volume purple_media_set_output_volume; */
alias da_purple_media_set_output_window = gulong function(PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant, gulong window_id);																																																						/* da_purple_media_set_output_window purple_media_set_output_window; */
alias da_purple_media_remove_output_windows = void function(PurpleMedia* media);																																																						/* da_purple_media_remove_output_windows purple_media_remove_output_windows; */
