#pragma once
#include "GameObject.h"

class Monster 
	: public GameObject
{
public:
	Monster();
	virtual ~Monster();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

