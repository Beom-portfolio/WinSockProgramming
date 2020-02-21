#pragma once
#include "Effect.h"

class NomalAttack
	: public CEffect
{
public:
	NomalAttack();
	virtual ~NomalAttack();

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	int Update_Position(const float& TimeDelta, const DIRECTION& Direction);
	int Update_Sprite(const float& TimeDelta);
};

