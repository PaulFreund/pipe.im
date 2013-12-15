extern (C):

alias _PurpleMediaBackend PurpleMediaBackend;
alias _PurpleMediaBackendIface PurpleMediaBackendIface;

struct _PurpleMediaBackendIface
{
	GTypeInterface parent_iface;
	gboolean function (PurpleMediaBackend*, const(gchar)*, const(gchar)*, PurpleMediaSessionType, gboolean, const(gchar)*, guint, GParameter*) add_stream;
	void function (PurpleMediaBackend*, const(gchar)*, const(gchar)*, GList*) add_remote_candidates;
	gboolean function (PurpleMediaBackend*, const(gchar)*) codecs_ready;
	GList* function (PurpleMediaBackend*, const(gchar)*) get_codecs;
	GList* function (PurpleMediaBackend*, const(gchar)*, const(gchar)*) get_local_candidates;
	gboolean function (PurpleMediaBackend*, const(gchar)*, const(gchar)*, GList*) set_remote_codecs;
	gboolean function (PurpleMediaBackend*, const(gchar)*, PurpleMediaCodec*) set_send_codec;
	void function (PurpleMediaBackend*, guint, GParameter*) set_params;
	const(gchar*)* function () get_available_params;
}

struct _PurpleMediaBackend;


GType purple_media_backend_get_type ();
gboolean purple_media_backend_add_stream (PurpleMediaBackend* self, const(gchar)* sess_id, const(gchar)* who, PurpleMediaSessionType type, gboolean initiator, const(gchar)* transmitter, guint num_params, GParameter* params);
void purple_media_backend_add_remote_candidates (PurpleMediaBackend* self, const(gchar)* sess_id, const(gchar)* participant, GList* remote_candidates);
gboolean purple_media_backend_codecs_ready (PurpleMediaBackend* self, const(gchar)* sess_id);
GList* purple_media_backend_get_codecs (PurpleMediaBackend* self, const(gchar)* sess_id);
GList* purple_media_backend_get_local_candidates (PurpleMediaBackend* self, const(gchar)* sess_id, const(gchar)* participant);
gboolean purple_media_backend_set_remote_codecs (PurpleMediaBackend* self, const(gchar)* sess_id, const(gchar)* participant, GList* codecs);
gboolean purple_media_backend_set_send_codec (PurpleMediaBackend* self, const(gchar)* sess_id, PurpleMediaCodec* codec);
void purple_media_backend_set_params (PurpleMediaBackend* self, guint num_params, GParameter* params);
const(gchar*)* purple_media_backend_get_available_params (PurpleMediaBackend* self);