#pragma once

#define SERVER_PORT 3500

// 클라이언트 패킷 처리
#define SP_LOGIN_OK			1		// 로그인
#define SP_PLAYER			2		// 플레이어 상태
#define SP_OTHERPLAYER		3		// 다른 유저 상태
#define SP_MONSTER			4		// 몬스터 상태
#define SP_HIT  			5		// 충돌 상태
#define SP_GONEXT			6		// 다음 Scene 전환
#define SP_CHAT				7		// 채팅
#define SP_EVENT			99		// Event



// 최대 보낼 버퍼 크기
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