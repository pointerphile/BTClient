#include "PPSample.h"

PPSample::PPSample() {
}


PPSample::~PPSample() {
}


bool PPSample::Init() {
	m_SceneTimer.Init();
	m_Bank.m_SetDirectWrite(&m_DirectWrite);
	m_Bank.Init();
	
	m_planeJudgeLine.SetID3D11Device(m_pd3dDevice);
	m_planeJudgeLine.SetID3D11DeviceContext(m_pd3dContext);
	m_planeJudgeLine.m_SetPositionAndSize(30, 30 + 132 - 4, 407, 3);
	m_planeJudgeLine.m_LoadTexture(L"../Texture/bar.bmp");
	m_planeJudgeLine.m_SetTexelPositionAndSize(0, 0, 407, 3);
	m_planeJudgeLine.Init();

	m_planeManual.SetID3D11Device(m_pd3dDevice);
	m_planeManual.SetID3D11DeviceContext(m_pd3dContext);
	m_planeManual.m_SetPositionAndSize(100, 320, 270, 212);
	m_planeManual.m_LoadTexture(L"../Texture/sign.bmp");
	m_planeManual.m_SetTexelPositionAndSize(0, 0, 270, 212);
	m_planeManual.Init();

	m_planeGameOver.SetID3D11Device(m_pd3dDevice);
	m_planeGameOver.SetID3D11DeviceContext(m_pd3dContext);
	m_planeGameOver.m_SetPositionAndSize(0, 0, 800, 600);
	m_planeGameOver.m_LoadTexture(L"../Texture/GameOver.png");
	m_planeGameOver.m_SetTexelPositionAndSize(0, 0, 800, 600);
	m_planeGameOver.Init();

	m_planeCongratuation.SetID3D11Device(m_pd3dDevice);
	m_planeCongratuation.SetID3D11DeviceContext(m_pd3dContext);
	m_planeCongratuation.m_SetPositionAndSize(0, 0, 800, 600);
	m_planeCongratuation.m_LoadTexture(L"../Texture/Congratuation.png");
	m_planeCongratuation.m_SetTexelPositionAndSize(0, 0, 800, 600);
	m_planeCongratuation.Init();

	for (int i = 0; i < 3; i++) {
		m_Reel[i].SetID3D11Device(m_pd3dDevice);
		m_Reel[i].SetID3D11DeviceContext(m_pd3dContext);
		m_Reel[i].m_SetPositionAndSize(30, 30, 129, 259);
		m_Reel[i].m_LoadTexture(L"../Texture/reel.bmp");
		m_Reel[i].m_SetTexelPositionAndSize(0, 65 * 2, 129, 259);
		m_Reel[i].Init();
	}

	m_Reel[1].m_SetPosition(30 + 129 + 10, 30);
	m_Reel[2].m_SetPosition(30 + 129 + 10 + 129 + 10, 30);
	m_Reel[0].m_SetRollingTime(1);
	m_Reel[1].m_SetRollingTime(2);
	m_Reel[2].m_SetRollingTime(3);

	m_planeInsertCredit.SetID3D11Device(m_pd3dDevice);
	m_planeInsertCredit.SetID3D11DeviceContext(m_pd3dContext);
	m_planeInsertCredit.m_SetPositionAndSize(0, 300, 800, 150);
	m_planeInsertCredit.m_LoadTexture(L"../Texture/InsertCredit.png");
	m_planeInsertCredit.m_SetTexelPositionAndSize(0, 0, 800, 150);
	m_planeInsertCredit.Init();
	m_planeInsertCredit.m_SetBlinking(true);
	m_planeInsertCredit.m_SetBlinkingTime(1.0f , 1.0f);
	m_planeInsertCredit.m_IsHide = true;

	m_planePressStart.SetID3D11Device(m_pd3dDevice);
	m_planePressStart.SetID3D11DeviceContext(m_pd3dContext);
	m_planePressStart.m_SetPositionAndSize(0, 300, 800, 150);
	m_planePressStart.m_LoadTexture(L"../Texture/PressStart.png");
	m_planePressStart.m_SetTexelPositionAndSize(0, 0, 800, 150);
	m_planePressStart.Init();
	m_planePressStart.m_SetBlinking(true);
	m_planePressStart.m_SetBlinkingTime(1.0f, 1.0f);
	m_planePressStart.m_IsHide = true;

	//LegalWarning
	m_planeLegalWarning.SetID3D11Device(m_pd3dDevice);
	m_planeLegalWarning.SetID3D11DeviceContext(m_pd3dContext);
	m_planeLegalWarning.m_SetPositionAndSize(0, 0, 800, 600);
	m_planeLegalWarning.m_LoadTexture(L"../Texture/LegalWarning.png");
	m_planeLegalWarning.m_SetTexelPositionAndSize(0, 0, 800, 600);
	m_planeLegalWarning.Init();

	m_DirectWrite.m_pDWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, m_DirectWrite.m_GetResizedFont(28), L"en-us", &m_pDWriteTextFormatLegalWarning);
	m_DirectWrite.m_pDWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, m_DirectWrite.m_GetResizedFont(28), L"en-us", &m_pDWriteTextFormatCredit);
	m_pDWriteTextFormatCredit->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
	m_DirectWrite.m_pDWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, m_DirectWrite.m_GetResizedFont(50), L"en-us", &m_pDWriteTextFormatContinue);
	m_pDWriteTextFormatContinue->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pDWriteTextFormatContinue->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	

	m_strLegalWarning = L"WARNING\n\n";
	m_strLegalWarning.append(L"THIS GAME IS FOR USE ON EARTH AND\n");
	m_strLegalWarning.append(L"BY EARTHIAN ONLY. SALES, EXPORT, OR\n");
	m_strLegalWarning.append(L"OPERATION OUTSIDE THIS PLANET AND/OR\n");
	m_strLegalWarning.append(L"TO THE EXTRATERRESTRIALS MAY BE\n");
	m_strLegalWarning.append(L"CONSTRUED AS COPYRIGHT AND TRADEMARK\n");
	m_strLegalWarning.append(L"INFRINGEMENT.\n");
	m_strLegalWarning.append(L"VIOLATORS ARE SUBJECT TO SEVERE\n");
	m_strLegalWarning.append(L"PENALTIES AND WILL BE PROSECUTED TO\n");
	m_strLegalWarning.append(L"THE FULL EXTENT OF THE LAW.");
	//_LegalWarning
	
	//SplashScreen
	m_planeSplashScreen.SetID3D11Device(m_pd3dDevice);
	m_planeSplashScreen.SetID3D11DeviceContext(m_pd3dContext);
	m_planeSplashScreen.m_SetPositionAndSize(0, 0, 800, 600);
	m_planeSplashScreen.m_LoadTexture(L"../Texture/SplashScreen.png");
	m_planeSplashScreen.m_SetTexelPositionAndSize(0, 0, 800, 600);
	m_planeSplashScreen.Init();
	//_SplashScreen

	//OpeningScreen and Titlescreen
	m_planeCurtainTop.SetID3D11Device(m_pd3dDevice);
	m_planeCurtainTop.SetID3D11DeviceContext(m_pd3dContext);
	m_planeCurtainTop.m_SetPositionAndSize(0, 0, 800, 90);
	m_planeCurtainTop.m_LoadTexture(L"../Texture/curtain_top.png");
	m_planeCurtainTop.m_SetTexelPositionAndSize(0, 0, 800, 90);
	m_planeCurtainTop.Init();

	m_planeCurtainLeft.SetID3D11Device(m_pd3dDevice);
	m_planeCurtainLeft.SetID3D11DeviceContext(m_pd3dContext);
	m_planeCurtainLeft.m_SetPositionAndSize(0, 0, 290, 600);
	m_planeCurtainLeft.m_LoadTexture(L"../Texture/curtain_left.png");
	m_planeCurtainLeft.m_SetTexelPositionAndSize(0, 0, 290, 600);
	m_planeCurtainLeft.Init();

	m_planeCurtainRight.SetID3D11Device(m_pd3dDevice);
	m_planeCurtainRight.SetID3D11DeviceContext(m_pd3dContext);
	m_planeCurtainRight.m_SetPositionAndSize(510, 0, 290, 600);
	m_planeCurtainRight.m_LoadTexture(L"../Texture/curtain_right.png");
	m_planeCurtainRight.m_SetTexelPositionAndSize(0, 0, 290, 600);
	m_planeCurtainRight.Init();

	m_planeTitlescreen.SetID3D11Device(m_pd3dDevice);
	m_planeTitlescreen.SetID3D11DeviceContext(m_pd3dContext);
	m_planeTitlescreen.m_SetPositionAndSize(0, -600, 800, 600);
	m_planeTitlescreen.m_LoadTexture(L"../Texture/Titlescreen.png");
	m_planeTitlescreen.m_SetTexelPositionAndSize(0, 0, 800, 600);
	m_planeTitlescreen.Init();
	//_OpeningScreen and Titlescreen

	m_InitStage = &PPSample::m_InitLegalWarning;
	(this->*m_InitStage)();
	m_FrameStage = &PPSample::m_FrameLegalWarning;
	m_RenderStage = &PPSample::m_RenderLegalWarning;

	return true;
}

