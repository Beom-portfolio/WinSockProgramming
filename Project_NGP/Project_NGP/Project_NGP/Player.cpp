#include "stdafx.h"
#include "Player.h"
#include "Portal.h"
#include "Fade.h"
#include "Text.h"
#include "Chat_Box.h"
#include "Chat.h"

Player::Player()
	: GameObject()
{
}

Player::~Player()
{
	Release();
}

bool Player::Initialize()
{
	m_Info = GAMEOBJINFO{ 800, 600, 200, 200 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 40, 60 };
	m_Speed = 200.f;
	m_RenderType = RENDER_OBJ;

	m_Direction = DIR_LEFT;
	m_SpriteInfo.key = L"player_left";
	m_SpriteInfo.CurState = Idle;
	m_SpriteInfo.PreState = End;
	m_SpriteInfo.SpriteIndex = 0.f;
	m_SpriteInfo.StateIndex = 0;

	m_IdText = new Text;
	m_IdText->Initialize(20);
	m_IdText->SetBackColor(255, 255, 0);
	m_IdText->SetBackMode(OPAQUE);
	m_IdText->SetAlign(TA_CENTER);

	GameObject* chatBox = AbstractFactory<Chat_Box>::CreateObj();
	chatBox->SetFollowedObj(this);
	GET_MANAGER<ObjectManager>()->AddObject(L"chat_box", chatBox, OBJ_UI);
	m_ChatBox = dynamic_cast<Chat_Box*>(chatBox);

	return true;
}

int Player::Update(const float& TimeDelta)
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

	if (-1 == Update_Skill(TimeDelta))
	{
		return -1;
	}

	StateChange();
	return 0;
}

void Player::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_Width, m_Info.Size_Height,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_Width,
		m_SpriteInfo.StateIndex * m_Info.Size_Height,
		m_Info.Size_Width, m_Info.Size_Height, RGB(255, 0, 255));

	if (nullptr != m_IdText)
	{
		m_IdText->SetPosition(m_Rect.left + (m_Info.Size_Width / 2)
							, m_Rect.top + 135);
		m_IdText->Render(hdc);
	}

	//std::cout << m_Info.Pos_X << ", " << m_Info.Pos_Y << std::endl;
}

void Player::Release()
{
	if (nullptr != m_IdText)
	{
		delete m_IdText;
		m_IdText = nullptr;
	}
}

void Player::CollisionPixelPart(DIRECTION dir)
{
	switch (dir)
	{
	case DIR_BOTTOM:
		m_GravitySpeed = 0.f;
		m_GravityAcc = 0.f;
		m_fallCheck = false;
		m_SpriteInfo.CurState = Idle;
		break;
	}
}

void Player::CollisionActivate(GameObject* collideTarget)
{
	switch (collideTarget->GetObjectType())
	{
	case OBJ_PORTAL:
		m_isReadyGoNext = true;
		m_NextSceneInfo = dynamic_cast<Portal*>(collideTarget)->GetSceneInfo();
		break;
	}
}

void Player::CollisionDeactivate(GameObject* collideTarget)
{
	switch (collideTarget->GetObjectType())
	{
	case OBJ_PORTAL:
		m_isReadyGoNext = false;
		break;
	}
}

void Player::SetIdToText(int id)
{
	if (nullptr != m_IdText)
	{
		wstring tmpWString = to_wstring(id);
		m_IdText->SetNewlineCount(tmpWString.size());
		m_IdText->SetText(tmpWString.c_str());
	}
}

void Player::SetChatBox(const WCHAR* chat_buffer)
{
	if (nullptr != m_ChatBox)
	{
		m_ChatBox->SetChatBox(chat_buffer);
	}
}

