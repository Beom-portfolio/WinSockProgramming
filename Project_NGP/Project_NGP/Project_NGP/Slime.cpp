#include "stdafx.h"
#include "Slime.h"
Slime::Slime()
{
}

Slime::~Slime()
{
	Release();
}

bool Slime::Initialize()
{
	m_Info = GAMEOBJINFO{ 1703, 1222, 100, 100 };
	m_CollideInfo = GAMEOBJINFO{ 10, 20, 50, 60 };
	m_Speed = 0.f;
	m_RenderType = RENDER_OBJ;
	m_Direction = DIR_RIGHT;
	m_SpriteInfo.key = L"slime_idle_right";
	m_SpriteInfo.CurState = Monster_Idle;
	m_SpriteInfo.PreState = Monster_End;
	m_SpriteInfo.SpriteIndex = 0.f;
	m_SpriteInfo.StateIndex = 0;
	//몬스터가 Idle이 되기까지의 시간
	m_ChangeIdleTime = float((rand() % 10) + 5);
	m_CloseIdleTime = 3.f;
	//m_Dir |= 0x00000002;
	return true;
}

int Slime::Update_Input(const float& TimeDelta)
{
#ifdef CLIENT_MODE
	KeyManager* keyManager = GET_MANAGER<KeyManager>();
	//몬스터가 지형의 끝에 도달했는지
	bool OnBulePixel = false;
	//몬스터가 플레이어로부터 공격받았는지
	bool Damaged = false;
	//몬스터가 플레이어의 방향과 일치하는 방향에서 맞았는지
	bool HitBack = false;
	bool Died = false;
	if(m_SpriteInfo.CurState == Monster_Die)
	{
		return 0;
	}
	/*if (true == keyManager->GetKeyState(STATE_PUSH, VK_LCONTROL))
	{
		Damaged = true;
	}*/
	if (true == keyManager->GetKeyState(STATE_PUSH, VK_LCONTROL))
	{
		Died = true;
	}

	if (m_SpriteInfo.CurState == Monster_Idle)
	{
		m_CloseIdleDelta += TimeDelta;
		if (m_CloseIdleTime <= m_CloseIdleDelta)
		{
			m_Direction = DIRECTION(rand() % 2);
 			m_CloseIdleDelta = 0;
			m_SpriteInfo.CurState = Monster_Move;
			m_Speed = 120;
		}
	}
	else
	{
		//Idle 상태가 되기 까지의 시간의 누적치
		if (m_SpriteInfo.CurState == Monster_Hit) {}
		else
			m_IdleTimeDelta += TimeDelta;
	}
	//Idle이 되는 조건
	if (m_ChangeIdleTime <= m_IdleTimeDelta)
	{
		m_SpriteInfo.CurState = Monster_Idle;
		m_Speed = 0;
		//Idle이 되는 시간을 다시 랜덤하게 조절
		m_ChangeIdleTime = float((rand() % 10) + 5);
		m_IdleTimeDelta = 0;
	}
	//몬스터가 지형의 끝에 도달했으면 방향을 바꿔준다.
	if (OnBulePixel == true)
	{
		if (m_Direction == DIR_RIGHT)
		{
			m_Direction = DIR_LEFT;
			m_SpriteInfo.CurState = Monster_Move;
			OnBulePixel = false;
		}
		else if (m_Direction == DIR_LEFT)
		{
			m_Direction = DIR_RIGHT;
			m_SpriteInfo.CurState = Monster_Move;
			OnBulePixel = false;
		}
	}
	//몬스터가 공격 받았을때
	if (Damaged == true)
	{
		//만약 플레어의 방향과 몬스터의 방향이 반대라면 플레이어의 반대 방향으로 뒤돌아본다.
		if (HitBack)
		{
			if (m_Direction == DIR_LEFT)
			{
				m_Direction = DIR_RIGHT;
			}
			else
			{
				m_Direction = DIR_LEFT;
			}
		}
		m_SpriteInfo.CurState = Monster_Hit;
	}

	if (true == Died)
	{
		m_Speed = 0;
		m_SpriteInfo.CurState = Monster_Die;
	}
#endif
	return 0;
}

int Slime::Update(const float& TimeDelta)
{
	m_TimeDelta = TimeDelta;
	if (-1 == GameObject::Update(TimeDelta))
	{
		return -1;
	}

	if (-1 == Update_Input(TimeDelta))
	{
		return -1;
	}

	if (-1 == Update_Position(TimeDelta, m_Direction))
	{
		return -1;
	}

	if (-1 == Update_Sprite(TimeDelta))
	{
		return -1;
	}
	StateChange();
	return 0;
}

