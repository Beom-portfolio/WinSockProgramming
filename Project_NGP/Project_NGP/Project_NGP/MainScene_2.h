#pragma once
#include "Scene.h"

class MainScene_2
	: public Scene
{
public:
	MainScene_2();
	virtual ~MainScene_2();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Render(HDC hDC);
	virtual void Release();
};

