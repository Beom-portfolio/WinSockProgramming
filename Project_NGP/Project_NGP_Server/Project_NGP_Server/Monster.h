#pragma once
#include "GameObject.h"

class Monster 
	:public GameObject
{
public:
	Monster();
	virtual ~Monster();

public:
	const MONSTERTYPE& GetMonType() { return m_Type; }
	const MonsterState& GetMonState() { return m_State; }

public:
	void SetTurnCheck(bool check) { m_TurnCheck = check; }
	
public:
	void Hit(int src_id, int damage);

public:
	virtual bool Initialize(int pos_x, int pos_y);
	virtual int  Update(const float& TimeDelta);
	virtual void Release();
	virtual void CollisionPixelPart(DIRECTION dir);

protected:
	virtual void UpdateAI(const float& TimeDelta);
	virtual void UpdatePosition(const float& TimeDelta);

protected:
	MONSTERTYPE m_Type = MONTYPE_END;
	MonsterState m_State = Monster_End;
	int target_id = -1;

	float m_CloseIdleAcc = 0.f;
	float m_IdleAcc = 0.f;
	float m_ChangeIdleTime = 0.f;
	float m_TurnAcc = 0.f;
	bool m_TurnCheck = false;
	float m_KnockBackAcc = 0.f;
	float m_DeadAcc = 0.f;

	int m_hp = 0;

	float m_FollowAcc = 0.f;
};