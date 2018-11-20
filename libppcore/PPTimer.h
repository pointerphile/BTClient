#pragma once
#include "PPBasis.h"
class PPTimer : public PPBasis
{
public:
	TCHAR		m_csBuffer[MAX_PATH] = { 0 };
	int64_t			m_iFPS;// 1�ʴ� ������ ����
	float		m_fSecondPerFrame; // 1�������� ����ð�
	float		m_fAccumulation;// ����� ��� �ð�

	std::chrono::steady_clock::time_point		m_tpBeforeTick;
	float		m_fFrameTime; // �ӽú���
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

