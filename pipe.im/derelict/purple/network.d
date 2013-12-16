module derelict.purple.network;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;

extern (C):

alias _PurpleNetworkListenData PurpleNetworkListenData;
alias void function (int, void*) PurpleNetworkListenCallback;

struct _PurpleNetworkListenData;


alias da_purple_network_ip_atoi = const(ubyte)* function(const(char)* ip);																																																						/* da_purple_network_ip_atoi purple_network_ip_atoi; */
alias da_purple_network_set_public_ip = void function(const(char)* ip);																																																						/* da_purple_network_set_public_ip purple_network_set_public_ip; */
alias da_purple_network_get_public_ip = const(char)* function();																																																						/* da_purple_network_get_public_ip purple_network_get_public_ip; */
alias da_purple_network_get_local_system_ip = const(char)* function(int fd);																																																						/* da_purple_network_get_local_system_ip purple_network_get_local_system_ip; */
alias da_purple_network_get_all_local_system_ips = GList* function();																																																						/* da_purple_network_get_all_local_system_ips purple_network_get_all_local_system_ips; */
alias da_purple_network_get_my_ip = const(char)* function(int fd);																																																						/* da_purple_network_get_my_ip purple_network_get_my_ip; */
alias da_purple_network_listen_map_external = void function(gboolean map_external);																																																						/* da_purple_network_listen_map_external purple_network_listen_map_external; */
alias da_purple_network_listen = PurpleNetworkListenData* function(ushort port, int socket_type, PurpleNetworkListenCallback cb, gpointer cb_data);																																																						/* da_purple_network_listen purple_network_listen; */
alias da_purple_network_listen_family = PurpleNetworkListenData* function(ushort port, int socket_family, int socket_type, PurpleNetworkListenCallback cb, gpointer cb_data);																																																						/* da_purple_network_listen_family purple_network_listen_family; */
alias da_purple_network_listen_range = PurpleNetworkListenData* function(ushort start, ushort end, int socket_type, PurpleNetworkListenCallback cb, gpointer cb_data);																																																						/* da_purple_network_listen_range purple_network_listen_range; */
alias da_purple_network_listen_range_family = PurpleNetworkListenData* function(ushort start, ushort end, int socket_family, int socket_type, PurpleNetworkListenCallback cb, gpointer cb_data);																																																						/* da_purple_network_listen_range_family purple_network_listen_range_family; */
alias da_purple_network_listen_cancel = void function(PurpleNetworkListenData* listen_data);																																																						/* da_purple_network_listen_cancel purple_network_listen_cancel; */
alias da_purple_network_get_port_from_fd = ushort function(int fd);																																																						/* da_purple_network_get_port_from_fd purple_network_get_port_from_fd; */
alias da_purple_network_is_available = gboolean function();																																																						/* da_purple_network_is_available purple_network_is_available; */
alias da_purple_network_force_online = void function();																																																						/* da_purple_network_force_online purple_network_force_online; */
alias da_purple_network_get_handle = void* function();																																																						/* da_purple_network_get_handle purple_network_get_handle; */
alias da_purple_network_set_stun_server = void function(const(gchar)* stun_server);																																																						/* da_purple_network_set_stun_server purple_network_set_stun_server; */
alias da_purple_network_get_stun_ip = const(gchar)* function();																																																						/* da_purple_network_get_stun_ip purple_network_get_stun_ip; */
alias da_purple_network_set_turn_server = void function(const(gchar)* turn_server);																																																						/* da_purple_network_set_turn_server purple_network_set_turn_server; */
alias da_purple_network_get_turn_ip = const(gchar)* function();																																																						/* da_purple_network_get_turn_ip purple_network_get_turn_ip; */
alias da_purple_network_remove_port_mapping = void function(gint fd);																																																						/* da_purple_network_remove_port_mapping purple_network_remove_port_mapping; */
alias da_purple_network_convert_idn_to_ascii = int function(const(gchar)* in_, gchar** out_);																																																						/* da_purple_network_convert_idn_to_ascii purple_network_convert_idn_to_ascii; */
alias da_purple_network_init = void function();																																																						/* da_purple_network_init purple_network_init; */
alias da_purple_network_uninit = void function();																																																						/* da_purple_network_uninit purple_network_uninit; */
