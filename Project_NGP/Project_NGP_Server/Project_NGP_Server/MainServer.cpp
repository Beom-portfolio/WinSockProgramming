#include "pch.h"
#include "MainServer.h"
#include "Scene.h"
#include "Spawn.h"
#include "Monster.h"
#include "GameObject.h"
#include "MainScene_1.h"
#include "MainScene_2.h"

vector<Scene*> MainServer::m_vecScene;

MainServer::MainServer()
{
}

MainServer::~MainServer()
{
	Release();
}

bool MainServer::Initialize()
{
	// �����ڵ� �ѱ� ����� ����
	wcout.imbue(std::locale("korean"));
	// ���� �ʱ�ȭ
	if (0 != WSAStartup(MAKEWORD(2, 2), &m_WSAData))
	{
		error_quit("���� �ʱ�ȭ ����");
		return false;
	}
		
	// listen ���� ����
	m_listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
		WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_listenSocket)
	{ 
		error_quit("���� ���� ���� ����");
		return false;
	}

	// ���� �ɼ�
	// SO_RCVBUF 
	int optval, optlen;

	optlen = sizeof(optval);
	int result = getsockopt(m_listenSocket, SOL_SOCKET, SO_RCVBUF,
		(char*)& optval, &optlen);
	if (SOCKET_ERROR == result)
	{
		error_quit("������ ���� ���� ũ�� �������� ����");
		return false;
	}

	optval *= 2;
	result = setsockopt(m_listenSocket, SOL_SOCKET, SO_RCVBUF,
		(char*)& optval, sizeof(optval));
	if (SOCKET_ERROR == result)
	{
		error_quit("���� �ɼ� SO_RCVBUF ���� ����");
		return false;
	}

	// ���� �ּ� ���� ����ü
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// ���� �ּ�, ��Ʈ �Ҵ�
	if (0 != ::bind(m_listenSocket, (sockaddr*)&serverAddr,
		sizeof(SOCKADDR_IN)))
	{ 
		error_quit("���� ���� ���ε� ����");
		return false;
	}
	// ���� ���� ���� �������� ����
	if (0 != listen(m_listenSocket, SOMAXCONN))
	{ 
		error_quit("���� ���� ���� ���� ����");
		return false;
	}
	
	memset(&m_clientAddr, 0, sizeof(SOCKADDR_IN));

	// iocp ����
	g_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);
	if (NULL == g_iocp)
	{ 
		error_quit("IOCP ���� ����");
		return false;
	}

	return true;
}

bool MainServer::Running()
{
	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);

	// cpu thread ������ ������ �´�.
	int thread_count = sys_info.dwNumberOfProcessors;

	// cpu thread ������ŭ ����ó���� �ϰڴ�.
	for (int i = 0; i < thread_count - 1; ++i)
	{
		HANDLE hThread = CreateThread(NULL, 0, do_worker, NULL, 0, NULL);
		if (NULL == hThread)
			continue;
		CloseHandle(hThread);
	}
	// ������ �� �����忡���� �������� ó���� Scene�� ���Ѱ��̴�.
	HANDLE hThread = CreateThread(NULL, 0, do_scene, NULL, 0, NULL);
	if (NULL == hThread)
		return false;
	CloseHandle(hThread);

	int addrLen = sizeof(SOCKADDR_IN);
	g_id = 1;
	while (true)
	{
		m_clientSocket = accept(m_listenSocket, (sockaddr*)&m_clientAddr, &addrLen);
		
		int user_id = g_id++;

		g_mapClient[user_id] = new SOCKET_INFO;
		memset(&g_mapClient[user_id]->over_info.over, 0x00, sizeof(WSAOVERLAPPED));
		g_mapClient[user_id]->socket = m_clientSocket;
		g_mapClient[user_id]->over_info.wsaBuffer.len = MAX_BUFFER;
		g_mapClient[user_id]->over_info.wsaBuffer.buf = g_mapClient[user_id]->over_info.buffer;
		g_mapClient[user_id]->over_info.is_recv = true;
		
		// �Ӱ迵�� �ʱ�ȭ
		InitializeCriticalSection(&g_mapClient[user_id]->queue_cs);

		printf("[Ŭ���̾�Ʈ ����] ID : %d, IP : %s, PORT : %d, SOCKET : %d\n",  
			user_id, inet_ntoa(m_clientAddr.sin_addr), ntohs(m_clientAddr.sin_port), (int)m_clientSocket);

		memcpy(&g_mapClient[user_id]->addr_info, &m_clientAddr, sizeof(SOCKADDR_IN));

		m_flags = 0;
		CreateIoCompletionPort(reinterpret_cast<HANDLE>(m_clientSocket), g_iocp, user_id, 0);

		// ���� ������ �ٸ� Ŭ���̾�Ʈ �̺�Ʈ ť�� ���� �߰��Ǿ����� �˸��� �̺�Ʈ �߰�
		EVENTINFO info;
		info.size = sizeof(info);
		info.type = SP_EVENT;
		info.event_state = EV_PUTOTHERPLAYER;
		for (auto& cl : g_mapClient)
		{
			if (cl.first == user_id) continue;

			info.id = user_id;
			info.scene_state = SCENE_MAIN_1;
			// �Ӱ迵�� ����
			EnterCriticalSection(&cl.second->queue_cs);
			cl.second->event_queue.push(info);
			LeaveCriticalSection(&cl.second->queue_cs);

			info.id = cl.first;
			info.scene_state = cl.second->scene_state;
			// �Ӱ迵�� ����
			EnterCriticalSection(&g_mapClient[user_id]->queue_cs);
			g_mapClient[user_id]->event_queue.push(info);
			LeaveCriticalSection(&g_mapClient[user_id]->queue_cs);
		}

		int result = WSARecv(m_clientSocket, &g_mapClient[user_id]->over_info.wsaBuffer,
			1, NULL, &m_flags, &(g_mapClient[user_id]->over_info.over), NULL);
		if (0 != result)
		{
			int err_no = WSAGetLastError();
			if (WSA_IO_PENDING != err_no)
			{
				error_quit("WSARecv �Լ� ����");
				return false;
			}
		}
	}
	return true;
}

