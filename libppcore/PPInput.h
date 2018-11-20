#pragma once
#include "PPBasis.h"
#include "PPSingletone.h"

enum KeyState {
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_HOLD,
};

class PPInput : public PPBasis, public PPSingleton<PPInput>
{
private:
	friend class PPSingleton<PPInput>;
public:
	std::vector<std::wstring> m_strList;
	TCHAR m_csBuffer[MAX_PATH] = { 0 };
	DWORD m_dwKeyState[256] = { 0 };
	DWORD m_dwMouseState[3] = { 0 };
	DWORD m_dwBeforeMouseState[3] = { 0 };
	POINT m_MousePos;

	PPInput();
	virtual ~PPInput();

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release() { return true; };

	DWORD KeyCheck(DWORD dwKey);
	void MsgEvent(MSG msg);
};

