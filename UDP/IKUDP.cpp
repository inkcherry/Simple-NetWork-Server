#include "IKUDP.h"
#include "IKUDP.h"
#include <system_error>
#define DAYTIME_BUF_SIZE    64  /* 缓冲区的大小 */
#define DAYTIME_DEF_COUNT    10  


void IKUDP:: _init_wsadata() {
	WSAStartup(WINSOCK_VERSION, &wsa);
	iksock = socket(AF_INET, SOCK_DGRAM, 0);
	if (iksock == INVALID_SOCKET)
			throw std::system_error(WSAGetLastError(), std::system_category(), "Error opening socket");

}
IKUDP::IKUDP(const std::string & address_, const int & port_):port(port_),flag(0)
{
	_init_wsadata();
    _init_sockaddr(address_);  //初始化
}
IKUDP::IKUDP(addr_config &config_):port(config_.port), flag(0)
{
	_init_wsadata();
	_init_sockaddr(config_.address);
}

void IKUDP::_init_sockaddr(const std::string &address_)
{
	int flag = 1;												//暂定
	addr.sin_family = AF_INET;
	InetPton(AF_INET, address_.c_str(), &addr.sin_addr.s_addr);  //初始化sin_addr.s_addr
	//	等价于 addr.sin_addr.s_addr = inet_addr(dest);
	addr.sin_port = htons(port);
}

IKUDP::~IKUDP()
{
	closesocket(iksock);
	WSACleanup();
}
bool IKUDP::Send(const std::string& buffer) 
{
	return Send(buffer.c_str(), buffer.length());
}


bool IKUDP::Send(const char *buffer,int buffer_len)
{   
	
	if (addr.sin_addr.s_addr == INADDR_NONE)
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
	int ret = sendto(iksock, buffer, buffer_len, 0,
		(struct sockaddr *)&addr, sizeof(addr));
	if (ret = buffer_len)      //完全发送算作发送成功
		return true;
	else  //发送失败
	{
		std::cout << "send error" << ret << std::endl;
		return false;
	}
}

sockaddr_in IKUDP::Recv(char *buffer,int buffer_len)  
{  
	sockaddr_in peer_addr;  //from（默认的监听addr)
	int peer_addr_size = sizeof(peer_addr);
	int ret=recvfrom(iksock,buffer,buffer_len, flag,
		(struct sockaddr *)&peer_addr, &peer_addr_size);
	
	//UDP无连接 故recvfrom返回值始终为0
    //有连接时 TCP 0表示断开连接
	return  peer_addr;
}
//sockaddr_in IKUDP::Recv(char *buffer, int buffer_len,bool is_block)
//{
//	sockaddr_in peer_addr;  //from（默认的监听addr)
//	int peer_addr_size = sizeof(peer_addr);
//	int ret = recvfrom(iksock, buffer, buffer_len, ,
//		(struct sockaddr *)&peer_addr, &peer_addr_size);
//
//
//	return  peer_addr;
//}

