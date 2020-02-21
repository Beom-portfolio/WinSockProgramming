#pragma once

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	const GAMEOBJINFO&	GetInfo()		{ return m_Info; }
	const bool&			GetState()		{ return m_isDead; }
	const float&		GetGravity()	{ return m_GravitySpeed; }
	const DIRECTION&	GetDirection()	{ return m_Direction; }
public:
	void SetPosition(int posX, int posY);
	void SetFall(bool fall);

public:
	virtual bool Initialize(int pos_x, int pos_y);
	virtual int  Update(const float& TimeDelta);
	virtual void Release() PURE;
	virtual void CollisionPixelPart(DIRECTION dir);

protected:
	GAMEOBJINFO m_Info;
	DIRECTION	m_Direction = DIR_END;
	DWORD		m_Dir = 0;

	float		m_Speed = 0.f;
	float		m_GravitySpeed = 0.f;
	float		m_GravityAcc = 9.8f;

	bool		m_FallCheck = true;
	bool		m_isDead = false;
};