#pragma once
class GdiImage
{
public:
	GdiImage();
	virtual ~GdiImage();

public:
	HDC GetMemDC() { return m_hMemDC; }

public:
	GdiImage* LoadBmp(const TCHAR* pFilePath);

private:
	HDC		m_hDC;
	HDC		m_hMemDC;

	HBITMAP m_Bitmap;
	HBITMAP m_OldBmp;
};

