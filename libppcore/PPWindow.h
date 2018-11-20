#pragma once
#include "PPBasis.h"
#include "PPInput.h"
class PPWindow : public PPBasis
{
public:
	HWND m_hWnd;// ������ �ڵ�
	HINSTANCE m_hInstance;// ���ఴü �ڵ�
	RECT m_rcWindowBounds;// ������ ����
	RECT m_rcWindowClient;// Ŭ���̾�Ʈ ����	
	UINT m_iWindowClientWidth;// Ŭ���̾�Ʈ ���� ����ũ��
	UINT m_iWindowClientHeight;// �����̾�Ʈ ���� ����ũ��

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

