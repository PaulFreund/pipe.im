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

gboolean purple_privacy_permit_add (PurpleAccount* account, const(char)* name, gboolean local_only);
gboolean purple_privacy_permit_remove (PurpleAccount* account, const(char)* name, gboolean local_only);
gboolean purple_privacy_deny_add (PurpleAccount* account, const(char)* name, gboolean local_only);
gboolean purple_privacy_deny_remove (PurpleAccount* account, const(char)* name, gboolean local_only);
void purple_privacy_allow (PurpleAccount* account, const(char)* who, gboolean local, gboolean restore);
void purple_privacy_deny (PurpleAccount* account, const(char)* who, gboolean local, gboolean restore);
gboolean purple_privacy_check (PurpleAccount* account, const(char)* who);
void purple_privacy_set_ui_ops (PurplePrivacyUiOps* ops);
PurplePrivacyUiOps* purple_privacy_get_ui_ops ();
void purple_privacy_init ();