#include "stdafx.h"
#include "Chat.h"
#include "Text.h"

Chat::Chat()
	: GameObject()
{
}

Chat::~Chat()
{
}

void Chat::SetActivate(bool check)
{
	if (true == check)
	{
		SetFocus(hChatEdit);
		m_renderCheck = true;
	}
	else
	{
		SetFocus(g_hWnd);
		m_renderCheck = false;

		// 네트워크로 정보를 보낸다.
		GET_MANAGER<NetworkManager>()->SendChatting(m_ChatEditBuffer);

		// 썼던 버퍼를 지운다.
		memset(&m_ChatEditBuffer, 0x00, sizeof(WCHAR) * 25);
		SetWindowTextW(hChatEdit, L"");
		m_TypingText->ClearAll();
	}
}

bool Chat::Initialize()
{
	m_Info = GAMEOBJINFO{ 450 / 2, WINSIZE_Y - 56 - (24 / 2), 450, 24 };
	m_isNoScroll = true;
	m_RenderType = RENDER_UI;
	m_renderCheck = false;

	m_TypingText = new Text;
	m_TypingText->Initialize(13);
	m_TypingText->SetNewlineCount(25);

	// 최대 24글자까지만
	m_TypingText->SetText(L"");

	return true;
}

int Chat::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	if (true == m_renderCheck)
	{
		int size = GetWindowTextW(hChatEdit, m_ChatEditBuffer, 25);
		if (nullptr != m_TypingText)
		{
			m_TypingText->SetText(m_ChatEditBuffer, size);
		}
	}

	return 0;
}

void Chat::Render(HDC hdc)
{
	if (false == m_renderCheck)
		return;

	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"chat")->GetGdiImageDefault();

	BitBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height,
		hMemDC, 0, 0, SRCCOPY);

	if (nullptr != m_TypingText)
	{
		m_TypingText->SetPosition(m_Rect.left + 60
			, m_Rect.top + 6);
		m_TypingText->Render(hdc);
	}
}

void Chat::Release()
{
}
