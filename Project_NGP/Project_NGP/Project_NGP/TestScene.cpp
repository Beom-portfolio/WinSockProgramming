#include "stdafx.h"
#include "TestScene.h"
#include "Player.h"
#include "Mouse.h"
#include "Background.h"
#include "Monster.h"
#include "BlueSnail.h"
#include "Slime.h"
#include "Mushroom.h"
#include "GreenMush.h"
#include "NomalAttack.h"
#include "Portal.h"
#include "Fade.h"
#include "MainUI.h"
#include "Chat.h"


TestScene::TestScene()
	:Scene()
{
}

TestScene::~TestScene()
{
	Release();
}

bool TestScene::Initialize()
{
	GET_MANAGER<GdiPlusManager>()->LoadImageBySceneState(SCENE_TEST);
	GET_MANAGER<GdiManager>()->LoadImageBySceneState(SCENE_TEST);
	
	m_ObjManager->AddObject(L"background", AbstractFactory<Background>::CreateObj(), OBJ_BACK);
	//m_ObjManager->AddObject(L"attackeffect", AbstractFactory<AttackEffect>::CreateObj(), OBJ_EFFECT);
	m_ObjManager->AddObject(L"nomalattack", AbstractFactory<NomalAttack>::CreateObj(), OBJ_EFFECT);
	m_ObjManager->AddObject(L"bluesnail", AbstractFactory<BlueSnail>::CreateObj(), OBJ_MONSTER);
	m_ObjManager->AddObject(L"slime", AbstractFactory<Slime>::CreateObj(), OBJ_MONSTER);
	m_ObjManager->AddObject(L"mushroom", AbstractFactory<Mushroom>::CreateObj(), OBJ_MONSTER);
	m_ObjManager->AddObject(L"greenmush", AbstractFactory<GreenMush>::CreateObj(), OBJ_MONSTER);
	m_ObjManager->AddObject(L"mouse", AbstractFactory<Mouse>::CreateObj(), OBJ_UI);
	m_ObjManager->AddObject(L"fade", AbstractFactory<Fade>::CreateObj(), OBJ_UI);
	m_ObjManager->AddObject(L"main_ui", AbstractFactory<MainUI>::CreateObj(), OBJ_UI);
	m_ObjManager->AddObject(L"chat", AbstractFactory<Chat>::CreateObj(), OBJ_UI);

	GameObject* pPortal = AbstractFactory<Portal>::CreateObj(1172, 298 - (257 / 2));
	dynamic_cast<Portal*>(pPortal)->SetSceneInfo(SCENE_MAIN_2);
	m_ObjManager->AddObject(L"portal", pPortal, OBJ_PORTAL);

	GameObject* pPlayer = m_ObjManager->GetObjFromTag(L"player", OBJ_PLAYER);
	if (nullptr == pPlayer)
	{
		pPlayer = AbstractFactory<Player>::CreateObj();
		m_ObjManager->AddObject(L"player", pPlayer, OBJ_PLAYER);
	}
	pPlayer->SetPosition(1703, 1222);
	
	// id¸¦ Set
	dynamic_cast<Player*>(pPlayer)->SetIdToText(m_NetworkManager->GetMyId());
	m_CamManager->SetTarget(pPlayer);

	GameObject* pBackGround = m_ObjManager->GetObjFromTag(L"background", OBJ_BACK);
	m_CamManager->SetResolution(pBackGround->GetInfo().Size_Width, pBackGround->GetInfo().Size_Height);

	return true;
}

int TestScene::Update(const float & TimeDelta)
{
	KeyManager *keyManager = GET_MANAGER<KeyManager>();

	if (true == keyManager->GetKeyState(STATE_DOWN, VK_F1))
	{
		bool recentCheck = GET_MANAGER<CollisionManager>()->GetRenderCheck();

		if (true == recentCheck)
			GET_MANAGER<CollisionManager>()->SetRenderCheck(false);
		else
			GET_MANAGER<CollisionManager>()->SetRenderCheck(true);
	}

	m_CamManager->Update(TimeDelta);
	m_ObjManager->Update(TimeDelta);

	return 0;
}

void TestScene::Render(HDC hDC)
{
	//Rectangle(hDC, 0, 0, WINSIZE_X, WINSIZE_Y);
	m_ObjManager->Render(hDC);
}

void TestScene::Release()
{
	m_ObjManager->ReleaseFromType(OBJ_BACK);
	m_ObjManager->ReleaseFromType(OBJ_OTHERPLAYER);
	m_ObjManager->ReleaseFromType(OBJ_MONSTER);
	m_ObjManager->ReleaseFromType(OBJ_EFFECT);
	m_ObjManager->ReleaseFromType(OBJ_PORTAL);
}