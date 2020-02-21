#include "stdafx.h"
#include "GdiPlusManager.h"

GdiPlusManager::GdiPlusManager()
{
	// Gdi+ 라이브러리 초기화
	GdiplusStartupInput m_gdiPlusStartupInput;
	GdiplusStartup(&m_gdiPlusToken, &m_gdiPlusStartupInput, NULL);

	// Graphics 초기화
	//g_pGraphic = new Graphics()
}

GdiPlusManager::~GdiPlusManager()
{
	ResetContainer();
	GdiplusShutdown(m_gdiPlusToken);
}

void GdiPlusManager::LoadImageBySceneState(SCENESTATE SceneState)
{
	switch (SceneState)
	{
	case SCENESTATE::SCENE_TEST:
	case SCENESTATE::SCENE_MAIN_1:
		// Load Image
		LoadGdiPlusImage(L"cursor", L"../Resources/Cursor.png");
		LoadGdiPlusImageFromFolder(L"nomal_attack","../Resources/NomalAttack");
		LoadGdiPlusImageFromFolder(L"nomal_attack_hit", "../Resources/NomalAttackHit");
		LoadGdiPlusImageFromFolder(L"skill1", "../Resources/Skill1");
		LoadGdiPlusImageFromFolder(L"skill1_hit", "../Resources/Skill1Hit");
		LoadGdiPlusImageFromFolder(L"skill2", "../Resources/Skill2");
		LoadGdiPlusImageFromFolder(L"skill2_hit", "../Resources/Skill2Hit");
		break;
	case SCENESTATE::SCENE_MAIN_2:
		break;
	case SCENESTATE::SCENE_MAIN_3:
		break;
	}
}

GdiPlusImage* GdiPlusManager::FindImage(const TCHAR* tag)
{
	MAPIMAGES::const_iterator iter = m_mapImages.find(tag);

	if (m_mapImages.end() == iter)
		return nullptr;

	return iter->second;
}

void GdiPlusManager::LoadGdiPlusImage(const TCHAR* tag, const TCHAR* filePath)
{
	m_mapImages.emplace(MAPIMAGES::value_type(tag, (new GdiPlusImage)->LoadGdiPlusImage(filePath)));
}

void GdiPlusManager::LoadGdiPlusImageFromFolder(const TCHAR* tag, bstr_t folderPath)
{
	m_mapImages.emplace(MAPIMAGES::value_type(tag, (new GdiPlusImage)->LoadGdiPlusImageFromFolder(folderPath)));
}

void GdiPlusManager::ResetContainer()
{
	for (auto& image : m_mapImages)
	{
		delete image.second;
		image.second = nullptr;
	}

	m_mapImages.clear();
}
