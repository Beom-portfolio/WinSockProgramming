#pragma once

class Monster;
// 몬스터 스폰 정보
class Spawn
{
public:
	Spawn();
	virtual ~Spawn();

public:
	Monster* GetMonster() { return m_Monster; }

public:
	virtual bool Initialize(MONSTERTYPE type, seconds spawn_time,
							int pos_x, int pos_y);
	virtual int  Update(const float& TimeDelta);
	virtual void Release();

private:
	Monster* m_Monster = nullptr;
	GAMEOBJINFO m_Info;
	MONSTERTYPE m_Type = MONTYPE_END;

	// 스폰 시간용
	system_clock::time_point m_Start;
	system_clock::time_point m_End;
	seconds					 m_SpawnSec = 0s;
};

