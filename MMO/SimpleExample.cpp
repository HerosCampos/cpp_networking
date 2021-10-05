#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <pthread.h>
#include <chrono>


std::vector<char> vBuffer(20 * 1024);

void GrabSomeData(boost::asio::ip::tcp::socket& socket)
{
    socket.async_read_some(boost::asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t length)
        {
            if(!ec)
            {
                std::cout << "\n\nRead: " << length << " bytes\n\n";

                for(int i = 0; i < length; i++)
                {
                    std::cout << vBuffer[i];
                }
                GrabSomeData(socket);
            }
        }
    );
}


int main()
{
    boost::system::error_code ec;

    // Create a "context" - essentially the platform specific interface
    boost::asio::io_context context;

    // Give some fake tasks to asio so the context doesnt finish
    boost::asio::io_context::work idleWork(context);

    // Start the context
    std::thread thrContext = std::thread([&]() {context.run(); });

    // Get the adress of somewhere we want to connect to
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("93.184.216.34", ec), 80);

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
            "Connection: Close\r\n\r\n";

        socket.write_some(boost::asio::buffer(sRequest.data(), sRequest.size()), ec);

        // Program does something else, while asio handles data transfer in background
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);

        context.stop();
        if(thrContext.joinable())
        {
            thrContext.join();
        } 
    }
    system("pause");
    return 0;
}
