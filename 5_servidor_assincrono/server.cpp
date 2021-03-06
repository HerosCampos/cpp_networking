#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

typedef std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

boost::asio::io_service io_service;
boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234));

void handle_accept(socket_ptr sock, const boost::system::error_code& err);

void start_accept(socket_ptr sock)
{
    acceptor_.async_accept(*sock, boost::bind(handle_accept, sock, _1));
}

void handle_accept(socket_ptr sock, const boost::system::error_code& err)
{
    if(err) return;

    boost::system::error_code ec;
    boost::asio::streambuf buf;
    char data[10];
    size_t len = sock->read_some(boost::asio::buffer(data), ec);

        if(len > 0)
        {
            std::cout << "Received " << len << " bytes." << std::endl;
            write(*sock, boost::asio::buffer(data), ec);
            if(ec) std::cout << ec.message() << std::endl;
        }

    socket_ptr sock_(new boost::asio::ip::tcp::socket(io_service));
    start_accept(sock_);
}


int main()
{
    socket_ptr sock(new boost::asio::ip::tcp::socket(io_service));
    start_accept(sock);
    io_service.run();
    return 0;
}
