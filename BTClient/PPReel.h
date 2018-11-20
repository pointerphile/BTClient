#pragma once
#include "../libppcore/PPD3DObject.h"

enum ReelState {
	SEVEN = 0,
	THREEBAR,
	TWOBAR,
	ONEBAR,
	CHERRY,
	SEVEN_ONEBAR,
	ONEBAR_TWOBAR,
	TWOBAR_CHERRY,
	CHERRY_THREEBAR,
	THREEBAR_SEVEN
};
class PPReel : public PPD3DObject
{
public:
	bool m_isRoll;
	bool m_isFinished;
	float m_fTimer;
	float m_fRollingTime;
	ReelState m_ReelState;

	PPReel();
	virtual ~PPReel();

	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	void m_Roll();
	void m_SetReelRoll();
	void m_SetRollingTime(float second);
	void m_SetReelPosition();
	void m_SetReelState(ReelState reelState);
	bool m_GetIsFinished();

	void m_initializeRoll();
	
};

