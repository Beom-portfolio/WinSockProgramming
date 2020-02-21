#pragma once
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	const GAMEOBJINFO& GetInfo()				{ return m_Info; }
	const GAMEOBJINFO& GetCollideInfo()			{ return m_CollideInfo; }
	const RECT& GetCollideRect()				{ return m_CollideRect; }
	const RENDERTYPE& GetRenderType()			{ return m_RenderType; }
	const bool& GetState()						{ return m_isDead; }
	const bool& GetRenderCheck()				{ return m_renderCheck; }
	const float& GetAngle()						{ return m_Angle; }
	const float& GetSpeed()						{ return m_Speed; }
	const float& GetGravity()					{ return m_GravitySpeed; }
	const PIXELCOLLIDERINFO* GetPixelCollider() { return m_PixelInfo; }
	const SPRITEINFO& GetSpriteInfo()			{ return m_SpriteInfo; }
	const DIRECTION& GetDirection()				{ return m_Direction; }
	const OBJTYPE& GetObjectType()				{ return m_ObjType; }
public:
	void SetPosition(int posX, int posY);
	void SetSize(int sizeWidth, int sizeHeight);
	void SetAngle(float angle);
	void SetSpeed(float speed);
	void SetCollideOn(bool on);
	void SetFall(bool fall);
	void SetRenderCheck(bool render);
	void SetSpriteInfo(SPRITEINFO spriteInfo);
	void SetDirection(DIRECTION dir);
	void SetObjectType(OBJTYPE type);
	void SetFollowedObj (GameObject* obj);
public:
	bool LoadPixelCollider(const char* pFilePath,
		unsigned char r, unsigned char g, unsigned char b);

public:
	virtual bool Initialize() PURE;
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc) PURE;
	virtual void Release() PURE;
	virtual void CollisionActivate(GameObject* collideTarget);
	virtual void CollisionDeactivate(GameObject* collideTarget);
	virtual void CollisionPixelPart(DIRECTION dir);

protected:
	GAMEOBJINFO		m_Info;
	SPRITEINFO		m_SpriteInfo;
	RENDERTYPE		m_RenderType = RENDER_END;
	DIRECTION		m_Direction = DIR_END;
	DWORD			m_Dir = 0;
	// Collider
	PIXELCOLLIDERINFO	*m_PixelInfo = nullptr;
	RECT				m_Rect;
	GAMEOBJINFO			m_CollideInfo;
	RECT				m_CollideRect;

	OBJTYPE				m_ObjType = OBJ_END;

	bool			m_isNoScroll = false;
	bool			m_isDead = false;
	bool			m_isCollideOn = true;
	bool			m_fallCheck = true;
	bool			m_renderCheck = true;
	float			m_Angle = 0.f;
	float			m_Speed = 0.f;
	float			m_GravitySpeed = 0.f;
	float			m_GravityAcc = 9.8f;

	// 따라다녀야 할 오브젝트
	GameObject* m_FollowedObj = nullptr;
};

