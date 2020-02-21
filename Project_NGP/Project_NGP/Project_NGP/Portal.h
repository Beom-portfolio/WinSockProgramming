#pragma once
#include "GameObject.h"

class Portal
	: public GameObject
{
public:
	Portal();
	virtual ~Portal();
public:
	const SCENESTATE& GetSceneInfo() { return m_SceneInfo; }
	void SetSceneInfo(SCENESTATE scene) { m_SceneInfo = scene; }
public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
private:
	int Update_Sprite(const float& TimeDelta);
	SCENESTATE m_SceneInfo = SCENE_END;
};