bool PPSample::Frame() {
	
	m_SceneTimer.Frame();
	m_Bank.Frame();
	(this->*m_FrameStage)();
	m_planeInsertCredit.Frame();
	m_planePressStart.Frame();
	m_InsertCredit();

	return true;
}

bool PPSample::Render() {
	m_SceneTimer.Render();
	(this->*m_RenderStage)();
	m_Bank.Render();
	m_planeInsertCredit.Render();
	m_planePressStart.Render();
	return true;
}

bool PPSample::Release() {
	for (auto& plane : m_Reel) {
		plane.Release();
	}
	m_SceneTimer.Release();
	m_planeInsertCredit.Release();
	m_planeLegalWarning.Release();
	m_planeSplashScreen.Release();
	m_planeCurtainTop.Release();
	m_planeCurtainLeft.Release();
	m_planeCurtainRight.Release();
	m_planeTitlescreen.Release();
	m_planePressStart.Release();
	m_planeJudgeLine.Release();
	m_planeManual.Release();
	m_planeGameOver.Release();
	m_planeCongratuation.Release();

	m_pDWriteTextFormatLegalWarning->Release();
	m_pDWriteTextFormatCredit->Release();

	return true;
}

bool PPSample::m_InitLegalWarning() {
	m_iStrLegalWarningCount = (int)m_strLegalWarning.size();

	return true;
}
bool PPSample::m_FrameLegalWarning() {
	if (m_iStrLegalWarningCount>0) {
		if (PPInput::GetInstance().KeyCheck(VK_SPACE) == KEY_UP) {
			m_iStrLegalWarningCount = 0;
		}
		if (m_SceneTimer.m_fAccumulation > 0.1f) {
			m_iStrLegalWarningCount--;
			m_SceneTimer.m_fAccumulation = 0.0f;
		}
	}
	else {
		if ((m_SceneTimer.m_fAccumulation > 5.0f) || (PPInput::GetInstance().KeyCheck(VK_SPACE) == KEY_UP)) {
			m_InitStage = &PPSample::m_InitSplashScreen;
			m_FrameStage = &PPSample::m_FrameSplashScreen;
			m_RenderStage = &PPSample::m_RenderSplashScreen;
			(this->*m_InitStage)();
		}
	}
	return true;
}
bool PPSample::m_RenderLegalWarning() {
	D2D1_RECT_F rectLegalWarning = D2D1::RectF(20.0f, 20.0f, g_rcWindowClient.right - 20.0f, g_rcWindowClient.bottom - 20.0f);
	m_DirectWrite.m_pRenderTarget->DrawTextW(m_strLegalWarning.c_str(), (UINT32)(m_strLegalWarning.size() - m_iStrLegalWarningCount),
		m_pDWriteTextFormatLegalWarning, rectLegalWarning, m_DirectWrite.m_pWhiteBrush);

	m_planeLegalWarning.Render();

	return true;
}

