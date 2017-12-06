#include "IKUDP.h"
#include<cstring>
const std::string add = "127.0.0.1";
const int port = 7;
int main()
{
	UDP m;
	
	m.Send(add, 7, "hehe", 4);   
	std::cin.get();
	return 0;
}