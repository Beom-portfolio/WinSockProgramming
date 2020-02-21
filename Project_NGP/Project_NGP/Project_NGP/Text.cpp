#include "stdafx.h"
#include "Text.h"

Text::Text()
{
}

Text::~Text()
{
	Release();
}

void Text::SetPosition(int x, int y)
{
	m_StartPos.X = (float)x;
	m_StartPos.Y = (float)y;
}

void Text::SetText(const TCHAR* buffer)
{
	ClearAll();
	wmemcpy(m_TextBuffer, buffer, wcslen(buffer));
}

void Text::SetText(const TCHAR* buffer, int size)
{
	ClearAll();
	wmemcpy(m_TextBuffer, buffer, size);
}

void Text::SetNewlineCount(int count)
{
	m_NewlineCount = count;
}

void Text::SetBackColor(unsigned char r, unsigned char g, unsigned char b)
{
	m_BackColor.r = r;
	m_BackColor.g = g;
	m_BackColor.b = b;
}

void Text::SetBackMode(int mode)
{
	m_BackMode = mode;
}

void Text::SetAlign(int align)
{
	m_Align = align;
}

void Text::ClearAll()
{
	memset(m_TextBuffer, 0x00, sizeof(WCHAR) * 25);
}

bool Text::Initialize(int size)
{
	m_Size = size;

	m_OldFont;
	m_hFont = CreateFont(m_Size, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("±¼¸²"));

	return true;
}

void Text::Render(HDC hdc)
{
	m_OldFont = (HFONT)SelectObject(hdc, m_hFont);
	
	SetBkMode(hdc, m_BackMode);

	if (OPAQUE == m_BackMode)
		SetBkColor(hdc, RGB(m_BackColor.r, m_BackColor.g, m_BackColor.b));
	
	int len = wcslen(m_TextBuffer);
	int count = len / m_NewlineCount + 1;

	if (m_NewlineCount == len)
		count = 1;

	SetTextAlign(hdc, m_Align);
	for (int i = 0; i < count; ++i)
	{
		TextOut(hdc, (int)m_StartPos.X, (int)m_StartPos.Y + (m_Size * i), 
			&m_TextBuffer[i * m_NewlineCount], m_NewlineCount);
	}

	SelectObject(hdc, m_OldFont);
}

void Text::Release()
{
	DeleteObject(m_hFont);
}
