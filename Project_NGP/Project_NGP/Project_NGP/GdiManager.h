#pragma once
#include "GdiImage.h"

class GdiManager : public Singleton<GdiManager>
{
public:
	GdiManager();
	virtual ~GdiManager();

public:
	typedef unordered_map<const TCHAR*, GdiImage*>		MAPBITMAP;

public:
	void LoadImageBySceneState(SCENESTATE SceneState);
	MAPBITMAP& GetBmpContainer() { return m_mapBmp; }

public:
	GdiImage* FindImage(const TCHAR* pKey);

public:
	void LoadGdiImage(const TCHAR* pKey, const TCHAR* pFilePath);
	void LoadGdiImageFromFolder(const TCHAR* pKey, bstr_t folderPath);
	void ResetContainer();

private:
	unordered_map<const TCHAR*, GdiImage*>				m_mapBmp;
};

