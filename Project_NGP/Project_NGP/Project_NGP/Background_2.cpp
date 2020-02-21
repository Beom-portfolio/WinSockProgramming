#include "stdafx.h"
#include "Background_2.h"

Background_2::Background_2()
	: GameObject()
{
}

Background_2::~Background_2()
{
	Release();
}

bool Background_2::Initialize()
{
	// 1280 720
	m_Info = GAMEOBJINFO{ 1900 / 2, 1000 / 2, 1900, 1000 };
	m_RenderType = RENDER_BACKGROUND;

	LoadPixelCollider("../Resources/Map/Back_2_Collider_Real.bmp", 255, 0, 255);

	return true;
}

int Background_2::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
	{
		return -1;
	}

	return 0;
}

void Background_2::Render(HDC hdc)
{
	HDC hMemDC;

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"background_collider_2")->GetGdiImageDefault();
	else
		hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"background_2")->GetGdiImageDefault();

	BitBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height
		, hMemDC, 0, 0, SRCCOPY);
}

void Background_2::Release()
{
}
