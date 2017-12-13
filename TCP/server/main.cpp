#include <iostream>
#include "../src/IKTCP_SERVER.h"
IKTCP_SERVER tcp(11112);
void * loop(void * m)
{
	pthread_detach(pthread_self());
	
	while(1)
	{
		std::string str = tcp.Get_message();
		if( str!="" )
		{
			std::cout << "Message:" << str << std::endl;
			tcp.Send("Oh,you are cute:)");
			tcp.clean();
		}
		usleep(1000);
	}
	tcp.detach();
}

int main()
{   
	pthread_t msg;
	std::cout<<"server running"<<std::endl;
	
	if( pthread_create(&msg, NULL, loop, (void *)0) == 0)
	{   std::cout<<"listen"<<std::endl;
		tcp.Recv();
	}
	return 0;
}