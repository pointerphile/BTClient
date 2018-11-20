#include "PPSound.h"



PPSound::PPSound()
{
}


PPSound::~PPSound()
{
}

bool PPSound::Init() {
	void* extradriverdata = 0;
	FMOD::System_Create(&m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);

	return true;
}
bool PPSound::Frame() {
	return true;
}
bool PPSound::Render() {
	return true;
}
bool PPSound::Release() {
	if (m_pSound) {
		m_pSound->release();
	}
	if (m_pSystem) {
		m_pSystem->close();
		m_pSystem->release();
	}
	return true;
}
bool PPSound::m_LoadSound(const char* FileAddress) {
	m_pSystem->createSound(FileAddress, FMOD_DEFAULT, 0, &m_pSound);

	return true;
}
bool PPSound::m_PlaySound(FMOD::Sound* pSound, FMOD::Channel* pChannel) {
	m_pSystem->playSound(pSound, 0, false, &pChannel);

	return true;
}