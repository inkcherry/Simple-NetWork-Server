#include <iostream>
#include "../src/IKTCP_SERVER.h"
int main()
{   
    IKTCP_SERVER ser(11112);
    std::cout<<ser.Recv();
    return 0;
}