int Player::Update_Input(const float& TimeDelta)
{
	if (true == m_isOther)
		return 0;

	m_Dir = 0;
	KeyManager* keyManager = GET_MANAGER<KeyManager>();

	// 채팅창을 킨다.
	if (true == m_ChatOn)
	{
		keyManager->SetRunning(true);
		m_ChatAcc += TimeDelta;

		if (m_ChatAcc > 0.1f &&
			true == keyManager->GetKeyState(STATE_DOWN, VK_RETURN))
		{
			GameObject* pObj = GET_MANAGER<ObjectManager>()->GetObjFromTag(L"chat", OBJ_UI);
			m_ChatBox->SetChatBox(dynamic_cast<Chat*>(pObj)->GetChatBuffer());
			dynamic_cast<Chat*>(pObj)->SetActivate(false);

			m_ChatOn = false;
			m_ChatAcc = 0.f;
		}

		return 0;
	}

	if (true == keyManager->GetKeyState(STATE_PUSH, VK_LEFT))
	{
		m_Dir |= 0x00000001;
		m_Direction = DIR_LEFT;

		if (false == m_fallCheck)
			m_SpriteInfo.CurState = Walk;
	}

	if (true == keyManager->GetKeyState(STATE_PUSH, VK_RIGHT))
	{
		m_Dir |= 0x00000002;
		m_Direction = DIR_RIGHT;

		if (false == m_fallCheck)
			m_SpriteInfo.CurState = Walk;
	}

	if (true == keyManager->GetKeyState(STATE_DOWN, VK_UP))
	{
		m_Dir |= 0x00000004;
		if (true == m_isReadyGoNext &&
			SCENE_END != m_NextSceneInfo)
		{
			Fade* fade = dynamic_cast<Fade*>
				(GET_MANAGER<ObjectManager>()->GetObjFromTag(L"fade", OBJ_UI));
			fade->SetNextSceneInfo(m_NextSceneInfo);
			fade->SetFade(true);

			m_isReadyGoNext = false;
			m_NextSceneInfo = SCENE_END;
		}
	}

	if (true == keyManager->GetKeyState(STATE_PUSH, VK_DOWN))
	{
		m_Dir |= 0x00000008;
		m_SpriteInfo.CurState = Crouch;
	}

	if (true == keyManager->GetKeyState(STATE_DOWN, VK_SPACE))
	{
		// 점프
		m_SpriteInfo.CurState = Jump;
		m_GravitySpeed = -300.f;
		m_GravityAcc = 0.f;
		m_fallCheck = true;
	}

	if (true == keyManager->GetKeyState(STATE_PUSH, VK_LCONTROL))
	{
		int r = rand() % 2;
		if (0 == r)
		{
			m_SpriteInfo.CurState = Att_1;
		}
		else
		{
			m_SpriteInfo.CurState = Att_2;
		}
	}

	if (true == keyManager->GetKeyState(STATE_PUSH, VK_LSHIFT))
	{
		m_SpriteInfo.CurState = Att_3;
	}

	if (m_ChatOn == false &&
		true == keyManager->GetKeyState(STATE_DOWN, VK_RETURN))
	{
		GameObject* pObj = GET_MANAGER<ObjectManager>()->GetObjFromTag(L"chat", OBJ_UI);
		dynamic_cast<Chat*>(pObj)->SetActivate(true);

		keyManager->SetRunning(true);
		m_ChatOn = true;
		m_ChatAcc = 0.f;
	}

	if (false == m_fallCheck &&
		false == keyManager->GetKeyState(STATE_PUSH, VK_LEFT) &&
		false == keyManager->GetKeyState(STATE_PUSH, VK_RIGHT) &&
		false == keyManager->GetKeyState(STATE_PUSH, VK_LCONTROL)&&
		false == keyManager->GetKeyState(STATE_PUSH, VK_LSHIFT))
	{
		m_SpriteInfo.CurState = Idle;
	}
	return 0;
}

int Player::Update_Position(const float& TimeDelta, const DIRECTION& Direction)
{
	if (true == m_isOther)
		return 0;

	int speed = int(m_Speed * TimeDelta);

	// L
	if (0x00000001 == (m_Dir & 0x00000001))
	{
		m_Info.Pos_X -= speed;
	}

	// R
	if (0x00000002 == (m_Dir & 0x00000002))
	{
		m_Info.Pos_X += speed;
	}

	// U
	if (0x00000004 == (m_Dir & 0x00000004))
	{
		// m_Info.Pos_Y -= speed * 2;
	}

	// D
	if (0x00000008 == (m_Dir & 0x00000008))
	{
		// m_Info.Pos_Y += speed;
	}

	// 중력
	m_Info.Pos_Y += int(m_GravitySpeed * TimeDelta);
	m_GravitySpeed += m_GravityAcc * TimeDelta;

	if (true == m_fallCheck)
	{
		if (1000.f > m_GravityAcc)
			m_GravityAcc += 9.8f * 10.f;
	}

	//printf("X : %d  Y : %d\n", m_Info.Pos_X, m_Info.Pos_Y + (m_CollideInfo.Size_Height / 2));

	return 0;
}

