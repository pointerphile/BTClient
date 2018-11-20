#include "PPWindow.h"

PPWindow* g_Window = nullptr;

RECT g_rcWindowClient;
HWND g_hWnd;
HINSTANCE g_hInstance;
UINT* g_iWindowClientWidth;
UINT* g_iWindowClientHeight;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_SIZE:
	{
		g_Window->m_RefreshClientRect();
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		if (g_hWnd) {
			g_Window->m_ResizeDevice(width, height);
		}
		
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

PPWindow::PPWindow() {
	g_Window = this;
}

PPWindow::~PPWindow() {
}


bool PPWindow::Run() {
	GameInit();
	MSG msg = { 0 };
	// �޼��� ť���� �޼��� 1���� �����´�.

	while (PPInput::GetInstance().KeyCheck(VK_ESCAPE) != KEY_UP) {
		// PM_NOREMOVE, PM_REMOVE
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			// Ű�� �ؼ���.
			TranslateMessage(&msg);
			// �޼��� ���ν����� ����.
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}

			MsgEvent(msg);
		}
		else {
			GameRun();
		}
	}
	GameRelease();

	return true;
}

bool PPWindow::m_SetWindowCenter() {
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

	// ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
	int iDestX = (iScreenWidth - (m_rcWindowBounds.right - m_rcWindowBounds.left)) / 2;
	int iDestY = (iScreenHeight - (m_rcWindowBounds.bottom - m_rcWindowBounds.top)) / 2;

	// �����츦 ȭ���߾����� �̵���Ų��.
	MoveWindow(m_hWnd, iDestX, iDestY, m_rcWindowBounds.right - m_rcWindowBounds.left, m_rcWindowBounds.bottom - m_rcWindowBounds.top, true);

	return true;
}

bool PPWindow::m_SetWindow(HINSTANCE hInstance, const TCHAR* pTitleName, int iWidth, int iHeight, DWORD dwStyle)
{
	m_hInstance = hInstance;

	//1, ������ Ŭ���� ��ü ���(�ü��)
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// ������ ���ν���
	wc.lpfnWndProc = WndProc,
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_QUESTION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = L"SampleWindow",
	wc.hIconSm = LoadIcon(nullptr, IDI_QUESTION);
	if (RegisterClassEx(&wc) == false) {
		return false;
	}
	//2, ��ϵ� Ŭ���� ��ü�� ����Ͽ� ������ ����	
	RECT rc = {0, 0, iWidth, iHeight};
	// �۾�����(  Ÿ��Ʋ ��/��輱/�޴�/��ũ�� �� ���� ������ ������ ����), ������ ��Ÿ��, �޴�����
	AdjustWindowRect(&rc, dwStyle, FALSE);
	m_hWnd = CreateWindowEx( WS_EX_APPWINDOW, L"SampleWindow", pTitleName, dwStyle, 0, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);
	if (m_hWnd == nullptr) {
		return false;
	}

	GetWindowRect(m_hWnd, &m_rcWindowBounds);
	m_RefreshClientRect();

	m_SetWindowCenter();
	ShowWindow(m_hWnd, SW_SHOW);

	g_hWnd = m_hWnd;
	return true;
};

bool PPWindow::m_RefreshClientRect() {
	GetClientRect(m_hWnd, &m_rcWindowClient);
	m_iWindowClientWidth = m_rcWindowClient.right - m_rcWindowClient.left;
	m_iWindowClientHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;
	g_rcWindowClient = m_rcWindowClient;
	g_iWindowClientWidth = &m_iWindowClientWidth;
	g_iWindowClientHeight = &m_iWindowClientHeight;

	return true;
}