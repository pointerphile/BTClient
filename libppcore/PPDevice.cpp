#include "PPDevice.h"

PPDevice::PPDevice() {
}


PPDevice::~PPDevice() {
}

bool PPDevice::InitDevice() {
	m_CreateDevice();
	m_CreateDXGIFactory();
	m_CreateSwapChain();
	m_CreateAndSetRenderTargetView();
	m_SetViewPort();

	return true;
}

bool PPDevice::PreRender() {
	float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_pd3dContext->ClearRenderTargetView(m_pRenderTargetView, color);

	return true;
}

bool PPDevice::PostRender() {
	m_pSwapChain->Present(0, 0);

	return true;
}

bool PPDevice::ReleaseDevice() {
	m_pSwapChain->SetFullscreenState(false, nullptr);

	//m_DirectWrite.Release();

	m_pd3dContext->ClearState();
	m_pd3dContext->Flush();

	if (m_pRenderTargetView) {
		m_pRenderTargetView->Release();
		m_pRenderTargetView = nullptr;
	}
	if (m_pSwapChain) {
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}
	if (m_pd3dContext) {
		m_pd3dContext->Release();
		m_pd3dContext = nullptr;
	}
	if (m_pd3dDevice) {
		m_pd3dDevice->Release();
		m_pd3dDevice = nullptr;
	}
	if (m_pGIFactory) {
		m_pGIFactory->Release();
		m_pGIFactory = nullptr;
	}
	
	return true;
}

HRESULT PPDevice::m_CreateDevice() {
	HRESULT hr;
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);

	for (auto& driverType : driverTypes) {
		hr = D3D11CreateDevice(nullptr, driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &m_pd3dDevice, nullptr, &m_pd3dContext);
		if (SUCCEEDED(hr)) {
			break;
		}
	}

	return hr;
}
HRESULT PPDevice::m_CreateDXGIFactory() {
	HRESULT hr;

	if (FAILED(hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_pGIFactory)))) {
		return false;
	}

	return hr;
}
HRESULT PPDevice::m_CreateSwapChain() {
	HRESULT hr;

	m_pSwapChainDesc.BufferDesc.Width = g_rcWindowClient.right;
	m_pSwapChainDesc.BufferDesc.Height = g_rcWindowClient.bottom;
	m_pSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_pSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	m_pSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_pSwapChainDesc.BufferCount = 1;
	m_pSwapChainDesc.OutputWindow = g_hWnd;
	m_pSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	m_pSwapChainDesc.SampleDesc.Count = 1;
	//pDesc.SwapEffect = ;
	m_pSwapChainDesc.Windowed = true;
	m_pSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	if (FAILED(hr = m_pGIFactory->CreateSwapChain(m_pd3dDevice, &m_pSwapChainDesc, &m_pSwapChain))) {
		return false;
	}

	return hr;
}
HRESULT PPDevice::m_CreateAndSetRenderTargetView() {
	ID3D11Texture2D* pResource;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pResource);
	m_pd3dDevice->CreateRenderTargetView(pResource, nullptr, &m_pRenderTargetView);
	pResource->Release();
	pResource = nullptr;
	//Àû¿ë
	m_pd3dContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

	return true;
}
bool PPDevice::m_SetViewPort() {
	D3D11_VIEWPORT m_vp;

	m_vp.TopLeftX = 0.0f;
	m_vp.TopLeftY = 0.0f;
	m_vp.Width = (float)m_pSwapChainDesc.BufferDesc.Width;
	m_vp.Height = (float)m_pSwapChainDesc.BufferDesc.Height;
	m_vp.MinDepth = 0.0f;
	m_vp.MaxDepth = 1.0f;
	m_pd3dContext->RSSetViewports(1, &m_vp);

	return true;
}

HRESULT PPDevice::m_ResizeDevice(UINT iWidth, UINT iHeight) {
	HRESULT hr = 0;
	if (m_pd3dDevice == nullptr) {
		return true;
	}
	else {
		//m_DirectWrite.m_pRenderTarget->Release();
		//m_DirectWrite.m_pRenderTarget = nullptr;
		//m_DirectWrite.m_pWhiteBrush->Release();
		//m_DirectWrite.m_pWhiteBrush = nullptr;

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
		
		//m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&m_DirectWrite.m_pDXGISurface);
		//m_DirectWrite.CreateDeviceResources();

		return hr;
	}
}