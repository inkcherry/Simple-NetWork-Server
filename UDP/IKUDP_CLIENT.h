#pragma once
#include "IKUDP.h"
class IKUDP_CLIENT :
	public IKUDP
{
public:
	IKUDP_CLIENT(const std::string &address_, const int &port_);
	IKUDP_CLIENT(addr_config &config_);
	~IKUDP_CLIENT();
private:

protected:
	void _init_sockaddr(const std::string &address,const int &port_);   
};

