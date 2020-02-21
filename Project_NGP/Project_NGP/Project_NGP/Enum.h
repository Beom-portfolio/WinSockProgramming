#pragma once

enum DIRECTION
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_TOP,
	DIR_BOTTOM,
	DIR_END
};

enum KEYSTATE
{
	STATE_DOWN,
	STATE_PUSH,
	STATE_UP,
	STATE_END
};

enum SCENESTATE
{
	SCENE_MENU,
	SCENE_TEST,
	SCENE_MAIN_1,
	SCENE_MAIN_2,
	SCENE_MAIN_3,
	SCENE_END
};

enum FILETYPE
{
	FILE_FILE,
	FILE_FOLDER,
	FILE_END_
};

enum SPRITEPLAY
{
	PLAY_EACH,
	PLAY_ALL,
	PLAY_END
};

enum SPRITETYPE
{
	SPRITE_ONCE,
	SPRITE_ONCE_END,
	SPRITE_REPEAT,
	SPRITE_REPEAT_END,
	SPRITE_END
};

enum OBJTYPE
{
	OBJ_BACK,
	OBJ_OTHERPLAYER,
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_EFFECT,
	OBJ_PORTAL,
	OBJ_UI,
	OBJ_END
};

enum RENDERTYPE
{
	RENDER_BACKGROUND,
	RENDER_OBJ,
	RENDER_EFFECT,
	RENDER_UI,
	RENDER_UI_1,
	RENDER_UI_2,
	RENDER_UI_3,
	RENDER_END
};

enum MonsterState
{
	Monster_Idle,
	Monster_Move,
	Monster_Att,
	Monster_Spell,
	Monster_Hit,
	Monster_Die,
	Monster_End
};

enum MONSTERTYPE
{
	MONTYPE_SNAIL,
	MONTYPE_SLIME,
	MONTYPE_BLUEMUSHROOM,
	MONTYPE_GREENMUSHROOM,
	MONTYPE_END
};