void MainServer::Release()
{
	// ��� Ŭ���̾�Ʈ�� ������ ���´�.
	for (auto& cl : g_mapClient)
	{
		closesocket(cl.second->socket);
		DeleteCriticalSection(&cl.second->queue_cs);
	}
	g_mapClient.clear();

	closesocket(m_listenSocket);
	WSACleanup();
}

void MainServer::error_quit(const char * msg)
{
	WCHAR *lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	cout << L"[" << msg << L"] ";
	wcout << L"Error : " << lpMsgBuf << endl;
	LocalFree(lpMsgBuf);
	exit(1);
}

DWORD WINAPI MainServer::do_worker(LPVOID arg)
{
	while (true)
	{
		DWORD byte;
		ULONG key;
		PULONG pKey = &key;
		WSAOVERLAPPED *pOver;

		// ��� �Ϸ� ������ ������ ť�� ���� ������ �´�.
		GetQueuedCompletionStatus(g_iocp, &byte, (PULONG_PTR)pKey,
			&pOver, INFINITE);

		SOCKET clientsocket = g_mapClient[key]->socket;

		// ���� ó��
		if (0 == byte)
		{
			closesocket(clientsocket);
			printf("[Ŭ���̾�Ʈ ����] ID : %d, IP : %s, PORT : %d, SOCKET : %d\n",
				key, inet_ntoa(g_mapClient[key]->addr_info.sin_addr),
					 ntohs(g_mapClient[key]->addr_info.sin_port), (int)clientsocket);

			// ���� �۾�
			EVENTINFO info;
			info.size = sizeof(info);
			info.type = SP_EVENT;
			info.id = key;
			info.event_state = EV_END;
			for (auto& cl : g_mapClient)
			{
				if (cl.first == key) continue;
				EnterCriticalSection(&cl.second->queue_cs);
				cl.second->event_queue.push(info);
				LeaveCriticalSection(&cl.second->queue_cs);
			}

			DeleteCriticalSection(&g_mapClient[key]->queue_cs);
			delete g_mapClient[key];
			g_mapClient[key] = nullptr;
			g_mapClient.erase(key);
			continue;
		}

		OVERLAPPED_INFO *over_info = reinterpret_cast<OVERLAPPED_INFO*>(pOver);

		if (true == over_info->is_recv)
		{
			// ��Ŷ�� �� ������

			// Ŭ���̾�Ʈ���� ���� ��Ŷ�� ó��
			ProcessPacket(key, over_info->buffer, byte);

			// �޾������� ó��
			DWORD flags = 0;
			memset(&over_info->over, 0x00, sizeof(WSAOVERLAPPED));
			WSARecv(clientsocket, &over_info->wsaBuffer, 1, 0, &flags, &over_info->over, NULL);
		}
		else
		{
			// �����Ҷ��� ó��
			// Send�Ҷ� 
			delete over_info;
		}
	}

	return 0;
}

