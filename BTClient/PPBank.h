#pragma once
#include "../libppcore/PPCore.h"
class PPBank
{
public:
	uint64_t m_uiCredit;
	uint64_t m_uiBet;
	uint64_t m_uiPrize;

	std::wstring m_wstrCredit;
	std::wstring m_wstrBet;
	std::wstring m_wstrPrize;
	std::wstring m_wstrHUD;

	PPDirectWrite* m_pDirectWrite;
	IDWriteTextFormat* m_pDWriteTextFormat;

	PPBank();
	virtual ~PPBank();

	bool Init();
	bool Frame();
	bool Render();
	bool Release() { return true; };

	bool m_SetDirectWrite(PPDirectWrite* PPDirectWrite);
	bool m_AddCredit(int iCredit);
	bool m_GetPrize();
};

