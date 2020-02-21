#pragma once
#include "Monster.h"

class GreenMushroom
	: public Monster
{
public:
	GreenMushroom();
	virtual ~GreenMushroom();

public:
	virtual bool Initialize(int pos_x, int pos_y);
	virtual int  Update(const float& TimeDelta);
	virtual void Release();
};
