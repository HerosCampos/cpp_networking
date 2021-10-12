#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <fstream>
#include <pthread.h>
#include <chrono>
#include <filesystem>
#include <experimental/filesystem>


                // std::ofstream file("dados.txt", std::ofstream::binary);
                // file.write(vBuffer.data(), vBuffer.size());


std::vector<char> vBuffer(5000);


void GrabSomeData(boost::asio::ip::tcp::socket& socket)
{
    socket.async_read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            std::cout << "\n\nRead: " << length << " bytes\n\n";

            for(int i = 0; i < length; i++)
            {
                std::cout << vBuffer[i];
            }
            GrabSomeData(socket);
        }
    );
}


int main()
{
    boost::system::error_code ec;

    // Create a "Context" - essentially the platform specific interface
    boost::asio::io_context context;

    // Give some fake tasks to asio so the context doesnt finish
    boost::asio::io_context::work idleWork(context);

    // Start context
    std::thread thrContext = std::thread([&]() {context.run();});

    // Get the address of somewhere we wish to connect to
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("172.217.168.238", ec), 80);

    // Create a socket, the context will deliver the implementation
    boost::asio::ip::tcp::socket socket(context);

    // Tell the socket to try and connect
    socket.connect(endpoint, ec);


    if(!ec)
    {
        std::cout << "Connected!" << std::endl;
    }
    else
    {
        std::cout << "Failed to connect to address: " << ec.message() << std::endl;
    }
    
    if(socket.is_open())
    {
        GrabSomeData(socket);

        std::string sRequest =
            "GET /index.html HTTP/1.1\r\n"
            "Host: example.com\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(boost::asio::buffer(sRequest.data(), sRequest.size()), ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);
    }

    std::ofstream file("rede.txt", std::ofstream::app);
    for(char c: vBuffer)
    {
        file << c;
    }
    file.close();
}