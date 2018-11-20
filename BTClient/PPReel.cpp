#include "PPReel.h"



PPReel::PPReel()
{
	m_isRoll = false;
	m_isFinished = false;
	m_fTimer = 0;
	m_fRollingTime = 0;
}


PPReel::~PPReel()
{
}

bool PPReel::Init() {
	PPD3DObject::Init();
	m_isRoll = false;
	m_isFinished = false;
	m_fTimer = 0;
	return true;
};
bool PPReel::Frame() {
	PPD3DObject::Frame();
	m_Roll();
	return true;
};
bool PPReel::Render() {
	PPD3DObject::Render();
	return true;
};
bool PPReel::Release() {
	PPD3DObject::Release();
	return true;
};

void PPReel::m_Roll() {
	if (m_isRoll == true) {
		m_TranslateUVPerSecond(0, -3200);
		m_fTimer = m_fTimer + g_fSecPerFrame;
		if (m_fTimer > m_fRollingTime) {
			m_isRoll = false;
			m_fTimer = 0;
			m_SetReelPosition();
			m_isFinished = true;
		}
	}
}

void PPReel::m_SetReelRoll()
{
	m_isRoll = true;
}

void PPReel::m_SetRollingTime(float fSecond)
{
	m_fRollingTime = fSecond;
}

void PPReel::m_SetReelPosition()
{
	switch (m_ReelState) {
	case SEVEN_ONEBAR:
		m_SetTexelPosition(0, 65 * 2);
		break;
	case ONEBAR:
		m_SetTexelPosition(0, 65 * 3);
		break;
	case ONEBAR_TWOBAR:
		m_SetTexelPosition(0, 65 * 4);
		break;
	case TWOBAR:
		m_SetTexelPosition(0, 65 * 5);
		break;
	case TWOBAR_CHERRY:
		m_SetTexelPosition(0, 65 * 6);
		break;
	case CHERRY:
		m_SetTexelPosition(0, 65 * 7);
		break;
	case CHERRY_THREEBAR:
		m_SetTexelPosition(0, 65 * 8);
		break;
	case THREEBAR:
		m_SetTexelPosition(0, 65 * 9);
		break;
	case THREEBAR_SEVEN:
		m_SetTexelPosition(0, 65 * 10);
		break;
	case SEVEN:
		m_SetTexelPosition(0, 65 * 11);
		break;
	}
}

void PPReel::m_SetReelState(ReelState reelState)
{
	m_ReelState = reelState;
}

bool PPReel::m_GetIsFinished()
{
	return m_isFinished;
}

void PPReel::m_initializeRoll() {
	m_isRoll = false;
	m_isFinished = false;
	m_fTimer = 0;
}