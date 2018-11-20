#include "PPD3DObject.h"


PPD3DObject::PPD3DObject()
{
}


PPD3DObject::~PPD3DObject()
{
}

bool PPD3DObject::Init() {
	m_BlinkingTimer.Init();

	m_pInputLayout = nullptr;
	m_pVertexShader = nullptr;
	m_pPixelShader = nullptr;
	m_pSamplerState = nullptr;
	m_pAlphaBlend = nullptr;
	m_IsRendering = true;
	m_IsBlinking = false;
	m_IsHide = false;

	m_CreateVertexBuffer();
	m_CreateVertexShader();
	m_CreateSamplerState();
	m_CreatePixelShader();
	m_CreateInputLayout();
	m_CreateBlendState();

	//임시버퍼 해제
	if (m_pVertexShaderBlob) {
		m_pVertexShaderBlob->Release();
	}
	if (m_pErrorBlob) {
		m_pErrorBlob->Release();
	}
	m_pd3dContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_pd3dContext->IASetInputLayout(m_pInputLayout);

	return true;
}

bool PPD3DObject::Frame() {
	m_BlinkingTimer.Frame();
	if (m_IsHide) {
		m_IsRendering = false;
	}

	if (m_IsBlinking) {
		if (m_IsRendering) {
			if (m_BlinkingTimer.m_fAccumulation >= m_fShowTime) {
				m_IsRendering = false;
				m_BlinkingTimer.m_ResetCount();
			}
		}
		else {
			if (m_BlinkingTimer.m_fAccumulation >= m_fHideTime) {
				m_IsRendering = true;
				m_BlinkingTimer.m_ResetCount();
			}
		}
	}

	return true;
}

bool PPD3DObject::Render() {
	m_BlinkingTimer.Render();
	if (m_IsRendering && !(m_IsHide)) {
		m_pd3dContext->OMSetBlendState(m_pAlphaBlend, 0, -1);
		//RSSetState

		m_pd3dContext->VSSetShader(m_pVertexShader, nullptr, 0);
		m_pd3dContext->PSSetShader(m_pPixelShader, nullptr, 0);
		m_pd3dContext->PSSetSamplers(0, 1, &m_pSamplerState);

		//버텍스 1개의 사이즈
		UINT pStrides = sizeof(PPVertex);
		//버텍스 버퍼에서 시작 위치
		UINT pOffsets = 0;

		m_pd3dContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &pStrides, &pOffsets);
		m_pd3dContext->PSSetShaderResources(0, 1, &m_pTextureSRVs.back());
		m_pd3dContext->UpdateSubresource(m_pVertexBuffer, 0, nullptr, m_Vertices, 0, 0);
		m_pd3dContext->Draw(4, 0);
	}

	return true;
}

bool PPD3DObject::Release() {
	while (m_pTextureSRVs.empty() == false) {
		m_pTextureSRVs.back()->Release();
		m_pTextureSRVs.back() = nullptr;
		m_pTextureSRVs.pop_back();
	}
	if (m_pVertexBuffer) {
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;
	}

	if (m_pInputLayout) {
		m_pInputLayout->Release();
	}
	if (m_pVertexShader) {
		m_pVertexShader->Release();
	}
	if (m_pSamplerState) {
		m_pSamplerState->Release();
	}
	if (m_pPixelShader) {
		m_pPixelShader->Release();
	}
	if (m_pAlphaBlend) {
		m_pAlphaBlend->Release();
	}
	m_BlinkingTimer.Release();

	return true;
}

HRESULT PPD3DObject::m_CreateSamplerState() {
	HRESULT hr;
	D3D11_SAMPLER_DESC pSamplerDesc;
	ZeroMemory(&pSamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	pSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	pSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	pSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	pSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	pSamplerDesc.MaxAnisotropy = 16;
	if (FAILED(hr = m_pd3dDevice->CreateSamplerState(&pSamplerDesc, &m_pSamplerState))) {
		return hr;
	}

	return hr;
}

HRESULT PPD3DObject::m_CreateVertexBuffer() {
	//버텍스 버퍼 생성
	//GPU 메모리 확보
	HRESULT hr;

	D3D11_BUFFER_DESC pBufferDesc;
	ZeroMemory(&pBufferDesc, sizeof(D3D11_BUFFER_DESC));
	UINT numVertices = sizeof(m_Vertices) / sizeof(m_Vertices[0]);
	pBufferDesc.ByteWidth = sizeof(PPVertex) * numVertices;
	pBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	pBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//시스템 메모리->GPU 메모리
	D3D11_SUBRESOURCE_DATA pSubresourceData;
	ZeroMemory(&pSubresourceData, sizeof(D3D11_SUBRESOURCE_DATA));
	pSubresourceData.pSysMem = m_Vertices;
	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&pBufferDesc, &pSubresourceData, &(m_pVertexBuffer)))) {
		return false;
	}

	return hr;
}

