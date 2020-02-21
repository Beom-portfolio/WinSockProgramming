#pragma once

#include <Gdiplus.h>

class GdiPlusImage
{
public:
	GdiPlusImage();
	virtual ~GdiPlusImage();

public:
	Gdiplus::Image* GetGdiPlusImageDefault();
	Gdiplus::Image* GetGdiPlusImageFromIndex(int index);

public:
	GdiPlusImage* LoadGdiPlusImage(const TCHAR* filePath);
	GdiPlusImage* LoadGdiPlusImageFromFolder(bstr_t folderPath);

private:
	// GDI와 다르게 이미지 자체를 직접 컨테이너에 넣을 수 없으므로 
	// 이미지의 경로만 넣어놓고 경로를 통해 로드한다.
	vector<const TCHAR*> m_vecFilePath;
};

