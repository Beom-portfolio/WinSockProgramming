// Project_NGP_Server.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "MainServer.h"

std::map<int, SOCKET_INFO*>  g_mapClient;
HANDLE						 g_iocp = NULL;
int							 g_id = 1;
int main()
{
	MainServer server; 
	if (false == server.Initialize())
		return -1;
	if (false == server.Running())
		return -1;
}
