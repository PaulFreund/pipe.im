module derelict.purple.sound;

import derelict.glib.gtypes;
import derelict.glib.glibconfig;
import derelict.purple.account;

extern (C):

alias _PurpleSoundEventID PurpleSoundEventID;
alias _PurpleSoundUiOps PurpleSoundUiOps;

enum _PurpleSoundEventID
{
	PURPLE_SOUND_BUDDY_ARRIVE = 0,
	PURPLE_SOUND_BUDDY_LEAVE = 1,
	PURPLE_SOUND_RECEIVE = 2,
	PURPLE_SOUND_FIRST_RECEIVE = 3,
	PURPLE_SOUND_SEND = 4,
	PURPLE_SOUND_CHAT_JOIN = 5,
	PURPLE_SOUND_CHAT_LEAVE = 6,
	PURPLE_SOUND_CHAT_YOU_SAY = 7,
	PURPLE_SOUND_CHAT_SAY = 8,
	PURPLE_SOUND_POUNCE_DEFAULT = 9,
	PURPLE_SOUND_CHAT_NICK = 10,
	PURPLE_SOUND_GOT_ATTENTION = 11,
	PURPLE_NUM_SOUNDS = 12
}

struct _PurpleSoundUiOps
{
	void function () init;
	void function () uninit;
	void function (const(char)*) play_file;
	void function (PurpleSoundEventID) play_event;
	void function () _purple_reserved1;
	void function () _purple_reserved2;
	void function () _purple_reserved3;
	void function () _purple_reserved4;
}

void purple_sound_play_file (const(char)* filename, const(PurpleAccount)* account);
void purple_sound_play_event (PurpleSoundEventID event, const(PurpleAccount)* account);
void purple_sound_set_ui_ops (PurpleSoundUiOps* ops);
PurpleSoundUiOps* purple_sound_get_ui_ops ();
void purple_sound_init ();
void purple_sound_uninit ();
void* purple_sounds_get_handle ();