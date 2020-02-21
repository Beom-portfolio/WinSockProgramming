#include "pch.h"
#include "Monster.h"

Monster::Monster()
	: GameObject()
{
}

Monster::~Monster()
{
	Release();
}

void Monster::Hit(int target, int damage)
{
	if (Monster_Hit != m_State &&
		0 < m_hp)
	{
		m_hp -= damage;
		if (0 >= m_hp)
		{
			m_Speed = 0;
			m_State = Monster_Die;
			return;
		}
		m_State = Monster_Hit;

		if (DIR_LEFT == m_Direction)
		{
			if (g_mapClient[target]->player_info.pos_x >= m_Info.Pos_X)
				m_Direction = DIR_RIGHT;
		}
		else
		{
			if (g_mapClient[target]->player_info.pos_x < m_Info.Pos_X)
				m_Direction = DIR_LEFT;
		}
	}

	target_id = target;
}

bool Monster::Initialize(int pos_x, int pos_y)
{
	GameObject::Initialize(pos_x, pos_y);

	m_ChangeIdleTime = float((rand() % 10) + 5);
	m_State = Monster_Idle;

	return true;
}

int Monster::Update(const float& TimeDelta)
{
	GameObject::Update(TimeDelta);

	UpdateAI(TimeDelta);
	UpdatePosition(TimeDelta);

	return 0;
}

void Monster::Release()
{
}

void Monster::CollisionPixelPart(DIRECTION dir)
{
	switch (dir)
	{
	case DIR_BOTTOM:
		m_GravitySpeed = 0.f;
		m_GravityAcc = 0.f;
		m_FallCheck = false;
		break;
	}
}

void Monster::UpdateAI(const float& TimeDelta)
{
	if (Monster_Die == m_State)
	{
		m_DeadAcc += TimeDelta;
		
		if (m_DeadAcc > 1.f)
			m_isDead = true;
		
		return;
	}

	if (Monster_Idle == m_State)
	{
		m_CloseIdleAcc += TimeDelta;
		if (3.f <= m_CloseIdleAcc)
		{
			m_Direction = DIRECTION(rand() % 2);
			m_CloseIdleAcc = 0.f;
			m_State = Monster_Move;
			//m_Speed = 100;
		}
	}
	else
	{
		//Idle 상태가 되기 까지의 시간의 누적치
		if (Monster_Hit == m_State) {}
		else
			m_IdleAcc += TimeDelta;
	}

	// 플레이어를 따라다닌다.
	if (Monster_Move == m_State &&
		false == m_TurnCheck)
	{
		if (-1 != target_id)
		{
			m_FollowAcc += TimeDelta;

			// 플레이어가 없으면
			if (g_mapClient.end() == g_mapClient.find(target_id))
			{ 
				target_id = -1;
				m_FollowAcc = 0.f;
				return;
			}

			if (2.f <= m_FollowAcc)
			{
				if (g_mapClient[target_id]->player_info.pos_x >= m_Info.Pos_X)
					m_Direction = DIR_RIGHT;

				if (g_mapClient[target_id]->player_info.pos_x < m_Info.Pos_X)
					m_Direction = DIR_LEFT;

				m_FollowAcc = 0.f;
			}
		}
	}

	//Idle이 되는 조건
	if (m_ChangeIdleTime <= m_IdleAcc)
	{
		m_State = Monster_Idle;
		m_Speed = 0;
		//Idle이 되는 시간을 다시 랜덤하게 조절
		m_ChangeIdleTime = float((rand() % 10) + 5);
		m_IdleAcc = 0;
	}

	//몬스터가 지형의 끝에 도달했으면 방향을 바꿔준다.
	m_TurnAcc += TimeDelta;
	if (1.f <= m_TurnAcc)
	{
		if (true == m_TurnCheck)
		{
			if (m_Direction == DIR_RIGHT)
			{
				m_Direction = DIR_LEFT;
				m_State = Monster_Move;
				m_TurnCheck = false;
				m_TurnAcc = 0.f;
			}
			else if (m_Direction == DIR_LEFT)
			{
				m_Direction = DIR_RIGHT;
				m_State = Monster_Move;
				m_TurnCheck = false;
				m_TurnAcc = 0.f;
			}
		}
	}

}

void Monster::UpdatePosition(const float& TimeDelta)
{
	int speed = int(m_Speed * TimeDelta);

	/*if (0.f != m_Speed)
		m_FallCheck = true;*/

	if (m_Direction == DIR_LEFT)
	{
		m_Info.Pos_X -= speed;
	}

	if (m_Direction == DIR_RIGHT)
	{
		m_Info.Pos_X += speed;
	}

	if (m_State == Monster_Hit)
	{
		m_KnockBackAcc += TimeDelta;
		if (0.2f <= m_KnockBackAcc)
		{
			m_State = Monster_Move;
			m_Speed = 100;
			m_KnockBackAcc = 0.f;
		}
		else
		{
			if (m_Direction == DIR_LEFT)
			{
				m_Info.Pos_X = Lerp<int, int>(m_Info.Pos_X, m_Info.Pos_X += 5, 5.f * TimeDelta);
			}
			else
			{
				m_Info.Pos_X = Lerp<int, int>(m_Info.Pos_X, m_Info.Pos_X -= 5, 5.f * TimeDelta);
			}
		}
	}
}
