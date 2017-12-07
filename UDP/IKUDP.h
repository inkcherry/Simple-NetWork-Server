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
//public: static void _init_wsadata_();
//		int count_of_obj=0;
public:
	IKUDP(const std::string &address_, const int &port_);
	IKUDP(addr_config &config_);
	~IKUDP();
	bool Send(const char *buffer, int buffer_len);
	bool Send(const std::string& buffer);  //发送出去但不一定保证接受到
	sockaddr_in Recv(char *buffer, int buffer_len);
	/*sockaddr_in Recv(char *buffer, int buffer_len, bool is_block);*/
	/*bool Recv(std::string &buffer);*/ //重载一个string对象意义不大
private:
	void _init_wsadata();   
	void _init_sockaddr(const std::string &address);
	std::string address;   
	int port;			   
	SOCKET iksock;  //socket对象
	WSADATA wsa;  //用于iksock初始化
	sockaddr_in addr;        
	int flag;        //flag默认为0 考虑提供config配置
};

