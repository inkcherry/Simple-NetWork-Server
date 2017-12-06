#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  /* WinSock使用的库函数 */
#include <iostream>
#include <WS2tcpip.h>  //该头文件替代了WSA初始化
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

