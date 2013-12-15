module derelict.purple.media;

extern (C):

alias _PurpleMedia PurpleMedia;

struct _PurpleMediaManager;


struct _PurpleMedia;


GType purple_media_get_type ();
GList* purple_media_get_session_ids (PurpleMedia* media);
PurpleAccount* purple_media_get_account (PurpleMedia* media);
gpointer purple_media_get_prpl_data (PurpleMedia* media);
void purple_media_set_prpl_data (PurpleMedia* media, gpointer prpl_data);
void purple_media_error (PurpleMedia* media, const(gchar)* error, ...);
void purple_media_end (PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant);
void purple_media_stream_info (PurpleMedia* media, PurpleMediaInfoType type, const(gchar)* session_id, const(gchar)* participant, gboolean local);
void purple_media_set_params (PurpleMedia* media, guint num_params, GParameter* params);
const(gchar*)* purple_media_get_available_params (PurpleMedia* media);
gboolean purple_media_param_is_supported (PurpleMedia* media, const(gchar)* param);
gboolean purple_media_add_stream (PurpleMedia* media, const(gchar)* sess_id, const(gchar)* who, PurpleMediaSessionType type, gboolean initiator, const(gchar)* transmitter, guint num_params, GParameter* params);
PurpleMediaSessionType purple_media_get_session_type (PurpleMedia* media, const(gchar)* sess_id);
_PurpleMediaManager* purple_media_get_manager (PurpleMedia* media);
GList* purple_media_get_codecs (PurpleMedia* media, const(gchar)* sess_id);
void purple_media_add_remote_candidates (PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant, GList* remote_candidates);
GList* purple_media_get_local_candidates (PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant);
GList* purple_media_get_active_local_candidates (PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant);
GList* purple_media_get_active_remote_candidates (PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant);
gboolean purple_media_set_remote_codecs (PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant, GList* codecs);
gboolean purple_media_candidates_prepared (PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant);
gboolean purple_media_set_send_codec (PurpleMedia* media, const(gchar)* sess_id, PurpleMediaCodec* codec);
gboolean purple_media_codecs_ready (PurpleMedia* media, const(gchar)* sess_id);
gboolean purple_media_is_initiator (PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant);
gboolean purple_media_accepted (PurpleMedia* media, const(gchar)* sess_id, const(gchar)* participant);
void purple_media_set_input_volume (PurpleMedia* media, const(gchar)* session_id, double level);
void purple_media_set_output_volume (PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant, double level);
gulong purple_media_set_output_window (PurpleMedia* media, const(gchar)* session_id, const(gchar)* participant, gulong window_id);
void purple_media_remove_output_windows (PurpleMedia* media);