bool PPSample::m_InitSplashScreen() {
	m_SceneTimer.m_fAccumulation = 0.0f;
	m_planeInsertCredit.m_IsHide = false;
	return true;
}
bool PPSample::m_FrameSplashScreen() {
	if (m_Bank.m_uiCredit) {
		m_InitStage = &PPSample::m_InitTitleScreen;
		m_FrameStage = &PPSample::m_FrameTitleScreen;
		m_RenderStage = &PPSample::m_RenderTitleScreen;
		(this->*m_InitStage)();
	}
	if ((PPInput::GetInstance().KeyCheck(VK_SPACE) == KEY_UP)) {
		m_InitStage = &PPSample::m_InitOpeningScreen;
		m_FrameStage = &PPSample::m_FrameOpeningScreen;
		m_RenderStage = &PPSample::m_RenderOpeningScreen;
		(this->*m_InitStage)();
	}
	if (m_SceneTimer.m_fAccumulation > 5.0f) {
		m_InitStage = &PPSample::m_InitOpeningScreen;
		m_FrameStage = &PPSample::m_FrameOpeningScreen;
		m_RenderStage = &PPSample::m_RenderOpeningScreen;
		(this->*m_InitStage)();
	}

	return true;
}
bool PPSample::m_RenderSplashScreen() {
	m_planeSplashScreen.Render();

	return true;
}

