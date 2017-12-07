#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  /* WinSockʹ�õĿ⺯�� */
#include <iostream>
#include <WS2tcpip.h>  //��ͷ�ļ������WSA��ʼ��
#include <cwchar>
#include <cstring>
struct addr_config {
	const std::string address;
	const int port;
};



class IKUDP
{
//public: static void _init_wsadata_();
//		int count_of_obj=0;
public:
	IKUDP(const std::string &address_, const int &port_);
	IKUDP(addr_config &config_);
	~IKUDP();
	bool Send(const char *buffer, int buffer_len);
	bool Send(const std::string& buffer);  //���ͳ�ȥ����һ����֤���ܵ�
	sockaddr_in Recv(char *buffer, int buffer_len);
	/*sockaddr_in Recv(char *buffer, int buffer_len, bool is_block);*/
	/*bool Recv(std::string &buffer);*/ //����һ��string�������岻��
private:
	void _init_wsadata();   
	void _init_sockaddr(const std::string &address);
	std::string address;   
	int port;			   
	SOCKET iksock;  //socket����
	WSADATA wsa;  //����iksock��ʼ��
	sockaddr_in addr;        
	int flag;        //flagĬ��Ϊ0 �����ṩconfig����
};

