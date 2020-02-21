#pragma once

#define SERVER_PORT 3500

// Ŭ���̾�Ʈ ��Ŷ ó��
#define SP_LOGIN_OK			1		// �α���
#define SP_PLAYER			2		// �÷��̾� ����
#define SP_OTHERPLAYER		3		// �ٸ� ���� ����
#define SP_MONSTER			4		// ���� ����
#define SP_HIT  			5		// �浹 ����
#define SP_GONEXT			6		// ���� Scene ��ȯ
#define SP_CHAT				7		// ä��
#define SP_EVENT			99		// Event



// �ִ� ���� ���� ũ��
constexpr int MAX_BUFFER = 1024;

enum EventState
{
	EV_PUTOTHERPLAYER,
	EV_END,
	EV_CHAT,
	EV_NONE
};


#pragma pack(push, 1)
typedef struct EventInfo
{
	short size;
	char type;
	int id;
	//
	char scene_state;
	char event_state;
	//
	char chat_buffer[128];
	char chat_size;
}EVENTINFO;

typedef struct PlayerInfo
{
	short	pos_x, pos_y;
	int		player_state;
	char	player_dir;
}PLAYERINFO;

typedef struct MonsterInfo
{
	char	monster_type;
	short	pos_x, pos_y;
	int		monster_state;
	char	monster_dir;
}MONSTERINFO;

// Network Packet
typedef struct ServerPacketTypeLogin
{
	short size;
	char type;
	int id;
}SPLOGIN;

typedef struct ServerPacketTypePlayer
{
	short size;
	char type;
	int id;
	char scene_state;
	PLAYERINFO info;
}SPPLAYER;

typedef struct ServerPacketOtherPlayers
{
	int id;
	char scene_state;
	PLAYERINFO info;
}SPOTHERPLAYERS;

typedef struct ServerPacketMonster
{
	int monster_id;
	MONSTERINFO info;
}SPMONSTER;

typedef struct ServerPacketHit
{
	short size;
	char type;
	int id;
	int monster_id;
	int damage;
}SPHIT;

typedef struct ServerPacketGoNext
{
	short size;
	char type;
	int id;
	char cur_scene_state;
	char next_scene_state;
}SPGONEXT;

typedef struct ServerPacketEnd
{
	short size;
	char type;
	int id;
	char scene_state;
}SPEND;

#pragma pack(pop)