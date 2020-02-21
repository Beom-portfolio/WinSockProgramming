#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject()
{
	ZeroMemory(&m_Info, sizeof(GAMEOBJINFO));
	ZeroMemory(&m_Rect, sizeof(RECT));
	ZeroMemory(&m_SpriteInfo, sizeof(SPRITEINFO));
	ZeroMemory(&m_CollideInfo, sizeof(GAMEOBJINFO));
	ZeroMemory(&m_CollideRect, sizeof(RECT));
}


GameObject::~GameObject()
{
	if (nullptr != m_PixelInfo)
	{
		m_PixelInfo->vecPixel.clear();

		delete m_PixelInfo;
		m_PixelInfo = nullptr;
	}
}

void GameObject::SetPosition(int posX, int posY)
{
	m_Info.Pos_X = posX;
	m_Info.Pos_Y = posY;
}

void GameObject::SetSize(int sizeWidth, int sizeHeight)
{
	m_Info.Size_Width = sizeWidth;
	m_Info.Size_Height = sizeHeight;
}

void GameObject::SetAngle(float angle)
{
	m_Angle = angle;
}

void GameObject::SetSpeed(float speed)
{
	m_Speed = speed;
}

void GameObject::SetCollideOn(bool on)
{
	m_isCollideOn = on;
}

void GameObject::SetFall(bool fall)
{
	if (true == fall && false == m_fallCheck)
	{
		m_GravitySpeed = 0;
		m_GravityAcc = 0;
		m_fallCheck = fall;
	}

	if (false == fall && true == m_fallCheck)
	{
		m_GravitySpeed = 0;
		m_GravityAcc = 0;
		m_fallCheck = fall;
	}
}

void GameObject::SetRenderCheck(bool render)
{
	m_renderCheck = render;
}

void GameObject::SetSpriteInfo(SPRITEINFO spriteInfo)
{
	m_SpriteInfo = spriteInfo;
}

void GameObject::SetDirection(DIRECTION dir)
{
	m_Direction = dir;
}

void GameObject::SetObjectType(OBJTYPE type)
{
	m_ObjType = type;
}

void GameObject::SetFollowedObj(GameObject* obj)
{
	m_FollowedObj = obj;
}

bool GameObject::LoadPixelCollider(const char* pFilePath, unsigned char r, unsigned char g, unsigned char b)
{
	if (nullptr != m_PixelInfo)
	{
		m_PixelInfo->vecPixel.clear();

		delete m_PixelInfo;
		m_PixelInfo = nullptr;
	}

	m_PixelInfo = new PIXELCOLLIDERINFO;
	m_PixelInfo->CollPixel.r = r;
	m_PixelInfo->CollPixel.g = g;
	m_PixelInfo->CollPixel.b = b;

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

int GameObject::Update(const float & TimeDelta)
{
	POSITION CamPos = GET_MANAGER<CameraManager>()->GetPos();

	if (true == m_isNoScroll)
	{
		ZeroMemory(&CamPos, sizeof(POSITION));
	}

	POSITION TotalPos = POSITION{ m_Info.Pos_X + CamPos.X , m_Info.Pos_Y + CamPos.Y };

	// 오브젝트 정보를 바탕으로 Rect 정보를 갱신한다.
	m_Rect.left = (int)TotalPos.X - m_Info.Size_Width / 2;
	m_Rect.top = (int)TotalPos.Y - m_Info.Size_Height / 2;
	m_Rect.right = (int)TotalPos.X + m_Info.Size_Width / 2;
	m_Rect.bottom = (int)TotalPos.Y + m_Info.Size_Height / 2;

	// Collide Rect 정보를 갱신한다.
	m_CollideRect.left = (int)(TotalPos.X + m_CollideInfo.Pos_X) - m_CollideInfo.Size_Width / 2;
	m_CollideRect.top = (int)(TotalPos.Y + m_CollideInfo.Pos_Y) - m_CollideInfo.Size_Height / 2;
	m_CollideRect.right = (int)(TotalPos.X + m_CollideInfo.Pos_X) + m_CollideInfo.Size_Width / 2;
	m_CollideRect.bottom = (int)(TotalPos.Y + m_CollideInfo.Pos_Y) + m_CollideInfo.Size_Height / 2;

	return 0;
}

void GameObject::CollisionActivate(GameObject* collideTarget)
{
}

void GameObject::CollisionDeactivate(GameObject* collideTarget)
{
}

void GameObject::CollisionPixelPart(DIRECTION dir)
{
}
