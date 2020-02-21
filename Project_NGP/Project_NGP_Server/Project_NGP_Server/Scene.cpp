#include "pch.h"
#include "Scene.h"
#include "Spawn.h"
#include "Monster.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	Release();
}

int Scene::Update(const float& TimeDelta)
{
	// 픽셀 충돌
	if (nullptr == m_PixelInfo)
		return -1;

	for (auto& Src : m_mapSpawn)
	{
		Monster* mon = Src.second->GetMonster();

		if (nullptr == mon)
			continue;

		GAMEOBJINFO info = mon->GetInfo();
		//GAMEOBJINFO collideInfo = Src.second->GetCollideInfo();
		RECT rc;
		rc.bottom = info.Pos_Y + (info.Size_Height / 2);

		int addr;

		// 아래 
		addr = rc.bottom * m_PixelInfo->Width + info.Pos_X;
		if (addr < 0 || addr >= (int)m_PixelInfo->vecPixel.size()) 
			return -1;

		// 지형 충돌 픽셀일때 
		if (m_PixelInfo->vecPixel[addr].r == m_PixelInfo->CollPixel.r &&
			m_PixelInfo->vecPixel[addr].g == m_PixelInfo->CollPixel.g &&
			m_PixelInfo->vecPixel[addr].b == m_PixelInfo->CollPixel.b)
		{
			// 지형 높이값 만큼 게임 오브젝트를 올려준다.
			int Y = rc.bottom;
			while (Y > 0)
			{
				--Y;
				addr = Y * m_PixelInfo->Width + info.Pos_X;

				if (m_PixelInfo->vecPixel[addr].r == m_PixelInfo->CollPixel.r &&
					m_PixelInfo->vecPixel[addr].g == m_PixelInfo->CollPixel.g &&
					m_PixelInfo->vecPixel[addr].b == m_PixelInfo->CollPixel.b)
				{
					continue;
				}
				else
				{
					if (0 < mon->GetGravity())
					{
						mon->SetPosition(info.Pos_X, Y - (info.Size_Height / 2));
						mon->CollisionPixelPart(DIR_BOTTOM);
					}
					break;
				}
			}
		}
		else
		{
			// 떨림 방지
			// 밑에 한 픽셀 더 검사
			addr = (rc.bottom + 2) * m_PixelInfo->Width + info.Pos_X;
			if (addr < 0 || addr >= (int)m_PixelInfo->vecPixel.size()) return -1;

			// 몬스터가 돌아보는 위치에 있는경우
			if (m_PixelInfo->vecPixel[addr].r == m_PixelInfo->TurnPixel.r &&
				m_PixelInfo->vecPixel[addr].g == m_PixelInfo->TurnPixel.g &&
				m_PixelInfo->vecPixel[addr].b == m_PixelInfo->TurnPixel.b)
			{
				mon->SetTurnCheck(true);
			}
			else if (m_PixelInfo->vecPixel[addr].r != m_PixelInfo->CollPixel.r &&
				m_PixelInfo->vecPixel[addr].g != m_PixelInfo->CollPixel.g &&
				m_PixelInfo->vecPixel[addr].b != m_PixelInfo->CollPixel.b)
			{
				mon->SetFall(true);
			}
		}
	}

	return 0;
}

void Scene::Release()
{
	if (nullptr != m_PixelInfo)
	{
		m_PixelInfo->vecPixel.clear();

		delete m_PixelInfo;
		m_PixelInfo = nullptr;
	}
}

bool Scene::LoadPixelCollider(const char* pFilePath, unsigned char r, unsigned char g, unsigned char b)
{
	if (nullptr != m_PixelInfo)
	{
		m_PixelInfo->vecPixel.clear();

		delete m_PixelInfo;
		m_PixelInfo = nullptr;
	}

	m_PixelInfo = new PIXELCOLLIDERINFO;
	// 지형충돌 체크
	m_PixelInfo->CollPixel.r = r;
	m_PixelInfo->CollPixel.g = g;
	m_PixelInfo->CollPixel.b = b;

	// 돌아보는 체크
	m_PixelInfo->TurnPixel.r = 255;
	m_PixelInfo->TurnPixel.g = 255;
	m_PixelInfo->TurnPixel.b = 255;

	FILE* pFile = NULL;

	fopen_s(&pFile, pFilePath, "rb");

	if (pFile)
	{
		// File Header와 Info Header 선언
		// 비트맵 파일 자체에 관한 정보를 가진다.
		BITMAPFILEHEADER	tBf = {};
		// 크기(가로 폭, 세로 높이)와 색상 포맷 등에 관한 정보를 가진다.
		BITMAPINFOHEADER	tIf = {};

		// 파일 자체의 정보를 읽는다.
		fread(&tBf, sizeof(tBf), 1, pFile);
		fread(&tIf, sizeof(tIf), 1, pFile);

		fseek(pFile, tBf.bfOffBits, SEEK_SET);

		m_PixelInfo->Width = tIf.biWidth;
		m_PixelInfo->Height = tIf.biHeight;

		m_PixelInfo->vecPixel.clear();
		m_PixelInfo->vecPixel.resize(tIf.biWidth * tIf.biHeight);

		fread(&m_PixelInfo->vecPixel[0], sizeof(PIXEL24), m_PixelInfo->vecPixel.size(), pFile);

		fclose(pFile);
	}
	else
	{
		return false;
	}
	return true;
}
