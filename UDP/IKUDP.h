#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  /* WinSockʹ�õĿ⺯�� */
#include <iostream>
#include <WS2tcpip.h>  //��ͷ�ļ������WSA��ʼ��
#include <cwchar>
#include <cstring>
class UDP
{
public:
	UDP();
	~UDP();
	void Send(const std::string& address_, unsigned short port, const char *buffer,int buffer_len);
private:
	SOCKET iksock;
	
};

