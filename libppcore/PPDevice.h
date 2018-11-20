#pragma once
#include "PPWindow.h"


class PPDevice : public PPWindow {
public:
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pd3dContext;
	IDXGISwapChain* m_pSwapChain = { 0 };
	DXGI_SWAP_CHAIN_DESC m_pSwapChainDesc;
	IDXGIFactory*  m_pGIFactory;
	ID3D11RenderTargetView* m_pRenderTargetView;

	PPDevice();
	virtual ~PPDevice();

	virtual bool Init() { return true; };
	virtual bool Frame() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };

	virtual bool GameInit() { return true; };
	virtual bool GameFrame() { return true; };
	virtual bool GameRender() { return true; };
	virtual bool GameRelease() { return true; };
	virtual bool GameRun() { return true; };
	virtual HRESULT m_ResizeDevice(UINT width, UINT height);

	HRESULT m_CreateDevice();
	HRESULT m_CreateDXGIFactory();
	HRESULT m_CreateSwapChain();
	HRESULT m_CreateAndSetRenderTargetView();
	bool m_SetViewPort();

	bool InitDevice();
	bool PreRender();
	bool PostRender();
	bool ReleaseDevice();
};

