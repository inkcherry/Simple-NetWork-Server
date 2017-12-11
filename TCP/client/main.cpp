#include <iostream>
#include "../src/IKTCP_CLIENT.h"
int main(int argc,char *argv[])
{
   if(argc >= 2)
	{   
        IKTCP_CLIENT cln("127.0.0.1",11112);
		int time = atoi(argv[2]);
		for(int i = 0; i < time; i++)
		{
			std::string send_buffer = argv[1];
			cln.Send(send_buffer);
			std::string recv_buffer = cln.Recv();
			if( recv_buffer!= "" )
			{
				std::cout << "Server Response:" << recv_buffer << std::endl;
			}
			sleep(1);
		}
		exit(0);
		return 0;
	}
}
