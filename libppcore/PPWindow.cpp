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
	// 메세지 큐에서 메세지 1개를 가져온다.

	while (PPInput::GetInstance().KeyCheck(VK_ESCAPE) != KEY_UP) {
		// PM_NOREMOVE, PM_REMOVE
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			// 키를 해석함.
			TranslateMessage(&msg);
			// 메세지 프로시져에 전달.
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

	// 윈도우 클라이언트 중앙과 화면 스크린 중앙을 맞춘다.
	int iDestX = (iScreenWidth - (m_rcWindowBounds.right - m_rcWindowBounds.left)) / 2;
	int iDestY = (iScreenHeight - (m_rcWindowBounds.bottom - m_rcWindowBounds.top)) / 2;

	// 윈도우를 화면중앙으로 이동시킨다.
	MoveWindow(m_hWnd, iDestX, iDestY, m_rcWindowBounds.right - m_rcWindowBounds.left, m_rcWindowBounds.bottom - m_rcWindowBounds.top, true);

	return true;
}

bool PPWindow::m_SetWindow(HINSTANCE hInstance, const TCHAR* pTitleName, int iWidth, int iHeight, DWORD dwStyle)
{
	m_hInstance = hInstance;

	//1, 윈도우 클래스 객체 등록(운영체제)
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	// 윈도우 프로시져
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
	//2, 등록된 클래스 객체를 사용하여 윈도우 생성	
	RECT rc = {0, 0, iWidth, iHeight};
	// 작업영역(  타이틀 바/경계선/메뉴/스크롤 바 등의 영역을 제외한 영역), 윈도우 스타일, 메뉴여부
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