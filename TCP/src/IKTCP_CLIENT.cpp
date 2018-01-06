#include "/home/l/desktop/network/Simple-NetWork-Server/TCP/src/IKTCP_CLIENT.h"

IKTCP_CLIENT::IKTCP_CLIENT(const std::string &address,const int &port):iksock(-1),port(0),address("")
{	_init_block_sock();
    _init_connect(address,port);
}
IKTCP_CLIENT::IKTCP_CLIENT(const std::string &address,const int &port,bool isunblock):iksock(-1),port(0),address("")
{	if(isunblock==1) //����Ϊ������
	{_init_unblcok_sock();
	_init_connect(address,port);}
	else{//ί�й�������
		IKTCP_CLIENT(address,port);
	}
}
void IKTCP_CLIENT::_init_unblcok_sock()//�����������߷�����ģʽ
{
    iksock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);//ָ��������

}
void IKTCP_CLIENT::_init_block_sock()
{
    iksock= socket(AF_INET , SOCK_STREAM , 0);

}
void IKTCP_CLIENT::_init_connect(const std::string &address,const int &port)
{
    if(iksock==-1)
        std::cout<<"errot with init sock";
    addr.sin_addr.s_addr = inet_addr( address.c_str() );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( port );

    if (connect(iksock , (struct sockaddr *)&addr , sizeof(addr)) < 0)
		std::cout<<"unblock connect";
}

bool IKTCP_CLIENT::Send(const std::string &buffer)
{
	if( send(iksock , buffer.c_str() , buffer.length() , 0) < 0)
	{
		std::cout << "Send failed : " <<buffer;
		return false;
	}
	return true;
}
std::string IKTCP_CLIENT::Recv(const int buffer_len)
{
  	char buffer[buffer_len];

	if( recv(iksock , buffer,buffer_len, 0) < 0)// sizeof(buffer)
  	{
		// std::cout << "receive failed!" << std::endl;
			return "";
  	}
	buffer[buffer_len]='\0';
  	return (std::string)buffer;
}
