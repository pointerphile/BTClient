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
	ProcessPacket();
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

void PPSample::ProcessPacket() {
	if (PPReceivePacketPool::GetInstance().m_PacketList.empty() != true) {
		UPACKET PacketRecv = {};
		PacketRecv = PPReceivePacketPool::GetInstance().m_PacketList.front();
		switch (PacketRecv.m_ph.m_type) {
		case PACKETTYPE_PET_PET_DATA: {
			PACKET_PET_DATA PacketPet = {};
			memcpy(&PacketPet, PacketRecv.m_msg, PacketRecv.m_ph.m_len - PACKET_HEADER_SIZE);
			m_ObjManager.insert(PacketPet.m_iPetID, L"../Texture/dog.png", PacketPet.m_iPosition * 50, 300, 50, 50, 0, 0, 50, 50);
			break;
		}
		case PACKETTYPE_PET_FOOD_DATA: {
			PACKET_FOOD_DATA PacketFood = {};
			memcpy(&PacketFood, PacketRecv.m_msg, PacketRecv.m_ph.m_len - PACKET_HEADER_SIZE);
			m_ObjManager.insert(PacketFood.m_iObjectID, L"../Texture/food.png", PacketFood.m_iPosition * 50, 350, 50, 50, 0, 0, 50, 50);
			break;
		}
		case PACKETTYPE_PET_MOVE: {
			PACKET_PET_MOVE PacketMove = {};
			memcpy(&PacketMove, PacketRecv.m_msg, PacketRecv.m_ph.m_len - PACKET_HEADER_SIZE);
			int64_t iPetHandle = PacketMove.m_iPetID;
			PPD3DObject* pPet = m_ObjManager.m_map.find(iPetHandle)->second;
			pPet->m_SetPosition(pPet->m_Position.x + PacketMove.m_iDirection * 50, pPet->m_Position.y);
			break;
		}
		case PACKETTYPE_PET_DELETE_FOOD: {
			PACKET_DELETE_FOOD PacketDeleteFood = {};
			memcpy(&PacketDeleteFood, PacketRecv.m_msg, PacketRecv.m_ph.m_len - PACKET_HEADER_SIZE);
			int64_t iTargetFoodID = PacketDeleteFood.m_iTargetFoodID;
			m_ObjManager.m_map.erase(iTargetFoodID);
			break;
		}

		default: {
			break;
		}
		}
		PPReceivePacketPool::GetInstance().m_PacketList.pop_front();
	}

	
}

