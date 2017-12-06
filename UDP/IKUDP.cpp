#include "IKUDP.h"
UDP::UDP()
{
	WSADATA wsa;
	WSAStartup(WINSOCK_VERSION, &wsa);
	iksock = socket(AF_INET, SOCK_DGRAM, 0);
	if (iksock == INVALID_SOCKET)
		std::cout << "未能初始化" << std::endl;
	
}



UDP::~UDP()
{
}

void UDP::Send(const std::string& address_,unsigned short port,const char *buffer,int buffer_len)
{   
	int flag = 1;
	sockaddr_in add;
	add.sin_family = AF_INET;
	InetPton(AF_INET, address_.c_str() ,&add.sin_addr.s_addr);
	add.sin_port = htons(port);

	if (add.sin_addr.s_addr == INADDR_NONE)
	{
		printf("[ECHO] invalid address\n");
		
	};

	int ret = sendto(iksock, buffer, buffer_len, flag, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));

	if (ret < 0)
		std::cout << "file to send";
}
