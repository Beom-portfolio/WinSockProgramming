#pragma once

class GameObject;

class CameraManager : public Singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

public:
	void SetPos(int x, int y);

public:
	const POSITION& GetPos() { return m_Pos; }
	const RESOLUTION& GetResolution() { return m_Resolution; }

public:
	void SetTarget(GameObject * target);
	void SetResolution(int x, int y);
	void SetOffset(int x, int y);

public:
	int  Update(const float& TimeDelta);
	void Release();

private:
	GameObject* m_Target = nullptr;
	POSITION	m_Pos;
	POSITION	m_OldDestPos;
	POSITION	m_DestPos;

	RESOLUTION	m_Resolution;
	OFFSET		m_Offset;
	
	float		m_Time = 0.f;

	bool		m_Refresh = false;
};

