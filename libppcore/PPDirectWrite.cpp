#include "PPDirectWrite.h"



PPDirectWrite::PPDirectWrite()
{
}


PPDirectWrite::~PPDirectWrite()
{
}

bool PPDirectWrite::Init() {
	HRESULT hr;
	if (FAILED(hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, 
		&m_pD2D1Factory))) {
		return false;
	}

	m_pD2D1Factory->GetDesktopDpi(&m_fDPI_X, &m_fDPI_Y);
	m_fDPIScaleX = m_fDPI_X / 96.0f;
	m_fDPIScaleY = m_fDPI_Y / 96.0f;

	if (FAILED(hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&m_pDWriteFactory)))) {
		return false;
	}

	if (FAILED(hr = m_pDWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, m_GetResizedFont(16), L"en-us", &m_pDWriteTextFormat))) {
		return false;
	}
	m_pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
	//디바이스 종속적인 요소 초기화
	
	
	return true;
}

bool PPDirectWrite::Render() {
	return true;
}
bool PPDirectWrite::Release() {
	if (m_pWhiteBrush) {
		m_pWhiteBrush->Release();
		m_pWhiteBrush = nullptr;
	}
	if (m_pDXGISurface) {
		m_pDXGISurface->Release();
		m_pDXGISurface = nullptr;
	}
	if (m_pDWriteTextFormat) {
		m_pDWriteTextFormat->Release();
		m_pDWriteTextFormat = nullptr;
	}
	if (m_pTextLayoutCredit) {
		m_pTextLayoutCredit->Release();
		m_pTextLayoutCredit = nullptr;
	}
	if (m_pDWriteFactory) {
		m_pDWriteFactory->Release();
		m_pDWriteFactory = nullptr;
	}
	if (m_pD2D1Factory) {
		m_pD2D1Factory->Release();
		m_pD2D1Factory = nullptr;
	}
	if (m_pRenderTarget) {
		m_pRenderTarget->Release();
		m_pRenderTarget = nullptr;
	}

	return true;
}

bool PPDirectWrite::PreRender() {
	if (m_pRenderTarget) {
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->SetTransform(D2D1::IdentityMatrix());
	}

	return true;
}
bool PPDirectWrite::PostRender() {
	if (FAILED(m_pRenderTarget->EndDraw())) {
		return false;
	}

	return true;
}

HRESULT PPDirectWrite::CreateDeviceResources(IDXGISwapChain* pSwapChain) {
	HRESULT hr;
	D2D1_RENDER_TARGET_PROPERTIES RenderTargetProperties;
	RenderTargetProperties = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
		m_fDPI_X,
		m_fDPI_Y
	);
	pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&m_pDXGISurface);
	if (FAILED(hr = m_pD2D1Factory->CreateDxgiSurfaceRenderTarget(m_pDXGISurface, &RenderTargetProperties, &m_pRenderTarget))) {
		return hr;
	}
	if (FAILED(hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pWhiteBrush))) {
		return hr;
	}
	m_pDXGISurface->Release();
	m_pDXGISurface = nullptr;

	return hr;
}

bool PPDirectWrite::m_DrawText(std::wstring wstring, UINT32 StringLength, IDWriteTextFormat* TextFormat, D2D1_RECT_F &rect, ID2D1Brush* Brush) {
	D2D1_RECT_F LayoutRect = D2D1::RectF(
		static_cast<FLOAT>(rect.left) / m_fDPIScaleX,
		static_cast<FLOAT>(rect.top) / m_fDPIScaleY,
		static_cast<FLOAT>(rect.right) / m_fDPIScaleX,
		static_cast<FLOAT>(rect.bottom) / m_fDPIScaleY
	);

	m_pRenderTarget->DrawTextW(wstring.c_str(), StringLength, TextFormat, LayoutRect, m_pWhiteBrush);
	//m_pRenderTarget->DrawTextW(wstring.c_str(), StringLength, TextFormat, rect, m_pWhiteBrush);

	return true;
}
HRESULT PPDirectWrite::m_DrawText(D2D1_POINT_2F pos, ID2D1Brush* Brush)
{
	D2D1_POINT_2F origin = D2D1::Point2F(
		static_cast<FLOAT>(pos.x / m_fDPIScaleX),
		static_cast<FLOAT>(pos.y / m_fDPIScaleY));
	m_pRenderTarget->DrawTextLayout(origin, m_pTextLayoutCredit, m_pWhiteBrush);

	return S_OK;
}
float PPDirectWrite::m_GetResizedFont(int size) {
	float fResized;

	fResized = size * (96.0f / (72.0f * m_fDPIScaleY));

	return fResized;
}