#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>

class IKTCP_CLIENT
{
public:
    IKTCP_CLIENT(const std::string &address ,const  int &port);
    IKTCP_CLIENT(const std::string &address ,const  int &port,bool isunblock);
    bool Send(const std::string &buffer);
    std::string Recv(const int buffer_len=128);
    void set_block_config(bool isunblock);  //������������ 0Ϊ���� 1Ϊ������
private:
    std::string address;
    void _init_unblcok_sock();//�����������߷�����ģʽ
    void _init_block_sock();//�����������߷�����ģʽ

    void _init_connect(const std::string &address,const int &port);
    int iksock;

    int port;
    sockaddr_in addr;

};
