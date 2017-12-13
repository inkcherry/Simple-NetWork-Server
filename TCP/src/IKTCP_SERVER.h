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
    IKTCP_SERVER( int port);
    std::string Recv();
    void Send(const std::string &buffer);
    static std::string message;
    std::string Get_message();
    void clean();
    void detach();

    char msg[64];
    pthread_t server_thread;
    void _init_sock();
    int iksock,next_iksock;
    int port;
    sockaddr_in server_addr,client_addr;
    std::string address;
    const static int buffer_len=64;
    private:
    static void * add_task(void * argv);
   
};