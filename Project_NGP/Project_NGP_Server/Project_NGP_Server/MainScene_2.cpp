#include "pch.h"
#include "MainScene_2.h"
#include "Spawn.h"

MainScene_2::MainScene_2()
	: Scene()
{
}


MainScene_2::~MainScene_2()
{
	Release();
}

bool MainScene_2::Initialize()
{
	// 픽셀 정보
	LoadPixelCollider("../Data/Back_2_Collider_Real.bmp", 255, 0, 255);

	int count = 0;
	// 몬스터 스폰 정보
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 1; j < 7; ++j)
		{
			if (-1 == m_SpawnPosInfo[i][j])
				break;

			int x = m_SpawnPosInfo[i][j];
			int y = m_SpawnPosInfo[i][0];

			Spawn* temp = new Spawn;

			switch (MONSTERTYPE(rand() % 2 + 2))
			{
			case MONTYPE_BLUEMUSHROOM:
				temp->Initialize(MONTYPE_BLUEMUSHROOM, 5s, x, y);
				break;
			case MONTYPE_GREENMUSHROOM:
				temp->Initialize(MONTYPE_GREENMUSHROOM, 5s, x, y);
				break;
			}

			m_mapSpawn.insert(make_pair(count, temp));
			++count;
		}
	}

	return true;
}

int MainScene_2::Update(const float & TimeDelta)
{
	Scene::Update(TimeDelta);
	for (auto& s : m_mapSpawn)
	{
		s.second->Update(TimeDelta);
	}
	return 0;
}

void MainScene_2::Release()
{
	for (auto& s : m_mapSpawn)
	{
		delete s.second;
		s.second = nullptr;
	}
	m_mapSpawn.clear();
}
