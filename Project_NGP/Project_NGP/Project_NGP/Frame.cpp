#include "stdafx.h"
#include "Frame.h"


Frame::Frame()
{
}


Frame::~Frame()
{
}

bool Frame::Initialize(const float & CallCount)
{
	// 프레임 제한을 걸 기준 TimeDelta
	m_TimePerSec = 1.f / CallCount;

	return true;
}

bool Frame::Permit_Call(const float & TimeDelta)
{
	m_TimeAcc += TimeDelta;
	
	// 누적 시간이 프레임 제한 TimeDelta보다 크거나 같으면 
	// 프레임 제한을 만족하는 TimeDelta이므로 true를 리턴한다.
	if (m_TimePerSec <= m_TimeAcc)
	{
		m_FrameTimeDelta = m_TimeAcc;
		m_TimeAcc = 0.f;
		return true;
	}

	return false;
}
