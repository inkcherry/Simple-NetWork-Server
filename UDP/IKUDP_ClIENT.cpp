#include "IKUDP_CLIENT.h"



IKUDP_CLIENT::IKUDP_CLIENT(const std::string &address_, const int &port):IKUDP()
{
	_init_sockaddr(address_, port);  //��ʼ��iksock�Լ�addr
}
IKUDP_CLIENT::~IKUDP_CLIENT()
{	iksock = socket(AF_INET, SOCK_DGRAM, 0);
}
void IKUDP_CLIENT::_init_sockaddr(const std::string &address_,const int &port)
{
	iksock = socket(AF_INET, SOCK_DGRAM, 0);
	int flag = 1;												//�ݶ�
	addr.sin_family = AF_INET;
	InetPton(AF_INET, address_.c_str(), &addr.sin_addr.s_addr);  //��ʼ��sin_addr.s_addr
    //�ȼ��� addr.sin_addr.s_addr = inet_addr(dest);
	addr.sin_port = htons(port);
}