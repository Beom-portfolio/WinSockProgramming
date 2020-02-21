#include "stdafx.h"
#include "MainScene_2.h"
#include "Portal.h"
#include "Background_2.h"
#include "Background_3.h"
#include "Player.h"

MainScene_2::MainScene_2()
	:Scene()
{
}

MainScene_2::~MainScene_2()
{
	Release();
}

bool MainScene_2::Initialize()
{
	GET_MANAGER<GdiPlusManager>()->LoadImageBySceneState(SCENE_MAIN_1);
	GET_MANAGER<GdiManager>()->LoadImageBySceneState(SCENE_MAIN_1);
	GET_MANAGER<GdiPlusManager>()->LoadImageBySceneState(SCENE_MAIN_2);
	GET_MANAGER<GdiManager>()->LoadImageBySceneState(SCENE_MAIN_2);

	m_ObjManager->AddObject(L"background", AbstractFactory<Background_2>::CreateObj(), OBJ_BACK);

	GameObject* pPortal = AbstractFactory<Portal>::CreateObj(85, 727 - (257 / 2));
	dynamic_cast<Portal*>(pPortal)->SetSceneInfo(SCENE_MAIN_1);
	m_ObjManager->AddObject(L"portal_left", pPortal, OBJ_PORTAL);

	GameObject* pPlayer = m_ObjManager->GetObjFromTag(L"player", OBJ_PLAYER);
	if (nullptr == pPlayer)
	{
		pPlayer = AbstractFactory<Player>::CreateObj();
		m_ObjManager->AddObject(L"player", pPlayer, OBJ_PLAYER);
	}
	pPlayer->SetPosition(85, 639);
	m_CamManager->SetTarget(pPlayer);

	GameObject* pBackGround = m_ObjManager->GetObjFromTag(L"background", OBJ_BACK);
	m_CamManager->SetResolution(pBackGround->GetInfo().Size_Width, pBackGround->GetInfo().Size_Height);

#ifdef SERVER_MODE
	if (false == InitializeNetwork(SCENE_MAIN_2))
		return false;
#endif

	return true;
}

int MainScene_2::Update(const float& TimeDelta)
{
	KeyManager* keyManager = GET_MANAGER<KeyManager>();

	if (true == keyManager->GetKeyState(STATE_DOWN, VK_F1))
	{
		bool recentCheck = GET_MANAGER<CollisionManager>()->GetRenderCheck();

		if (true == recentCheck)
			GET_MANAGER<CollisionManager>()->SetRenderCheck(false);
		else
			GET_MANAGER<CollisionManager>()->SetRenderCheck(true);
	}

#ifdef SERVER_MODE
	if (false == UpdateNetwork())
		return -1;
#endif

	m_CamManager->Update(TimeDelta);
	m_ObjManager->Update(TimeDelta);

	return 0;
}

void MainScene_2::Render(HDC hDC)
{
	m_ObjManager->Render(hDC);
}

void MainScene_2::Release()
{
	m_ObjManager->ReleaseFromType(OBJ_BACK);
	m_ObjManager->ReleaseFromType(OBJ_OTHERPLAYER);
	m_ObjManager->ReleaseFromType(OBJ_MONSTER);
	m_ObjManager->ReleaseFromType(OBJ_EFFECT);
	m_ObjManager->ReleaseFromType(OBJ_PORTAL);
}