bool PPSample::m_InitOpeningScreen() {
	m_planeCurtainLeft.m_SetPosition(0, 0);
	m_planeCurtainRight.m_SetPosition(510, 0);
	m_planeTitlescreen.m_SetPosition(0, -600);
	m_SceneTimer.m_fAccumulation = 0.0f;

	return true;
}
bool PPSample::m_FrameOpeningScreen() {
	if ((PPInput::GetInstance().KeyCheck(VK_SPACE) == KEY_UP)) {
		m_InitStage = &PPSample::m_InitTitleScreen;
		m_FrameStage = &PPSample::m_FrameTitleScreen;
		m_RenderStage = &PPSample::m_RenderTitleScreen;
		(this->*m_InitStage)();

		m_SceneTimer.m_fAccumulation = 0.0f;
	}

	if (m_planeCurtainRight.m_Position.x < 800 && m_SceneTimer.m_fAccumulation > 0.5f) {
		m_planeCurtainLeft.m_TranslatePerSecond(-150, 0);
		m_planeCurtainRight.m_TranslatePerSecond(150, 0);
	}
	else if (m_planeCurtainRight.m_Position.x >= 800 && m_planeTitlescreen.m_Position.y < 0) {
		m_planeTitlescreen.m_TranslatePerSecond(0, 100);
		m_SceneTimer.m_fAccumulation = 0.0f;
	}
	if ((m_planeTitlescreen.m_Position.y >= 0) || m_Bank.m_uiCredit) {
		m_InitStage = &PPSample::m_InitTitleScreen;
		m_FrameStage = &PPSample::m_FrameTitleScreen;
		m_RenderStage = &PPSample::m_RenderTitleScreen;
		(this->*m_InitStage)();

		m_SceneTimer.m_fAccumulation = 0.0f;
	}
	return true;
}
bool PPSample::m_RenderOpeningScreen() {
	m_planeCurtainLeft.Render();
	m_planeCurtainRight.Render();
	m_planeTitlescreen.Render();
	m_planeCurtainTop.Render();

	return true;
}

bool PPSample::m_InitTitleScreen() {
	m_SceneTimer.m_fAccumulation = 0.0f;
	m_planePressStart.m_IsHide = true;
	m_planeTitlescreen.m_SetPosition(0, 0);

	return true;
}
bool PPSample::m_FrameTitleScreen() {
	m_RenderInsertCredit();
	if ((PPInput::GetInstance().KeyCheck(VK_SPACE) == KEY_UP) && m_Bank.m_uiCredit) {
		m_InitStage = &PPSample::m_InitGame;
		m_FrameStage = &PPSample::m_FrameGame;
		m_RenderStage = &PPSample::m_RenderGame;
		(this->*m_InitStage)();

		m_SceneTimer.m_fAccumulation = 0.0f;
		m_IsDemoPlay = false;
	}

	if (m_SceneTimer.m_fAccumulation > 3.0f && !(m_Bank.m_uiCredit)) {
		m_SceneTimer.m_fAccumulation = 0.0f;
		m_IsDemoPlay = true;

		m_InitStage = &PPSample::m_InitGame;
		m_FrameStage = &PPSample::m_FrameGame;
		m_RenderStage = &PPSample::m_RenderGame;
		(this->*m_InitStage)();
	}
	return true;
}
bool PPSample::m_RenderTitleScreen() {
	m_planeTitlescreen.Render();
	m_planeCurtainTop.Render();

	return true;
}

