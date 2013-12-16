module derelict.purple.cmds;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.glib.glist;
import derelict.purple.conversation;
extern (C):

alias _PurpleCmdStatus PurpleCmdStatus;
alias _PurpleCmdRet PurpleCmdRet;
alias _PurpleCmdRet function (_PurpleConversation*, const(char)*, char**, char**, void*) PurpleCmdFunc;
alias uint PurpleCmdId;
alias _PurpleCmdPriority PurpleCmdPriority;
alias _PurpleCmdFlag PurpleCmdFlag;

enum _PurpleCmdStatus
{
	PURPLE_CMD_STATUS_OK = 0,
	PURPLE_CMD_STATUS_FAILED = 1,
	PURPLE_CMD_STATUS_NOT_FOUND = 2,
	PURPLE_CMD_STATUS_WRONG_ARGS = 3,
	PURPLE_CMD_STATUS_WRONG_PRPL = 4,
	PURPLE_CMD_STATUS_WRONG_TYPE = 5
}

enum _PurpleCmdRet
{
	PURPLE_CMD_RET_OK = 0,
	PURPLE_CMD_RET_FAILED = 1,
	PURPLE_CMD_RET_CONTINUE = 2
}

enum _PurpleCmdPriority
{
	PURPLE_CMD_P_VERY_LOW = -1000,
	PURPLE_CMD_P_LOW = 0,
	PURPLE_CMD_P_DEFAULT = 1000,
	PURPLE_CMD_P_PRPL = 2000,
	PURPLE_CMD_P_PLUGIN = 3000,
	PURPLE_CMD_P_ALIAS = 4000,
	PURPLE_CMD_P_HIGH = 5000,
	PURPLE_CMD_P_VERY_HIGH = 6000
}

enum _PurpleCmdFlag
{
	PURPLE_CMD_FLAG_IM = 1,
	PURPLE_CMD_FLAG_CHAT = 2,
	PURPLE_CMD_FLAG_PRPL_ONLY = 4,
	PURPLE_CMD_FLAG_ALLOW_WRONG_ARGS = 8
}

PurpleCmdId purple_cmd_register (const(gchar)* cmd, const(gchar)* args, PurpleCmdPriority p, PurpleCmdFlag f, const(gchar)* prpl_id, PurpleCmdFunc func, const(gchar)* helpstr, void* data);
void purple_cmd_unregister (PurpleCmdId id);
PurpleCmdStatus purple_cmd_do_command (PurpleConversation* conv, const(gchar)* cmdline, const(gchar)* markup, gchar** errormsg);
GList* purple_cmd_list (PurpleConversation* conv);
GList* purple_cmd_help (PurpleConversation* conv, const(gchar)* cmd);
gpointer purple_cmds_get_handle ();
void purple_cmds_init ();
void purple_cmds_uninit ();