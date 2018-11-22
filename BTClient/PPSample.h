#pragma once
#include "../libppcore/PPCore.h"
#include "PPD3DObjectManager.h"
#include "PPClient.h"

#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/libppcore.lib")
#endif // _DEBUG
#ifndef _DEBUG
#pragma comment(lib, "PPCoreLib.lib")
#endif // _DEBUG

class PPSample : public PPCore
{
public:
	PPClient Client;
	PPD3DObjectManager m_ObjManager;
	PPTimer m_SceneTimer;
	//IDWriteTextFormat* m_pDWriteTextFormatLegalWarning;

	bool m_isRunning;
	bool m_isPlayable;
	bool m_IsDemoPlay;

	int m_iDemoCount;
	float m_fConitnueCount;

	//LegalWarning
	std::wstring m_strLegalWarning;
	int m_iStrLegalWarningCount;
	//_LegalWarning
	
	PPSample();
	virtual ~PPSample();

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	bool m_RenderInsertCredit();
	void ProcessPacket();
};