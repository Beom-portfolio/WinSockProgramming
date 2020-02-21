#pragma once
class FileManager : public Singleton<FileManager>
{
public:
	FileManager();
	virtual ~FileManager();

public:
	void GetFileListFromFolder(bstr_t folderPath, vector<bstr_t>& vecStr);
};

