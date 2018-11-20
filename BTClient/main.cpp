#include "PPSample.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCMdShow) {
	PPSample Sample;
	if (Sample.m_SetWindow(hInstance, L"Sample Modern DirectX", 800, 600, WS_OVERLAPPEDWINDOW))
	{
		Sample.Run();
	}
	return 0;
}