#pragma once
#include "GameObject.h"

class Background 
	: public GameObject
{
public:
	Background();
	virtual ~Background();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

