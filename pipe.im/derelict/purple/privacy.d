module derelict.purple.privacy;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.purple.account;
extern (C):

alias _PurplePrivacyType PurplePrivacyType;
alias _Anonymous_0 PurplePrivacyUiOps;

enum _PurplePrivacyType
{
	PURPLE_PRIVACY_ALLOW_ALL = 1,
	PURPLE_PRIVACY_DENY_ALL = 2,
	PURPLE_PRIVACY_ALLOW_USERS = 3,
	PURPLE_PRIVACY_DENY_USERS = 4,
	PURPLE_PRIVACY_ALLOW_BUDDYLIST = 5
}

struct _Anonymous_0
{
	void function (PurpleAccount*, const(char)*) permit_added;
	void function (PurpleAccount*, const(char)*) permit_removed;
	void function (PurpleAccount*, const(char)*) deny_added;
	void function (PurpleAccount*, const(char)*) deny_removed;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

alias da_purple_privacy_permit_add = gboolean function(PurpleAccount* account, const(char)* name, gboolean local_only);																																																						/* da_purple_privacy_permit_add purple_privacy_permit_add; */
alias da_purple_privacy_permit_remove = gboolean function(PurpleAccount* account, const(char)* name, gboolean local_only);																																																						/* da_purple_privacy_permit_remove purple_privacy_permit_remove; */
alias da_purple_privacy_deny_add = gboolean function(PurpleAccount* account, const(char)* name, gboolean local_only);																																																						/* da_purple_privacy_deny_add purple_privacy_deny_add; */
alias da_purple_privacy_deny_remove = gboolean function(PurpleAccount* account, const(char)* name, gboolean local_only);																																																						/* da_purple_privacy_deny_remove purple_privacy_deny_remove; */
alias da_purple_privacy_allow = void function(PurpleAccount* account, const(char)* who, gboolean local, gboolean restore);																																																						/* da_purple_privacy_allow purple_privacy_allow; */
alias da_purple_privacy_deny = void function(PurpleAccount* account, const(char)* who, gboolean local, gboolean restore);																																																						/* da_purple_privacy_deny purple_privacy_deny; */
alias da_purple_privacy_check = gboolean function(PurpleAccount* account, const(char)* who);																																																						/* da_purple_privacy_check purple_privacy_check; */
alias da_purple_privacy_set_ui_ops = void function(PurplePrivacyUiOps* ops);																																																						/* da_purple_privacy_set_ui_ops purple_privacy_set_ui_ops; */
alias da_purple_privacy_get_ui_ops = PurplePrivacyUiOps* function();																																																						/* da_purple_privacy_get_ui_ops purple_privacy_get_ui_ops; */
alias da_purple_privacy_init = void function();																																																						/* da_purple_privacy_init purple_privacy_init; */
