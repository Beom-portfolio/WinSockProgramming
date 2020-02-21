#include "stdafx.h"
#include "Effect.h"

CEffect::CEffect()
{
}

CEffect::~CEffect()
{
	Release();
}

bool CEffect::Initialize()
{
	return true;
}

int CEffect::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void CEffect::Render(HDC hdc)
{
}

void CEffect::Release()
{
}

void CEffect::SetEffectSpawn(int x, int y, DIRECTION Dir, int AttCheck)
{
	SetPosition(x, y);
	m_AttCheck = AttCheck;
	m_Direction = Dir;
}