HRESULT PPD3DObject::m_CreateVertexShader() {
	HRESULT hr;
	//정점 셰이더 컴파일
	//VertexShader.vsh 컴파일
	if (FAILED(hr = D3DCompileFromFile(L"VertexShader.hlsl", nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_DEBUG, 0, &m_pVertexShaderBlob, &m_pErrorBlob))) {
		OutputDebugStringA((char*)m_pErrorBlob->GetBufferPointer());

		return hr;
	}
	//버텍스 셰이더 생성
	//버텍스 셰이더 : 버텍스 버퍼의 정점을 실제 처리하는 곳
	if (FAILED(hr = m_pd3dDevice->CreateVertexShader((DWORD*)m_pVertexShaderBlob->GetBufferPointer(), m_pVertexShaderBlob->GetBufferSize(), nullptr, &m_pVertexShader))) {
		return hr;
	}

	return hr;
}

HRESULT PPD3DObject::m_CreatePixelShader() {
	HRESULT hr;
	//픽셀 셰이더 컴파일 결과
	ID3DBlob* pPixelShaderBlob = 0;
	//PixelShader.psh 컴파일
	if (FAILED(hr = D3DCompileFromFile(L"PixelShader.hlsl", nullptr, nullptr, "main", "ps_5_0", 0, 0, &pPixelShaderBlob, &m_pErrorBlob))) {
		OutputDebugStringA((char*)m_pErrorBlob->GetBufferPointer());

		return hr;
	}
	//픽셀 셰이더 생성
	//픽셀 셰이더 : 버텍스 셰이더 채색
	if (FAILED(hr = m_pd3dDevice->CreatePixelShader((DWORD*)pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), nullptr, &m_pPixelShader))) {
		return hr;
	}
	pPixelShaderBlob->Release();

	return hr;
}

HRESULT PPD3DObject::m_CreateInputLayout() {
	HRESULT hr;
	//레이아웃 설정
	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT, 0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	int iNumElement = sizeof(ied) / sizeof(ied[0]);
	if (FAILED(hr = m_pd3dDevice->CreateInputLayout(ied, iNumElement, m_pVertexShaderBlob->GetBufferPointer(), m_pVertexShaderBlob->GetBufferSize(), &m_pInputLayout))) {
		return hr;
	}

	return hr;
}

HRESULT PPD3DObject::m_LoadTexture(const TCHAR* ImageFileAddress) {
	ID3D11ShaderResourceView* pSRV;
	HRESULT hr;
	if (FAILED(hr = DirectX::CreateWICTextureFromFileEx(m_pd3dDevice, ImageFileAddress, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, &pSRV))) {
		return hr;
	}
	m_pTextureSRVs.push_back(pSRV);
	m_SetTextureResolutionFromSRV();

	return hr;
}

HRESULT PPD3DObject::m_CreateBlendState() {
	HRESULT hr;
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(D3D11_BLEND_DESC));
	BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	if (FAILED(hr = m_pd3dDevice->CreateBlendState(&BlendDesc, &m_pAlphaBlend)))
	{
		return hr;
	}
	return hr;
}

bool PPD3DObject::SetID3D11Device(ID3D11Device* ID3D11Device) {
	m_pd3dDevice = ID3D11Device;
	return true;
}
bool PPD3DObject::SetID3D11DeviceContext(ID3D11DeviceContext* ID3D11DeviceContext) {
	m_pd3dContext = ID3D11DeviceContext;
	return true;
}
bool PPD3DObject::m_SetPosition(long x, long y) {
	m_Position.x = (float)x;
	m_Position.y = (float)y;

	m_SetVertexPosition();

	return true;
}
bool PPD3DObject::m_SetSize(long width, long height) {
	m_Size.x = width;
	m_Size.y = height;

	m_SetVertexPosition();

	return true;
}
bool PPD3DObject::m_SetPositionAndSize(long x, long y, long width, long height) {
	m_Position.x = (float)x;
	m_Position.y = (float)y;
	m_Size.x = width;
	m_Size.y = height;

	m_SetVertexPosition();

	return true;
}
bool PPD3DObject::m_SetTexelPosition(long x, long y) {
	m_TexelPosition.x = (float)x;
	m_TexelPosition.y = (float)y;

	m_SetVertexUV();

	return true;
}

