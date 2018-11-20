#include "PPTimer.h"

//int64_t g_iFPS;// 1초당 프레임 개수
//float g_fSecPerFrame; // 1프레임의 경과시간
//float g_fAccumulation;// 실행된 경과 시간
//TCHAR* g_csBuffer;

PPTimer::PPTimer() {
	m_iFPS = 0;// 1초당 프레임 개수
	m_dwFrameCnt = 0;
	m_fSecondPerFrame = 0.0f; // 1프레임의 경과시간
	m_fAccumulation = 0.0f;// 실행된 경과 시간
	m_fFrameTime = 0.0f;
	m_IsCount = true;
}
PPTimer::~PPTimer() {
}

bool PPTimer::Init() {
	m_tpBeforeTick = std::chrono::high_resolution_clock::now();
	return true;
}
bool PPTimer::Frame() {
	if (m_IsCount) {
		auto tpCurrentTick = std::chrono::high_resolution_clock::now();
		auto tpElapseTick = std::chrono::duration_cast<std::chrono::nanoseconds>(tpCurrentTick - m_tpBeforeTick);

		m_fSecondPerFrame = tpElapseTick.count() / 1000000000.0f;
		m_fAccumulation += m_fSecondPerFrame;
		m_fFrameTime += m_fSecondPerFrame;

		if (m_fFrameTime > 1.0f)
		{
			g_iFPS = m_iFPS = m_dwFrameCnt;
			m_dwFrameCnt = 0;
			m_fFrameTime = 0.0f;
		}

		m_dwFrameCnt++;
		m_tpBeforeTick = tpCurrentTick;

		_stprintf_s(m_csBuffer, L"Timer:[%10.4f] FPS:[%I64d] %10.4f\n",
			m_fAccumulation, m_iFPS, m_fSecondPerFrame);
		
	}

	return true;
}
bool PPTimer::Render() {
	return true;
}
bool PPTimer::Release() {
	return true;
}
bool PPTimer::m_ResetCount() {
	m_fAccumulation = 0.0f;

	return true;
}