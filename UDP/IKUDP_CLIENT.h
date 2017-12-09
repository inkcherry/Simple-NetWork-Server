#pragma once
#include "IKUDP.h"
class IKUDP_CLIENT :
	public IKUDP
{
public:
	bool Send(const char *buffer, int buffer_len);
	bool Send(const std::string& buffer);  //发送出去但不一定保证接受到
	IKUDP_CLIENT(const std::string &address_, const int &port_);
	IKUDP_CLIENT(addr_config &config_);
	~IKUDP_CLIENT();
private:
	std::string address;
	int port;
	sockaddr_in addr;    //本地  Server需要绑定端口 
protected:
	void _init_sockaddr(const std::string &address,const int &port_);   
};

