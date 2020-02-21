#pragma once

class GameObject;
class ObjectManager : public Singleton<ObjectManager>
{
public:
	ObjectManager();
	virtual ~ObjectManager();

public:
	typedef unordered_multimap<const TCHAR*, GameObject*>	MAPOBJ;

public:
	const TCHAR* GetTagFromObj(GameObject* Obj, OBJTYPE ObjType);
	
	MAPOBJ& GetObjFromType(OBJTYPE ObjType) { return m_mapObj[ObjType]; }
	GameObject* GetObjFromTag(const TCHAR* tag, OBJTYPE ObjType);
	
public:
	void AddObject(const TCHAR* tag, GameObject* Obj, OBJTYPE ObjType);
	void Update(const float& TimeDelta);
	void Render(HDC hDC);
	void ReleaseAll();
	void ReleaseFromType(OBJTYPE ObjType);
	void ReleaseObjFromTag(const TCHAR* tag, OBJTYPE ObjType);
	void ReleaseObj(GameObject* Obj, OBJTYPE ObjType);

private:
	unordered_multimap<const TCHAR*, GameObject*>			m_mapObj[OBJ_END];
	vector<GameObject*> m_vecRender[RENDER_END];
};

