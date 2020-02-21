#include "pch.h"
#include "MainScene_1.h"
#include "Spawn.h"

MainScene_1::MainScene_1()
	:Scene()
{
}

MainScene_1::~MainScene_1()
{
	Release();
}

bool MainScene_1::Initialize()
{
	// 픽셀 정보
	LoadPixelCollider("../Data/Back_Collider_Real.bmp", 255, 0, 255);
	
	int count = 0;
	// 몬스터 스폰 정보
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 1; j < 10; ++j)
		{
			if (-1 == m_SpawnPosInfo[i][j])
				break;

			int x = m_SpawnPosInfo[i][j];
			int y = m_SpawnPosInfo[i][0];
			
			Spawn* temp = new Spawn;
			temp->Initialize(MONTYPE_SNAIL, 1s, x, y, 44, 34);
			m_mapSpawn.insert(make_pair(count, temp));
			++count;
		}
	}

	return true;
}

int MainScene_1::Update(const float& TimeDelta)
{
	Scene::Update(TimeDelta);
	for (auto& s : m_mapSpawn)
	{
		s.second->Update(TimeDelta);
	}
	return 0;
}

void MainScene_1::Release()
{
	for (auto& s : m_mapSpawn)
	{
		delete s.second;
		s.second = nullptr;
	}
	m_mapSpawn.clear();
}
