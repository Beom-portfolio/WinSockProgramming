#pragma once
#include "Scene.h"

class MainScene_1
	: public Scene
{
public:
	MainScene_1();
	virtual ~MainScene_1();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Render(HDC hDC);
	virtual void Release();
};

