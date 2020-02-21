#pragma once
#include <map>
#include "struct.h"

extern std::map<int, SOCKET_INFO*>  g_mapClient;	// 소켓 구조체를 담을 STL map 컨테이너
extern HANDLE					    g_iocp;			// iocp 핸들
extern int						    g_id;