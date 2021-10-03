#include <iostream>
#include <string>
#include <boost/asio.hpp>


int main()
{
    // Create an I/O manager
    boost::asio::io_service l_io_service;

    // Step 0 - get IP ant Port
    std::string l_raw_ip("127.0.0.1");
    unsigned short l_port(8574);

    try
    {
        // Step 1 - Create endpoint to server
        boost::asio::ip::tcp::endpoint l_endpoint(boost::asio::ip::address::from_string(l_raw_ip), l_port);

        // Step 2 - Create active socket
        boost::asio::ip::tcp::socket l_socket(l_io_service, l_endpoint.protocol());

        // Step 3 - Connect to the server
        l_socket.connect(l_endpoint);

        std::cout << "[CLIENT] - Connected to server IP: " << l_raw_ip << " port: " << l_port << std::endl;
    }
    catch(const boost::system::system_error& err)
    {
        std::cerr << "[CLIENT] - Error code: " << err.code() << ". Message: " << err.what() << std::endl;
    }
    getchar();
    return 0;
    
}