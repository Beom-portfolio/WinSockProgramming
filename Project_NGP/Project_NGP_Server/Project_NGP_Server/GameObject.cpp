#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
	ZeroMemory(&m_Info, sizeof(GAMEOBJINFO));
}

GameObject::~GameObject()
{
	Release();
}

void GameObject::SetPosition(int posX, int posY)
{
}

void GameObject::SetFall(bool fall)
{
}

bool GameObject::Initialize(int pos_x, int pos_y)
{
	m_Info.Pos_X = pos_x;
	m_Info.Pos_Y = pos_y;
	return true;
}

int GameObject::Update(const float& TimeDelta)
{
	// ม฿ทย
	m_Info.Pos_Y += int(m_GravitySpeed * TimeDelta);
	m_GravitySpeed += m_GravityAcc * TimeDelta;

	if (true == m_FallCheck)
	{
		if (1000.f > m_GravityAcc)
			m_GravityAcc += 9.8f * 10.f;
	}

	return 0;
}

void GameObject::Release()
{
}

void GameObject::CollisionPixelPart(DIRECTION dir)
{
}
