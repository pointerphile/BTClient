#pragma once
#include "PPDevice.h"
#include "PPTimer.h"
#include "PPSound.h"
#include "PPDirectWrite.h"
#include "PPD3DObject.h"

class PPCore : public PPDevice {
public:
	PPCore();
	virtual ~PPCore();
	
	PPTimer m_Timer;
	PPInput m_Input;
	PPSound m_Sound;
	PPDirectWrite m_DirectWrite;

	virtual bool Init() { return true; };
	virtual bool Frame() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };

	virtual bool GameInit();
	virtual bool GameFrame();
	virtual bool GameRender();
	virtual bool GameRelease();
	virtual bool GameRun();

	void MsgEvent(MSG msg);
	virtual HRESULT m_ResizeDevice(UINT width, UINT height);
};

