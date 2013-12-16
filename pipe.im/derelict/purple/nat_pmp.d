module derelict.purple.nat_pmp;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _Anonymous_0 PurplePmpType;

enum _Anonymous_0
{
	PURPLE_PMP_TYPE_UDP = 0,
	PURPLE_PMP_TYPE_TCP = 1
}

alias da_purple_pmp_init = void function();																																																						/* da_purple_pmp_init purple_pmp_init; */
alias da_purple_pmp_get_public_ip = char* function();																																																						/* da_purple_pmp_get_public_ip purple_pmp_get_public_ip; */
alias da_purple_pmp_create_map = gboolean function(PurplePmpType type, ushort privateport, ushort publicport, int lifetime);																																																						/* da_purple_pmp_create_map purple_pmp_create_map; */
alias da_purple_pmp_destroy_map = gboolean function(PurplePmpType type, ushort privateport);																																																						/* da_purple_pmp_destroy_map purple_pmp_destroy_map; */
