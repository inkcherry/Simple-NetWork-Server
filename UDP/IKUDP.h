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
public:
	static int count_of_obj;
	IKUDP();
	~IKUDP();
	bool Send(const char * buffer, int buffer_len, sockaddr_in &to_addr);
	bool Send(const std::string&buffer, sockaddr_in&to_addr);
	sockaddr_in Recv(char *buffer);
	void ReSet_buffer_size(int &buffer_size_);          
	/*const int  Get_buffer_size() { return buffer_size; }*/
private:
	void _init_buffer();
	void _init_wsadata();   	   
	int flag;            //flagĬ��Ϊ0 �����ṩconfig����
	std::pair<int, char*>buffer_config;   //first:buffer length second:buffer; Ĭ��Ϊ64;
protected:
	SOCKET iksock;       //ԭʼ���� 

};

