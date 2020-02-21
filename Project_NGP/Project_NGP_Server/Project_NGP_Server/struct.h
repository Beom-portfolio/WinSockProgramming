#pragma once
#include <WS2tcpip.h>
#include "define.h"
#include "constant.h"

// 소켓 구조체
struct OVERLAPPED_INFO
{
	WSAOVERLAPPED over;			// OVERLAPPED I/O를 사용하기 위해 필요한 윈도우 구조체
	WSABUF	wsaBuffer;			// 통신을 위해 필요한 버퍼 (length, buffer 구조의 구조체로 되어 있음)
	char	buffer[MAX_BUFFER];	// wsaBuffer에서 buffer는 이 변수의 포인터를 참조 하도록 할것이다.
	bool	is_recv;			// 보내거나 받는다는 것을 알 수 있도록 해주기 위함
};

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

#pragma pack(pop)

struct SOCKET_INFO
{
	OVERLAPPED_INFO over_info;
	SOCKADDR_IN		addr_info;
	SOCKET socket;				// 소켓
	
	// 게임 정보가 들어간다.
	// 플레이어
	char scene_state;
	PLAYERINFO player_info;
	// 이벤트 큐
	queue<EVENTINFO> event_queue;
	CRITICAL_SECTION queue_cs;
};

///////////////////////////////////////////////////////////////
#pragma pack(push, 1)
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

////////////////////////////////////////////////////////////////
// 픽셀 정보
typedef struct _tagPixel24
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}PIXEL24;

typedef struct _tagPixelColliderInfo
{
	vector<PIXEL24>		vecPixel;
	UINT				Width;
	UINT				Height;
	PIXEL24				CollPixel;
	PIXEL24				TurnPixel;
}PIXELCOLLIDERINFO;

// 게임 오브젝트 정보
typedef struct GameObjectInfo
{
	int Pos_X;
	int Pos_Y;
	int Size_Width;
	int Size_Height;
}GAMEOBJINFO;

