#include "stdafx.h"
#include "Background_3.h"

Background_3::Background_3()
	: GameObject()
{
}

Background_3::~Background_3()
{
	Release();
}

bool Background_3::Initialize()
{
	// 1280 720
	m_Info = GAMEOBJINFO{ 1920 / 2, 680 / 2, 1920, 680 };
	m_RenderType = RENDER_BACKGROUND;

	LoadPixelCollider("../Resources/Map/Back_Town_Collider_Real.bmp", 255, 0, 255);

	return true;
}

int Background_3::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
	{
		return -1;
	}

	return 0;
}

void Background_3::Render(HDC hdc)
{
	HDC hMemDC;

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"background_collider_3")->GetGdiImageDefault();
	else
		hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"background_3")->GetGdiImageDefault();

	BitBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height
		, hMemDC, 0, 0, SRCCOPY);
}

void Background_3::Release()
{
}
