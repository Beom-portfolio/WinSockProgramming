#include "stdafx.h"
#include "Fade.h"

Fade::Fade()
	:GameObject()
{
}

Fade::~Fade()
{
	Release();
}

bool Fade::Initialize()
{
	m_Info = GAMEOBJINFO{ WINSIZE_X / 2, WINSIZE_Y / 2, 1024, 1024 };
	m_isNoScroll = true;
	m_RenderType = RENDER_UI_3;
	m_Speed = 700;
	return true;
}

int Fade::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	if (true == m_FadeInCheck)
	{
		m_Alpha += m_Speed * TimeDelta;

		if (m_Alpha >= 255.f)
		{
			m_WaitAcc += TimeDelta;
			m_Alpha = 255.f;

			if (1.f <= m_WaitAcc)
			{
				// 씬이 바뀜을 서버에 알린다.
				GET_MANAGER<NetworkManager>()->SendGoNextSceneInfo(
					m_NextSceneInfo, GET_MANAGER<SceneManager>()->GetCurrentSceneState());
				GET_MANAGER<SceneManager>()->ChangeSceneState(m_NextSceneInfo);
				m_FadeInCheck = false;
				m_WaitAcc = 0.f;
			}
		}
	}
	else
	{
		m_Alpha -= m_Speed / 2.f * TimeDelta;

		if (m_Alpha <= 0.f)
			m_Alpha = 0.f;
	}

	//cout << m_Alpha << endl;

	/*KeyManager* keyManager = GET_MANAGER<KeyManager>();
	if (true == keyManager->GetKeyState(STATE_DOWN, VK_F2))
	{
		if (false == m_FadeInCheck)
			m_FadeInCheck = true;
		else
			m_FadeInCheck = false;
	}*/

	return 0;
}

void Fade::Render(HDC hdc)
{
	if (0.f == m_Alpha)
		return;

	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"fade")->GetGdiImageDefault();

	BLENDFUNCTION	_bf;
	_bf.SourceConstantAlpha = (int)m_Alpha; // 투명도
	_bf.AlphaFormat = AC_SRC_OVER;
	_bf.BlendOp = 0;
	_bf.BlendFlags = 0;

	GdiAlphaBlend(hdc, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height,
		hMemDC, 0, 0, m_Info.Size_Width, m_Info.Size_Height, _bf);
}

void Fade::Release()
{
}
