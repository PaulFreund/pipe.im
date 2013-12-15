extern (C):

alias _PurpleMediaCodec PurpleMediaCodec;

struct _PurpleMediaCodec;


GType purple_media_codec_get_type ();
PurpleMediaCodec* purple_media_codec_new (int id, const(char)* encoding_name, PurpleMediaSessionType media_type, guint clock_rate);
guint purple_media_codec_get_id (PurpleMediaCodec* codec);
gchar* purple_media_codec_get_encoding_name (PurpleMediaCodec* codec);
guint purple_media_codec_get_clock_rate (PurpleMediaCodec* codec);
guint purple_media_codec_get_channels (PurpleMediaCodec* codec);
GList* purple_media_codec_get_optional_parameters (PurpleMediaCodec* codec);
void purple_media_codec_add_optional_parameter (PurpleMediaCodec* codec, const(gchar)* name, const(gchar)* value);
void purple_media_codec_remove_optional_parameter (PurpleMediaCodec* codec, PurpleKeyValuePair* param);
PurpleKeyValuePair* purple_media_codec_get_optional_parameter (PurpleMediaCodec* codec, const(gchar)* name, const(gchar)* value);
PurpleMediaCodec* purple_media_codec_copy (PurpleMediaCodec* codec);
GList* purple_media_codec_list_copy (GList* codecs);
void purple_media_codec_list_free (GList* codecs);
gchar* purple_media_codec_to_string (const(PurpleMediaCodec)* codec);