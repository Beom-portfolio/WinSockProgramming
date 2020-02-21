#pragma once
#include "GameObject.h"

class Background_2
	: public GameObject
{
public:
	Background_2();
	virtual ~Background_2();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

