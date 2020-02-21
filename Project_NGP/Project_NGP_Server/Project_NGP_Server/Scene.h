#pragma once
class Spawn;
class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	const map<int, Spawn*>& GetMapSpawn() { return m_mapSpawn; }

public:
	virtual bool Initialize() PURE;
	virtual int Update(const float& TimeDelta);
	virtual void Release();

public:
	bool LoadPixelCollider(const char* pFilePath,
		unsigned char r, unsigned char g, unsigned char b);

protected:
	PIXELCOLLIDERINFO *m_PixelInfo = nullptr;
	map<int, Spawn*> m_mapSpawn;
};

