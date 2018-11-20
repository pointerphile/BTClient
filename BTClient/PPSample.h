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
	PPD3DObject m_planeInsertCredit;
	PPD3DObject m_planeLegalWarning;
	PPD3DObject m_planeSplashScreen;
	PPD3DObject m_planeCurtainTop;
	PPD3DObject m_planeCurtainLeft;
	PPD3DObject m_planeCurtainRight;
	PPD3DObject m_planeTitlescreen;
	PPD3DObject m_planePressStart;
	PPD3DObject m_planeJudgeLine;
	PPD3DObject m_planeManual;
	PPD3DObject m_planeGameOver;
	PPD3DObject m_planeCongratuation;

	PPReel m_Reel[3];
	ReelState m_ReelState[3];

	RNG m_RNG;
	PPTimer m_SceneTimer;
	PPBank m_Bank;
	IDWriteTextFormat* m_pDWriteTextFormatLegalWarning;
	IDWriteTextFormat* m_pDWriteTextFormatCredit;
	IDWriteTextFormat* m_pDWriteTextFormatContinue;

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

	bool (PPSample::*m_InitStage)();
	bool (PPSample::*m_FrameStage)();
	bool (PPSample::*m_RenderStage)();
	
	PPSample();
	virtual ~PPSample();

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	bool m_InitLegalWarning();
	bool m_FrameLegalWarning();
	bool m_RenderLegalWarning();
	bool m_InitSplashScreen();
	bool m_FrameSplashScreen();
	bool m_RenderSplashScreen();
	bool m_InitOpeningScreen();
	bool m_FrameOpeningScreen();
	bool m_RenderOpeningScreen();
	bool m_InitTitleScreen();
	bool m_FrameTitleScreen();
	bool m_RenderTitleScreen();
	bool m_InitGame();
	bool m_FrameGame();
	bool m_RenderGame();
	bool m_InitGameOver();
	bool m_FrameGameOver();
	bool m_RenderGameOver();
	bool m_InitCongratuation();
	bool m_FrameCongratuation();
	bool m_RenderCongratuation();
	ReelState m_ReelSelector(int iRandomNumber);
	bool m_RenderInsertCredit();
	bool m_InsertCredit();
	void m_JudgeReel();
};