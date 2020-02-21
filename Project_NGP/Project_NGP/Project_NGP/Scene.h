#pragma once
class CameraManager;
class ObjectManager;
class NetworkManager;
class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual bool Initialize() PURE;
	virtual int Update(const float& TimeDelta) PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

public:
	bool InitializeNetwork(SCENESTATE curScene);
	bool UpdateNetwork();

private:
	bool UpdateNetPlayer();
	bool UpdateNetOthers();
	bool UpdateNetMonster();
	bool UpdateNetEvent();

protected:
	CameraManager* m_CamManager = nullptr;
	ObjectManager* m_ObjManager = nullptr;
	NetworkManager* m_NetworkManager = nullptr;

	SCENESTATE		m_curScene = SCENE_END;
};

