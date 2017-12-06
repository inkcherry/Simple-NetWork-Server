#include<iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost\thread.hpp>


using namespace boost::asio;
using namespace boost::system;

using boost::asio::ip::tcp;

class async_client
{
private:
	io_service&  ioservice_;
	tcp::socket socket_;
	char read_buffer_[512];
	char write_buffer_[513];
public:
	async_client(io_service& service, tcp::endpoint endpoint)
		:ioservice_(service),
		socket_(service)
	{
		socket_.async_connect(endpoint,
			boost::bind(&async_client::connet_handle, this, _1)
		);
	}

	void connet_handle(const error_code& error)
	{
		if (!error)
		{
			std::cout << "连接成功\n";
			socket_.async_read_some(buffer(read_buffer_),
				boost::bind(&async_client::read_handle, this, _1));
		}
	}

	void read_handle(const error_code& error)
	{
		if (!error)
		{
			std::cout << "封包内容为:" << read_buffer_ << std::endl;
			memset(read_buffer_, 0, sizeof(read_buffer_));
			socket_.async_read_some(buffer(read_buffer_),
				boost::bind(&async_client::read_handle, this, _1));
		}
	}

	void send(const char* msg, size_t len)
	{
		memcpy(write_buffer_, msg, len);
		boost::asio::async_write(socket_, buffer(write_buffer_, len), bind(&async_client::write_handle, this, _1));
	}

	void write_handle(const error_code& error)
	{

	}

};


int main(int argc, char** argv)
{
	io_service service;
	tcp::endpoint endpoint(ip::address::from_string("127.0.0.1"), 8888);

	async_client client(service, endpoint);

	boost::thread t(boost::bind(&boost::asio::io_service::run, &service));

	char line[512 + 1];
	while (std::cin.getline(line, sizeof(line)))
	{
		if (strcmp(line, "exit") == 0)
		{
			break;
		}
		client.send(line, strlen(line));
	}

	t.join();
	getchar();
	return 0;
}
