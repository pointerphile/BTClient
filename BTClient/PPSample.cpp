#include "PPSample.h"

PPSample::PPSample() {
}


PPSample::~PPSample() {
}


bool PPSample::Init() {
	m_SceneTimer.Init();

	//LegalWarning
	m_planeLegalWarning.SetID3D11Device(m_pd3dDevice);
	m_planeLegalWarning.SetID3D11DeviceContext(m_pd3dContext);
	m_planeLegalWarning.m_SetPositionAndSize(0, 0, 800, 600);
	m_planeLegalWarning.m_LoadTexture(L"../Texture/LegalWarning.png");
	m_planeLegalWarning.m_SetTexelPositionAndSize(0, 0, 800, 600);
	m_planeLegalWarning.Init();

	m_DirectWrite.m_pDWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, m_DirectWrite.m_GetResizedFont(28), L"en-us", &m_pDWriteTextFormatLegalWarning);

	m_strLegalWarning = L"WARNING\n\n";
	//_LegalWarning
	

	return true;
}

bool PPSample::Frame() {
	m_SceneTimer.Frame();

	return true;
}

bool PPSample::Render() {
	m_planeLegalWarning.Render();
	return true;
}

bool PPSample::Release() {
	m_SceneTimer.Release();
	m_planeLegalWarning.Release();

	m_pDWriteTextFormatLegalWarning->Release();

	return true;
}