int Slime::Update_Position(const float& TimeDelta, const DIRECTION& Direction)
{
	int speed = int(m_Speed * TimeDelta);
	// L
	//if (0x00000001 == (m_Dir & 0x00000001))
	if (m_Direction == DIR_LEFT)
	{
		m_Info.Pos_X -= speed;
	}
	// R
	//if (0x00000002 == (m_Dir & 0x00000002))
	if (m_Direction == DIR_RIGHT)
	{
		m_Info.Pos_X += speed;
	}

#ifdef CLIENT_MODE
	if (m_SpriteInfo.CurState == Monster_Hit)
	{
		m_KnockBackTimeDelta += TimeDelta;
		if (m_KnockBackTime <= m_KnockBackTimeDelta)
		{
			m_SpriteInfo.CurState = Monster_Move;
			m_Speed = 120;
			m_KnockBackTimeDelta = 0;
			return 0;
		}
		else
		{
			//m_Speed = 300;
			if (m_Direction == DIR_LEFT)
			{
				m_Info.Pos_X = Lerp<int, int>(m_Info.Pos_X, m_Info.Pos_X += 10, 5 * TimeDelta);
			}
			else
			{
				m_Info.Pos_X = Lerp<int, int>(m_Info.Pos_X, m_Info.Pos_X -= 10, 5 * TimeDelta);
			}
		}
	}
#endif
	return 0;
}

int Slime::Update_Sprite(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
	switch (m_SpriteInfo.Type)
	{
	case SPRITE_ONCE:
		if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		{
		}
		break;
	case SPRITE_ONCE_END:
		if ((float)m_SpriteInfo.MaxFrame > m_SpriteInfo.SpriteIndex)
		{
			m_SpriteInfo.CurState = m_SpriteInfo.PreState;
		}
		else
		{
			//m_SpriteInfo.CurState = 0;
		}
		break;
	case SPRITE_REPEAT:
		if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		{
			m_SpriteInfo.SpriteIndex = 0.f;
		}
		break;
	case SPRITE_REPEAT_END:
		if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		{
			//m_SpriteInfo.CurState = m_SpriteInfo.PreState;
			m_SpriteInfo.SpriteIndex = 4.f;
		}
		break;
	}

	switch (m_Direction)
	{
	case DIR_LEFT: 
		if (m_SpriteInfo.CurState == Monster_Idle)
			m_SpriteInfo.key = L"slime_idle_left";
		else if (m_SpriteInfo.CurState == Monster_Move)
			m_SpriteInfo.key = L"slime_move_left";
		else if (m_SpriteInfo.CurState == Monster_Hit)
			m_SpriteInfo.key = L"slime_hit_left";
		break;
	case DIR_RIGHT: 
		if (m_SpriteInfo.CurState == Monster_Idle)
			m_SpriteInfo.key = L"slime_idle_right";
		else if (m_SpriteInfo.CurState == Monster_Move)
			m_SpriteInfo.key = L"slime_move_right";
		else if (m_SpriteInfo.CurState == Monster_Hit)
			m_SpriteInfo.key = L"slime_hit_right";
		break;
	}
	if (m_SpriteInfo.CurState == Monster_Die)
	{
		m_SpriteInfo.key = L"slime_die";

		if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		{
			m_isDead = true;
		}
	}
	StateChange();
	//cout << m_SpriteInfo.CurState << endl;
	return 0;
}

void Slime::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageFromIndex((int)m_SpriteInfo.SpriteIndex);

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height
		, hMemDC, 0, 0, m_Info.Size_Width, m_Info.Size_Height, RGB(255, 0, 255));
}

void Slime::Release()
{
}

void Slime::StateChange()
{
	if (m_SpriteInfo.CurState != m_SpriteInfo.PreState)
	{
		m_SpriteInfo.SpriteIndex = 0.f;
		switch (m_SpriteInfo.CurState)
		{
		case Monster_Idle:
			m_SpriteInfo.Type = SPRITE_REPEAT;
			m_SpriteInfo.MaxFrame = 3;
			m_SpriteInfo.Speed = 6.f;
			break;
		case Monster_Move:
			m_SpriteInfo.Type = SPRITE_REPEAT;
			m_SpriteInfo.MaxFrame = 6;
			m_SpriteInfo.Speed = 6.f;
			break;
		case Monster_Hit:
			m_SpriteInfo.Type = SPRITE_REPEAT_END;
			m_SpriteInfo.MaxFrame = 1;
			m_SpriteInfo.Speed = 1.f;
			break;
		case Monster_Die:
			m_SpriteInfo.Type = SPRITE_ONCE;
			m_SpriteInfo.SpriteIndex = 0;
			m_SpriteInfo.MaxFrame = 13;
			m_SpriteInfo.Speed = 6.f;
			break;
		}
	}
	m_SpriteInfo.PreState = m_SpriteInfo.CurState;
}