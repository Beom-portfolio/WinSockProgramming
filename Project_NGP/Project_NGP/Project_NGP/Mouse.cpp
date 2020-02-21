#include "stdafx.h"
#include "Mouse.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
	Release();
}

bool Mouse::Initialize()
{
	m_Info.Size_Width = 30;
	m_Info.Size_Height = 30;

	ShowCursor(false);

	m_isNoScroll = true;

	m_RenderType = RENDER_UI_3;

	return true;
}

int Mouse::Update(const float & TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
	{
		return -1;
	}

	// GetCursorPos: 현재 마우스 커서 위치의 좌표를 얻어오는 함수.
	GetCursorPos(&m_MousePos);

	// ScreenToClient: 클라이언트 좌표 기준으로 변환해주는 함수.
	ScreenToClient(g_hWnd, &m_MousePos);

	m_Info.Pos_X = m_MousePos.x;
	m_Info.Pos_Y = m_MousePos.y;

	return 0;
}

void Mouse::Render(HDC hdc)
{
	Image* image = GET_MANAGER<GdiPlusManager>()->FindImage(L"cursor")->GetGdiPlusImageDefault();

	Graphics g(hdc);
	
	//Ellipse(hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	g.DrawImage(image, m_Rect.left + (m_Info.Size_Width / 2),
					   m_Rect.top + (m_Info.Size_Height / 2));
	//g.DrawImage(image, m_Info.Pos_X, m_Info.Pos_Y, m_Info.Size_Width, m_Info.Size_Height);
}

void Mouse::Release()
{
	ShowCursor(true);
}
