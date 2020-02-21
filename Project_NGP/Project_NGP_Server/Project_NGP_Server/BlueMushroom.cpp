#include "pch.h"
#include "BlueMushroom.h"


BlueMushroom::BlueMushroom()
	: Monster()
{
}


BlueMushroom::~BlueMushroom()
{
	Release();
}

bool BlueMushroom::Initialize(int pos_x, int pos_y)
{
	Monster::Initialize(pos_x, pos_y);
	m_Type = MONTYPE_BLUEMUSHROOM;
	m_hp = 10;
	m_Info.Size_Width = 70;
	m_Info.Size_Height = 70;
	return true;
}

int BlueMushroom::Update(const float & TimeDelta)
{
	Monster::Update(TimeDelta);

	if (Monster_Move == m_State)
	{
		m_Speed = 120;
	}

	return 0;
}

void BlueMushroom::Release()
{
}
