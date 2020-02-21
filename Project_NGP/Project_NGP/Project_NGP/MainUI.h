#pragma once
#include "GameObject.h"

class MainUI
	: public GameObject
{
public:
	MainUI();
	virtual ~MainUI();
public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

