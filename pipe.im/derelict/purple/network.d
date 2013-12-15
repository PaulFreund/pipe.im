module derelict.purple.network;

extern (C):

alias _PurpleNetworkListenData PurpleNetworkListenData;
alias void function (int, void*) PurpleNetworkListenCallback;

struct _PurpleNetworkListenData;


const(ubyte)* purple_network_ip_atoi (const(char)* ip);
void purple_network_set_public_ip (const(char)* ip);
const(char)* purple_network_get_public_ip ();
const(char)* purple_network_get_local_system_ip (int fd);
GList* purple_network_get_all_local_system_ips ();
const(char)* purple_network_get_my_ip (int fd);
void purple_network_listen_map_external (gboolean map_external);
PurpleNetworkListenData* purple_network_listen (ushort port, int socket_type, PurpleNetworkListenCallback cb, gpointer cb_data);
PurpleNetworkListenData* purple_network_listen_family (ushort port, int socket_family, int socket_type, PurpleNetworkListenCallback cb, gpointer cb_data);
PurpleNetworkListenData* purple_network_listen_range (ushort start, ushort end, int socket_type, PurpleNetworkListenCallback cb, gpointer cb_data);
PurpleNetworkListenData* purple_network_listen_range_family (ushort start, ushort end, int socket_family, int socket_type, PurpleNetworkListenCallback cb, gpointer cb_data);
void purple_network_listen_cancel (PurpleNetworkListenData* listen_data);
ushort purple_network_get_port_from_fd (int fd);
gboolean purple_network_is_available ();
void purple_network_force_online ();
void* purple_network_get_handle ();
void purple_network_set_stun_server (const(gchar)* stun_server);
const(gchar)* purple_network_get_stun_ip ();
void purple_network_set_turn_server (const(gchar)* turn_server);
const(gchar)* purple_network_get_turn_ip ();
void purple_network_remove_port_mapping (gint fd);
int purple_network_convert_idn_to_ascii (const(gchar)* in_, gchar** out_);
void purple_network_init ();
void purple_network_uninit ();