DWORD WINAPI MainServer::do_scene(LPVOID arg)
{
	// cpu �������� timedelta ���
	LARGE_INTEGER cpuTick;
	LARGE_INTEGER fixTime;
	LARGE_INTEGER lastTime;
	LARGE_INTEGER frameTime;

	QueryPerformanceCounter(&frameTime);
	QueryPerformanceCounter(&fixTime);
	QueryPerformanceCounter(&lastTime);
	QueryPerformanceFrequency(&cpuTick);

	float TimeDelta = 0.f;
	float TimeAcc = 0.f;
	float FrameLimitTime = 1 / 60.f;

	// Scene�� �ʱ�ȭ �Ѵ�.
	for (int i = SCENE_MENU; i < SCENE_END; ++i)
	{
		Scene* s = nullptr;

		switch (i)
		{
		case SCENE_MENU:
			break;
		case SCENE_TEST:
			break;
		case SCENE_MAIN_1:
			s = new MainScene_1;
			break;
		case SCENE_MAIN_2:
			s = new MainScene_2;
			break;
		}

		if (nullptr != s &&
			false == s->Initialize())
		{
			cout << "Scene �ʱ�ȭ ����!" << endl;
			delete s;
			s = nullptr;
			return -1;
		}

		m_vecScene.emplace_back(s);
	}

	while (true)
	{
		QueryPerformanceCounter(&frameTime);
		
		if ((frameTime.QuadPart - lastTime.QuadPart) > cpuTick.QuadPart)
		{
			QueryPerformanceFrequency(&cpuTick);
			lastTime.QuadPart = frameTime.QuadPart;
		}
		
		TimeDelta = float(frameTime.QuadPart - fixTime.QuadPart) / cpuTick.QuadPart;
		fixTime = frameTime;

		TimeAcc += TimeDelta;

		if (FrameLimitTime <= TimeAcc)
		{
			for (auto& scene : m_vecScene)
			{
				if (nullptr != scene)
					scene->Update(FrameLimitTime);
			}
			TimeAcc = 0.f;
		}
	}

	return 0;
}

