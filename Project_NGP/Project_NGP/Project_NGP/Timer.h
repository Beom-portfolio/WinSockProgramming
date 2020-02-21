#pragma once

class Timer
{
public:
	explicit Timer();
	virtual ~Timer();
public:
	const float& Get_TimeDelta() const { return m_TimeDelta; }
public:
	bool Initialize();
public:
	void Compute_Timer();
private:
	LARGE_INTEGER			m_FrameTime;
	LARGE_INTEGER			m_FixTime;
	LARGE_INTEGER			m_LastTime;
	LARGE_INTEGER			m_CpuTick;
private:
	float					m_TimeDelta = 0.f;
};

