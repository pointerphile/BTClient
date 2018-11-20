#pragma once
#include "PPBasis.h"
class PPTimer : public PPBasis
{
public:
	TCHAR		m_csBuffer[MAX_PATH] = { 0 };
	int64_t			m_iFPS;// 1초당 프레임 개수
	float		m_fSecondPerFrame; // 1프레임의 경과시간
	float		m_fAccumulation;// 실행된 경과 시간

	std::chrono::steady_clock::time_point		m_tpBeforeTick;
	float		m_fFrameTime; // 임시변수
	int64_t		m_dwFrameCnt;

	bool m_IsCount;
	
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	bool m_ResetCount();

	PPTimer();
	virtual ~PPTimer();
};

