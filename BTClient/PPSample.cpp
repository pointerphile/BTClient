#include "PPSample.h"
#include "PPReceivePacketPool.h"
#include "PPSendPacketPool.h"

PPSample::PPSample() {}
PPSample::~PPSample() {}

bool PPSample::Init() {
	m_SceneTimer.Init();
	m_ObjManager.SetID3D11Device(this->m_pd3dDevice);
	m_ObjManager.SetID3D11DeviceContext(this->m_pd3dContext);
	//LegalWarning
	m_ObjManager.insert(0, L"../Texture/LegalWarning.png", 0, 0, 800, 600, 0, 0, 800, 600);
	//m_DirectWrite.m_pDWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, m_DirectWrite.m_GetResizedFont(28), L"en-us", &m_pDWriteTextFormatLegalWarning);
	m_strLegalWarning = L"WARNING\n\n";
	Client.Init();
	
	{
		UPACKET Packet = {};
		//보낼 페킷 처리
		Packet.m_ph.m_type = PACKET_WELCOME_REQ;
		std::string strBuf = "Hello, Server!";
		memcpy(Packet.m_msg, strBuf.c_str(), strBuf.size());
		Packet.m_ph.m_len = PACKET_HEADER_SIZE + (unsigned short)strBuf.size();
		PPSendPacketPool::GetInstance().m_PacketList.push_back(Packet);
	}

	return true;
}

bool PPSample::Frame() {
	m_SceneTimer.Frame();
	m_ObjManager.Frame();
	
	return true;
}

bool PPSample::Render() {
	m_ObjManager.Render();
	
	return true;
}

bool PPSample::Release() {
	m_SceneTimer.Release();
	m_ObjManager.Release();
	//m_pDWriteTextFormatLegalWarning->Release();

	return true;
}

