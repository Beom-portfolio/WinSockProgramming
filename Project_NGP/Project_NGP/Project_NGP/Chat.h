#pragma once
#include "GameObject.h"

class Text;
class Chat
	:public GameObject
{
public:
	Chat();
	virtual ~Chat();
public:
	void SetActivate(bool check);
	const WCHAR* GetChatBuffer() { return m_ChatEditBuffer; }
public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
private:
	WCHAR m_ChatEditBuffer[25] = { 0, };
	Text* m_TypingText = nullptr;
	int m_MaxLength = 24;
};

