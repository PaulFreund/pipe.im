import core.stdc.config;

extern (C):

alias _PurpleMediaCandidate PurpleMediaCandidate;

struct _PurpleMediaCandidate;


GType purple_media_candidate_get_type ();
PurpleMediaCandidate* purple_media_candidate_new (const(gchar)* foundation, guint component_id, PurpleMediaCandidateType type, PurpleMediaNetworkProtocol proto, const(gchar)* ip, guint port);
PurpleMediaCandidate* purple_media_candidate_copy (PurpleMediaCandidate* candidate);
GList* purple_media_candidate_list_copy (GList* candidates);
void purple_media_candidate_list_free (GList* candidates);
gchar* purple_media_candidate_get_foundation (PurpleMediaCandidate* candidate);
guint purple_media_candidate_get_component_id (PurpleMediaCandidate* candidate);
gchar* purple_media_candidate_get_ip (PurpleMediaCandidate* candidate);
guint16 purple_media_candidate_get_port (PurpleMediaCandidate* candidate);
gchar* purple_media_candidate_get_base_ip (PurpleMediaCandidate* candidate);
guint16 purple_media_candidate_get_base_port (PurpleMediaCandidate* candidate);
PurpleMediaNetworkProtocol purple_media_candidate_get_protocol (PurpleMediaCandidate* candidate);
guint32 purple_media_candidate_get_priority (PurpleMediaCandidate* candidate);
PurpleMediaCandidateType purple_media_candidate_get_candidate_type (PurpleMediaCandidate* candidate);
gchar* purple_media_candidate_get_username (PurpleMediaCandidate* candidate);
gchar* purple_media_candidate_get_password (PurpleMediaCandidate* candidate);
guint purple_media_candidate_get_ttl (PurpleMediaCandidate* candidate);