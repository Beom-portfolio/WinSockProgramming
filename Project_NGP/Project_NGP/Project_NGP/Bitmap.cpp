#include "stdafx.h"
#include "Bitmap.h"


GdiImage::GdiImage()
{
}


GdiImage::~GdiImage()
{
	// 해제 순서 유의
	// DC에 선택된 GDI 오브젝트는 바로 해제가 불가능하다.
	// 따라서, m_OldBmp를 이용해 해방 시킨 후 해제해야한다.
	SelectObject(m_hMemDC, m_OldBmp);
	DeleteObject(m_Bitmap);
	DeleteDC(m_hMemDC);
}

GdiImage * GdiImage::LoadBmp(const TCHAR * pFilePath)
{
	m_hDC = GetDC(g_hWnd);

	// 실제 출력 DC와 호환이 되는 m_hMemDC에 읽어온 비트맵을 미리 그려넣어 저장
	m_hMemDC = CreateCompatibleDC(m_hDC);

	m_Bitmap = (HBITMAP)LoadImage(NULL, pFilePath, IMAGE_BITMAP
		, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (NULL == m_Bitmap)
	{
		MessageBox(g_hWnd, pFilePath, L"Image load failed!", MB_OK);
		return NULL;
	}

	m_OldBmp = (HBITMAP)SelectObject(m_hMemDC, m_Bitmap);

	ReleaseDC(g_hWnd, m_hDC);
	return this;
}
