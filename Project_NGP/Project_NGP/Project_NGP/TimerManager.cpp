#include "stdafx.h"
#include "TimerManager.h"

#include "Timer.h"

TimerManager::TimerManager()
{
}


TimerManager::~TimerManager()
{
	for (auto& timer : m_mapTimer)
	{
		delete timer.second;
		timer.second = nullptr;
	}
	m_mapTimer.clear();
}

const float TimerManager::Get_TimeDelta(const TCHAR * TimerTag)
{
	Timer *pTimer = nullptr;

	pTimer = Find_Timer(TimerTag);

	if (nullptr == pTimer)
		return 0.f;

	return pTimer->Get_TimeDelta();
}

bool TimerManager::Add_Timer(const TCHAR * TimerTag, Timer * Timer)
{
	if (nullptr != Find_Timer(TimerTag))
		return false;

	m_mapTimer.emplace(MAPTIMER::value_type(TimerTag, Timer));

	return true;
}

void TimerManager::Compute_Timer(const TCHAR * TimerTag)
{
	Timer *pTimer = nullptr;

	pTimer = Find_Timer(TimerTag);

	if (nullptr == pTimer)
		return;

	pTimer->Compute_Timer();
}

Timer * TimerManager::Find_Timer(const TCHAR * TimerTag)
{
	MAPTIMER::const_iterator iter = m_mapTimer.find(TimerTag);

	if (m_mapTimer.end() == iter)
		return nullptr;

	return iter->second;
}
