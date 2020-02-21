#pragma once

#include "Include.h"

class Frame;
class FrameManager : public Singleton<FrameManager>
{
public:
	FrameManager();
	virtual ~FrameManager();
public:
	const float Get_FrameTimeDelta(const TCHAR* FrameTag);
public:
	bool Add_Frame(const TCHAR* FrameTag, const float& CallCount);
	bool Permit_Call(const TCHAR* FrameTag, const float& TimeDelta);
private:
	map<const TCHAR*, Frame*>			m_mapFrame;
	typedef map<const TCHAR*, Frame*>	MAPFRAME;
private:
	Frame*	Find_Frame(const TCHAR* FrameTag);
};

