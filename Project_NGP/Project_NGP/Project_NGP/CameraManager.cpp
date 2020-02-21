#include "stdafx.h"
#include "CameraManager.h"

#include "GameObject.h"

CameraManager::CameraManager()
{
	ZeroMemory(&m_Pos, sizeof(POSITION));
	ZeroMemory(&m_Pos, sizeof(RESOLUTION));
	ZeroMemory(&m_OldDestPos, sizeof(POSITION));
	ZeroMemory(&m_DestPos, sizeof(POSITION));

	// 카메라 움직임 기준을 정중앙으로 놓는다.
	m_Offset.X = ((float)WINSIZE_X / 2);
	m_Offset.Y = ((float)WINSIZE_Y / 2);
}

CameraManager::~CameraManager()
{
	Release();
}

void CameraManager::SetPos(int x, int y)
{
	if (nullptr == m_Target)
		return;

	m_Pos.X = -float(x - ((int)WINSIZE_X / 2));
	m_Pos.Y = -float(y - ((int)WINSIZE_Y / 2));
}

void CameraManager::SetTarget(GameObject * target)
{
	m_Target = target;
	
	// 타겟을 정함과 동시에 타겟의 위치를 미리 Set
	GAMEOBJINFO targetInfo = m_Target->GetInfo();
	SetPos(targetInfo.Pos_X, targetInfo.Pos_Y);
}

void CameraManager::SetResolution(int x, int y)
{
	// 백그라운드 텍스쳐의 크기이다.
	m_Resolution.X = (float)x;
	m_Resolution.Y = (float)y;
}

void CameraManager::SetOffset(int x, int y)
{
	m_Offset.X = ((float)WINSIZE_X / 2) - (float)x;
	m_Offset.Y = ((float)WINSIZE_Y / 2) - (float)y;
}

int CameraManager::Update(const float & TimeDelta)
{
	if (nullptr != m_Target)
	{
		if (true == m_Refresh) m_Time += TimeDelta * 1.f;
		else m_Time -= TimeDelta * 1.f;

		if (m_Time > 1.f) m_Time = 1.f;
		else if (m_Time <= 0.f) m_Time = 0.f;

		GAMEOBJINFO targetInfo = m_Target->GetInfo();

		m_Refresh = false;

		// X축 카메라 움직임을 포착하면
		if ((targetInfo.Pos_X + (int)m_Pos.X + (int)m_Offset.X) >= (int)WINSIZE_X ||
			(targetInfo.Pos_X + (int)m_Pos.X - (int)m_Offset.X) <= 0 )
		{
			m_OldDestPos.X = -float(targetInfo.Pos_X - ((int)WINSIZE_X / 2));
			// 이전 프레임의 위치와 변화가 없는 경우 업데이트 하지 않는다.
			// 왜냐면 움직이는 상황이 아니기 때문에
			if ((int)m_OldDestPos.X != (int)m_DestPos.X)
			{
				m_DestPos.X = -float(targetInfo.Pos_X - ((int)WINSIZE_X / 2));
				m_Refresh = true;
			}
		}

		// Y축 카메라 움직임을 포착하면
		if ((targetInfo.Pos_Y + (int)m_Pos.Y + (int)m_Offset.Y) >= (int)WINSIZE_Y ||
			(targetInfo.Pos_Y + (int)m_Pos.Y - (int)m_Offset.Y) <= 0 )
		{
			m_OldDestPos.Y = -float(targetInfo.Pos_Y - ((int)WINSIZE_Y / 2));
			if ((int)m_OldDestPos.Y != (int)m_DestPos.Y)
			{
				m_DestPos.Y = -float(targetInfo.Pos_Y - ((int)WINSIZE_Y / 2));
				m_Refresh = true;
			}
		}

		// 카메라의 움직임 속도는 보간을 해준다.
		float m_speed = Lerp<float, float>(10.f, m_Target->GetSpeed(), m_Time);

		// 가야하는 Direction 벡터를 구하여 그 방향으로 가도록 계산한다.
		POSITION Dir = m_DestPos - m_Pos;
		float Length = sqrt(Dir.X * Dir.X + Dir.Y * Dir.Y);
		POSITION totalDir = POSITION{ 0.f, 0.f };

		if (0.f != Length)
		{
			totalDir.X = Dir.X / Length;
			totalDir.Y = Dir.Y / Length;
		}

		//printf("Length : %f\n", Length);
		//printf("DirX : %f,  DirY : %f\n", Dir.X, Dir.Y);
		
		// 정중앙으로 놓기위해 카메라 좌표를 움직여준다.
		if (targetInfo.Pos_X + (int)m_Pos.X > ((int)WINSIZE_X / 2) ||
			targetInfo.Pos_X + (int)m_Pos.X < ((int)WINSIZE_X / 2))
		{
			//float temp = totalDir.X * m_speed * TimeDelta;

			m_Pos.X += totalDir.X * m_speed * TimeDelta;
		}

		if (targetInfo.Pos_Y + (int)m_Pos.Y > ((int)WINSIZE_Y / 2) ||
			targetInfo.Pos_Y + (int)m_Pos.Y < ((int)WINSIZE_Y / 2))
		{
			m_Pos.Y += totalDir.Y * m_speed * TimeDelta;
		}

		// 백그라운드의 크기를 카메라가 벗어나려고 하면 카메라 움직임을 정지 시킨다.
		if (0.f <= m_Pos.X) m_Pos.X = 0.f;
		if (0.f <= m_Pos.Y) m_Pos.Y = 0.f;
		if (-m_Resolution.X > m_Pos.X - (int)WINSIZE_X) m_Pos.X = -float(m_Resolution.X - (int)WINSIZE_X);
		if (-m_Resolution.Y > m_Pos.Y - (int)WINSIZE_Y) m_Pos.Y = -float(m_Resolution.Y - (int)WINSIZE_Y);

		// 카메라 위치와 목표 위치의 사이의 길이가 너무 가까운 경우 
		// 카메라의 속도를 확 줄인다.
		if (Length < 30.f)
		{
			//m_DestPos = m_Pos;
			m_Time = 0.f;
		}

	}

	return 0;
}

void CameraManager::Release()
{
	m_Target = nullptr;
}
