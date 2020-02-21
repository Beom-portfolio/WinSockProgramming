#include "stdafx.h"
#include "GdiPlusImage.h"

GdiPlusImage::GdiPlusImage()
{
}

GdiPlusImage::~GdiPlusImage()
{
	for (auto& filePath : m_vecFilePath)
	{
		if (nullptr != filePath)
		{
			delete[] filePath;
			filePath = nullptr;
		}
	}
	m_vecFilePath.clear();
}

Gdiplus::Image* GdiPlusImage::GetGdiPlusImageDefault()
{
	if (m_vecFilePath.empty())
		return nullptr;

	return Gdiplus::Image::FromFile(m_vecFilePath[0]);
}

Gdiplus::Image* GdiPlusImage::GetGdiPlusImageFromIndex(int index)
{
	if (index >= (int)m_vecFilePath.size() || m_vecFilePath.empty())
		return nullptr;

	return Gdiplus::Image::FromFile(m_vecFilePath[index]);
}

GdiPlusImage* GdiPlusImage::LoadGdiPlusImage(const TCHAR* filePath)
{
	TCHAR* tmpPath = new TCHAR[MAX_BUFFER];
	memset(tmpPath, 0, sizeof(TCHAR) * MAX_BUFFER);

	lstrcpy(tmpPath, filePath);

	m_vecFilePath.emplace_back(tmpPath);
	return this;
}

GdiPlusImage* GdiPlusImage::LoadGdiPlusImageFromFolder(bstr_t folderPath)
{
	vector<bstr_t> fileNames;
	GET_MANAGER<FileManager>()->GetFileListFromFolder(folderPath + "/*.*", fileNames);

	TCHAR originPath[MAX_BUFFER];
	memset(originPath, 0, sizeof(TCHAR) * MAX_BUFFER);
	
	lstrcpy(originPath, (TCHAR*)(folderPath + "/"));

	for (auto& file : fileNames)
	{
		TCHAR *tmpPath = new TCHAR[MAX_BUFFER];
		memset(tmpPath, 0, sizeof(TCHAR) * MAX_BUFFER);

		lstrcpy(tmpPath, originPath);
		lstrcat(tmpPath, (TCHAR*)file);

		m_vecFilePath.emplace_back(tmpPath);
	}

	return this;
}
