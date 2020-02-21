#include "stdafx.h"
#include "Monster.h"

Monster::Monster()
	: GameObject()
{
}

Monster::~Monster()
{
	Release();
}

bool Monster::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 44, 34};
	m_RenderType = RENDER_OBJ;

	return true;
}

int Monster::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
	{
		return -1;
	}

	return 0;
}

void Monster::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);

	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"snail")->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height
		, hMemDC, 0, 0, m_Info.Size_Width, m_Info.Size_Height, RGB(255, 0, 255));
}

void Monster::Release()
{
}
