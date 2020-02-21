#include "stdafx.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "TestScene.h"
#include "MainScene_1.h"
#include "MainScene_2.h"

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	Release();
}

bool SceneManager::ChangeSceneState(SCENESTATE SceneState)
{
	if (nullptr != m_Scene)
	{
		Release();
	}

	switch (SceneState)
	{
	case SCENE_MENU :
		m_Scene = new MainMenu;
		break;
	case SCENE_TEST:
		m_Scene = new TestScene;
		break;
	case SCENE_MAIN_1:
		m_Scene = new MainScene_1;
		break;
	case SCENE_MAIN_2:
		m_Scene = new MainScene_2;
		break;
	}

	if (nullptr == m_Scene)
		return false;

	if (false == m_Scene->Initialize())
	{
		MessageBox(g_hWnd_New, L"씬 초기화 실패!", L"Error", MB_OK);
		Release();
		return false;
	}

	m_CurrentScene = SceneState;

	return true;
}

int SceneManager::Update(const float & TimeDelta)
{
	if (-1 == m_Scene->Update(TimeDelta))
		return -1;
	return 0;
}

void SceneManager::Render(HDC hDC)
{
	m_Scene->Render(hDC);
}

void SceneManager::Release()
{
	if (m_Scene)
	{
		delete m_Scene;
		m_Scene = nullptr;
	}
}
