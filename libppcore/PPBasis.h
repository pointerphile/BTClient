#pragma once

#include <iostream>
#include <chrono>
#include <tchar.h>
#include <vector>
#include <string>

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "../WICTextureLoader/WICTextureLoader.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/WICTextureLoader.lib")
#else
#pragma comment(lib, "WICTextureLoader.lib")
#endif // _DEBUG

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern RECT g_rcWindowClient;
extern UINT* g_iWindowClientWidth;
extern UINT* g_iWindowClientHeight;
extern int64_t g_iFPS;// FPS
extern float g_fSecPerFrame; // 1프레임의 경과시간
extern float g_fAccumulation;// 실행된 경과 시간
extern TCHAR* g_csBuffer;

class PPBasis
{
public:
	PPBasis();
	virtual ~PPBasis();

	virtual bool Init() = 0;
	virtual bool Frame() = 0;
	virtual bool Render() = 0;
	virtual bool Release() = 0;
};

