#include "IKTCP_SERVER.h"
IKTCP_SERVER::IKTCP_SERVER(const int &port_):iksock(-1),port(0),address("")
{
void _init_sock(const int &port_);
}
void* IKTCP_SERVER::add_task(void *arg)
{
	int n;
	int next_iksock = (long)arg;
	char msg[buffer_len];
	pthread_detach(pthread_self());
	while(1)
	{
		n=recv(next_iksock,msg,buffer_len,0);
		if(n==0)
		{
		   close(next_iksock);
		   break;
		}
		msg[n]=0;
		std::string message = std::string(msg);
        }
	return 0;
}

void IKTCP_SERVER::_init_sock(const int &port_)
{
    iksock=socket(AF_INET,SOCK_STREAM,0);
 	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(port);
	bind(iksock,(struct sockaddr *)&server_addr, sizeof(server_addr));
 	listen(iksock,5);
}

std::string IKTCP_SERVER::Recv(int buffer_len)
{
	std::string buffer;
	while(1)
	{
		socklen_t sosize  = sizeof(client_addr);
		next_iksock = accept(iksock,(struct sockaddr*)&client_addr,&sosize);
		buffer = inet_ntoa(client_addr.sin_addr);
		pthread_create(&server_thread,NULL,&add_task,(void *)next_iksock);
	}
	return buffer;
}
void IKTCP_SERVER::Send(const std::string &buffer)
{
	send(next_iksock,buffer.c_str(),buffer.length(),0);
}