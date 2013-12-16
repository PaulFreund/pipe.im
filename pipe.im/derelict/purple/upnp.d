module derelict.purple.upnp;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _UPnPMappingAddRemove UPnPMappingAddRemove;
alias void function (int, void*) PurpleUPnPCallback;

struct _UPnPMappingAddRemove;


alias da_purple_upnp_init = void function();																																																						/* da_purple_upnp_init purple_upnp_init; */
alias da_purple_upnp_discover = void function(PurpleUPnPCallback cb, gpointer cb_data);																																																						/* da_purple_upnp_discover purple_upnp_discover; */
alias da_purple_upnp_get_public_ip = const(gchar)* function();																																																						/* da_purple_upnp_get_public_ip purple_upnp_get_public_ip; */
alias da_purple_upnp_cancel_port_mapping = void function(UPnPMappingAddRemove* mapping_data);																																																						/* da_purple_upnp_cancel_port_mapping purple_upnp_cancel_port_mapping; */
alias da_purple_upnp_set_port_mapping = UPnPMappingAddRemove* function(ushort portmap, const(gchar)* protocol, PurpleUPnPCallback cb, gpointer cb_data);																																																						/* da_purple_upnp_set_port_mapping purple_upnp_set_port_mapping; */
alias da_purple_upnp_remove_port_mapping = UPnPMappingAddRemove* function(ushort portmap, const(gchar)* protocol, PurpleUPnPCallback cb, gpointer cb_data);																																																						/* da_purple_upnp_remove_port_mapping purple_upnp_remove_port_mapping; */
