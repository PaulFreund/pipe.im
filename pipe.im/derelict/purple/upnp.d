module derelict.purple.upnp;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;

extern (C):

alias _UPnPMappingAddRemove UPnPMappingAddRemove;
alias void function (int, void*) PurpleUPnPCallback;

struct _UPnPMappingAddRemove;


void purple_upnp_init ();
void purple_upnp_discover (PurpleUPnPCallback cb, gpointer cb_data);
const(gchar)* purple_upnp_get_public_ip ();
void purple_upnp_cancel_port_mapping (UPnPMappingAddRemove* mapping_data);
UPnPMappingAddRemove* purple_upnp_set_port_mapping (ushort portmap, const(gchar)* protocol, PurpleUPnPCallback cb, gpointer cb_data);
UPnPMappingAddRemove* purple_upnp_remove_port_mapping (ushort portmap, const(gchar)* protocol, PurpleUPnPCallback cb, gpointer cb_data);