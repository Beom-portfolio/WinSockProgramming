#pragma once
#include "Scene.h"

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	virtual ~SceneManager();

public:
	SCENESTATE GetCurrentSceneState() { return m_CurrentScene; }
public:
	bool ChangeSceneState(SCENESTATE SceneState);

public:
	int Update(const float& TimeDelta);
	void Render(HDC hDC);
	void Release();

private:
	Scene *m_Scene = nullptr;
	SCENESTATE m_CurrentScene = SCENE_END;
};

