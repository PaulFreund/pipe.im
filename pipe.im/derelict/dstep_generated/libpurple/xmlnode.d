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

xmlnode* xmlnode_new (const(char)* name);
xmlnode* xmlnode_new_child (xmlnode* parent, const(char)* name);
void xmlnode_insert_child (xmlnode* parent, xmlnode* child);
xmlnode* xmlnode_get_child (const(xmlnode)* parent, const(char)* name);
xmlnode* xmlnode_get_child_with_namespace (const(xmlnode)* parent, const(char)* name, const(char)* xmlns);
xmlnode* xmlnode_get_next_twin (xmlnode* node);
void xmlnode_insert_data (xmlnode* node, const(char)* data, gssize size);
char* xmlnode_get_data (const(xmlnode)* node);
char* xmlnode_get_data_unescaped (const(xmlnode)* node);
void xmlnode_set_attrib (xmlnode* node, const(char)* attr, const(char)* value);
void xmlnode_set_attrib_with_prefix (xmlnode* node, const(char)* attr, const(char)* prefix, const(char)* value);
void xmlnode_set_attrib_with_namespace (xmlnode* node, const(char)* attr, const(char)* xmlns, const(char)* value);
void xmlnode_set_attrib_full (xmlnode* node, const(char)* attr, const(char)* xmlns, const(char)* prefix, const(char)* value);
const(char)* xmlnode_get_attrib (const(xmlnode)* node, const(char)* attr);
const(char)* xmlnode_get_attrib_with_namespace (const(xmlnode)* node, const(char)* attr, const(char)* xmlns);
void xmlnode_remove_attrib (xmlnode* node, const(char)* attr);
void xmlnode_remove_attrib_with_namespace (xmlnode* node, const(char)* attr, const(char)* xmlns);
void xmlnode_set_namespace (xmlnode* node, const(char)* xmlns);
const(char)* xmlnode_get_namespace (xmlnode* node);
void xmlnode_set_prefix (xmlnode* node, const(char)* prefix);
const(char)* xmlnode_get_prefix (const(xmlnode)* node);
xmlnode* xmlnode_get_parent (const(xmlnode)* child);
char* xmlnode_to_str (const(xmlnode)* node, int* len);
char* xmlnode_to_formatted_str (const(xmlnode)* node, int* len);
xmlnode* xmlnode_from_str (const(char)* str, gssize size);
xmlnode* xmlnode_copy (const(xmlnode)* src);
void xmlnode_free (xmlnode* node);
xmlnode* xmlnode_from_file (const(char)* dir, const(char)* filename, const(char)* description, const(char)* process);