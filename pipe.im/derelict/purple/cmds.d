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

alias da_purple_cmd_register = PurpleCmdId function(const(gchar)* cmd, const(gchar)* args, PurpleCmdPriority p, PurpleCmdFlag f, const(gchar)* prpl_id, PurpleCmdFunc func, const(gchar)* helpstr, void* data);																																																						/* da_purple_cmd_register purple_cmd_register; */
alias da_purple_cmd_unregister = void function(PurpleCmdId id);																																																						/* da_purple_cmd_unregister purple_cmd_unregister; */
alias da_purple_cmd_do_command = PurpleCmdStatus function(PurpleConversation* conv, const(gchar)* cmdline, const(gchar)* markup, gchar** errormsg);																																																						/* da_purple_cmd_do_command purple_cmd_do_command; */
alias da_purple_cmd_list = GList* function(PurpleConversation* conv);																																																						/* da_purple_cmd_list purple_cmd_list; */
alias da_purple_cmd_help = GList* function(PurpleConversation* conv, const(gchar)* cmd);																																																						/* da_purple_cmd_help purple_cmd_help; */
alias da_purple_cmds_get_handle = gpointer function();																																																						/* da_purple_cmds_get_handle purple_cmds_get_handle; */
alias da_purple_cmds_init = void function();																																																						/* da_purple_cmds_init purple_cmds_init; */
alias da_purple_cmds_uninit = void function();																																																						/* da_purple_cmds_uninit purple_cmds_uninit; */