bool PPSample::m_InitGame() {
	m_isPlayable = false;
	m_isRunning = false;
	m_planeInsertCredit.m_IsHide = true;
	m_planePressStart.m_IsHide = true;
	m_fConitnueCount = 10.0f;

	for (int i = 0; i < 3; i++) {
		m_Reel[i].m_isRoll = false;
		m_ReelState[i] = SEVEN;
		m_Reel[i].m_SetReelState(m_ReelState[i]);
		m_Reel[i].m_SetReelPosition();
		m_ReelState[i] = m_ReelSelector(m_RNG.GetRandomNumber(1, 95));
		m_Reel[i].m_SetReelState(m_ReelState[i]);
 		if (m_IsDemoPlay) {
			m_iDemoCount = 0;
			m_Reel[i].m_SetReelRoll();
		}
	}

	return true;
}
bool PPSample::m_FrameGame() {
	if (m_IsDemoPlay) {
		m_planeInsertCredit.m_IsHide = false;
		if (m_SceneTimer.m_fAccumulation > 4.0f) {
			for (int i = 0; i < 3; i++) {
				m_Reel[i].m_SetReelRoll();
				m_ReelState[i] = m_ReelSelector(m_RNG.GetRandomNumber(1, 95));
				m_Reel[i].m_SetReelState(m_ReelState[i]);
				m_iDemoCount++;
			}
			m_SceneTimer.m_fAccumulation = 0;

			if (m_iDemoCount > 6) {
				m_InitStage = &PPSample::m_InitSplashScreen;
				m_FrameStage = &PPSample::m_FrameSplashScreen;
				m_RenderStage = &PPSample::m_RenderSplashScreen;
				(this->*m_InitStage)();
			}
		}
	}
	else {
		if (m_Bank.m_uiCredit) {
			if (PPInput::GetInstance().KeyCheck(VK_RETURN) == KEY_UP) {
				m_Bank.m_uiCredit = 0;
				m_InitStage = &PPSample::m_InitCongratuation;
				m_FrameStage = &PPSample::m_FrameCongratuation;
				m_RenderStage = &PPSample::m_RenderCongratuation;
				(this->*m_InitStage)();
			}
		}

		if ((m_Bank.m_uiCredit == 0) && !(m_Bank.m_uiPrize == 0)) {
			m_isPlayable = true;
		}
		else if ((m_Bank.m_uiCredit == 0) && !(m_Bank.m_uiBet == 0) && !(m_Bank.m_uiPrize == 0)) {
			m_Bank.m_uiBet = 0;
			m_isPlayable = true;
		}
		else if ((m_Bank.m_uiCredit == 0) && (m_Bank.m_uiBet == 0) && !(m_Bank.m_uiPrize == 0)) {
			m_isPlayable = false;
		}
		else if ((m_Bank.m_uiCredit == 0) && !(m_Bank.m_uiBet == 0) && (m_Bank.m_uiPrize == 0)) {
			m_isPlayable = false;
		}
		else if ((m_Bank.m_uiCredit == 0) && (m_Bank.m_uiBet == 0) && (m_Bank.m_uiPrize == 0)) {
			m_isPlayable = false;
		}
		else if ((m_Bank.m_uiCredit == 0) && (m_Bank.m_uiPrize == 0)) {
			m_isPlayable = false;
		}
		else if (m_Bank.m_uiCredit - m_Bank.m_uiBet < 0) {
			m_isPlayable = false;
		}
		else if (m_Bank.m_uiBet == 0) {
			m_isPlayable = false;
		}
		else {
			m_isPlayable = true;
		}

		if (m_isRunning == false) {
			if (PPInput::GetInstance().KeyCheck(VK_UP) == KEY_UP) {
				if (m_Bank.m_uiBet < m_Bank.m_uiCredit) {
					m_Bank.m_uiBet = m_Bank.m_uiBet + 1000;
				}
			}
			if (PPInput::GetInstance().KeyCheck(VK_DOWN) == KEY_UP) {
				if (m_Bank.m_uiBet > 0) {
					m_Bank.m_uiBet = m_Bank.m_uiBet - 1000;
				}
			}
		}

		if (m_isPlayable == true && m_isRunning == false) {
			m_fConitnueCount = 10.0f;
			if (PPInput::GetInstance().KeyCheck(VK_SPACE) == KEY_UP) {
				m_isPlayable = false;
				m_isRunning = true;
				m_Bank.m_GetPrize();
				m_Bank.m_uiCredit = m_Bank.m_uiCredit - m_Bank.m_uiBet;
				m_Bank.m_uiPrize = 0;
				for (int i = 0; i < 3; i++) {
					m_Reel[i].m_SetReelRoll();
					m_ReelState[i] = m_ReelSelector(m_RNG.GetRandomNumber(1, 95));
					m_Reel[i].m_SetReelState(m_ReelState[i]);
				}
			}
			else if (PPInput::GetInstance().KeyCheck(VK_END) == KEY_UP) {
				m_isPlayable = false;
				m_isRunning = true;
				m_Bank.m_GetPrize();
				m_Bank.m_uiCredit = m_Bank.m_uiCredit - m_Bank.m_uiBet;
				m_Bank.m_uiPrize = 0;
				for (int i = 0; i < 3; i++) {
					m_Reel[i].m_SetReelRoll();
					//m_ReelState[i] = m_ReelSelector(m_RNG(1, 95));
					//for debugging
					m_ReelState[i] = SEVEN;
					//
					m_Reel[i].m_SetReelState(m_ReelState[i]);
				}
			}
		}
		if (m_Reel[0].m_GetIsFinished() && m_Reel[1].m_GetIsFinished() && m_Reel[2].m_GetIsFinished()) {
			m_isPlayable = true;
			m_JudgeReel();
			//m_Bank.m_GetPrize();
			for (int i = 0; i < 3; i++) {
				m_Reel[i].m_initializeRoll();
			}
			m_isRunning = false;
		}
		if ((m_Bank.m_uiCredit + m_Bank.m_uiPrize == 0) && !(m_isRunning)) {
			m_Bank.m_uiBet = 0;
			m_fConitnueCount = m_fConitnueCount - (1 * g_fSecPerFrame);

			if (m_fConitnueCount < 1.0f) {
				m_InitStage = &PPSample::m_InitGameOver;
				m_FrameStage = &PPSample::m_FrameGameOver;
				m_RenderStage = &PPSample::m_RenderGameOver;
				(this->*m_InitStage)();
			}
		}

	}

	for (auto& plane : m_Reel) {
		plane.Frame();
	}
	return true;


}
bool PPSample::m_RenderGame() {
	for (auto& plane : m_Reel) {
		plane.Render();
	}
	m_planeJudgeLine.Render();
	m_planeManual.Render();

	D2D1_RECT_F rectHUD = D2D1::RectF(0.0f, (float)g_rcWindowClient.top + 30, (float)g_rcWindowClient.right - 30, (float)g_rcWindowClient.bottom);
	m_DirectWrite.m_DrawText(m_Bank.m_wstrHUD.c_str(), (UINT32)m_Bank.m_wstrHUD.size(), m_DirectWrite.m_pDWriteTextFormat, rectHUD, m_DirectWrite.m_pWhiteBrush);

	if ((m_Bank.m_uiCredit + m_Bank.m_uiPrize == 0) && !(m_isRunning) && !(m_IsDemoPlay)) {

		std::wstring wstrContinue = L"CONTINUE?";
		wstrContinue.append(std::to_wstring(((int)m_fConitnueCount)));
		D2D1_RECT_F rect = D2D1::RectF(0.0f, 0.0f, (float)g_rcWindowClient.right, (float)g_rcWindowClient.bottom);
		m_DirectWrite.m_DrawText(wstrContinue.c_str(), (UINT32)wstrContinue.size(), m_pDWriteTextFormatContinue, rect, m_DirectWrite.m_pWhiteBrush);
	}

	return true;
}