void MainServer::ProcessPacket(int id, void* buf, int recv_byte)
{
	char* packet = reinterpret_cast<char*> (buf);

#ifdef LOG_CHECK
	SOCKET_INFO* sockInfo = g_mapClient[id];
	printf("-----------------------------------------------------\n");
	printf("[����] ID : %d, IP : %s, PORT : %d, SOCKET : %d\n",
		id, inet_ntoa(g_mapClient[id]->addr_info.sin_addr),
		ntohs(g_mapClient[id]->addr_info.sin_port), g_mapClient[id]->socket);
	printf("[���� ����] ");
	switch (packet[2])
	{
	case SP_LOGIN_OK: 
		printf(" �α��� ��û");
		break;
	case SP_PLAYER:
		printf(" Ŭ���̾�Ʈ �÷��̾� ����\n");
		break;
	case SP_OTHERPLAYER:
		printf(" �ٸ� Ŭ���̾�Ʈ �÷��̾� ���� ��û");
		break;
	case SP_MONSTER:
		printf(" ���� ���� ��û");
		break;
	case SP_HIT:
		printf(" ���� ����");
		break;
	case SP_GONEXT:
		printf(" �� ��ȯ ����");
		break;
	case SP_EVENT:
		printf(" �̺�Ʈ ���� ��û");
		break;
	}
	printf(" | ���� ���� ����Ʈ ũ�� : %d[byte]\n", recv_byte);
	printf("-----------------------------------------------------\n\n");
#endif

	switch (packet[2])
	{
	case SP_PLAYER:
	{
		SPPLAYER *PlayerInfo = reinterpret_cast<SPPLAYER*> (buf);
		g_mapClient[id]->scene_state = PlayerInfo->scene_state;
		g_mapClient[id]->player_info.pos_x = PlayerInfo->info.pos_x;
		g_mapClient[id]->player_info.pos_y = PlayerInfo->info.pos_y;
		g_mapClient[id]->player_info.player_state = PlayerInfo->info.player_state;
		g_mapClient[id]->player_info.player_dir = PlayerInfo->info.player_dir;
	}
	break;
	case SP_HIT:
	{
		SPHIT* HitInfo = reinterpret_cast<SPHIT*> (buf);
		Scene* curScene = m_vecScene[g_mapClient[HitInfo->id]->scene_state];
		if (nullptr == curScene)
			return;
		Monster* DstMon = curScene->GetMapSpawn().find(HitInfo->monster_id)->second->GetMonster();
		if (nullptr == DstMon)
			return;
		DstMon->Hit(HitInfo->id, HitInfo->damage);
	}
	break;
	case SP_GONEXT:
	{
		SPGONEXT* GoNextInfo = reinterpret_cast<SPGONEXT*> (buf);

		EVENTINFO info;
		info.size = sizeof(info);
		info.type = SP_EVENT;
		for (auto& cl : g_mapClient)
		{
			if (cl.first == GoNextInfo->id) continue;

			// �������� �Ѿ ���� �����ϴ� �����鿡�� �̺�Ʈ ť�� ���� �߰��Ǿ����� �˸���.
			if (GoNextInfo->next_scene_state == cl.second->scene_state)
			{
				info.event_state = EV_PUTOTHERPLAYER;
				info.id = GoNextInfo->id;
				info.scene_state = GoNextInfo->next_scene_state;
				EnterCriticalSection(&cl.second->queue_cs);
				cl.second->event_queue.push(info);
				LeaveCriticalSection(&cl.second->queue_cs);
			}
			
			// ���� ���� �����ϴ� �����鿡�� �̺�Ʈ ť�� ���� ��������� �˸���.
			if (GoNextInfo->cur_scene_state == cl.second->scene_state)
			{
				info.event_state = EV_END;
				info.id = GoNextInfo->id;
				info.scene_state = GoNextInfo->cur_scene_state;
				EnterCriticalSection(&cl.second->queue_cs);
				cl.second->event_queue.push(info);
				LeaveCriticalSection(&cl.second->queue_cs);
			}
		}
	}
	break;
	case SP_CHAT:
	{
		char* ChatInfo = reinterpret_cast<char*> (buf);
		short total_size = 0;
		memcpy(&total_size, ChatInfo, sizeof(short));
		short chat_start = sizeof(short) + sizeof(char) + sizeof(int);
		int chat_size = total_size - chat_start;

		EVENTINFO info;
		info.size = sizeof(info);
		info.type = SP_EVENT;
		info.event_state = EV_CHAT;
		memcpy(&info.id, &ChatInfo[3], sizeof(int));
		info.scene_state = g_mapClient[info.id]->scene_state;
		info.chat_size = chat_size;
		memcpy(&info.chat_buffer, &ChatInfo[7], info.chat_size);

		for (auto& cl : g_mapClient)
		{
			if (cl.first == info.id) continue;

			EnterCriticalSection(&cl.second->queue_cs);
			cl.second->event_queue.push(info);
			LeaveCriticalSection(&cl.second->queue_cs);
		}
	}
	break;
	}

	SendProcess(id, buf);
}

