#include "pch.h"
#include "Slime.h"

Slime::Slime()
	: Monster()
{

}

Slime::~Slime()
{
	Release();
}

bool Slime::Initialize(int pos_x, int pos_y)
{
	Monster::Initialize(pos_x, pos_y);
	m_Type = MONTYPE_SLIME;
	m_hp = 10;
	m_Info.Size_Width = 50;
	m_Info.Size_Height = 70;
	return true;
}

int Slime::Update(const float& TimeDelta)
{
	Monster::Update(TimeDelta);

	if (Monster_Move == m_State)
	{
		m_Speed = 120;
	}

	return 0;
}

void Slime::Release()
{
}
