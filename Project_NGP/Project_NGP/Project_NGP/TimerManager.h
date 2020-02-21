#pragma once

#include "Include.h"

class Timer;
class TimerManager : public Singleton<TimerManager>
{
public:
	TimerManager();
	virtual ~TimerManager();
public:
	const float Get_TimeDelta(const TCHAR* TimerTag);
public:
	bool Add_Timer(const TCHAR* TimerTag, Timer* Timer);
	void Compute_Timer(const TCHAR* TimerTag);
private:
	map<const TCHAR*, Timer*>			m_mapTimer;
	typedef map<const TCHAR*, Timer*>	MAPTIMER;
private:
	Timer*	Find_Timer(const TCHAR* TimerTag);
};

