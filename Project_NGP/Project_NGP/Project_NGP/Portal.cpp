#include "stdafx.h"
#include "Portal.h"

Portal::Portal()
{
}

Portal::~Portal()
{
	Release();
}

bool Portal::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 89, 257 };
	m_CollideInfo = GAMEOBJINFO{ 0, 80, 89, 90 };
	m_RenderType = RENDER_EFFECT;

	m_SpriteInfo.key = L"portal";
	m_SpriteInfo.SpriteIndex = 0.f;
	m_SpriteInfo.MaxFrame = 8;
	m_SpriteInfo.Speed = 10.f;
	return true;
}

int Portal::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
	{
		return -1;
	}

	if (-1 == Update_Sprite(TimeDelta))
	{
		return -1;
	}

	return 0;
}

void Portal::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_Width,
		m_SpriteInfo.StateIndex * m_Info.Size_Height,
		m_Info.Size_Width, m_Info.Size_Height, RGB(250, 250, 250));
}

void Portal::Release()
{
}

int Portal::Update_Sprite(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;

	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
	{
		m_SpriteInfo.SpriteIndex = 0.f;
	}

	return 0;
}
