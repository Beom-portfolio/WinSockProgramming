#pragma once
#include "Scene.h"

class TestScene
	: public Scene
{
public:
	TestScene();
	virtual ~TestScene();

public:
	virtual bool Initialize();
	virtual int Update(const float& TimeDelta);
	virtual void Render(HDC hDC);
	virtual void Release();
};

