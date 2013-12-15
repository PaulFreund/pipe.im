module derelict.purple.nat_pmp;

extern (C):

alias _Anonymous_0 PurplePmpType;

enum _Anonymous_0
{
	PURPLE_PMP_TYPE_UDP = 0,
	PURPLE_PMP_TYPE_TCP = 1
}

void purple_pmp_init ();
char* purple_pmp_get_public_ip ();
gboolean purple_pmp_create_map (PurplePmpType type, ushort privateport, ushort publicport, int lifetime);
gboolean purple_pmp_destroy_map (PurplePmpType type, ushort privateport);