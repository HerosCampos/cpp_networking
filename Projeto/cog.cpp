#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/asio/steady_timer.hpp>
#include <fstream>
#include <pthread.h>
#include <chrono>


int main()
{
    boost::system::error_code ec;

    // Criando um contexto - de acordo com a documentação o io_context fornece funcionalidades como socket, acceptor...
    boost::asio::io_context context;

    // Criando um Endpoint do tipo TCP, ou seja, é determinado por um endereço de IP e uma porta do lugar que queremos conectar
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::make_address("93.184.216.34", ec), 80);

    // Criando um socket 
    boost::asio::ip::tcp::socket socket(context);
    // Solicitando o socket para conectar com o endpoint
    socket.connect(endpoint, ec);
}
