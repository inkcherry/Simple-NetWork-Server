#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

class IKTCP_SERVER
{
public:
    IKTCP_SERVER(const int &port);
    std::string Recv(int buffer_len_ = 128);
    std::string Read();
    void Send(const std::string &buffer);
    static std::string message;
private:
    pthread_t server_thread;
    void _init_sock(const int &port);
    int iksock,next_iksock;
    int port;
    sockaddr_in server_addr,client_addr;
    std::string address;
   
    const static int buffer_len=64;
	static void * add_task(void * argv);
};