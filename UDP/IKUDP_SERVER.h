#pragma once
#include "IKUDP.h"
class IKUDP_SERVER :
	public IKUDP
{

public:
	IKUDP_SERVER(const UINT &port_);
	void Bind(const UINT port);
	void test();

	
//private:
	sockaddr_in client_addr,serv_addr;           //for bind
};

