#pragma once

class CollisionManager : public Singleton<CollisionManager>
{
public:
	CollisionManager();
	virtual ~CollisionManager();

public:
	void SetRenderCheck(bool check) { m_RenderCheck = check; }
	bool GetRenderCheck() { return m_RenderCheck; }

public:
	void CollisionRect(ObjectManager::MAPOBJ* DstList, ObjectManager::MAPOBJ* SrcList);
	void CollisionRectEx(ObjectManager::MAPOBJ* DstList, ObjectManager::MAPOBJ* SrcList);

	void CollisionPixelToRect(ObjectManager::MAPOBJ* pixel, ObjectManager::MAPOBJ* rect);
	void CollisionPixelToPoint(ObjectManager::MAPOBJ* pixel, ObjectManager::MAPOBJ* rect);

private:
	bool CheckCollisionRectDist(int* moveX, int* moveY, GameObject* Dst, GameObject* Src);
	bool m_RenderCheck = false;
};

