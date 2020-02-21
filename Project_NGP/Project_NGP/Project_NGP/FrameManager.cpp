#include "stdafx.h"
#include "FrameManager.h"

#include "Frame.h"


FrameManager::FrameManager()
{
}


FrameManager::~FrameManager()
{
	for (auto& frame : m_mapFrame)
	{
		delete frame.second;
		frame.second = nullptr;
	}
	m_mapFrame.clear();
}

const float FrameManager::Get_FrameTimeDelta(const TCHAR * FrameTag)
{
	Frame *pFrame = Find_Frame(FrameTag);

	if (nullptr == pFrame)
		return 0.f;

	return pFrame->Get_FrameTimeDelta();
}

bool FrameManager::Add_Frame(const TCHAR * FrameTag, const float & CallCount)
{
	// 기존에 Frame정보가 있는 경우 넣지 않는다.
	if(nullptr != Find_Frame(FrameTag))
		return false;

	Frame *pFrame = new Frame;

	if (false == pFrame->Initialize(CallCount))
	{
		delete pFrame;
		pFrame = nullptr;
		return false;
	}

	m_mapFrame.emplace(MAPFRAME::value_type(FrameTag, pFrame));

	return true;
}

bool FrameManager::Permit_Call(const TCHAR * FrameTag, const float & TimeDelta)
{
	Frame *pFrame = Find_Frame(FrameTag);

	if (nullptr == pFrame)
		return false;

	return pFrame->Permit_Call(TimeDelta);
}

Frame * FrameManager::Find_Frame(const TCHAR * FrameTag)
{
	MAPFRAME::const_iterator iter = m_mapFrame.find(FrameTag);

	if(m_mapFrame.end() == iter)
		return nullptr;

	return iter->second;
}