void MainServer::SendProcess(int send_id, void* buf)
{
	char* packet = reinterpret_cast<char*> (buf);

#ifdef LOG_CHECK
	SOCKET_INFO* sockInfo = g_mapClient[send_id];
	printf("-----------------------------------------------------\n");
	printf("[�۽�] ID : %d, IP : %s, PORT : %d, SOCKET : %d\n",
		send_id, inet_ntoa(g_mapClient[send_id]->addr_info.sin_addr),
		ntohs(g_mapClient[send_id]->addr_info.sin_port), g_mapClient[send_id]->socket);
	printf("[�۽� ����] ");
	switch (packet[2])
	{
	case SP_LOGIN_OK:
		printf(" �α��� ����");
		break;
	case SP_PLAYER:
		printf(" Ŭ���̾�Ʈ �÷��̾� ����\n");
		break;
	case SP_OTHERPLAYER:
		printf(" �ٸ� Ŭ���̾�Ʈ �÷��̾� ����");
		break;
	case SP_MONSTER:
		printf(" ���� ����");
		break;
	case SP_HIT:
		printf(" ���� ����");
		break;
	case SP_GONEXT:
		printf(" �� ��ȯ ����");
		break;
	case SP_EVENT:
		printf(" �̺�Ʈ ����");
		break;
	}
#endif

	switch (packet[2])
	{
	case SP_LOGIN_OK:
	{
		SPLOGIN packet;
		packet.id = send_id;
		packet.size = sizeof(packet);
		packet.type = SP_LOGIN_OK;
		SendPacket(send_id, &packet, sizeof(packet));
	}
	break;
	case SP_OTHERPLAYER:
	{
		char tempBuffer[MAX_BUFFER];

		// size type�� ���� ��Ŷ�� �ּ� ���� ��ġ
		int startAddrPos = 2 + 1;
		int count = 0;
		for (auto& c : g_mapClient)
		{
			// �ڽ��� ���� �ʴ´�.
			if (send_id == c.first)
				continue;

			SPOTHERPLAYERS info = SPOTHERPLAYERS{};
			info.id = c.first;
			info.scene_state = c.second->scene_state;
			info.info.pos_x = c.second->player_info.pos_x;
			info.info.pos_y = c.second->player_info.pos_y;
			info.info.player_state = c.second->player_info.player_state;
			info.info.player_dir = c.second->player_info.player_dir;

			memcpy((tempBuffer + startAddrPos + sizeof(SPOTHERPLAYERS) * count),
				&info, sizeof(SPOTHERPLAYERS));
			++count;
		}
		// size
		short size = sizeof(SPOTHERPLAYERS) * count + sizeof(short) + sizeof(char);
		memcpy(&tempBuffer[0], &size, sizeof(short));
		// type
		tempBuffer[2] = SP_OTHERPLAYER;

		SendPacket(send_id, &tempBuffer, size);
	}
	break;
	case SP_MONSTER:
	{
		SCENESTATE CurSceneState = (SCENESTATE)packet[3];

		Scene* CurScene = m_vecScene[CurSceneState];
		char tempBuffer[MAX_BUFFER];

		if (nullptr == CurScene)
		{
			int size = 2;
			memcpy(&tempBuffer[0], &size, sizeof(short));
			tempBuffer[2] = SP_MONSTER;
			SendPacket(send_id, &tempBuffer, 3);
			break;
		}

		// size type�� ���� ��Ŷ�� �ּ� ���� ��ġ
		int startAddrPos = 2 + 1;
		int count = 0;
		for (auto& s : CurScene->GetMapSpawn())
		{
			// packet struct
			SPMONSTER monster_info = SPMONSTER{};
			monster_info.monster_id = s.first;

			Monster* m = s.second->GetMonster();
			if (nullptr == m)
				continue;

			// monster info struct
			MONSTERINFO info = MONSTERINFO{};
			info.monster_type = m->GetMonType();
			info.monster_state = m->GetMonState();
			info.pos_x = m->GetInfo().Pos_X;
			info.pos_y = m->GetInfo().Pos_Y;
			info.monster_dir = m->GetDirection();

			monster_info.info = info;

			memcpy((tempBuffer + startAddrPos + sizeof(SPMONSTER) * count),
				&monster_info, sizeof(SPMONSTER));
			++count;
		}
		// size
		short size = short(sizeof(SPMONSTER) * count + sizeof(short) + sizeof(char));
		memcpy(&tempBuffer[0], &size, sizeof(short));
		// type
		tempBuffer[2] = SP_MONSTER;
		SendPacket(send_id, &tempBuffer, size);
	}
	break;
	case SP_EVENT:
	{
		EnterCriticalSection(&g_mapClient[send_id]->queue_cs);
		if (g_mapClient[send_id]->event_queue.empty())
		{
			LeaveCriticalSection(&g_mapClient[send_id]->queue_cs);
			EVENTINFO packet = EVENTINFO{ };
			packet.size = sizeof(packet);
			packet.event_state = EV_NONE;
			SendPacket(send_id, &packet, sizeof(packet));
			break;
		}

		const EVENTINFO& evInfo = g_mapClient[send_id]->event_queue.front();
		EVENTINFO packet = evInfo;
		g_mapClient[send_id]->event_queue.pop();
		LeaveCriticalSection(&g_mapClient[send_id]->queue_cs);
		SendPacket(send_id, &packet, sizeof(packet));
	}
	break;
	}
}

void MainServer::SendPacket(int send_id, void* buf, int size)
{
	char* packet = reinterpret_cast<char*>(buf);
	int packet_size = size;

#ifdef LOG_CHECK
	printf(" | �۽��� ����Ʈ ũ�� : %d[byte]\n", packet_size);
	printf("-----------------------------------------------------\n\n");
#endif

	OVERLAPPED_INFO* send_over = new OVERLAPPED_INFO;
	memset(send_over, 0x00, sizeof(OVERLAPPED_INFO));
	send_over->is_recv = false; // recv �ƴϴ�~
	memcpy(send_over->buffer, packet, packet_size);
	send_over->wsaBuffer.buf = send_over->buffer;
	send_over->wsaBuffer.len = packet_size;
	int result = WSASend(g_mapClient[send_id]->socket, &send_over->wsaBuffer, 1, 0, 0, &send_over->over, NULL);
}