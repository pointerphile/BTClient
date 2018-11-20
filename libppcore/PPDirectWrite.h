#pragma once
#include "PPBasis.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class PPDirectWrite : public PPBasis
{
public:
	ID2D1RenderTarget* m_pRenderTarget;
	ID2D1Factory* m_pD2D1Factory;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pDWriteTextFormat;
	IDXGISurface* m_pDXGISurface;
	ID2D1SolidColorBrush* m_pWhiteBrush;
	IDWriteTextLayout* m_pTextLayoutCredit;

	float m_fDPIScaleX;
	float m_fDPIScaleY;
	float m_fDPI_X;
	float m_fDPI_Y;

	virtual bool Init();
	virtual bool Frame() { return true; };
	virtual bool Render();
	virtual bool Release();

	bool PreRender();
	bool PostRender();

	HRESULT CreateDeviceResources(IDXGISwapChain* pSwapChain);

	bool m_DrawText(std::wstring wstring, UINT32 StringLength, IDWriteTextFormat * TextFormat, D2D1_RECT_F & rect, ID2D1Brush * Brush);
	HRESULT	m_DrawText(D2D1_POINT_2F origin, ID2D1Brush* Brush);

	float m_GetResizedFont(int size);

	HRESULT SetText(D2D1_POINT_2F size, wchar_t * text, ID2D1Brush * Brush);

	PPDirectWrite();
	virtual ~PPDirectWrite();
};

