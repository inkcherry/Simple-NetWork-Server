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
bool IKUDP_CLIENT::Send(const std::string& buffer)
{
	return Send(buffer.c_str(), buffer.length());
}


bool IKUDP_CLIENT::Send(const char *buffer, int buffer_len)
{

	if (addr.sin_addr.s_addr == INADDR_NONE)
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
	int ret = sendto(iksock, buffer, buffer_len, 0,
		(struct sockaddr *)&addr, sizeof(addr));
	if (ret == buffer_len)      //��ȫ�����������ͳɹ�
		return true;
	else  //����ʧ��
	{
		std::cout << "send error with" << WSAGetLastError() << std::endl;
		return false;
	}
}