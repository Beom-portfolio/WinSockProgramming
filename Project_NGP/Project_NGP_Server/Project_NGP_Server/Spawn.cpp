#include "pch.h"
#include "Spawn.h"
#include "Monster.h"
#include "BlueSnail.h"
#include "Slime.h"
#include "BlueMushroom.h"
#include "GreenMushroom.h"

Spawn::Spawn()
{
	ZeroMemory(&m_Info, sizeof(GAMEOBJINFO));
}

Spawn::~Spawn()
{
	Release();
}

bool Spawn::Initialize(MONSTERTYPE type, seconds spawn_time,
	int pos_x, int pos_y)
{
	m_Type = type;
	m_Info.Pos_X = pos_x;
	m_Info.Pos_Y = pos_y;
	m_Start = system_clock::now();
	m_SpawnSec = spawn_time;

	return true;
}

int Spawn::Update(const float& TimeDelta)
{
	// 스폰 시간이 되었을때 스폰한다.
	if (nullptr == m_Monster)
	{
		m_End = system_clock::now();
		
		if (m_SpawnSec <= duration_cast<seconds>(m_End - m_Start))
		{
			switch (m_Type)
			{
			case MONTYPE_SNAIL:
				m_Monster = new BlueSnail;
				break;
			case MONTYPE_SLIME:
				m_Monster = new Slime;
				break;
			case MONTYPE_BLUEMUSHROOM:
				m_Monster = new BlueMushroom;
				break;
			case MONTYPE_GREENMUSHROOM:
				m_Monster = new GreenMushroom;
				break;
			}
			m_Monster->Initialize(m_Info.Pos_X, m_Info.Pos_Y);
		}
	}
	else
	{
		m_Monster->Update(TimeDelta);

		// isDead가 true이면 죽은것이므로 사라지도록 한다.
		if (true == m_Monster->GetState())
		{
			delete m_Monster;
			m_Monster = nullptr;
			m_Start = system_clock::now();
		}
	}
	return 0;
}

void Spawn::Release()
{
	if (m_Monster)
	{
		delete m_Monster;
		m_Monster = nullptr;
	}
}
