#include "pch.h"
#include "GreenMushroom.h"


GreenMushroom::GreenMushroom()
	: Monster()
{
}


GreenMushroom::~GreenMushroom()
{
	Release();
}

bool GreenMushroom::Initialize(int pos_x, int pos_y)
{
	Monster::Initialize(pos_x, pos_y);
	m_Type = MONTYPE_GREENMUSHROOM;
	m_hp = 10;
	m_Info.Size_Width = 60;
	m_Info.Size_Height = 60;
	return true;
}

int GreenMushroom::Update(const float & TimeDelta)
{
	Monster::Update(TimeDelta);

	if (Monster_Move == m_State)
	{
		m_Speed = 100;
	}

	return 0;
}

void GreenMushroom::Release()
{
}
