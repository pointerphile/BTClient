#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include "C:\Users\User\source\repos\BTClient\libppcore\PPCore.h"

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <string>
#include <thread>

#include "PPProtocol.h"
#define LOCALHOST

#ifdef LOCALHOST
#define SERVER_IPV4 "127.0.0.1"
#else
#define SERVER_IPV4 "192.168.0.36"
#endif // LOCALHOST

#define SERVER_PORT 10000
#define BUFFERSIZE 2048

class PPClient {
public:
	SOCKET socketClient;
public:
	PPClient();
	~PPClient();
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	int Receive();
	int Send();
};