int Player::Update_Skill(const float& TimeDelta)
{
	if (Att_1 == m_SpriteInfo.CurState ||
		Att_2 == m_SpriteInfo.CurState)
	{
		if (false == m_OnceCheck &&
			1.f <= m_SpriteInfo.SpriteIndex)
		{
			GameObject* effect = AbstractFactory<NomalAttack>::CreateObj();
			dynamic_cast<CEffect*>(effect)->SetEffectSpawn(m_Info.Pos_X, m_Info.Pos_Y, m_Direction, true);
			GET_MANAGER<ObjectManager>()->AddObject(L"effect", effect, OBJ_EFFECT);
			m_OnceCheck = true;
		}
	}

	else if (Att_3 == m_SpriteInfo.CurState)
	{
		if (false == m_OnceCheck &&
			1.f <= m_SpriteInfo.SpriteIndex)
		{
			GameObject* skill1 = AbstractFactory<SmashAttack>::CreateObj();
			if(DIR_LEFT == m_Direction)
				dynamic_cast<CEffect*>(skill1)->SetEffectSpawn(m_Info.Pos_X - 100, m_Info.Pos_Y - 50, m_Direction, true);
			else
				dynamic_cast<CEffect*>(skill1)->SetEffectSpawn(m_Info.Pos_X + 100, m_Info.Pos_Y - 50, m_Direction, true);
			GET_MANAGER<ObjectManager>()->AddObject(L"skill1", skill1, OBJ_EFFECT);
			m_OnceCheck = true;
		}
	}
	return 0;
}

int Player::Update_Sprite(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;

	switch (m_SpriteInfo.Type)
	{
	case SPRITE_ONCE:
		if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		{
			m_SpriteInfo.CurState = 0;
		}
		break;
	case SPRITE_ONCE_END:
		if ((float)m_SpriteInfo.MaxFrame > m_SpriteInfo.SpriteIndex)
		{
			m_SpriteInfo.CurState = m_SpriteInfo.PreState;
		}
		else
		{
			m_SpriteInfo.CurState = 0;
			m_OnceCheck = false;
		}
		break;
	case SPRITE_REPEAT:
		if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		{
			m_SpriteInfo.SpriteIndex = 0.f;
		}
		break;
	}

	switch (m_Direction)
	{
	case DIR_LEFT: m_SpriteInfo.key = L"player_left"; break;
	case DIR_RIGHT: m_SpriteInfo.key = L"player_right"; break;
	}

	return 0;
}

void Player::StateChange()
{
	if (m_SpriteInfo.CurState != m_SpriteInfo.PreState)
	{
		m_SpriteInfo.SpriteIndex = 0.f;
		switch (m_SpriteInfo.CurState)
		{
		case Idle:
			m_SpriteInfo.Type = SPRITE_REPEAT;
			m_SpriteInfo.StateIndex = 0;
			m_SpriteInfo.MaxFrame = 5;
			m_SpriteInfo.Speed = 2.f;
			break;
		case Walk:
			m_SpriteInfo.Type = SPRITE_REPEAT;
			m_SpriteInfo.StateIndex = 2;
			m_SpriteInfo.MaxFrame = 4;
			m_SpriteInfo.Speed = 6.f;
			break;
		case Jump:
			m_SpriteInfo.Type = SPRITE_REPEAT;
			m_SpriteInfo.StateIndex = 5;
			m_SpriteInfo.MaxFrame = 1;
			m_SpriteInfo.Speed = 1.f;
			break;
		case Crouch:
			m_SpriteInfo.Type = SPRITE_REPEAT;
			m_SpriteInfo.StateIndex = 11;
			m_SpriteInfo.MaxFrame = 1;
			m_SpriteInfo.Speed = 1.f;
			break;
		case Att_1:
			m_SpriteInfo.Type = SPRITE_ONCE_END;
			m_SpriteInfo.StateIndex = 14;
			m_SpriteInfo.MaxFrame = 3;
			m_SpriteInfo.Speed = 5.f;
			break;
		case Att_2:
			m_SpriteInfo.Type = SPRITE_ONCE_END;
			m_SpriteInfo.StateIndex = 15;
			m_SpriteInfo.MaxFrame = 3;
			m_SpriteInfo.Speed = 5.f;
			break;
		case Att_3:
			m_SpriteInfo.Type = SPRITE_ONCE_END;
			m_SpriteInfo.StateIndex = 15;
			m_SpriteInfo.MaxFrame = 3;
			m_SpriteInfo.Speed = 5.f;
			break;
		}
	}

	m_SpriteInfo.PreState = m_SpriteInfo.CurState;
}