bool PPD3DObject::m_SetTexelSize(long width, long height) {
	m_TexelSize.x = width;
	m_TexelSize.y = height;

	m_SetVertexUV();

	return true;
}
bool PPD3DObject::m_SetTexelPositionAndSize(long x, long y, long width, long height) {
	m_TexelPosition.x = (float)x;
	m_TexelPosition.y = (float)y;
	m_TexelSize.x = width;
	m_TexelSize.y = height;

	m_SetVertexUV();

	return true;
}

bool PPD3DObject::m_SetTextureResolutionFromSRV() {
	ID3D11Resource* pRes;
	ID3D11Texture2D* pTexture2d;

	m_pTextureSRVs.back()->GetResource(&pRes);
	pRes->QueryInterface(&pTexture2d);

	D3D11_TEXTURE2D_DESC Texture2DDesc;
	pTexture2d->GetDesc(&Texture2DDesc);

	m_TextureSize.x = Texture2DDesc.Width;
	m_TextureSize.y = Texture2DDesc.Height;

	pRes->Release();
	pRes = nullptr;
	pTexture2d->Release();
	pTexture2d = nullptr;

	return true;
}
bool PPD3DObject::m_SetVertexPosition() {
	float fVertexWidth;
	float fVertexHeight;

	float fVertexLeft;
	float fVertexTop;
	float fVertexRight;
	float fVertexBottom;

	fVertexWidth = (2.0f * m_Size.x) / (float)g_rcWindowClient.right;
	fVertexHeight = (2.0f * m_Size.y) / (float)g_rcWindowClient.bottom;

	fVertexLeft = ((2.0f * m_Position.x) / (float)g_rcWindowClient.right) - 1.0f;
	fVertexTop = ((2.0f * -m_Position.y) / (float)g_rcWindowClient.bottom) + 1.0f;
	fVertexRight = fVertexLeft + fVertexWidth;
	fVertexBottom = fVertexTop - fVertexHeight;

	m_Vertices[0].m_position = DirectX::XMFLOAT3(fVertexLeft, fVertexTop, 0.0f);
	m_Vertices[1].m_position = DirectX::XMFLOAT3(fVertexRight, fVertexTop, 0.0f);
	m_Vertices[2].m_position = DirectX::XMFLOAT3(fVertexLeft, fVertexBottom, 0.0f);
	m_Vertices[3].m_position = DirectX::XMFLOAT3(fVertexRight, fVertexBottom, 0.0f);

	return true;
}
bool PPD3DObject::m_SetVertexUV() {
	float fWidth;
	float fHeight;

	float fTop;
	float fLeft;
	float fBottom;
	float fRight;

	fWidth = m_TexelSize.x / (float)m_TextureSize.x;
	fHeight = m_TexelSize.y / (float)m_TextureSize.y;

	fTop = m_TexelPosition.y / (float)m_TextureSize.y;
	fLeft = m_TexelPosition.x / (float)m_TextureSize.x;
	fBottom = fTop + fHeight;
	fRight = fLeft + fWidth;

	m_Vertices[0].m_texture = DirectX::XMFLOAT2(fLeft, fTop);
	m_Vertices[1].m_texture = DirectX::XMFLOAT2(fRight, fTop);
	m_Vertices[2].m_texture = DirectX::XMFLOAT2(fLeft, fBottom);
	m_Vertices[3].m_texture = DirectX::XMFLOAT2(fRight, fBottom);

	return true;
}

bool PPD3DObject::m_TranslatePerSecond(long x, long y) {
	m_Position.x = m_Position.x + ((float)x * g_fSecPerFrame);
	m_Position.y = m_Position.y + ((float)y * g_fSecPerFrame);

	m_SetVertexPosition();

	return true;
}

bool PPD3DObject::m_TranslateUVPerSecond(long x, long y) {
	m_TexelPosition.x = m_TexelPosition.x + ((float)x * g_fSecPerFrame);
	m_TexelPosition.y = m_TexelPosition.y + ((float)y * g_fSecPerFrame);

	m_SetVertexUV();

	return true;
}

bool PPD3DObject::m_SetBlinkingTime(float fShowTime, float fHideTime) {
	m_fShowTime = fShowTime;
	m_fHideTime = fHideTime;

	return true;
}

bool PPD3DObject::m_SetBlinking(bool IsBlinking) {
	m_IsBlinking = IsBlinking;
	//m_BlinkingTimer.m_ResetCount();

	return true;
}