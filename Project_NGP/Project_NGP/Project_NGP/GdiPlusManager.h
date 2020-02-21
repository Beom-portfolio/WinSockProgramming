#pragma once

#include "GdiPlusImage.h"

class GdiPlusManager : public Singleton<GdiPlusManager>
{
public:
	GdiPlusManager();
	virtual ~GdiPlusManager();

public:
	typedef unordered_map<const TCHAR*, GdiPlusImage*>  MAPIMAGES;

public:
	void	   LoadImageBySceneState(SCENESTATE SceneState);
	MAPIMAGES& GetImageContainer() { return m_mapImages; }

public:
	GdiPlusImage* FindImage(const TCHAR* tag);

public:
	void LoadGdiPlusImage(const TCHAR* tag, const TCHAR* filePath);
	void LoadGdiPlusImageFromFolder(const TCHAR* tag, bstr_t folderPath);
	void ResetContainer();

private:
	unordered_map<const TCHAR*, GdiPlusImage*>			m_mapImages;
	ULONG_PTR		    m_gdiPlusToken;
};