#pragma once

class NetworkManager : public Singleton<NetworkManager>
{
public:
	NetworkManager();
	virtual ~NetworkManager();

public:
	bool Initialize();
	void Release();

public:
	const int& GetMyId() { return m_myID; }

public:
	bool ConnectToServer(const char* ip);
	bool SendPlayerInfo(SCENESTATE SceneState, const PLAYERINFO& PInfo);
	bool SendAndRecvOtherInfo(char* OutInfo);
	bool SendAndRecvEvent(EVENTINFO* OutEvInfo);
	bool SendAndRecvMonster(char* OutInfo);
	bool SendHitInfo(int monster_id, int damage);
	bool SendGoNextSceneInfo(SCENESTATE nextState, SCENESTATE curState);
	bool SendChatting(const TCHAR* chat);
public:
	void AttackCollisionForNetwork(ObjectManager::MAPOBJ* TargetList, ObjectManager::MAPOBJ* SkillList);

private:
	bool error_quit(const WCHAR* msg);
	
	// 블로킹 보내기
	int Send(void* packet_struct, char type, short size);
	// 블로킹 받기
	int Recv(void* OutPacket_struct);
	// 패킹
	void Packing(char* OutBuf, void* packet_struct, char type);
	// 풀기
	void Depacking(void* OutPacket_struct, char* buf, short size = 0);

private:
	WSADATA			m_wsa;
	SOCKET			m_serversocket;
	sockaddr_in		m_serverAddr;

	char			m_netBuffer[MAX_BUFFER];
	
	int				m_myID = 0;
};