bool PPSample::m_InitGameOver() {
	m_SceneTimer.m_fAccumulation = 0.0f;
	return true;
}
bool PPSample::m_FrameGameOver() {
	if (m_SceneTimer.m_fAccumulation > 5.0f) {
		m_InitStage = &PPSample::m_InitSplashScreen;
		m_FrameStage = &PPSample::m_FrameSplashScreen;
		m_RenderStage = &PPSample::m_RenderSplashScreen;
		(this->*m_InitStage)();
	}
	return true;
}
bool PPSample::m_RenderGameOver() {
	m_planeGameOver.Render();
	return true;
}

bool PPSample::m_InitCongratuation() {
	m_SceneTimer.m_fAccumulation = 0.0f;
	return true;
}
bool PPSample::m_FrameCongratuation() {
	if (m_SceneTimer.m_fAccumulation > 5.0f) {
		m_InitStage = &PPSample::m_InitSplashScreen;
		m_FrameStage = &PPSample::m_FrameSplashScreen;
		m_RenderStage = &PPSample::m_RenderSplashScreen;
		(this->*m_InitStage)();
	}
	return true;
}
bool PPSample::m_RenderCongratuation() {
	m_planeCongratuation.Render();
	return true;
}

ReelState PPSample::m_ReelSelector(int iRandomNumber) {
	if (iRandomNumber <= 6) {
		return SEVEN;
	}
	else if (iRandomNumber >= 7 && iRandomNumber <= 17) {
		return THREEBAR;
	}
	else if (iRandomNumber >= 18 && iRandomNumber <= 28) {
		return TWOBAR;
	}
	else if (iRandomNumber >= 29 && iRandomNumber <= 39) {
		return ONEBAR;
	}
	else if (iRandomNumber >= 40 && iRandomNumber <= 50) {
		return CHERRY;
	}
	else {
		return (ReelState)m_RNG.GetRandomNumber(5, 9);
	}
}

