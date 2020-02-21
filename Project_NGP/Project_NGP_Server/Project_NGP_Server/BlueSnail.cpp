#include "pch.h"
#include "BlueSnail.h"

BlueSnail::BlueSnail()
	: Monster()
{
}

BlueSnail::~BlueSnail()
{
	Release();
}

bool BlueSnail::Initialize(int pos_x, int pos_y)
{
	Monster::Initialize(pos_x, pos_y);
	m_Type = MONTYPE_SNAIL;
	m_hp = 10;
	m_Info.Size_Width = 44;
	m_Info.Size_Height = 34;
	return true;
}

int BlueSnail::Update(const float& TimeDelta)
{
	Monster::Update(TimeDelta);
	
	if (Monster_Move == m_State)
	{
		m_Speed = 100;
	}

	return 0;
}

void BlueSnail::Release()
{
}
