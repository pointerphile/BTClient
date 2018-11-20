#pragma once
#include "PPBasis.h"
#include "../dependencies/FMOD/include/fmod.hpp"

#ifdef _WIN64
#pragma comment(lib, "../dependencies/FMOD/lib/x64/fmod64_vc.lib")
#else
#pragma comment(lib, "../dependencies/FMOD/lib/Win32/fmod_vc.lib")
#endif // _WIN64


class PPSound
{
public:
	FMOD::System* m_pSystem;
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;

	PPSound();
	virtual ~PPSound();

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool m_LoadSound(const char* FileAddress);
	bool m_PlaySound(FMOD::Sound* pSound, FMOD::Channel* m_pChannel);
};

