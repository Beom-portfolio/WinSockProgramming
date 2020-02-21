#include "stdafx.h"
#include "GdiManager.h"


GdiManager::GdiManager()
{
}


GdiManager::~GdiManager()
{
	ResetContainer();
}

GdiImage * GdiManager::FindImage(const TCHAR * pKey)
{
	MAPBITMAP::const_iterator iter = m_mapBmp.find(pKey);

	if (m_mapBmp.end() == iter)
		return nullptr;

	return iter->second;
}

void GdiManager::LoadImageBySceneState(SCENESTATE SceneState)
{
	// 씬에 필요한 이미지를 여기서 미리 로드해 놓는다.
	GdiManager* GdiMgr = GET_MANAGER<GdiManager>();
	switch (SceneState)
	{
	case SCENESTATE::SCENE_MENU:
		break;
	case SCENESTATE::SCENE_TEST:
	case SCENESTATE::SCENE_MAIN_1:
		// Load Image
		//BlueSanil
		GdiMgr->LoadGdiImageFromFolder(L"bluesnail_left", "../Resources/Monster/BlueSnail/BlueSnail_Left");
		GdiMgr->LoadGdiImageFromFolder(L"bluesnail_right", "../Resources/Monster/BlueSnail/BlueSnail_Right");
		GdiMgr->LoadGdiImageFromFolder(L"bluesnail_die", "../Resources/Monster/BlueSnail/BlueSnail_Die");
		//Slime
		GdiMgr->LoadGdiImageFromFolder(L"slime_idle_left", "../Resources/Monster/Slime/Slime_Idle_Left");
		GdiMgr->LoadGdiImageFromFolder(L"slime_idle_right", "../Resources/Monster/Slime/Slime_Idle_Right");
		GdiMgr->LoadGdiImageFromFolder(L"slime_move_left", "../Resources/Monster/Slime/Slime_Move_Left");
		GdiMgr->LoadGdiImageFromFolder(L"slime_move_right", "../Resources/Monster/Slime/Slime_Move_Right");
		GdiMgr->LoadGdiImageFromFolder(L"slime_hit_left", "../Resources/Monster/Slime/Slime_Hit_Left");
		GdiMgr->LoadGdiImageFromFolder(L"slime_hit_right", "../Resources/Monster/Slime/Slime_Hit_Right");
		GdiMgr->LoadGdiImageFromFolder(L"slime_die", "../Resources/Monster/Slime/Slime_Die");
		//Mushroom
		GdiMgr->LoadGdiImage(L"mushroom_left", L"../Resources/Monster/Mushroom/Mushroom_Left/Mushroom_L.bmp");
		GdiMgr->LoadGdiImage(L"mushroom_right", L"../Resources/Monster/Mushroom/Mushroom_Right/Mushroom_R.bmp");
		//GreenMhsh
		GdiMgr->LoadGdiImage(L"greenmush_left", L"../Resources/Monster/Mushroom/GreenMush_Left/GreenL.bmp");
		GdiMgr->LoadGdiImage(L"greenmush_right", L"../Resources/Monster/Mushroom/GreenMush_Right/GreenR.bmp");
		//TestMonster
		GdiMgr->LoadGdiImage(L"snail", L"../Resources/Monster/0.bmp");
		// Background
		GdiMgr->LoadGdiImage(L"background", L"../Resources/Map/Back.bmp");
		GdiMgr->LoadGdiImage(L"background_collider", L"../Resources/Map/Back_Collider.bmp");
		// Player
		GdiMgr->LoadGdiImage(L"player_left", L"../Resources/Player/player_L.bmp");
		GdiMgr->LoadGdiImage(L"player_right", L"../Resources/Player/player_R.bmp");
		// Portal
		GdiMgr->LoadGdiImage(L"portal", L"../Resources/Map/portal.bmp");
		// Fade
		GdiMgr->LoadGdiImage(L"fade", L"../Resources/FadeBuffer.bmp");
		// UI
		GdiMgr->LoadGdiImage(L"main_ui", L"../Resources/UI/Main_UI.bmp");
		GdiMgr->LoadGdiImage(L"chat", L"../Resources/UI/chat.bmp");
		GdiMgr->LoadGdiImage(L"chat_box", L"../Resources/UI/chat_box.bmp");
		break;
	case SCENESTATE::SCENE_MAIN_2:
		// Background
		GdiMgr->LoadGdiImage(L"background_2", L"../Resources/Map/Back_2.bmp");
		GdiMgr->LoadGdiImage(L"background_collider_2", L"../Resources/Map/Back_2_Collider.bmp");
		break;
	case SCENESTATE::SCENE_MAIN_3:
		// Background
		GdiMgr->LoadGdiImage(L"background_3", L"../Resources/Map/Back_Town.bmp");
		GdiMgr->LoadGdiImage(L"background_collider_3", L"../Resources/Map/Back_Town_Collider.bmp");
		break;
	}
}

void GdiManager::LoadGdiImage(const TCHAR * pKey, const TCHAR * pFilePath)
{
	m_mapBmp.emplace(MAPBITMAP::value_type(pKey, (new GdiImage)->LoadGdiImage(pFilePath)));
}

void GdiManager::LoadGdiImageFromFolder(const TCHAR* pKey, bstr_t folderPath)
{
	m_mapBmp.emplace(MAPBITMAP::value_type(pKey, (new GdiImage)->LoadGdiImageFromFolder(folderPath)));
}

void GdiManager::ResetContainer()
{
	for (auto& bmp : m_mapBmp)
	{
		delete bmp.second;
		bmp.second = nullptr;
	}

	m_mapBmp.clear();
}
