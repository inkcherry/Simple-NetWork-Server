#include "IKUDP_SERVER.h"
#include "time.h"


IKUDP_SERVER::IKUDP_SERVER(const UINT &port_):IKUDP()
{
	Bind(port_);
}
void IKUDP_SERVER::Bind(const UINT port)
{  
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	int ret = bind(iksock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (ret == SOCKET_ERROR)
		std::cout << "bind error " << WSAGetLastError();
	std::cout << "serving runing" << std::endl;
}
