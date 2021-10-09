#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>


int main()
{
    // The size of the queue - pending connection
    const int l_size_queue = 10;

    // Step 0 - Get Port
    unsigned short l_port = 8574;

    // Step 1 - Creating a server endpoint
    boost::asio::ip::tcp::endpoint l_endpoint(boost::asio::ip::address_v4::any(), l_port);
    boost::asio::io_service l_io_service;

    try
    {
        std::cout << "[SERVER] - Waiting for clients on port: " << l_port << std::endl;

        // Step 2 - Creating acceptor socket
        boost::asio::ip::tcp::acceptor l_acceptor(l_io_service, l_endpoint.protocol());

        // Step 3 - Binding acceptor to endpoint 
        l_acceptor.bind(l_endpoint);

        // Step 4 - Listen client
        l_acceptor.listen(l_size_queue);

        // Step 5 - Creating active socket
        boost::asio::ip::tcp::socket l_socket(l_io_service);

        // Step 6 - Processing the next connection and connect active socket to the client
        l_acceptor.accept(l_socket);

        std::cout << "[SERVER] Accepted connection from client" << std::endl;
    }
    catch(const boost::system::system_error& err)
    {
        std::cerr << "Code: " << err.code() << ". Message: " << err.what() << std::endl;
    }
    
}

