#include "stdafx.h"
#include "MainUI.h"

MainUI::MainUI()
	:GameObject()
{
}

MainUI::~MainUI()
{
	Release();
}

bool MainUI::Initialize()
{
	m_Info = GAMEOBJINFO{ WINSIZE_X / 2, WINSIZE_Y - (56 / 2), 800, 56};
	m_isNoScroll = true;
	m_RenderType = RENDER_UI_2;
	return true;
}

int MainUI::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void MainUI::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"main_ui")->GetGdiImageDefault();

	BitBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height,
		hMemDC, 0, 0, SRCCOPY);
}

void MainUI::Release()
{
}
