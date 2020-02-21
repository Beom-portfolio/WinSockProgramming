#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
}


Timer::~Timer()
{
}

bool Timer::Initialize()
{
	QueryPerformanceCounter(&m_FrameTime);	//현재 CPU가 카운팅한 시간을 받아온다.
	
	QueryPerformanceCounter(&m_FixTime);    //초기화
	QueryPerformanceCounter(&m_LastTime);

	QueryPerformanceFrequency(&m_CpuTick);   //CPU 초당 진동수를 얻어온다.

	return true;
}

void Timer::Compute_Timer()
{
	// DeltaTime을 구하는 함수

	// 매 프레임 시간을 측정한다.
	QueryPerformanceCounter(&m_FrameTime);

	// 전 프레임 시간과 뺀 값이 진동수 보다 크다면 -> 뭔가 일시적으로 처리가 안되었다는것
	// 프로세스 부하가 걸렸을 경우 시간이 뒤로 밀리는 것을 방지
	if ((m_FrameTime.QuadPart - m_LastTime.QuadPart) > m_CpuTick.QuadPart)
	{
		// CPU 진동수를 다시 계산
		QueryPerformanceFrequency(&m_CpuTick);

		// 프레임 시간을 갱신한다.
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	// 매 프레임 사이의 시간을 초당 진동수와 나누면 매 프레임당 움직이는 값이 도출된다.
	m_TimeDelta = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;

	m_FixTime = m_FrameTime;
}