#include "PPInput.h"

PPInput::PPInput()
{
}

PPInput::~PPInput()
{
}

bool PPInput::Init() {
	return true;
}
bool PPInput::Frame() {
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hWnd, &m_MousePos);

	for (int iButton = 0; iButton < 3; iButton++)
	{
		if (m_dwBeforeMouseState[iButton] == KEY_PUSH)
		{
			if (m_dwMouseState[iButton] == KEY_PUSH)
			{
				m_dwMouseState[iButton] = KEY_HOLD;
			}
		}
		if (m_dwBeforeMouseState[iButton] == KEY_UP)
		{
			if (m_dwMouseState[iButton] == KEY_UP)
			{
				m_dwMouseState[iButton] = KEY_FREE;
			}
		}
		m_dwBeforeMouseState[iButton] = m_dwMouseState[iButton];
	}

	return true;
}
bool PPInput::Render() {
	m_strList.clear();

	std::wstring strData0;
	if (m_dwMouseState[0] == TRUE)
	{
		strData0 = L"m_dwMouseState[0] ";
		m_strList.push_back(strData0);
	}

	std::wstring strData1;
	if (m_dwMouseState[1] == TRUE)
	{
		strData1 = L"m_dwMouseState[1] ";
		m_strList.push_back(strData1);
	}

	std::wstring strData2;
	if (m_dwMouseState[2] == TRUE)
	{
		strData2 = L"m_dwMouseState[2] ";
		m_strList.push_back(strData2);
	}
	return true;
}

DWORD PPInput::KeyCheck(DWORD dwKey)
{
	SHORT sKey = GetAsyncKeyState(dwKey);
	// 0x8000 =  10000000 00000000
	if (sKey & 0x8000)
	{
		if (m_dwKeyState[dwKey] == KEY_FREE ||
			m_dwKeyState[dwKey] == KEY_UP)
			m_dwKeyState[dwKey] = KEY_PUSH;
		else
			m_dwKeyState[dwKey] = KEY_HOLD;
	}
	else
	{
		if (m_dwKeyState[dwKey] == KEY_PUSH ||
			m_dwKeyState[dwKey] == KEY_HOLD)
			m_dwKeyState[dwKey] = KEY_UP;
		else
			m_dwKeyState[dwKey] = KEY_FREE;
	}
	return m_dwKeyState[dwKey];
}

void PPInput::MsgEvent(MSG msg) {
	switch (msg.message) {
		case WM_LBUTTONDOWN:{
			m_dwMouseState[0] = KEY_PUSH;
		}break;
		case WM_LBUTTONUP:{
			m_dwMouseState[0] = KEY_UP;
		}break;
		case WM_RBUTTONDOWN:{
			m_dwMouseState[1] = KEY_PUSH;
		}break;
		case WM_RBUTTONUP:{
			m_dwMouseState[1] = KEY_UP;
		}break;
		case WM_MBUTTONDOWN:{
			m_dwMouseState[2] = KEY_PUSH;
		}break;
		case WM_MBUTTONUP:{
			m_dwMouseState[2] = KEY_UP;
		}break;
	}
}