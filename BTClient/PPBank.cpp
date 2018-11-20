#include "PPBank.h"


PPBank::PPBank()
{
}


PPBank::~PPBank()
{
}

bool PPBank::Init() {
	m_uiCredit = 0;
	m_pDirectWrite->m_pDWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_ITALIC, DWRITE_FONT_STRETCH_NORMAL, m_pDirectWrite->m_GetResizedFont(20), L"en-us", &m_pDWriteTextFormat);
	m_pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
	return true;
}
bool PPBank::Frame() {
	m_wstrCredit = std::to_wstring(this->m_uiCredit);
	m_wstrCredit.append(L" Credit(s)");

	m_wstrBet = L"BET :\n";
	m_wstrBet.append(std::to_wstring(this->m_uiBet));

	m_wstrPrize = L"PRIZE :\n";
	m_wstrPrize.append(std::to_wstring(this->m_uiPrize));

	m_wstrHUD.clear();
	m_wstrHUD.append(m_wstrBet);
	m_wstrHUD.append(L"\n");
	m_wstrHUD.append(m_wstrPrize);

	return true;
}
bool PPBank::Render() {
	D2D1_RECT_F rectCredit = D2D1::RectF(0.0f, (float)g_rcWindowClient.bottom - 40, (float)g_rcWindowClient.right - 20, (float)g_rcWindowClient.bottom);
	m_pDirectWrite->m_DrawText(m_wstrCredit.c_str(), (UINT32)m_wstrCredit.size(), m_pDWriteTextFormat, rectCredit, m_pDirectWrite->m_pWhiteBrush);
	
	return true;
}

bool PPBank::m_SetDirectWrite(PPDirectWrite* PPDirectWrite)
{
	m_pDirectWrite = PPDirectWrite;
	return false;
}

bool PPBank::m_AddCredit(int iCredit)
{
	m_uiCredit = m_uiCredit + iCredit;
	return true;
}

bool PPBank::m_GetPrize()
{
	m_uiCredit = m_uiCredit + m_uiPrize;
	return false;
}
