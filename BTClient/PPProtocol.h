#pragma once
constexpr auto BUFFER_SIZE = 2048;
#pragma pack(push, 1)
class PACKET_HEADER {
public:
	unsigned short m_len;
	unsigned short m_type;
};

class UPACKET {
public:
	PACKET_HEADER m_ph;
	char m_msg[BUFFER_SIZE];
};

class PACKET_ACCOUNT {
public:
	char m_strUsername[16];
	char m_strPassword[16];
};

//constexpr auto PACKETTYPE_PET_PET_DATA = 50000;
class PACKET_PET_DATA {
public:
	int m_iPetID;
	int m_iPosition;
};

//constexpr auto PACKETTYPE_PET_FOOD_DATA = 50005;
class PACKET_FOOD_DATA {
public:
	int m_iObjectID;
	int m_iPosition;
	int m_iQuantity;
};

//constexpr auto PACKETTYPE_PET_MOVE = 50002;
class PACKET_PET_MOVE {
public:
	int m_iPetID;
	int m_iDirection;
};

//constexpr auto PACKETTYPE_PET_EAT = 50003;
class PACKET_EAT_FOOD {
	int m_iTargetFoodID;
	int m_iQuantity;
};

//constexpr auto PACKETTYPE_PET_DELETE_FOOD = 50004;
class PACKET_DELETE_FOOD {
	int m_iTargetFoodID;
};

//constexpr auto PACKETTYPE_PET_GIVE_FOOD = 50001;
class PACKET_GIVE_FOOD {
	int m_iPosition;
	int m_iQuantity;
};

#pragma pack(pop)

constexpr auto PACKET_HEADER_SIZE = 4;

constexpr auto PACKET_WELCOME_REQ = 1000;
constexpr auto PACKET_WELCOME_ACK = 1001;
constexpr auto PACKET_ACCOUNT_REQ = 2000;
constexpr auto PACKET_ACCOUNT_ACK = 2001;

constexpr auto PACKET_CHAT_MSG = 4000;

constexpr auto PACKETTYPE_PET_PET_DATA = 50000;
constexpr auto PACKETTYPE_PET_GIVE_FOOD = 50001;
constexpr auto PACKETTYPE_PET_MOVE = 50002;
constexpr auto PACKETTYPE_PET_EAT = 50003;
constexpr auto PACKETTYPE_PET_DELETE_FOOD = 50004;
constexpr auto PACKETTYPE_PET_FOOD_DATA = 50005;
