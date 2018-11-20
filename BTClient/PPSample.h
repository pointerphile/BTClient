#pragma once
#include "../libppcore/PPCore.h"
#include "RNG.h"
#include "PPBank.h"
#include "PPReel.h"
#include <functional>

#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/libppcore.lib")
#endif // _DEBUG
#ifndef _DEBUG
#pragma comment(lib, "PPCoreLib.lib")
#endif // _DEBUG

class PPSample : public PPCore
{
public:
	PPD3DObject m_planeLegalWarning;

	RNG m_RNG;
	PPTimer m_SceneTimer;
	IDWriteTextFormat* m_pDWriteTextFormatLegalWarning;

	bool m_isRunning;
	bool m_isPlayable;
	bool m_IsDemoPlay;

	int m_iDemoCount;
	float m_fConitnueCount;

	//LegalWarning
	std::wstring m_strLegalWarning;
	int m_iStrLegalWarningCount;
	//_LegalWarning

	//SplashScreen
	//_SplashScreen

	//OpeningScreen
	//_OpeningScreen

	//Titlescreen
	//_Titlescreen
	
	PPSample();
	virtual ~PPSample();

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	ReelState m_ReelSelector(int iRandomNumber);
	bool m_RenderInsertCredit();
	void m_JudgeReel();
};