#include "stdafx.h"
#include "Background.h"


Background::Background()
	: GameObject()
{
}


Background::~Background()
{
	Release();
}

bool Background::Initialize()
{
	// 1280 720
	m_Info = GAMEOBJINFO{ 1800 / 2, 1500 / 2, 1800, 1500 };
	m_RenderType = RENDER_BACKGROUND;

	LoadPixelCollider("../Resources/Map/Back_Collider_Real.bmp", 255, 0, 255);

	return true;
}

int Background::Update(const float & TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
	{
		return -1;
	}

	return 0;
}

void Background::Render(HDC hdc)
{
	HDC hMemDC;
	
	if(true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"background_collider")->GetGdiImageDefault();
	else
		hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"background")->GetGdiImageDefault();

	BitBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height
		, hMemDC, 0, 0, SRCCOPY);
}

void Background::Release()
{
}
