module derelict.purple.xmlnode;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.ghash;
import core.stdc.config;

extern (C):

alias _XMLNodeType XMLNodeType;
alias _xmlnode xmlnode;

enum _XMLNodeType
{
	XMLNODE_TYPE_TAG = 0,
	XMLNODE_TYPE_ATTRIB = 1,
	XMLNODE_TYPE_DATA = 2
}

struct _xmlnode
{
	char* name;
	char* xmlns;
	XMLNodeType type;
	char* data;
	size_t data_sz;
	xmlnode* parent;
	xmlnode* child;
	xmlnode* lastchild;
	xmlnode* next;
	char* prefix;
	GHashTable* namespace_map;
}

alias da_xmlnode_new = xmlnode* function(const(char)* name);																																																						/* da_xmlnode_new xmlnode_new; */
alias da_xmlnode_new_child = xmlnode* function(xmlnode* parent, const(char)* name);																																																						/* da_xmlnode_new_child xmlnode_new_child; */
alias da_xmlnode_insert_child = void function(xmlnode* parent, xmlnode* child);																																																						/* da_xmlnode_insert_child xmlnode_insert_child; */
alias da_xmlnode_get_child = xmlnode* function(const(xmlnode)* parent, const(char)* name);																																																						/* da_xmlnode_get_child xmlnode_get_child; */
alias da_xmlnode_get_child_with_namespace = xmlnode* function(const(xmlnode)* parent, const(char)* name, const(char)* xmlns);																																																						/* da_xmlnode_get_child_with_namespace xmlnode_get_child_with_namespace; */
alias da_xmlnode_get_next_twin = xmlnode* function(xmlnode* node);																																																						/* da_xmlnode_get_next_twin xmlnode_get_next_twin; */
alias da_xmlnode_insert_data = void function(xmlnode* node, const(char)* data, gssize size);																																																						/* da_xmlnode_insert_data xmlnode_insert_data; */
alias da_xmlnode_get_data = char* function(const(xmlnode)* node);																																																						/* da_xmlnode_get_data xmlnode_get_data; */
alias da_xmlnode_get_data_unescaped = char* function(const(xmlnode)* node);																																																						/* da_xmlnode_get_data_unescaped xmlnode_get_data_unescaped; */
alias da_xmlnode_set_attrib = void function(xmlnode* node, const(char)* attr, const(char)* value);																																																						/* da_xmlnode_set_attrib xmlnode_set_attrib; */
alias da_xmlnode_set_attrib_with_prefix = void function(xmlnode* node, const(char)* attr, const(char)* prefix, const(char)* value);																																																						/* da_xmlnode_set_attrib_with_prefix xmlnode_set_attrib_with_prefix; */
alias da_xmlnode_set_attrib_with_namespace = void function(xmlnode* node, const(char)* attr, const(char)* xmlns, const(char)* value);																																																						/* da_xmlnode_set_attrib_with_namespace xmlnode_set_attrib_with_namespace; */
alias da_xmlnode_set_attrib_full = void function(xmlnode* node, const(char)* attr, const(char)* xmlns, const(char)* prefix, const(char)* value);																																																						/* da_xmlnode_set_attrib_full xmlnode_set_attrib_full; */
alias da_xmlnode_get_attrib = const(char)* function(const(xmlnode)* node, const(char)* attr);																																																						/* da_xmlnode_get_attrib xmlnode_get_attrib; */
alias da_xmlnode_get_attrib_with_namespace = const(char)* function(const(xmlnode)* node, const(char)* attr, const(char)* xmlns);																																																						/* da_xmlnode_get_attrib_with_namespace xmlnode_get_attrib_with_namespace; */
alias da_xmlnode_remove_attrib = void function(xmlnode* node, const(char)* attr);																																																						/* da_xmlnode_remove_attrib xmlnode_remove_attrib; */
alias da_xmlnode_remove_attrib_with_namespace = void function(xmlnode* node, const(char)* attr, const(char)* xmlns);																																																						/* da_xmlnode_remove_attrib_with_namespace xmlnode_remove_attrib_with_namespace; */
alias da_xmlnode_set_namespace = void function(xmlnode* node, const(char)* xmlns);																																																						/* da_xmlnode_set_namespace xmlnode_set_namespace; */
alias da_xmlnode_get_namespace = const(char)* function(xmlnode* node);																																																						/* da_xmlnode_get_namespace xmlnode_get_namespace; */
alias da_xmlnode_set_prefix = void function(xmlnode* node, const(char)* prefix);																																																						/* da_xmlnode_set_prefix xmlnode_set_prefix; */
alias da_xmlnode_get_prefix = const(char)* function(const(xmlnode)* node);																																																						/* da_xmlnode_get_prefix xmlnode_get_prefix; */
alias da_xmlnode_get_parent = xmlnode* function(const(xmlnode)* child);																																																						/* da_xmlnode_get_parent xmlnode_get_parent; */
alias da_xmlnode_to_str = char* function(const(xmlnode)* node, int* len);																																																						/* da_xmlnode_to_str xmlnode_to_str; */
alias da_xmlnode_to_formatted_str = char* function(const(xmlnode)* node, int* len);																																																						/* da_xmlnode_to_formatted_str xmlnode_to_formatted_str; */
alias da_xmlnode_from_str = xmlnode* function(const(char)* str, gssize size);																																																						/* da_xmlnode_from_str xmlnode_from_str; */
alias da_xmlnode_copy = xmlnode* function(const(xmlnode)* src);																																																						/* da_xmlnode_copy xmlnode_copy; */
alias da_xmlnode_free = void function(xmlnode* node);																																																						/* da_xmlnode_free xmlnode_free; */
alias da_xmlnode_from_file = xmlnode* function(const(char)* dir, const(char)* filename, const(char)* description, const(char)* process);																																																						/* da_xmlnode_from_file xmlnode_from_file; */
