#pragma once

enum SCENESTATE
{
	SCENE_MENU,
	SCENE_TEST,
	SCENE_MAIN_1,
	SCENE_MAIN_2,
	SCENE_MAIN_3,
	SCENE_END
};

enum DIRECTION
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_TOP,
	DIR_BOTTOM,
	DIR_END
};

enum PlayerState
{
	Player_Idle, 
	Player_Idle_Att, 
	Player_Walk, 
	Player_Jump, 
	Player_Crouch,
	Player_Att_1, 
	Player_Att_2, 
	Player_Att_3,
	Player_Hanging, 
	Player_End
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