bool PPSample::m_RenderInsertCredit() {
	if (m_Bank.m_uiCredit != 0) {
		m_planeInsertCredit.m_IsHide = true;
		m_planePressStart.m_IsHide = false;
	}
	else {
		m_planeInsertCredit.m_IsHide = false;
		m_planePressStart.m_IsHide = true;
	}

	return true;
}

bool PPSample::m_InsertCredit() {
	if ((PPInput::GetInstance().KeyCheck('1') == KEY_UP)) {
		m_Bank.m_AddCredit(1000);
	}
	if ((PPInput::GetInstance().KeyCheck('2') == KEY_UP)) {
		m_Bank.m_AddCredit(5000);
	}
	if ((PPInput::GetInstance().KeyCheck('3') == KEY_UP)) {
		m_Bank.m_AddCredit(10000);
	}
	if ((PPInput::GetInstance().KeyCheck('4') == KEY_UP)) {
		m_Bank.m_AddCredit(50000);
	}

	return true;
}

void PPSample::m_JudgeReel() {
	int iSevenCounter = 0;
	int iThreeBarCounter = 0;
	int iTwoBarCounter = 0;
	int iOneBarCounter = 0;
	int iCherryCounter = 0;
	for (auto& i : m_ReelState) {
		switch (i) {
		case SEVEN:
			iSevenCounter++;
			break;
		case THREEBAR:
			iThreeBarCounter++;
			break;
		case TWOBAR:
			iTwoBarCounter++;
			break;
		case ONEBAR:
			iOneBarCounter++;
			break;
		case CHERRY:
			iCherryCounter++;
			break;
		}
	}

	if (iCherryCounter != 0) {
		m_Bank.m_uiPrize = iCherryCounter * 2 * m_Bank.m_uiBet;
	}
	else if (iSevenCounter == 3) {
		m_Bank.m_uiPrize = 500 * m_Bank.m_uiBet;
	}
	else if (iThreeBarCounter == 3) {
		m_Bank.m_uiPrize = 40 * m_Bank.m_uiBet;
	}
	else if (iTwoBarCounter == 3) {
		m_Bank.m_uiPrize = 20 * m_Bank.m_uiBet;
	}
	else if (iOneBarCounter == 3) {
		m_Bank.m_uiPrize = 10 * m_Bank.m_uiBet;
	}
	else if ((iThreeBarCounter + iTwoBarCounter + iOneBarCounter) == 3) {
		m_Bank.m_uiPrize = 5 * m_Bank.m_uiBet;
	}
	else {
		m_Bank.m_uiPrize = 0;
	}
}