#include "stdafx.h"
#include "NomalAttack.h"
NomalAttack::NomalAttack()
{
}

NomalAttack::~NomalAttack()
{
	Release();
}

bool NomalAttack::Initialize()
{
	m_EffectRectX = 139;
	m_EffectRectY = 118;

	m_Info = GAMEOBJINFO{ m_Info.Pos_X, m_Info.Pos_X, m_EffectRectX, m_EffectRectY };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, m_EffectRectX, m_EffectRectY };
	m_Speed = 0.f;
	m_RenderType = RENDER_EFFECT;
	m_SpriteInfo.key = L"nomal_attack";
	m_SpriteInfo.SpriteIndex = 0.f;
	m_SpriteInfo.StateIndex = 0;
	m_SpriteInfo.MaxFrame = 5;
	m_SpriteInfo.Speed = 15.f;

	return true;
}

int NomalAttack::Update(const float& TimeDelta)
{
	if (-1 == CEffect::Update(TimeDelta))
	{
		return -1;
	}

	if (-1 == Update_Position(TimeDelta, m_Direction))
	{
		return -1;
	}

	if (-1 == Update_Sprite(TimeDelta))
	{
		return -1;
	}

	return 0;
}

int NomalAttack::Update_Position(const float& TimeDelta, const DIRECTION& Direction)
{
	if (DIR_LEFT == m_Direction)
	{
		m_Info.Size_Width = m_EffectRectX;
		/*m_Info = GAMEOBJINFO{ m_Info.Pos_X, m_Info.Pos_X, rectX, rectY };
		m_CollideInfo = GAMEOBJINFO{ m_Info.Pos_X, m_Info.Pos_Y, rectX, rectY };*/
	}
	else if (DIR_RIGHT == m_Direction)
	{
		m_Info.Size_Width = -m_EffectRectX;
		/*m_Info = GAMEOBJINFO{ m_Info.Pos_X, m_Info.Pos_X, -rectX, rectY };
		m_CollideInfo = GAMEOBJINFO{ m_Info.Pos_X, m_Info.Pos_Y, -rectX, rectY };*/
	}
	return 0;
}

int NomalAttack::Update_Sprite(const float& TimeDelta)
{
	// cout << m_SpriteInfo.SpriteIndex << endl;
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
	SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_isDead = true;

	return 0;
}

void NomalAttack::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	Graphics G(hdc);

	Image* img = GET_MANAGER<GdiPlusManager>()->FindImage(m_SpriteInfo.key)->GetGdiPlusImageFromIndex((int)m_SpriteInfo.SpriteIndex);

	G.DrawImage(img, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height);
}

void NomalAttack::Release()
{
}