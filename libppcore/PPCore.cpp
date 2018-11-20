#include "PPCore.h"
int64_t g_iFPS;// 1초당 프레임 개수
float g_fSecPerFrame; // 1프레임의 경과시간
float g_fAccumulation;// 실행된 경과 시간
TCHAR* g_csBuffer;

PPCore::PPCore()
{
}

PPCore::~PPCore()
{
}


bool PPCore::GameInit() {
	InitDevice();
	m_Timer.Init();
	
	g_csBuffer = m_Timer.m_csBuffer;

	m_Input.Init();
	m_Sound.Init();
	m_DirectWrite.Init();
	m_DirectWrite.CreateDeviceResources(m_pSwapChain);

	Init();
	
	return true;
}
bool PPCore::GameFrame() {
	m_Timer.Frame();
	m_Input.Frame();
	m_Sound.Frame();

	g_fSecPerFrame = m_Timer.m_fSecondPerFrame;
	g_fAccumulation = m_Timer.m_fAccumulation;

	Frame();
	return true;
}
bool PPCore::GameRender() {
	PreRender();
	m_DirectWrite.PreRender();
	Render();
	m_DirectWrite.Render();
	m_Timer.Render();
	m_Input.Render();
	m_Sound.Render();

	m_DirectWrite.PostRender();
	PostRender();

	return true;
}
bool PPCore::GameRelease() {
	Release();
	
	m_DirectWrite.Release();
	ReleaseDevice();
	m_Sound.Release();
	m_Input.Release();
	m_Timer.Release();

	return true;
}
bool PPCore::GameRun() {
	GameFrame();
	GameRender();
	return true;
}

void PPCore::MsgEvent(MSG msg) {
	m_Input.GetInstance().MsgEvent(msg);
};

HRESULT PPCore::m_ResizeDevice(UINT iWidth, UINT iHeight) {
	HRESULT hr = 0;
	if (m_pd3dDevice == nullptr) {
		return true;
	}
	else {
		m_DirectWrite.m_pRenderTarget->Release();
		m_DirectWrite.m_pRenderTarget = nullptr;
		m_DirectWrite.m_pWhiteBrush->Release();
		m_DirectWrite.m_pWhiteBrush = nullptr;

		m_pd3dContext->OMSetRenderTargets(0, nullptr, nullptr);
		if (m_pRenderTargetView) {
			m_pRenderTargetView->Release();
			m_pRenderTargetView = nullptr;
		}
		DXGI_SWAP_CHAIN_DESC pDesc;
		m_pSwapChain->GetDesc(&pDesc);
		if (FAILED(hr = m_pSwapChain->ResizeBuffers(pDesc.BufferCount, iWidth, iHeight, pDesc.BufferDesc.Format, pDesc.Flags))) {
			return hr;
		}
		m_pSwapChainDesc = { 0 };
		m_pSwapChain->GetDesc(&m_pSwapChainDesc);
		m_CreateAndSetRenderTargetView();
		m_SetViewPort();

		m_DirectWrite.CreateDeviceResources(m_pSwapChain);

		return hr;
	}
}