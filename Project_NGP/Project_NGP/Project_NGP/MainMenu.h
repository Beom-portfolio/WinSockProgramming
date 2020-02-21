#pragma once
#include "Scene.h"

class MainMenu
	: public Scene
{
public:
	MainMenu();
	virtual ~MainMenu();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Render(HDC hDC);
	virtual void Release();

private:
	NetworkManager* m_NetMgr = nullptr;
};

