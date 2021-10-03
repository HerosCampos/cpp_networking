#include <iostream>
#include <string>
#include <boost/asio.hpp>


int main()
{
    // The size of the queue - pending connection
    const int l_size_queue = 10;

    // Step 0 - Get port
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
        std::cerr << "[SERVER] - error code " << err.code() << ". Message: " << err.what() << std::endl;
    }
    getchar();
    return 0;

}






// int main()
// {
//     // Create an I/O manager
//     boost::asio::io_service l_io_service;

//     // Step 0 - get IP ant Port
//     std::string l_raw_ip("127.0.0.1");
//     unsigned short l_port(8574);

//     try
//     {
//         // Step 1 - Create endpoint to server
//         boost::asio::ip::tcp::endpoint l_endpoint(boost::asio::ip::address::from_string(l_raw_ip), l_port);

//         // Step 2 - Create active socket
//         boost::asio::ip::tcp::socket l_socket(l_io_service, l_endpoint.protocol());

//         // Step 3 - Connect to the server
//         l_socket.connect(l_endpoint);

//         std::cout << "[CLIENT] - Connected to server IP: " << l_raw_ip << " port: " << l_port << std::endl;
//     }
//     catch(const boost::system::system_error& err)
//     {
//         std::cerr << "[CLIENT] - Error code: " << err.code() << ". Message: " << err.what() << std::endl;
//     }
    // getchar();
    // return 0;
    
// }