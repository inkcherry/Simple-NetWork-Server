#include "IKUDP.h"
#include "IKUDP_CLIENT.h"
#include "IKUDP_SERVER.h"
#include<cstring>
#include <thread>
IKUDP_SERVER ser(13);
IKUDP_CLIENT cln("127.0.0.1", 13);
char serbuffer[64];
char clnbuffer[64];
char *m = "to cln";
void fun_ser()
{

}
int main()
{

	cln.Send("to ser");
	while (true)
	{
		
		sockaddr_in  cur_addr= ser.Recv(serbuffer);
		std::cout << serbuffer;
		ser.Send(m,10,cur_addr);
		cln.Recv(clnbuffer);
		std::cout << clnbuffer;
	}
	return 0;
}