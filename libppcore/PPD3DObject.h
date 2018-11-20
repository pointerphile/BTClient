#pragma once
#include "PPBasis.h"
#include "PPTimer.h"

struct PPVertex {
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT2 m_texture;
};

class PPD3DObject : public PPBasis
{
public:
	ID3D11Device*							m_pd3dDevice;
	ID3D11DeviceContext*					m_pd3dContext;

	ID3D11InputLayout*						m_pInputLayout;
	ID3D11VertexShader*						m_pVertexShader;
	ID3D11SamplerState*						m_pSamplerState;
	ID3D11PixelShader*						m_pPixelShader;
	ID3D11BlendState*						m_pAlphaBlend;

	ID3DBlob*								m_pVertexShaderBlob = 0;
	ID3DBlob*								m_pErrorBlob = 0;

	PPVertex								m_Vertices[4];
	ID3D11Buffer*							m_pVertexBuffer;
	std::vector<ID3D11ShaderResourceView*>	m_pTextureSRVs;

	DirectX::XMFLOAT2						m_Position;
	DirectX::XMFLOAT2						m_TexelPosition;
	DirectX::XMINT2							m_Size;
	DirectX::XMINT2							m_TexelSize;
	DirectX::XMINT2							m_TextureSize;

	PPTimer									m_BlinkingTimer;
	float m_fShowTime;
	float m_fHideTime;
	bool									m_IsRendering;
	bool									m_IsBlinking;
	bool									m_IsHide;


	PPD3DObject();
	virtual ~PPD3DObject();

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	bool SetID3D11Device(ID3D11Device* ID3D11Device);
	bool SetID3D11DeviceContext(ID3D11DeviceContext* ID3D11DeviceContext);
	bool m_SetPosition(long x, long y);
	bool m_SetSize(long width, long height);
	bool m_SetPositionAndSize(long x, long y, long width, long height);
	bool m_SetTexelPosition(long x, long y);
	bool m_SetTexelSize(long width, long height);
	bool m_SetTexelPositionAndSize(long x, long y, long width, long height);
	bool m_SetTextureResolutionFromSRV();
	bool m_SetVertexPosition();

	bool m_SetVertexUV();

	bool m_TranslatePerSecond(long x, long y);

	bool m_TranslateUVPerSecond(long x, long y);

	bool m_SetBlinkingTime(float fShowTime, float fHideTime);

	bool m_SetBlinking(bool IsBlinking);

	HRESULT m_CreateSamplerState();
	HRESULT m_CreateVertexBuffer();
	HRESULT m_CreateVertexShader();
	HRESULT m_CreatePixelShader();
	HRESULT m_CreateInputLayout();
	HRESULT m_LoadTexture(const TCHAR* ImageFileAddress);
	HRESULT m_CreateBlendState();
	//CreateRasterizerState;
};