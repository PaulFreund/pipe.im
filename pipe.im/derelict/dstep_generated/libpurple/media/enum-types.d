extern (C):

alias _Anonymous_0 PurpleMediaCandidateType;
alias _Anonymous_1 PurpleMediaCaps;
alias _Anonymous_2 PurpleMediaComponentType;
alias _Anonymous_3 PurpleMediaInfoType;
alias _Anonymous_4 PurpleMediaNetworkProtocol;
alias _Anonymous_5 PurpleMediaSessionType;
alias _Anonymous_6 PurpleMediaState;

enum _Anonymous_0
{
	PURPLE_MEDIA_CANDIDATE_TYPE_HOST = 0,
	PURPLE_MEDIA_CANDIDATE_TYPE_SRFLX = 1,
	PURPLE_MEDIA_CANDIDATE_TYPE_PRFLX = 2,
	PURPLE_MEDIA_CANDIDATE_TYPE_RELAY = 3,
	PURPLE_MEDIA_CANDIDATE_TYPE_MULTICAST = 4
}

enum _Anonymous_1
{
	PURPLE_MEDIA_CAPS_NONE = 0,
	PURPLE_MEDIA_CAPS_AUDIO = 1,
	PURPLE_MEDIA_CAPS_AUDIO_SINGLE_DIRECTION = 2,
	PURPLE_MEDIA_CAPS_VIDEO = 4,
	PURPLE_MEDIA_CAPS_VIDEO_SINGLE_DIRECTION = 8,
	PURPLE_MEDIA_CAPS_AUDIO_VIDEO = 16,
	PURPLE_MEDIA_CAPS_MODIFY_SESSION = 32,
	PURPLE_MEDIA_CAPS_CHANGE_DIRECTION = 64
}

enum _Anonymous_2
{
	PURPLE_MEDIA_COMPONENT_NONE = 0,
	PURPLE_MEDIA_COMPONENT_RTP = 1,
	PURPLE_MEDIA_COMPONENT_RTCP = 2
}

enum _Anonymous_3
{
	PURPLE_MEDIA_INFO_HANGUP = 0,
	PURPLE_MEDIA_INFO_ACCEPT = 1,
	PURPLE_MEDIA_INFO_REJECT = 2,
	PURPLE_MEDIA_INFO_MUTE = 3,
	PURPLE_MEDIA_INFO_UNMUTE = 4,
	PURPLE_MEDIA_INFO_PAUSE = 5,
	PURPLE_MEDIA_INFO_UNPAUSE = 6,
	PURPLE_MEDIA_INFO_HOLD = 7,
	PURPLE_MEDIA_INFO_UNHOLD = 8
}

enum _Anonymous_4
{
	PURPLE_MEDIA_NETWORK_PROTOCOL_UDP = 0,
	PURPLE_MEDIA_NETWORK_PROTOCOL_TCP = 1
}

enum _Anonymous_5
{
	PURPLE_MEDIA_NONE = 0,
	PURPLE_MEDIA_RECV_AUDIO = 1,
	PURPLE_MEDIA_SEND_AUDIO = 2,
	PURPLE_MEDIA_RECV_VIDEO = 4,
	PURPLE_MEDIA_SEND_VIDEO = 8,
	PURPLE_MEDIA_AUDIO = 3,
	PURPLE_MEDIA_VIDEO = 12
}

enum _Anonymous_6
{
	PURPLE_MEDIA_STATE_NEW = 0,
	PURPLE_MEDIA_STATE_CONNECTED = 1,
	PURPLE_MEDIA_STATE_END = 2
}

GType purple_media_candidate_type_get_type ();
GType purple_media_caps_get_type ();
GType purple_media_info_type_get_type ();
GType purple_media_network_protocol_get_type ();
GType purple_media_session_type_get_type ();
GType purple_media_state_changed_get_type ();