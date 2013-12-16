module derelict.purple.stun;

import core.stdc.time;

extern (C):

alias _PurpleStunNatDiscovery PurpleStunNatDiscovery;
alias _Anonymous_0 PurpleStunStatus;
alias _Anonymous_1 PurpleStunNatType;
alias void function (_PurpleStunNatDiscovery*) StunCallback;

enum _Anonymous_0
{
	PURPLE_STUN_STATUS_UNDISCOVERED = -1,
	PURPLE_STUN_STATUS_UNKNOWN = 0,
	PURPLE_STUN_STATUS_DISCOVERING = 1,
	PURPLE_STUN_STATUS_DISCOVERED = 2
}

enum _Anonymous_1
{
	PURPLE_STUN_NAT_TYPE_PUBLIC_IP = 0,
	PURPLE_STUN_NAT_TYPE_UNKNOWN_NAT = 1,
	PURPLE_STUN_NAT_TYPE_FULL_CONE = 2,
	PURPLE_STUN_NAT_TYPE_RESTRICTED_CONE = 3,
	PURPLE_STUN_NAT_TYPE_PORT_RESTRICTED_CONE = 4,
	PURPLE_STUN_NAT_TYPE_SYMMETRIC = 5
}

struct _PurpleStunNatDiscovery
{
	PurpleStunStatus status;
	PurpleStunNatType type;
	char[16] publicip;
	char* servername;
	time_t lookup_time;
}

alias da_purple_stun_discover = PurpleStunNatDiscovery* function(StunCallback cb);																																																						/* da_purple_stun_discover purple_stun_discover; */
alias da_purple_stun_init = void function();																																																						/* da_purple_stun_init purple_stun_init; */
