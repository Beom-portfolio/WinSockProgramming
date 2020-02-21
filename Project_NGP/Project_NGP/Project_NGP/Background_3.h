#pragma once
#include "GameObject.h"

class Background_3
	: public GameObject
{
public:
	Background_3();
	virtual ~Background_3();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
};

