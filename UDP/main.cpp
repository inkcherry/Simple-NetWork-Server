#include "IKUDP.h"
#include<cstring>
const std::string add = "192.168.31.132";
const std::string localadd = "127.0.0.1";
const int port = 13;
IKUDP udp(localadd, port);
const int TESTTIME = 30;
int fail_time = 0;
int test_time = 0;
void Test_Charsend()        //返回数据正确率
{   
	int fail_time = 0;
	double result = 0;
	const char* cha = "charchar";
	for (int i = 0; i <TESTTIME ; i++)
		if (!udp.Send(cha, strlen(cha)))
			fail_time++;
	test_time += TESTTIME;
}

void Test_Stringsend()		 //返回数据正确率
{
	double result = 0;
	int fail_time = 0;
	std::string str = "stringstring";
	for (int i = 0; i < TESTTIME; i++)
		if (!udp.Send(str))
			fail_time++;
	test_time += TESTTIME;
}

int main()
{
	int a;
	while (std::cin >> a)
	{
		if (a == 0)break;

		Test_Charsend();
		Test_Stringsend();
		std::cout << "ALL" << test_time << "   FAIL" << fail_time<<"    add?";
	}
	std::cin.get();
	return 0;
}