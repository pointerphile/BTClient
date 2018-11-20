#pragma once
#include "PPBasis.h"
#include "PPInput.h"
class PPWindow : public PPBasis
{
public:
	HWND m_hWnd;// 윈도우 핸들
	HINSTANCE m_hInstance;// 실행객체 핸들
	RECT m_rcWindowBounds;// 윈도우 영역
	RECT m_rcWindowClient;// 클라이언트 영역	
	UINT m_iWindowClientWidth;// 클라이언트 영역 가로크기
	UINT m_iWindowClientHeight;// 을라이언트 영역 세로크기

	PPWindow();
	virtual ~PPWindow();

	virtual bool Init() { return true; };
	virtual bool Frame() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };

	virtual bool GameInit() { return true; };
	virtual bool GameFrame() { return true; };
	virtual bool GameRender() { return true; };
	virtual bool GameRelease() { return true; };
	virtual bool GameRun() { return true; };
	virtual HRESULT m_ResizeDevice(UINT width, UINT height) { return true; };

	virtual void MsgEvent(MSG msg) {};

	bool m_SetWindowCenter();
	bool Run();
	bool m_SetWindow(HINSTANCE hInstance, const TCHAR* pTitleName, int iWidth, int iHeight, DWORD dwStyle);
	bool m_RefreshClientRect();
};

