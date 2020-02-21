#pragma once

class Frame
{
public:
	explicit Frame();
	virtual ~Frame();
public:
	const float& Get_FrameTimeDelta() { return m_FrameTimeDelta; }
public:
	bool Initialize(const float& CallCount);
	bool Permit_Call(const float& TimeDelta);
private:
	float	m_TimeAcc = 0.f;
	float	m_TimePerSec = 0.f;
	float	m_FrameTimeDelta = 0.f;
};

