#pragma once
#include <string>
#include <list>
#include <WinSock2.h>
#include "PPProtocol.h"
#include "../libppcore/PPSingletone.h"

class PPPacketPool {
public:
	std::list<UPACKET> m_PacketList;
public:
	PPPacketPool();
	virtual ~PPPacketPool();
};

