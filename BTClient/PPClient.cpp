#include "PPClient.h"
#include "PPReceivePacketPool.h"
#include "PPSendPacketPool.h"

bool g_isConnect = true;
WORD g_PacketType = PACKET_CHAT_MSG;

void err_display() {
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, nullptr
	);
	std::cout << (char*)lpMsgBuf;
	LocalFree(lpMsgBuf);
}

int SetNonBlockingSocket(SOCKET sock, u_long iMode) {
	int iResult;
	iResult = ioctlsocket(sock, FIONBIO, &iMode);
	if (iResult != NO_ERROR) {
		return -1;
	}

	return iResult;
}

PPClient::PPClient() {}
PPClient::~PPClient() {}

bool PPClient::Init() {
	int iRet = 0;

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return false;
	}

	socketClient = socket(AF_INET, SOCK_STREAM, 0);
	if (socketClient == INVALID_SOCKET) {
		return false;
	}

	SOCKADDR_IN saServer;
	saServer = { 0 };
	saServer.sin_family = AF_INET;
	saServer.sin_port = htons(SERVER_PORT);
	saServer.sin_addr.s_addr = inet_addr(SERVER_IPV4);
	std::cout << "Connecting to " << SERVER_IPV4 << ":" << SERVER_PORT << "..." << std::endl;
	iRet = connect(socketClient, (SOCKADDR*)&saServer, sizeof(saServer));
	if (iRet == SOCKET_ERROR) {
		std::cout << "Connection failed." << std::endl;
		MessageBox(nullptr, L"Connection failed.", nullptr, MB_OK);
		return false;
	}
	else {
		std::cout << "Connected" << std::endl;
	}

	SetNonBlockingSocket(socketClient, false);

	std::thread threadSend(&PPClient::Send, this);
	std::thread threadReceive(&PPClient::Receive, this);
	threadSend.detach();
	threadReceive.detach();

	return true;
}

bool PPClient::Frame()
{
	return false;
}

bool PPClient::Render()
{
	return false;
}

bool PPClient::Release()
{
	return false;
}

int PPClient::Receive() {
	while (g_isConnect) {
		int iRecvByte = 0;
		char buf[BUFFERSIZE] = { 0 };
		UPACKET rcvmsg = { 0 };
		while ((iRecvByte < PACKET_HEADER_SIZE) && (g_isConnect)) {
			iRecvByte += recv(socketClient, &buf[iRecvByte], PACKET_HEADER_SIZE - iRecvByte, 0);
			if (iRecvByte == 0) {
				std::cout << "Connection closed." << std::endl;
				err_display();
				g_isConnect = false;
				break;
			}
			if (iRecvByte == SOCKET_ERROR) {
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					std::cout << "Disconnected from server.(Receiving header failed)" << std::endl;
					err_display();
					g_isConnect = false;
					break;
				}
				iRecvByte = 0;
			}
		}
		if (!g_isConnect) {
			break;
		}
		if ((iRecvByte == PACKET_HEADER_SIZE) && (g_isConnect)) {
			memcpy(&rcvmsg, buf, PACKET_HEADER_SIZE);
			while (iRecvByte < rcvmsg.m_ph.m_len) {
				iRecvByte += recv(socketClient, buf, rcvmsg.m_ph.m_len - iRecvByte, 0);
				if (iRecvByte == SOCKET_ERROR) {
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						std::cout << "Disconnected from server.(Receiving body failed)" << std::endl;
						err_display();
						g_isConnect = false;
						break;
					}
				}
			}
			if (rcvmsg.m_ph.m_len) {
				memcpy(&rcvmsg.m_msg, buf, rcvmsg.m_ph.m_len - PACKET_HEADER_SIZE);
				switch (rcvmsg.m_ph.m_type) {
				case PACKET_WELCOME_ACK: {
					wchar_t uni[2048]{};
					std::cout << rcvmsg.m_msg << std::endl;
					MultiByteToWideChar(CP_ACP, 0, rcvmsg.m_msg, sizeof(rcvmsg.m_msg), uni, sizeof(uni));
					//MessageBox(nullptr, uni, nullptr, MB_OK);

					UPACKET Packet = {};
					//보낼 페킷 처리
					Packet.m_ph.m_type = PACKETTYPE_PET_PET_DATA;
					std::string strBuf = "Give me pet data!";
					memcpy(Packet.m_msg, strBuf.c_str(), strBuf.size());
					Packet.m_ph.m_len = PACKET_HEADER_SIZE + (unsigned short)strBuf.size();
					PPSendPacketPool::GetInstance().m_PacketList.push_back(Packet);
					break;
				}
				case PACKETTYPE_PET_PET_DATA: {
					PPReceivePacketPool::GetInstance().m_PacketList.push_back(rcvmsg);
					break;
				}
				case PACKETTYPE_PET_FOOD_DATA: {
					PPReceivePacketPool::GetInstance().m_PacketList.push_back(rcvmsg);
					break;
				}
				case PACKETTYPE_PET_MOVE: {
					PPReceivePacketPool::GetInstance().m_PacketList.push_back(rcvmsg);
					break;
				}
				case PACKETTYPE_PET_DELETE_FOOD: {
					PPReceivePacketPool::GetInstance().m_PacketList.push_back(rcvmsg);
					break;
				}
				case PACKET_CHAT_MSG: {
					if (g_PacketType == PACKET_CHAT_MSG) {
						wchar_t uni[2048]{};
						std::cout << rcvmsg.m_msg << std::endl;
						MultiByteToWideChar(CP_ACP, 0, rcvmsg.m_msg, sizeof(rcvmsg.m_msg), uni, sizeof(uni));
						//MessageBox(nullptr, uni, nullptr, MB_OK);
					}
					break;
				}
				default:
					break;
				}

			}
		}
	}
	shutdown(socketClient, SD_BOTH);
	return 0;
}

int PPClient::Send()
{
	char buf[BUFFERSIZE] = { 0 };
	while (1) {
		if (PPSendPacketPool::GetInstance().m_PacketList.empty() == true) {
			continue;
		}
		else {
			std::string buf;
			UPACKET sendmsg = {};

			//switch (g_PacketType) {
			//case PACKET_CHAT_MSG: {
			//	sendmsg.m_ph.m_type = PACKET_CHAT_MSG;
			//	std::getline(std::cin, buf);
			//	memcpy(sendmsg.m_msg, buf.c_str(), buf.size());
			//	sendmsg.m_ph.m_len = (WORD)strlen(sendmsg.m_msg) + PACKET_HEADER_SIZE;
			//	buf.clear();
			//	g_PacketType = PACKET_CHAT_MSG;
			//	break;
			//}
			//default:
			//	break;
			//}

			sendmsg = PPSendPacketPool::GetInstance().m_PacketList.front();

			int iSendByte = send(socketClient, (char*)&sendmsg, sendmsg.m_ph.m_len, 0);
			if (iSendByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					std::cout << "Disconnected from server.(Send failed)" << std::endl;
					err_display();
					break;
				}
			}
			PPSendPacketPool::GetInstance().m_PacketList.pop_front();
		}
	}
	g_isConnect = false;
	shutdown(socketClient, SD_BOTH);
	return 0;
}
