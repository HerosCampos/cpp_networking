#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <pthread.h>
#include <chrono>
#include <fstream>


int main()
{
    try
    {
        boost::asio::io_context io_context;

        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 5000));

        boost::asio::ip::tcp::socket socket(io_context);
        std::cout << "Aguardando conexões." << std::endl;
        acceptor.accept(socket);

        std::array<char, 9657> buffer;

        socket.read_some(boost::asio::buffer(buffer));

        std::ofstream file("salada_server.jpeg", std::ofstream::binary);
        file.write(buffer.data(), buffer.size());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

