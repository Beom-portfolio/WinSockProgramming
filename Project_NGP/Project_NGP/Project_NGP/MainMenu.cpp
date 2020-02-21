#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
	Release();
}

bool MainMenu::Initialize()
{
	ShowWindow(g_hWnd_New, SW_SHOW);
	UpdateWindow(g_hWnd_New);

	return true;
}

int MainMenu::Update(const float& TimeDelta)
{
	return 0;
}

void MainMenu::Render(HDC hDC)
{
}

void MainMenu::Release()
{
	ShowWindow(g_hWnd_New, SW_HIDE);
}
