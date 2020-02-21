#pragma once

#define SERVER_PORT 3500

// 서버 패킷 처리
#define SP_LOGIN_OK			1		// 로그인
#define SP_PLAYER			2		// 플레이어 위치
#define SP_OTHERPLAYER		3
#define SP_MONSTER			4
#define SP_HIT				5
#define SP_GONEXT			6
#define SP_CHAT				7
#define SP_EVENT			99		// Event

// 로그를 확인 할 수 있다.
//#define LOG_CHECK
