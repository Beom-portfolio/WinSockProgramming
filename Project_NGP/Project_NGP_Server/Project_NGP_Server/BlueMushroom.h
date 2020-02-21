#pragma once
#include "Monster.h"

class BlueMushroom
	: public Monster
{
public:
	BlueMushroom();
	virtual ~BlueMushroom();

public:
	virtual bool Initialize(int pos_x, int pos_y);
	virtual int  Update(const float& TimeDelta);
	virtual void Release();
};

