#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")  /* WinSock使用的库函数 */
#include <iostream>
#include <WS2tcpip.h>  //该头文件替代了WSA初始化
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
	int flag;            //flag默认为0 考虑提供config配置
	std::pair<int, char*>buffer_config;   //first:buffer length second:buffer; 默认为64;
protected:
	SOCKET iksock;       //原始对象 

};

