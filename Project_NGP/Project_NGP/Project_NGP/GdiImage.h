#pragma once
class GdiImage
{
public:
	GdiImage();
	virtual ~GdiImage();

public:
	//HDC GetMemDC() { return m_hMemDC; }
	HDC GetGdiImageDefault();
	HDC GetGdiImageFromIndex(int index);

public:
	GdiImage* LoadGdiImage(const TCHAR* pFilePath);
	GdiImage* LoadGdiImageFromFolder(bstr_t folderPath);

private:
	// 벡터로 담는 이유는 스프라이트 같은 경우에는 여러 이미지가 필요하기 때문이다.
	vector<GDIINFO> m_vecImages;
};

