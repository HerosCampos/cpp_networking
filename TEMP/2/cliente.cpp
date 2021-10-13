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

        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("127.0.0.1"), 5000);

        boost::asio::ip::tcp::socket socket(io_context);

        socket.connect(endpoint);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

